# Proposal: Tetris

## Synopsis

The user will open up a window with two components: an
active display of a Tetris game (a 20-by-10 grid of
squares that plays a traditional game of Tetris), and
a display that features the following three items:
the game score, the next brick coming, and a brick being
held for later use. Gameplay consists of a Tetrimino 
(a tetromino in one of 7 shapes) falling from the top of
screen to the bottom. The player manipulates the
x-position and rotational arrangement of the piece as it
falls to the bottom and inserts it in the arrangement of
existing bricks. When a 10-brick row is completely
filled, it is eliminated from the grid, and each brick
and empty space above it is moved down one row. The user
scores based on how many lines are cleared, and how many
of those clears occur simultaneously. At any point, the
user may choose to hold a block and not have to place it
until taking it out of the hold. This also allows the 
user to avoid having to place a brick or save it for
later. If there is no brick in the hold when the user
puts a brick in, the next brick in the sequence becomes
the user's brick. The game ends when the arrangement of 
blocks reaches the top of the grid without any blocks 
being eliminated.

## Functional requirements

The user will be able to do the following things:
 - Move the current brick left and right
 - "Soft drop" and "hard drop" the brick
    - "Soft dropping" means that the user lowers the brick
    by one column, "hard dropping" means the piece lowers to
    the lowest possible point it can go to at its current
    horizontal position
 - Rotate the brick in two directions
 - "Hold" a piece and remove it from the hold
    - Holding a piece means that the user places the
    piece in the "hold," and the piece is switched out
    for the piece that was either formerly in the hold
    or the next piece (only if there is no piece
    currently in the hold). Once a piece is placed
    in the hold, it cannot be switched out until the
    current piece is then placed
 
The game will run the following things:
 - Automatically lower a brick by one row if it has 
 not reached the bottom
 - Give a constant stream of randomized tetriminoes
 - Create 7 unique tetriminoes: J, L, S, Z, I, O, and T
 - Clear an arbitrary number of full brick lines
 - Keep score of how many lines are cleared, using lines
 cleared at once as a score calculator
 - Play audio that matches the game state (based on 
 either maximum height of the Brick stack or speed
 of Brick falling)
 - Speed up the rate at which bricks automatically lower
 as time progresses
 - Display a shadow of the current brick at where it would
 be hard dropped at that moment
 - Display the piece that will appear next and the piece in
 the hold

## Open questions

How will frame timing work in ge211? How can ticks have
variable timing based on game state?

What does an algorithm for rotation look like in each 
direction?

How will Brick be implemented as a class? How does a
Brick go from a unit to individual cells to be destroyed
in the row?