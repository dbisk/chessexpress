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
import game

def test_fn(args):
  """Tests various functionalities of this program"""
  options = ["Start interactive game"]
  main_menu = menu.TextMenu(options)
  print("-------------------------")
  print("Testing LPC communication")
  print("-------------------------")
  com = lpc_comm.LpcComm(args.port)
  g = game.Game(com)
  main_menu.set_art(art_str=g.board_to_str())
  main_menu.print()
  print("\n---------------------")
  print("Testing some moves...")
  print("---------------------")
  print(g.board_to_str())
  g.make_move((6, 3), (4, 3))
  print(g.board_to_str())
  g.make_move((1, 3), (3, 3))
  print(g.board_to_str())
  print("Tested moves:", g.moves)
  com.close_port()
  print("Tests completed... Press [enter] to continue.")
  input() # force user to hit enter before continuing

def main():
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('-p', '--port', required=True, type=str, help="the port that the chessboard is connected to")
  parser.add_argument('--debug', action="store_true", help="pass this to run debugging tests")
  args = parser.parse_args()

  # optionally run debug test
  if args.debug:
    test_fn(args)
  
  com = lpc_comm.LpcComm(args.port)
  g = game.Game(com)
  g.start()
  com.close_port()

if __name__ == "__main__":
  main()
