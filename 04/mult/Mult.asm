// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[3], respectively.)

// Put your code here.

    @R0
    D = M		
    @counter
    M = D    	//init counter to R0
    @result
    M = 0	//init result to 0
    @done
    D;JEQ	//if R0 is 0 then jump to done

(loop)
    @R1
    D = M	
    @done	
    D;JEQ	//if R1 is 0 then jump to done
    @result
    M = M + D	//add R1 to result
    @counter	
    M = M-1	//decrease counter
    D = M
    @loop
    D;JGT	//if greater than zero go to loop

(done)    
    @result
    D = M	
    
    @R2
    M = D

(END)
    @END
    0;JMP
   