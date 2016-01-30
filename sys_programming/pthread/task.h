#ifndef TASK_H
#define TASK_H


#include <malloc.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
//#include "version.h"
#include <sched.h>
#include <unistd.h>
typedef struct {
    pthread_t thread_handle;
    pthread_attr_t thread_attr;
    void* buffer;
} PthreadStruct;

class Task {
public:
    Task(const char *name = NULL) : mName(name) {
        memset(&mTaskId, 0, sizeof(mTaskId));
    }

    ~Task() {
        /*
        if(mTaskId.buffer != NULL)
        	free(mTaskId.buffer);
        	*/
    }

    void Run(void* routine (void *), void *param,
             int stkSize = 0, int policy = 0, int priority = 0, int cpu = -1) {
        int err = pthread_attr_init(&mTaskId.thread_attr);
        assert(err == 0);
        /*设置线程的分离属性：PTHREAD_CREATE_DETACHED 分离状态启动； PTHREAD_CREATE_JOINABLE 正常启动*/
        //	err = pthread_attr_setdetachstate(&mTaskId.thread_attr, PTHREAD_CREATE_DETACHED);
        //	pthread_attr_getdetachstate();
        //	assert(err == 0);
        mTaskId.buffer = NULL;
        if(stkSize != 0) {
            mTaskId.buffer = (char*)malloc(stkSize);
            /*设置线程栈的需地址空间*/
            err = pthread_attr_setstack(&mTaskId.thread_attr, (void*)mTaskId.buffer, stkSize);
            assert(err == 0);
        }

        err = pthread_attr_setscope(&mTaskId.thread_attr, PTHREAD_SCOPE_SYSTEM);
        assert(err == 0);

        err = pthread_attr_setinheritsched(&mTaskId.thread_attr, PTHREAD_EXPLICIT_SCHED);
        assert(err == 0);

        if(policy != 0)
        {
            err = pthread_attr_setschedpolicy(&mTaskId.thread_attr, SCHED_RR);
            assert(err == 0);
        }
        if(priority != 0) {
            sched_param sparam;
            sparam.sched_priority = priority;

            err = pthread_attr_setschedparam(&mTaskId.thread_attr, &sparam);
            assert(err == 0);
        }

        err = pthread_create(&mTaskId.thread_handle,
                             &mTaskId.thread_attr,
                             routine,
                             param);
        if(cpu != -1)
            GetAffinityConfig(cpu);
    }

    void Shadow (int cpu = -1) {
        GetAffinityConfig(cpu);
        return;
    }

    void Join() {
        pthread_cancel(mTaskId.thread_handle);
        pthread_join(mTaskId.thread_handle, NULL);
    }

    void Terminate() {
        pthread_detach(mTaskId.thread_handle);
        int old_state = 0;
        pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, &old_state);
        pthread_cancel(mTaskId.thread_handle);
    }

private:
    int GetAffinityConfig(int cpu) {
        cpu_set_t mask;
        cpu_set_t get;
        int num = sysconf(_SC_NPROCESSORS_CONF);
        //printf("system has %d processor(s)\n", num);
        CPU_ZERO(&mask);
        CPU_SET(cpu, &mask);
        if (pthread_setaffinity_np(mTaskId.thread_handle, sizeof(mask), &mask) < 0) {
            fprintf(stderr, "set thread affinity failed\n");
        }
        CPU_ZERO(&get);
        if (pthread_getaffinity_np(mTaskId.thread_handle, sizeof(get), &get) < 0) {
            fprintf(stderr, "get thread affinity failed\n");
        }
        for (int j = 0; j < num; j++) {
            if (CPU_ISSET(j, &get)) {
                //printf("thread data processing %s is running in processor %d\n", mName, j);
                break;
            }
        }

        return 0;
    }

    const char *mName;
    PthreadStruct mTaskId;
};

#endif
