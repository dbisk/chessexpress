"""Module for a simple text menu

Contains class that represents a text-based menu in our program. The TextMenu

Typical usage example:
  main_menu = TextMenu(args)
  game_menu = TextMenu(args)
"""

import os
import pyfiglet
from colorama import Fore, Back, Style

class TextMenu():
  """A text menu printed to the console.

  The TextMenu class represents a menu that is intended to be printed to the
  console. Starts with a large, block ASCII art of Chess Express, some ascii art
  (for us, this is the chessboard), then the menu options.

  Attributes:
    options: a list of strings with the possible options
    text_art: a string representation of the chessboard (or any other art)
  """

  def __init__(self, options: list=None):
    """Initializes TextMenu with options"""
    self.options = options.copy() if options is not None else []
    self.text_art = ""

  def set_art(self, board: list=None, art_str: str=None):
    """Sets the ASCII art printed before the menu options.
    
    If board is not provided, then art_str is directly passed into the art
    attribute. Otherwise, the input list is parsed as a chessboard. 

    Arguments:
      board - 2-D array in the form of a list of lists of the chessboard, 
        indexed by [row][col]. Each entry in the 2-D structure is one 
        character, representing a piece. Black pieces are represented by 
        lower-case characters, while white pieces represented by upper-case characters.
      art_str - a direct ascii-art string that can be printed as the art.
    """
    if board is None:
      self.text_art = self.text_art if art_str is None else art_str
    else:
      new_art = ""
      for row in board:
        new_art = new_art + " - - - - - - - -\n"
        for col in row:
          new_art = new_art + ' '
          c = col
          if (c.islower()):
            # piece is a black piece
            new_art = new_art + Fore.BLACK + Back.WHITE + c.upper() + Style.RESET_ALL
          else:
            # piece is a white piece
            new_art = new_art + Fore.WHITE + Back.BLACK + c + Style.RESET_ALL
        new_art = new_art + "\n"
      new_art = new_art + " - - - - - - - -\n"
      self.text_art = new_art


  def print(self):
    """Clears the terminal window and prints the menu"""
    q = pyfiglet.Figlet(font='slant')
  
    # clear the terminal screen and print the title sequence
    os.system('cls' if os.name == 'nt' else 'clear')
    print(q.renderText('Chess Express'))
    print(self.text_art) # print the text art

    # enumerate the options and print
    index = 0
    for opt in self.options:
      index += 1
      print(str(index) + ": " + opt)
    if (index > 0):
      # there were options, so ask which option
      print("Please choose your option: ")

