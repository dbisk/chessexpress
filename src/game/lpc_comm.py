"""Serial communicator to the LPC processor

Contains a class that represents the communication between this program and the LPC

Usage:
  lpc_proc = LpcComm('/dev/ttyUSB0')
  lpc_proc = LpcComm('COM5')
"""

import serial

class LpcComm():
  """ A communicator to communicate with an LPC1114 over the serial port.

  The LpcComm class contains functions that are related to communicating with an
  LPC1114FN28/102 processor from NXP. All of the commands sent to and data
  received from the processor are done using serial communication. This LpcComm
  class is specifically geared toward the chess game.

  Attributes:
    ser - serial object that is talking to the LPC
  """

  def __init__(self, port: str, encoding: str='ascii'):
    """Initializes a LpcComm object"""
    self.encoding = encoding
    self.ser = serial.Serial() # this needs to be set so that the close_port call works in set_port
    self.set_port(port)
  
  def set_port(self, port: str):
    self.close_port()
    try:
      self.ser = serial.Serial(port, 115200)
    except serial.serialutil.SerialException:
      print("Connecting to Serial failed, please try again.")
      self.ser = serial.Serial()
  
  def open_port(self):
    """Opens the port if it is not already, else does nothing"""
    if not self.ser.is_open:
      self.ser.open()
  
  def close_port(self):
    """Closes the port if it is open, else does nothing"""
    if self.ser.is_open:
      self.ser.close()
  
  def read_line(self):
    """Reads a line from the serial port"""
    if not self.ser.is_open:
      return -1
    
    result = self.ser.read_until()
    return result
  
  def send_command(self, command: str):
    """Sends a command to the processor via serial"""
    if self.ser.is_open:
      self.ser.write(command.encode(self.encoding))
      self.ser.read_until('ACK'.encode(self.encoding))

