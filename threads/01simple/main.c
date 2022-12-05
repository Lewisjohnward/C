
/* A thread is a single sequence stream within a process.
 *
 * Threads are not independent from each other unline processes. Threads
 * share code and data section and OS resources like open files & signals.
 *
 * Threads are a popular way to improve application through parallelism. E.g
 * in a browser, multiple tabs can be different threads. MS word uses multiple threads,
 * one to format the text and the other to process inputs etc.
 *
 * In C multithreading is not supported by the language standard.
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>

/* A normal C function that is executed as a thread
 * when its name is specified in pthread_create()
 *
 * gcc -o main main.c -lpthread
 */


void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Hello world\n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    /* int pthread_create(pthread)t *thread, const pthread_att_t *attr, void *(*start_routine)(void *), void *arg);
    * 1st arg thread id
    * 2nd arg attributes, if NULL default 
    * 3rd arg name of function to be executed for the created thread
    * 4th argument used to pass arguments to the function
    */
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    /* int pthread_join(pthread_t thread, void **value_ptr);
     * suspends execution of the calling thread until the target thread terminates
     * similar to wait() when forking
     */
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}
