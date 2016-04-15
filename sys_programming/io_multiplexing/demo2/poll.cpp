/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: poll.cpp
*******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int numPipes = 10, randPipe, numWrites = 3;
    int (*pfds)[2];
    struct pollfd *pollfd;

    pfds = (int (*)[2])calloc(numPipes, sizeof(int [2]));
    if (pfds == NULL) {
        return -1;
    }
    pollfd = (struct pollfd *)calloc(numPipes, sizeof(struct pollfd));
    if (pollfd == NULL) {
        return -1;
    }

    for (auto i=0; i<numPipes; ++i) {
        if (pipe(pfds[i]) == -1) {
            return -1;
        }
    }

    srand((int)time(NULL));
    for (auto i=0; i<numWrites; ++i) {
        randPipe = random() % numPipes;
        printf("Writing to fd: %3d(read fd: %3d)\n", pfds[randPipe][1], pfds[randPipe][0]);
        if (write(pfds[randPipe][1], "a", 1) == -1) {
            return -1;
        }
    }

    for (auto i=0; i<numPipes; ++i) {
        pollfd[i].fd = pfds[i][0];
        pollfd[i].events = POLLIN;
    }
    
    int ready = poll(pollfd, numPipes, -1);
    if (ready == -1) {
        return -1;
    }

    printf("poll() returned: %d\n", ready);

   for (auto i=0; i<numPipes; ++i) {
       if (pollfd[i].revents & POLLIN) {
           printf("Readable: %d %3d\n", i, pollfd[i].fd);
       }
   } 

    return 0;
}
