# The Chess Express

An implementation of "Wizard's Chess" - an automatically moving chessboard. Initially developed as part of ECE 395, Advanced Digital System Lab at the University of Illinois, Urbana-Champaign, Fall 2019.

Developers: [Mitalee Bharadwaj](https://www.github.com/mitaleeb) and [Dean Biskup](https://www.github.com/dbisk)

## Abstract

This project is inspired by "Wizard Chess", introduced in _Harry Potter and the Sorcerer's Stone_. It is an automagically moving chessboard, utilizing metal feet on the chesspieces and an electromagnet in order to move pieces around the board. Internally, the project uses an X-Y plotter setup with belts and stepper motors to accurately move the electromagnet head to the location of the pieces, and to accurately drag the pieces to their new positions. The Chess Express also automatically moves pieces to a "graveyard" once they've been taken, and given a promotion is able to move dead pieces back onto the board. The pieces are just steel plates that can be moved when the electromagnet is energized underneath it and moved by the motion of the stepper motors and belts. 

## Physical Design


### Overview

The physical chessboard design utilizes an X-Y plotter, with two stepper motors for the X-axis and one stepper motor for the Y-axis. This configuration was chosen because the X-axis motors would have to move an entire bar of metal, while the Y-axis motor only has to move the electromagnet module. The increased power from having two stepper motors makes moving the bar easier, as well as simplifies the mechanical design because the two outside rails do not need to be connected by belts.

### Drawing

Sketch of the Chessboard dimensions first iteration.

<img src=img/board_sketch.jpg width="50%">

Full chess board designed and created with the help of the ECEB Machine shop.

<img src=img/full_board.jpg width="50%"><img src=img/stepper_motors.jpg width="50%">

### <a id="pcb"></a> PCB Design

As a part of the hardware development, we further extended the circuit design into a schematic on Eagle in order to create a more compact and clean circuit. The files for the first iteration of the schematic and board are included in this project. This would allow for a PCB to potentially be used with a single power source underneath the chess board in a nice casing in the future for a fully packaged product. The board layout is 2 layers with a ground polygon plate on the bottom layer for many of the connections. The current board that was fabricated does not have full footprints of the stepper motor drivers and uses mostly through hole parts as well as a large surface area of around 5x5 inches. In addition, more changes were made to the circuit after the purchase order for the PCB from PCBWay. These changes can be made to create a more effective and customized PCB, since right now the PCB is primarily consisting of breakouts for jumpers to external parts. 

<img src=img/PCB.jpg width="50%">

## Motor Control

### MCU Hardware

In order to control the motors, we decided to opt for a driver made by SparkFun called the ["Easy Driver"], which lets us interface with a stepper motor with just 5 input pins. The input pins that we used are the following:

| Pin  | Connection | PURPOSE                                         |
| ---- | ---------- | -------                                         |
| EN   | GPIO0_X    | Enable motor control. Active Low.               |
| STEP | GPIO0_Y    | Move one step upon transition from low to high. |
| DIR  | GPIO0_Z    | Direction of the motor.                         |
| MS1  | GROUND     | Microstep resolution.                           |
| MS2  | GROUND     | Microstep resolution.                           |

note: GPIO0_X is some GPIO0 pin. Each are on different pins. For exact pinning, see the diagram elsewhere in this doc.

We also soldered the logic-level jumper on the board together in order to set the configuration of VCC to be 3.3V, which is the same as the VCC of the LPC1114/102 chip.

By using the Easy Driver, we are able to abstract the motor controls into just the pins listed above. Since we force the MS1/MS2 pins to be either high or low, we don't need to connect them to the processor. This means that for both axes, we just need a total of 3 x 2 = 6 pins, which fits on one GPIO bus. We choose GPIO0. 

### MCU Software

In software, we can control the movement of the motors by changing the values of the `EN`, `DIR`, and `STEP` pins based on the distance and direction we want to move. The process boils down to the following:
```
1. enable the motor
2. set the direction
3. trigger a step the amount of times for the specified direction
```

In order to figure out how many steps we need to go a certain distance, we need some parameters of the motor (we use a [NEMA 16 stepper motor from SparkFun]). The equation for this motor is as follows:

![Steps per distance calculation for NEMA 16](img/step_distance_calc.png)

where _d_ is the distance intending to be traveled, in meters. Once we have this, we can set up a control loop that steps the motor the number of steps needed, like follows:
```C
setPinGPIO0(X_AXIS_EN, PIN_LOW); // enable the motor control
setPinGPIO0(X_AXIS_DIR, direction); // set the direction
while (numSteps != 0) { // loop for the number of steps
  setPinGPIO0(X_AXIS_STP, PIN_HIGH);
  lpcWait(WAIT_TIME);
  setPinGPIO0(X_AXIS_STP, PIN_LOW);
  lpcWait(WAIT_TIME);
  numSteps--;
}
```

We then abstract this code further into the concept of moving the electromagnet around a grid of 8x8 squares &ndash; a chessboard. The code for this function first moves the motor into the corner of it's current square, then moves it the correct X and Y distances to the target square. It's header is as follows, which we can then call from the game-MCU interaction layer.
```C
int moveMotor(int toX, int toY);
```

["Easy Driver"]: https://learn.sparkfun.com/tutorials/easy-driver-hook-up-guide/all
[NEMA 16 stepper motor from SparkFun]: https://www.sparkfun.com/products/9238

## Electromagnet Control

### <a id="electromagnet"></a> Choosing an Electromagnet

In our experiements, we had a difficult time choosing an electromagnet that would work with our board. We initially tried using [5V Electromagents from Adafruit], both 5kg and 10kg holding force variants. Unfortunately, neither electromagnet was able to significantly drag a similarly diametered steel circle through 1/8" acryllic (our chessboard material). 

Because of this we decided to upgrade to a [12V, 50kg holding force electromagnet ordered off Amazon]. After some testing, we can see that the 50kg holding force magnet can attract a steel plate through the 1/8" acryllic barrier. Unfortunately, this electromagnet was _way_ too large for our planned chessboard size &ndash; it would cause our chessboard to be nearly 4 x 4 feet in dimensions!

As a middle ground, we finally tried a [12V, 30kg holding force electromagnet]. This electromagnet was still able to pull the steel discs through 1/8" acrylic, though we had to move the magnet slowly. We decided this was the best option and went with it.

A comparison between the electromagnets we tried is below.

| Holding Force | Voltage | Size | Thru 1/8" OK  | Thru 1/4" OK  |
| ------------- | ------- | ---- | ------------- | ------------- |
| 5 kg          | 5 V     |      | No            | No            |
| 10 kg         | 5 V     |      | Very slight   | No            |
| 30 kg         | 12 V    |      | Yes, but slow | No            |
| 50 kg         | 12 V    |      | Yes           | Yes, but slow |

### Electromagnet Circuit

Electromagnets are solenoids that generate a magnetic field when current flows through them. Since we are using steel plates on the bottom of our chess pieces, we don't care about the polarity of the magnetic field. Since the electromagnet both requires much more current than the ARM processor can output, as well as a different voltage, we use a simple transistor circuit and flyback diode to control it.

<img src=img/whiteboard_em_circuit.jpg width="50%">

With this circuit, powering the electromagnet on and off is pretty simple - just set the GPIO pin high when we want to turn on the electromagnet, and low otherwise.

[5V Electromagnets from Adafruit]: https://www.digikey.com/product-detail/en/adafruit-industries-llc/3873/1528-2689-ND/9603612
[12V, 50kg holding force electromagnet ordered off Amazon]: https://www.amazon.com/Suction-electric-Solenoid-cylinder-Electromagnet/dp/B07JL95XD8/
[12V, 30kg holding force electromagnet]: https://www.amazon.com/gp/product/B07HPC28ZM/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1

## Chess Game Software

### Overview

We are using the NXP LPC1114FN28/102 chip, which sports an ARM Cortex-M0 processor with 32 kB flash memory and 4kB SRAM. The software for ChessExpress is mostly implemented in Python on a host PC, with some motor control and serial code written in C on the embedded platform.

### C Code in the ARM Microprocessor

The code on the microprocessor primarily provides the control to the motors, as discussed in the MCU section above. It exposes the inputs to the MCU through a serial communication, which the ChessExpress Python application communicates with.

### The Python Application

The Python ChessExpress application is the top-level software for the project, and the file that the user should run after the board itself is connected to the host PC through a serial connection. It is centered around 4 different Python files.

#### <span>chessexpress.py</span>

`chessexpress.py` is the top-level file for this project. it defines the `main` method and parses the command line arguments. There is an option `--debug` parameter that tells the program to run a simple test sequence before starting the main game loop.

#### <span>menu.py</span>

`menu.py` defines a simple `TextMenu` class, which uses the `pyfiglet` and `colorama` python packages to print out cool ASCII art and prompt the user for information. By using this menu class to prompt the user for information rather than directly through PuTTY, we gain several advantages:

1. The user can actually see the input they are inputting. In PuTTY, this is unavailable.
2. The user has the option to backspace if they make a mistake. Since PuTTY sends the character through serial immediately after it is pressed, this isn't an option without using a python menu frontend.
3. Easier debugging. It's a lot easier to debug through python than trying to figure out what went wrong with the serial communication.

#### <span>lpc_comm.py</span>

`lpc_comm.py` defines a class to commmunicate with our C code on the LPC1114 processor. It uses the `pyserial` library to open a connection through a serial port. It has a function, `send_command`, that sends a command and listens for an acknowledge signal before returning.

```python
def send_command(self, command: str):
  """Sends a command to the processor via serial"""
  if self.ser.is_open:
    self.ser.write(command.encode(self.encoding))
    self.ser.read_until('ACK'.encode(self.encoding))
    self.ser.read_until('ACK'.encode(self.encoding))
```

#### <span>game.py</span>

`game.py` is the main game loop. It holds a `Game` class that represents an instance of a chess game. It holds the state of the game and uses menus and an `LpcComm` object to interface between the users and the board itself.

### Why Use Both Python and C?

The LPC1114FN28/102 chip unfortunately only has 4kB of SRAM. In the initialization code for the chip, the stack size is set to half of that &mdash; 2kB. Unfortunately, this meant that when we tried to keep the board structure in memory on the microprocessor, whenever we would try to put anything else in the stack we would get overflow issues.

It was a very perplexing problem: our board structure would get overwritten whenever we tried to print something to the serial console. It was only through tedious debugging that we realized it may be the stack being corrupted. This wasn't helped by the fact that the microprocessor, unlike modern laptops and desktops, doesn't have any way of telling you that its memory was corrupted.

For this reason we decided to move the bulk of the memory-intensive processing to on off-board computer. Since the game will be run through a serial connection to a PC anyway, we decided to use Python to make a nicer user interface for the users. (See [Issue #7] in the GitHub repository for specific implementation details).

[Issue #7]: https://github.com/dbisk/chessexpress/issues/7

## Future Improvements

The current status of this project (up to Dec. 17, 2019) was implemented within a semester for the Advanced Digital Projects Lab (ECE 395) at the University of Illinois, Urbana-Champaign. At this time, there are several improvements that can be made to improve both the functionality and robustness of ChessExpress. Some improvements for the PCB Design and board are indicated in the [PCB Design Section](#pcb). Many of the other improvements are mostly software-centric. Although the game currently has a nice GUI that interfaces python, C and the hardware, the actual game logic has not been implemented. Distinguishing between each type of piece and creating rules such that illegal moves cannot be made would be the first major improvement in Chess Express. After developing the right piece movements, having awareness of the location of all the pieces or the most recent moves stored in memory would create a faster chess game experience. Another interesting addition would be to pull online games currently being played to simulate a "computer" playing a game, and would be a fun visual experience to demo. The physical design could also use some improvements. In particular, the board is very large right now due to the constraint of the electromagnet requiring a 2 inch diameter to prevent incorrect piece pick-ups. By messing around with voltage input to the magnet, while still trying to use a single power source, the board could possibly pull a greater force and drag the pieces more fluidly and quickly. Experimenting further with this would potentially allow us to use a smaller holding force electromagnet, and therefore a magnet of smaller diameter. Feel free to refer to our process of [Choosing an Electromagnet](#electromagnet)  for the current status of the project. This would help us reduce the board size to something reasonable to sit on a coffee table rather than the approximately 30x30 inch board that it is now. 

### Hardware Improvements

1. Add limit switches to ensure the stepper motors do not accidentally go beyond the movable area. Currently, with poor calibration, the motors can attempt to go beyond their range of motion and potentially damage themselves.

# Appendix

## Bill of Materials and Parts List

| Name                    | Part Number     | Quantity | Unit Cost | Vendor                            |
| ----------------------- | --------------- | -------- | --------- | --------------------------------- | 
| Microprocessor          | LPC1114FN28/102 | 1        | N/A       | N/A (obsolete, provided by class) |
| FTDI Friend             | 284             | 1        | $14.95    | Adafruit                          |
| NEMA-16 Stepper Motor   | ROB-09238       | 3        | $15.95    | SparkFun                          |
| EasyDriver              | ROB-12779       | 3        | $14.95    | Sparkfun                          | 
| 12V, 30Kg Electromagnet | a2018092615     | 1        | $15.59    | Kaka Electric                     |
| BJT Transistor          | TIP-122         | 1        | $0.63     | ON Semiconductor                  |
| Various Resistors       | N/A             | N/A      | N/A       | N/A                               |
| Push Buttons            | N/A             | 2        | N/A       | N/A                               |
| AC/DC 12V Wall Adapter  | 364-1282-ND     | 1        | $10.16    | Tri-Mag, LLC                      |
| Power Barrel Jack 5.5mm | CP-102A-ND      | 1        | $0.64     | CUI Devices                       |
| IC Inverter             | N/A             | 1        | N/A       | N/A                               |
# Credits and Sources

1. SparkFun Easy Driver "https://learn.sparkfun.com/tutorials/easy-driver-hook-up-guide/all"