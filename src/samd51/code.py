"""Entry point to the CircuitPython code

code.py is run when the processor boots up, given default configuration.
"""

# import CircuitPython modules

# import user modules
from clu import CLU
from icu import ICU
from mcu import MCU
from vpu import VPU

# allow a debug function to exist
def debug_tests():
  return True

# "main function", but we just let it run global code because of how
# CircuitPython works
if debug_tests == False:
  # failed our tests, print out a message to the user but continue anyway
  print("1 OR MORE TEST CASES FAILED: SEE CONSOLE OUTPUT FOR MORE DETAILS.")

# create an instance of each module
clu = CLU()
icu = ICU()
mcu = MCU()
vpu = VPU()

# start the general operating loop
while True:
  print("Starting a game...")
  clu.game_loop()
  print("Game completed.")
