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

  def __init__(self, port: str, encoding: str='utf-8'):
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
      self.ser.read_until('OK\r\n'.encode(self.encoding))
  
  def get_board(self) -> list:
    """Requests the board state from the processor
    
    This assumes that the board state is provided in the following specific fashion.
    
    The board represented as
    row/col a b c d e f g h 
          1 r n b q k b n r
          2 p p p p p p p p
          3 _ _ _ _ _ _ _ _
          4 _ _ _ _ _ _ _ _
          5 _ _ _ _ _ _ _ _
          6 _ _ _ _ _ _ _ _
          7 P P P P P P P P
          8 R N B Q K B N R

    is sent via the byte-string
    ('rnbqkbnr\\npppppppp\\n________\\n________\\n________\\n________\\nPPPPPPPP\\nRNBQKBNR\\nDONE\\r\\n')
    """
    if not self.ser.is_open:
      return -1
    
    # send the command to the processor
    self.send_command('b')

    # read until the DONE string, then parse
    data = self.ser.read_until('DONE\r\n'.encode(self.encoding))
    data = data.decode(self.encoding)
    board = [[]]
    for i, c in enumerate(data):
      if c == '\n':
        board.append([])
      else:
        board[i].append(c)
    
    # remove the last two rows
    board.pop()
    board.pop()
    return board



