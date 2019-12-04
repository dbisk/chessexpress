"""The functions that play the chess game between two players.

This file contains the functions that facilitate the playing of the chess game
between two players. 
"""

# import python modules
# import third party modules
# import custom modules
import menu
import lpc_comm

class Game():
  """An instance of a chess game.

  The Game class represents the instance of a chess game. It holds the current
  state of the game as well as various information, as well as facilitates input
  from the users to progress the game forwards. It also understands the
  movements of chess pieces, indicating to the players when a move is illegal.

  Attributes:
    board - a representation of the chessboard. Holds tuples of the form (color, rank)
    moves - a list of all the moves performed in this game
    graveyard - a list of all pieces in the graveyard 
  """

  FILES = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
  RANKS = ['1', '2', '3', '4', '5', '6', '7', '8']
  
  def __init__(self, communicator: lpc_comm.LpcComm):
    self.communicator = communicator
    self.moves = []
    self.board_size = 8
    self.graveyard = []
    self.reset_board()
  
  def reset_board(self):
    """Resets the chessboard to the initial state"""
    self.board = [[0] * self.board_size for _ in range(self.board_size)]
    self.board[1] = [(1, 'P')] * self.board_size
    self.board[6] = [(0, 'P')] * self.board_size
    self.board[0][0] = (1, 'R')
    self.board[0][1] = (1, 'N')
    self.board[0][2] = (1, 'B')
    self.board[0][3] = (1, 'Q')
    self.board[0][4] = (1, 'K')
    self.board[0][5] = (1, 'B')
    self.board[0][6] = (1, 'N')
    self.board[0][7] = (1, 'R')
    self.board[7][0] = (0, 'R')
    self.board[7][1] = (0, 'N')
    self.board[7][2] = (0, 'B')
    self.board[7][3] = (0, 'Q')
    self.board[7][4] = (0, 'K')
    self.board[7][5] = (0, 'B')
    self.board[7][6] = (0, 'N')
    self.board[7][7] = (0, 'R')
    self.graveyard = []
  
  def make_move(self, from_pos: tuple, to_pos: tuple) -> int:
    """Makes a move on the chessboard.

    Makes a move on the chessboard. Records the move in (almost) algebraic
    notation in the moves list. Deletes the captured piece and detects
    check/checkmate.

    Arguments:
      from_pos - (row, column) tuple the position the piece is moving from
      to_pos   - (row, column) tuple the position the piece is moving to
    
    Returns:
      in_check - the color in check, -1 if no one is in check
    """
    is_capture = False
    # without checks 
    if not self.board[to_pos[0]][to_pos[1]] == 0:
      is_capture = True
    
    # move the piece
    piece = self.board[from_pos[0]][from_pos[1]]
    self.board[from_pos[0]][from_pos[1]] = 0 # clear the original
    self.board[to_pos[0]][to_pos[1]] = piece

    # construct an algebraic notation string
    alg_not = piece[1] + self._get_rank_file(from_pos)
    if (is_capture):
      alg_not += "x"
    alg_not += self._get_rank_file(to_pos)

    self.moves.append(alg_not)
    return self._in_check()

  def board_to_str(self) -> str:
    """Returns a string representing the board"""
    ret_str = "\n"
    # go in inverse row order so that A1 is bottom left corner
    for row in range(self.board_size - 1, -1, -1):
      for col in range(self.board_size):
        piece = self.board[row][col]
        if (piece == 0):
          ret_str += "_"
        else:
          if piece[0] == 0:
            # black
            ret_str += piece[1].lower()
          else:
            # white
            ret_str += piece[1]
        ret_str += " "
      ret_str += "\n"
    return ret_str

  def start(self):
    """Starts and plays the main loop of the game."""
    main_menu = menu.TextMenu(["Start 2P Game"])
    main_menu.set_art(art_str=self.board_to_str())
    main_menu.print()
    choice = main_menu.get_option()
    if choice == 2: return

    # player chose to start 2P Game
    gameover = False
    player = "White"
    options = ["Input " + player + "'s next move:"]
    while not gameover:
      game_menu = menu.TextMenu(options, op_type="INPUT")
      game_menu.set_art(art_str=self.board_to_str())
      game_menu.print()
      move = game_menu.get_option()
      if (len(move) != 4):
        options = [player + "'s move input in the wrong format, try again:"]
        continue
      move = move.lower()
      if (move == "quit"): # able to quit at any time
        return
      
      # parse move into coordinates
      try:
        from_pos = (Game.RANKS.index(move[1]), Game.FILES.index(move[0]))
        to_pos = (Game.RANKS.index(move[3]), Game.FILES.index(move[2]))
      except ValueError:
        options = [player + "'s move input in the wrong format, try again:"]
        continue

      # TODO: parse move to make sure it is valid
      # TODO: check chess rules?
      # TODO: send to LPC
      self.communicator.send_command(str(from_pos[0]) + str(from_pos[1]) + str(to_pos[0]) + str(to_pos[1]))

      check = self.make_move(from_pos, to_pos)

      # update variables and info
      player = "White" if player == "Black" else "Black"
      options = ["Input " + player + "'s next move:"]

  def _get_rank_file(self, position: tuple) -> str:
    """Returns the algebraic notation rank and file of a position.

    Arguments:
      position - (row, col) tuple position on the board
    
    Returns:
      rank_file - string representing "(rank)(file)"
    """
    rank_file = Game.FILES[position[1]] + Game.RANKS[position[0]]
    return rank_file
  
  def _in_check(self):
    """Returns the color that is in check, -1 otherwise"""
    # TODO: implement this
    pass
