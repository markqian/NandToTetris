// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.


    @KBD
    D = A

    @SCREEN
    D = D - A

    @dist
    M = D

    @counter
    M = D

    @counter2
    M = D


(forever)

    @dist
    D = M
    @counter
    M = D
    @counter2
    M = D
    @KBD
    D = M
    @black
    D;JGT
    @white
    D;JEQ
    @forever
    0;JEQ
    
    
(black)
    @SCREEN
    M = -1
    
    @SCREEN
    A = A + D
    M = -1

    @1
    D = A
    
    @counter
    M = M - 1 
    D = M
    
    @black
    D;JGT

    @forever
    0;JEQ

(white)
    @SCREEN
    M = 0
    
    @SCREEN
    A = A + D
    M = 0

    @1
    D = A
    
    @counter2
    M = M - 1 
    D = M
    
    @white
    D;JGT

    @forever
    0;JEQ
    

    
        
(END)
    @END
    0;JMP