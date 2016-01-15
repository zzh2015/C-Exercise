/*******************************************************************************
 * chapter 11 pthread
*******************************************************************************/
/* 0
 * 线程ID: pthread_t,只在它所属的进程上下文中才有意义。
 * 
 * */
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PID_AND_TID 0
#define EXIT_T_RET 1

#if PID_AND_TID
pthread_t g_Tid;

//pthread_equal(tid1, tid2)
static void PrintID(const char *str)
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s: pid %lu, tid %lu(0x%lx)\n", str, static_cast<unsigned long>(pid), static_cast<unsigned long>(tid), static_cast<unsigned long>(tid));
}

void *Func(void *arg)
{
    PrintID("New Thread");

    return arg;
}

int main()
{
    int ret = 0;
    ret = pthread_create(&g_Tid, NULL, Func, NULL);
    assert(ret == 0);
    PrintID("Main Thread");
    sleep(1);

    return 0;
}
#endif

#if EXIT_T_RET
static void *Func_1(void *arg)
{
    printf("Thread Func1\n");

    return ((void *)1);
}

static void *Func_2(void *arg)
{
    printf("Thread Func2\n");

    return ((void *)2);
}

int main()
{
    pthread_t tid1, tid2;
    int ret = 0;
    ret = pthread_create(&tid1, NULL, Func_1, NULL);
    assert(ret == 0);
    ret = pthread_create(&tid2, NULL, Func_2, NULL);
    assert(ret == 0);
    
    void *tRet = nullptr;
    ret = pthread_join(tid1, &tRet);
    assert(ret == 0);
    printf("thread 1 exit code %ld\n", (long)tRet);
    ret = pthread_join(tid2, &tRet);
    assert(ret == 0);
    printf("thread 2 exit code %ld\n", (long)tRet);

    return 0;
}
#endif

/*
 *  互斥量(Mutex):对互斥量加锁后，任何试图再次为它加锁的线程都将被堵塞，直到当前线程释放该互斥锁。
 *  当释放互斥量有一个以上的线程阻塞，所有线程从阻塞状态变为运行态，第一个开始运行的线程可以加锁，其他仍要回到阻塞态。
 *  死锁：线程对同一互斥量加锁两次，自身就会陷入死锁状态；两个线程互相申请另一方持有的资源时产生死锁。
 * */
//pthread_mutex_t mutex;
//int pthread_init(&mutx, NULL);
//int pthread_destroy(&mutex);
//int pthread_mutex_lock(&mutex);
//int pthread_mutex_unlock(&muetx);
/*
 * pthread_mutex_try_lock(); pthread_mutex_timedlock();
 * */

/* 读写锁(共享互斥锁)：读模式加锁(可多个线程占有)、写模式加锁(仅一个线程占有)、不加锁
 * 读写锁适合对数据结构读的次数远大于写的次数。
 * * /

















