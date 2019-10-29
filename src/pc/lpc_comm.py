"""Serial communicator to the LPC processor

Contains a class that represents the communication between this program and the LPC

Usage:
  lpc_proc = LpcComm('/dev/ttyUSB0')
"""

import serial

class LpcComm():
  """ A communicator to communicate with an LPC1114 over the serial port.

  The LpcComm class contains functions that are related to communicating with an
  LPC1114FN28/102 processor from NXP. All of the commands sent to and data
  received from the processor are processed done using serial communication.
  This LpcComm class is specifically geared toward the chess game.

  Attributes:
    ser - serial object that is talking to the LPC
  """

  def __init__(self, port: str):
    """Initializes a LpcComm object"""
    self.ser = serial.Serial(port, 115200)
  
  def open_port(self):
    """Opens the port if it is not already, else does nothing"""
    if not self.ser.is_open():
      self.ser.open()
  
  def close_port(self):
    """Closes the port if it is open, else does nothing"""
    if self.ser.is_open():
      self.ser.close()
  



