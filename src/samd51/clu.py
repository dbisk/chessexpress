"""The Chess Logic Unit of Chess Express

Defines a class that represents the "chess game" going on at the moment.
"""

class CLU:
  """An instance of the Chess Logic Unit, which runs the chess game.

  The CLU class represents an instance of the chess game. It holds the current state of
  the game as well as various information, and facilitates input from the users through the 
  VPU to progress the game forwards. It also understands the movements of chess pieces, 
  indicating to the players when a move is illegal.

  Attributes:
    board - a representation of the chessboard. Holds tuples of the form (color, rank)
    moves - a list of all the moves performed in this game
    graveyard - a list of all pieces in the graveyard
  """

  FILES = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
  RANKS = ['1', '2', '3', '4', '5', '6', '7', '8']

  def __init__(self):
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

  def make_move(self, from_pos, to_pos):
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
  
  def game_loop(self):
    return
  
  def _get_rank_file(self, position):
    """Returns the algebraic notation rank and file of a position.

    Arguments:
      position - (row, col) tuple position on the board
    
    Returns:
      rank_file - string representing "(rank)(file)"
    """
    rank_file = CLU.FILES[position[1]] + CLU.RANKS[position[0]]
    return rank_file
  
  def _in_check(self):
    """Returns the color that is in check, -1 otherwise"""
    # TODO: implement this
    pass
