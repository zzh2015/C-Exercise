/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: select_1.cpp
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/select.h>
#include <sys/time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

static void UsageInfo()
{
    printf("example: ./a.out -\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        UsageInfo();
        return 0;
    }
    fd_set readfds, writefds;
    int fd[2] = {-1};
    struct timeval timeout;
    struct timeval *pto;
    if (strcmp(argv[1], "-") == 0) {
        pto = nullptr;
    } else {
        pto = &timeout;
        timeout.tv_sec = atol(argv[1]);
        timeout.tv_usec = 0;
    }
    
    int nfds = 0;

    fd[0] = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if (fd[0] < 0) {
        printf("Open tty Error\n");
    }
    //fd[0] = 1;

    nfds = 2; 
    char ch = 0;
    auto flag = true;
    while (1) {
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);

        FD_SET(fd[0], &readfds);
        //FD_SET(fd[0], &writefds);

        auto ready = select(nfds, &readfds, &writefds, NULL, &timeout);
        if (ready < 0) {
            printf("select exec Error!\n");
            exit(-1);
        } else if (ready == 0) {
            printf("timeout\n");
            break;
        }

        for (auto i=0; i<1; ++i) {
#if 0           
            if (FD_ISSET(fd[i], &writefds)) {
                if (flag) {
                    printf("Write Events\n");
                    flag = false;
                }
            }
#endif
            if (FD_ISSET(fd[i], &readfds)) {
                read(fd[i], &ch, 1);
                if ('\n' == ch) {
                    continue;
                } else if ('q' == ch) {
                    break;
                }
                printf("The Key Value: %c\n", ch);
            }
             
        }
    }
    close(fd[1]);

    return 0;
}
