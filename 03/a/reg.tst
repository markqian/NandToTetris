// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/03/a/Register.tst

load Register.hdl,
output-file Register.out,
compare-to Register.cmp,
output-list time%S1.4.1 in%D1.6.1 load%B2.1.2 out%D1.6.1;

set in 0,
set load 0,
tick,
output;

tock,
output;

set in 0,
set load 1,
tick,
output;

tock,
output;

set in -32123,
set load 0,
tick,
output;

tock,
output;

set in 11111,
set load 0,
tick,
output;

tock,
output;

set in -32123,
set load 1,
tick,
output;

tock,
output;

set in -32123,
set load 1,
tick,
output;

tock,
output;

set in -32123,
set load 0,
tick,
output;

tock,
output;

set in 12345,
set load 1,
tick,
output;

set in 12345,
set load 0,
output;

set in 12345,
set load 0,
tock,
output;

//tock,
//output;

//set in 0,
//set load 0,
//tick,
//output;

//tock,
//output;
