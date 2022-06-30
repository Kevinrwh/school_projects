# This is a basic recreation of the popular connect-4 game. Upon beginning the game, the game asks the first player to choose the column they would like to place their piece. Then the next player is asked and the process repeats until the game is won by the traditional rules or if there are no more moves to be made.

import random

def createArray():
  createdArray = [['-' for i in range(cols)] for j in range(rows)]
  return createdArray

# Display the board tot he user
def printBoard():
  for a in arr:
    print(a)
    print()
  print()

# Game function - exit only with game over
def playGame(arr):

  print('Begin game')

  movesTaken = 0
  userPiece = 'X' # default
  playing = True

  # Ends when all columns are filled
  while playing:

    if movesTaken%2 == 0:
      userPiece = 'X'
    else:
      userPiece = 'O'

    move = promptUserInput(userPiece)
    while move == False:
      move = promptUserInput(userPiece)

    # Check if we can keep playing - reset each time
    fullCols = 0

    for idx in range(7):
      if arr[0][idx] != '-':
        fullCols+=1

    if fullCols >=7 or move == 'won':
      if fullCols >= 7:
        print('No more moves can be made. Game oover')
        print('Moves taken: ' + str(movesTaken+1))
      elif move == 'won':
        print('the game has been won')

      playing = False

    movesTaken+=1 # increment moves

# Ask for the column of choice
def promptUserInput(userPiece):

  # Ask the user which column
  print('Choose the column you would like to try.')
  print('Your options are [1, 2, 3, 4, 5, 6, 7]')

  response = False

  # Ensure the input is appropriate and in range
  while response == False or response < 1 or response > 7:
    print('Select a valid option')
    response = int(input())

  moveMade = selectCol(arr, response-1, userPiece) # user input decreased due to 0-indexing
  return moveMade

# Ensure we can place in this column
def selectCol(arr, col, val):

  # Check if in bounds and the piece is appropriate
  if col < 0 or col > 6 or (val != 'X' and val != 'O'): # unnecessary at this point i think
    if(val != 'X' and val != 'O'):
      print('enter a valid value')
      return False
    else:
      print('try again. stay in bounds')
    return False

  print('trying to place in column ' + str(col+1))

  # Check if the column is full
  for idx in range(6):
    if arr[idx][col] != '-':
      if idx == 0:
        print('couldn\'t place in column ' + str(col+1) + ' because it is full')
        return False
      else:
        # Place at the empty spot above this
        return placeCol(arr, idx-1, col, val)

  print('Column is empty. Placing.')
  return placeCol(arr, 5, col, val)

# Places the piece and displays the board after the move
def placeCol(arr, idx, col, val):
  print('Placed value: ' + str(val))
  arr[idx][col] = val

  printBoard()

  # Return True
  return keepPlaying(arr, idx, col, val)

# Keep playing if the move did not result in a win condition
def keepPlaying(arr, idx, col, val):
  row = idx
  column = col
  count = 0

  # reset
  row = idx
  column = col
  count = 0

  # check down
  while inBounds(arr, row, column) and arr[row][column] == val:
    count+=1
    row+=1
  if count >= 4:
    print('won down')
    return 'won'

  # reset
  row = idx
  column = col
  count = 0

  # check diagonal up right
  while inBounds(arr, row, column) and arr[row][column] == val:
    count+=1
    row-=1
    column+=1

  if count >= 4:
    print('won diagUp right')
    return 'won'

  # reset
  row = idx
  column = col
  count = 0

  # check diagonal up left
  while inBounds(arr, row, column) and arr[row][column] == val:
    count+=1
    row-=1
    column-=1

  if count >= 4:
    print('won diagUp left')
    return 'won'

  # reset
  row = idx
  column = col
  count = 0

  # check diagonal down left
  while inBounds(arr, row, column) and arr[row][column] == val:
    count+=1
    row+=1
    column-=1

  if count >= 4:
    print('won diagDown left')
    return 'won'

  # reset
  row = idx
  column = col
  count = 0

  # check diagonal down right
  while inBounds(arr, row, column) and arr[row][column] == val:
    count+=1
    row+=1
    column+=1

  if count >= 4:
    print('won diagDown right')
    return 'won'

  return True

def inBounds(arr, idx, col):

  # return false if out of bounds
  if idx < 0 or idx > 5 or col < 0 or col > 6:
    return False
  else:
    return True

# Main
rows, cols = (6, 7)

# Create the 2D array
arr = createArray()

playGame(arr)
print('Exiting')
