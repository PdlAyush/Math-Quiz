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

extern char *pipe_read(int fd)
{
    char *buffer =NULL;
    buffer = (char *)malloc(1024 * sizeof(char));
    if (buffer == NULL) {
    perror("couldn't allocate memory");
    return NULL;
    }
    
    while (read(fd, buffer, 1024) != 0) {}
    return buffer;
}

extern char *fetch(char *url)
{
    
    char *buffer;
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Error in making a pipe");
        return NULL;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Error forking");
        return NULL;
    }

    
    if (pid == 0)
    {
	char **arglist;
    	arglist = (char **)malloc(4 * sizeof(char *));
    	arglist[0] = "curl";
    	arglist[1] = "-s";
    	arglist[2] = url;
    	arglist[3] = NULL;
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execvp(arglist[0], arglist);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        buffer = pipe_read(fd[0]);
        close(fd[0]);
    }
    return buffer;
}

