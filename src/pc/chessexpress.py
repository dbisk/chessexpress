"""Chess Express

This script is the entry point to the ChessExpress user interface. It will print
prompts to the command line to allow either two players to play chess, or for
chess to be played out automatically. Requires Python 3.5+.

Typical usage example:
  python chessexpress.py
"""

import argparse
import os
from pyfiglet import Figlet

# import custom modules
import menu
import lpc_comm

def test_fn(args):
  """Tests various functionalities of this program"""
  options = ["Start interactive game", "Quit"]
  main_menu = menu.TextMenu(options)
  board = [['r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'],
           ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
           [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
           [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
           [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
           [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '],
           ['P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'],
           ['R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R']]
  main_menu.set_art(board)
  main_menu.print()
  # com = lpc_comm.LpcComm(args.port)
  # com.close_port()

def main():
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('-p', '--port', required=True, type=str, help="the port that the chessboard is connected to")
  args = parser.parse_args()

  test_fn(args)

  

if __name__ == "__main__":
  main()
