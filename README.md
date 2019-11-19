# The Chess Express

The Chess Express, an Automatic Chessboard inspired by Wizard's Chess from _Harry Potter and the Sorcerer's Stone_

Unfortunately, our implementation does not destroy the pieces like true wizard chess, but perhaps we can make a definitely not OSHA-compliant addon for that :P. (exploding capacitors, anyone?)

![That's barbaric!](https://thumbs.gfycat.com/ThunderousAnnualBushsqueaker-small.gif)

Hermoine doesn't approve.

## Repository Layout

The repository is laid out as follows:

1. `src` holds the source code for the programming both onto the LPC1114/102 FN28 processor, as well as a python program (in the works) that interfaces with the LPC code via serial.

2. `hardware` holds the hardware design files and documentation. See this if you are looking to reproduce the hardware rig made for this project.

3. `doc` holds high-level documentation as well as a full lab report for the project. See the README in the `doc` folder for the lab report.

## Usage

Assuming you have the rig completely set up (if not, see the next section for details), you can start up the python program to interface with the chessboard simply with
```
python chessexpress.py --port COM5
```
in the _____ folder.
