/* To run:
   gcc -O -o test fetch.c parse.c play.c quiz.c -ljson-c
   $ ./test
*/

#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"


int main()
{

quiz_t quiz;

quiz.n = 1;
quiz.score = 0;
quiz.max = 0;


while (1) {
if(play(&quiz) == -1) break;
}
return 0;
}