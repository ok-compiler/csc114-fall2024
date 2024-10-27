# i may or may not have remade tetris

I decided i wanted to go the extra mile with the final and do something more complex in order to challenge myself, and overall it’s been very fun so far. Learned a ton along the way that i wouldn’t have even touched otherwise (like multithreading)

I’ve somehow managed to write it in the most inefficient and unoptimized way possible, but i honestly don’t care as long as it works decent enough with minimal bugs to gameplay lol

All functions are currently in the main.cpp file but i may move each one to their own file for readability sake

This doc and project is a huge huge WIP so some information provided below may not be up to date with the current version.
# To-Do

- ~~add pieces~~ 
- ~~add color codes for each piece~~
- ~~add collision~~
- ~~add piece movement~~
- ~~add gravity~~
- ~~add rotation~~
- ~~add line clears~~
- add topout logic
- ~~add score/levels~~
- ~~add next piece display (right of board)~~
- add controls display (below board)
- ~~clean up the code to be readable LOL~~ (kinda)
- optimize (im not gonna do this part)

# Objects:

## 2D arrays

  * ```map[y][x]```
    * Base map function
    * Used to print the actual board to the console output and find positions of everything
    * Borders using #
    * Empty spaces are literally just a space
  * ```color[y][x]```
    * Same size as base map function
    * Used to assign colors to each individual space
      * Once a piece is set to the bottom, they turn into a # (same as border), need color to remain after new piece comes out
    * Borders are white
    * Spaces are gray
    * All pieces are same colors as original tetris

## 1D arrays
  * ```pieceX[4]```, ```pieceY[4]```
    * Used to determine the X/Y value of the player’s piece within original map array
    * Each piece has only 4 values
    * Some pieces have same X/Y values
    * All games start with an “I” piece (cyan)
  * ```newpieceY[4]```, ```newpieceX[4]```
    * Used as placeholder when updating pieces
        * Checks collision with placeholder X/Y values before replacing the true X/Y values (```pieceX``` and ```pieceY```)
## variables

   * ```mapX```, ```mapY``` (ints)
        * Used to determine size of map
        * Currently 25x25, can be sized up or down with ease
   * ```pieceValue``` (int)
        * Determines what piece is next
        * Can range from 0-6, each value has a different piece attached to it
   * ```wasd``` (char)
        * Object that all inputs into console are assigned to
        * Uses raw terminal to collect info instead of cin
            * This is so that you don’t need to press enter every time you want to input a move
   * ```topOut``` (bool) (not implemented)
        * If false, game continues
        * If true, game ends
            * Becomes true when highest value is filled with ‘#’ characters

# Functions:

## mapInit()

  * Initializes map
  * 2 for loops with both the X and Y values of 2D map array
  * If value is a border, set to #
  * If not and there **isn't** a #, set to an empty space (‘ ‘)

## printMap()

* Uses mutex to make sure only one thread can output data at the same time
* Clears console for a nice clean look
* 2 for loops with both the X and Y values of 2D map array (again)
* If x value isnt last in map, cout normally
* Else, cout with new line
* All couts output the ```map[y][x]``` value inside of the ```color[y][x]``` value so that it outputs the character with its assigned color
* On the side displays next piece in rotation (very much not implemented yet)
* Under map displays controls

## initPiece()

* Initializes piece
* Creates random number between 0 and 6, assigns that value to nextPiece int
* if the value is in the "piece bank", initialize new piece (loop until success)
* if pieceBank array is full, reset array
 * this gives makes sure **all** pieces are generated per 7 cycles
  * same random generation as all new tetris games

## spawnNewPiece() 
* Spawns new piece at top and center using ```pieceValue``` to determine which piece spawns
* Each time new piece is spawned, initPiece() is ran afterwards to obtain new next piece to display

## updatePiece()
* If 0, create initial position for start of game
* If 1, run while loop for rest of game
* Collects inputs from console
* Updates ```pieceX``` and ```pieceY``` values using ```newpieceX``` and ```newpieceY``` as explained previously
* Once pieceX and pieceY are updated, ```map[pieceY][pieceX]``` and ```color[pieceY][pieceX]``` are updated accordingly
* Runs ```printMap()``` function to display changes
* Use ~ to terminate code and end game

## rotatePiece()

* Rotates piece based on position
* Each pieceValue has their own type of rotation, and math/collision is calculated for each using switch function
* Updates ```map[pieceY][pieceX]``` and ```color[pieceY][pieceX]``` accordingly
* Runs ```printMap()``` function to display changes

## updatePos()

* Main gravity function
* Has its own thread to run independently from the rest of the code
* Every second, check for collision and update pieceY value by 1
* If collision is good, update ```map[pieceY][pieceX]``` and ```printMap()```
* If not, replace current ```map[pieceY][pieceX]``` values with #
    * Then ```spawnNewPiece()```

## main()

* Runs all functions in proper order
    * Run ```mapInit()``` to initialize starting map
    * Run ```updatePiece(0)``` to create initial position
    * Run ```updatePos()``` in its own thread
    * Run ```updatePiece(1)``` to start all other logic
