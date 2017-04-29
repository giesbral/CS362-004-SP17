/*
	Alex Giesbrecht - giesbral@oregonstate.edu
	4/29/2017
	CS362_400_SP17

	randomstring.c - CS362 Random Testing Quiz
*/

/*
	For my first implementation of the testing function inputChar() I was randomly obtaining any of the
	alphanumeric ascii characters from 33-126 (! to ~). I found that this implementation not only took a 
	very long time to trigger an error scenario, it was doing so because it was randomly generating 
	characters that were not pertinent to the function being tested. For my final implementation I decided
	to narrow the randomly generated characters to those relevant to the function testme,
	'[', '(', '{', ' ', 'a', 'x', '}', ')', and ']'. I put these characters in an array and randomly generated
	indexes to the array to pull out a character and return it to the testme() function.

	My first implementation of inputString() was similar to my implementation of inputChar(). I was generating
	strings of length 6 using all of the alphanumeric ascii characters. Again, this implementation took a long
	time to generate the error and was also generating a lot of strings that weren't relevant to the code being
	tested in the testme() function. For my final implementation of inputString I created a character array of 
	relevant characters ('r','e','s','t','\0') and generated a string of maximum length 6 by randomly adding 
	characters from this array to a return string. 

	My two final implementations of inputChar() and inputString() generated the error code after ~5-7k iterations
*/