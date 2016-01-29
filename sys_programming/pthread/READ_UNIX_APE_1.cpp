/*******************************************************************************
FileName: READ_UNIX_APE_1.cpp
*******************************************************************************/
/*
 * chapter 12. pthread attr
 * */
//pthread_attr_t at; //结构修改线程默认属性，并把这些属性与创建的线程关联起来
//int pthread_attr_init(&at);
//int pthread_attr_destroy(&at);
/*互斥量属性：
 * 1.共享属性，进程共享互斥量属性设置为PTHREAD_PROCESS_PRIVATE,多进程共享互斥量为PTHREAD_PROCESS_SHARED
 * 2.互斥量健壮属性
 * 3.类型属性*/
