// cursorleft.salcom (filename)

// syntax
/*
 * # comment
 * # main syntax
 * START # starts command
 * VAR p: 10; # variable (only integers)
 * POSV point1: 0,0; // point variable
 * MARK spot1; # marker
 * p-; # decrement
 * p:10; # set
 * 
 * IF p < 10: TRUE() FAlSE();
 * IF p < 10: ( # if statement
 * GOTO spot1; # goto marker
 * ) 
 * 
 * # salsa syntax
 * VAR ch1: 0;
 * VAR p1x;
 * VAR p1y;
 * 
 * TYPE 0,0,c42 # if c before number then turn the number into char, if not then type number, types at line:char
 * p2: ~L+0,~C+0;
 * CHARAT ~L+1,~C+-1,ch1; # ~L & ~C is the cursor position (line, character) the + is necessary
 * CHARAT ~L+-2,~C+10,ch1;
 * CURTO 0,0; # forces cursor to go to a specific location
 * SETBG: RED; # sets the background and a position to 
 * END # ends command 
*/