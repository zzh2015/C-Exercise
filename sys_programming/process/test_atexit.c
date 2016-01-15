/*******************************************************************************
FileName: test_atexit.c
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

static void HandleFunc_1(void)
{
    printf("cleanup func1\n");
}

static void HandleFunc_2(void)
{
    printf("cleanup func2\n");
}

int main(void)
{
    //exit handler,函数注册顺序与执行顺序相反
    if (atexit(HandleFunc_1) != 0) {
        perror("can't register HandleFunc_1");
    }
    
    if (atexit(HandleFunc_2) != 0) {
        perror("can't register HandleFunc_2");
    }
    
    printf("Hello world!\n");
    sleep(1);

    return 0;
}

