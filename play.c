#include "quiz.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <curl/curl.h>
#include <signal.h>


extern int play(quiz_t *quiz)
{
    char *json = fetch("http://numbersapi.com/random/math?min=1&max=100&fragment&json");
    if(json == NULL) return -1;
    if(parse(json, quiz) == -1) return -1;
    int user_number;
    unsigned question_score=8;
    printf("Q%u: What is %s?\n", quiz->n, quiz->text);
    while (question_score != 0)
    {
        printf("%d pt> ", question_score);
        if (scanf("%d", &user_number) == EOF)
        {
            printf("EOF");
            exit(1);
        }
        else if (user_number < quiz->number)
        {
            question_score = question_score/ 2;
            if(question_score != 0)
		printf("Too small, try again\n");
            else
                printf("Too small, ");
        }
        else if (user_number > quiz->number)
        {
            question_score= question_score/ 2;
            if(question_score != 0)
		printf("Too large, try again\n");
            else
                printf("Too large, ");
        }
        else
        {
            quiz->score = question_score + quiz->score;
            printf("Congratulations, your answer %d is correct.\n", user_number);
            break;
        }
    }
    if (question_score == 0){
        printf("the correct answer was %d\n",quiz->number);
    }
    quiz->n++;
    quiz->max = quiz->max + 8;
    printf("Your total score is %d/%d\n", quiz->score, quiz->max);
    printf("\n");
    return 0;
}

