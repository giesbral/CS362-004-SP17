#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define SAMPLE_LEN 5
#define STRING_LEN 6

char inputChar()
{
	// array to hold random character
	char randChar[9] = { '[', '(', '{', ' ', 'a', 'x', '}', ')',']' };
	
	// "randomly" obtain index to randChar array
	int i = rand() % 9;

	// return char at random index
    return randChar[i];
}

char *inputString()
{
	// array to hold possible string characters
	char reset[SAMPLE_LEN] = "rest";

	static char string[STRING_LEN];

	//memset(string, '\0', sizeof(char) * STRING_LEN);

	int i;

	for (i = 0; i < STRING_LEN; i++) {
		
		int randIdx = rand() % SAMPLE_LEN;
		string[i] = reset[randIdx];
	}

    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}