#include "lab2.h"
#include <cstring>
#include <semaphore.h>
//
// lab2 code should be located here!
//

#define NUMBER_OF_THREADS 12

// thread identifiers
pthread_t tid[NUMBER_OF_THREADS];
// critical section lock
pthread_mutex_t lock, lock2;
// semaphores for sequential threads
sem_t semH, semI, semM;

int err;

unsigned int lab2_thread_graph_id() 
{
    return 13;
}

const char* lab2_unsynchronized_threads()
{
    return "cdef";
}

const char* lab2_sequential_threads()
{
    return "him";
}


void* thread_b(void* ptr);
void* thread_c(void* ptr);
void* thread_d(void* ptr);
void* thread_e(void* ptr);
void* thread_f(void* ptr);
void* thread_g(void* ptr);
void* thread_h(void* ptr);
void* thread_i(void* ptr);
void* thread_k(void* ptr);
void* thread_m(void* ptr);
void* thread_n(void* ptr);


void* thread_a(void* ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "a" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    err = pthread_create(&tid[1], NULL, thread_b, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[2], NULL, thread_c, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    // wait for thread C to finish
    pthread_join(tid[2], NULL);

    return  ptr;
}

void* thread_b(void* ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "b" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    
    return ptr;
}

void* thread_c(void* ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "c" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    // wait for thread B to finish
    pthread_join(tid[1], NULL);

    err = pthread_create(&tid[3], NULL, thread_e, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[4], NULL, thread_d, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[5], NULL, thread_f, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "c" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    // wait for thread D to finish
    pthread_join(tid[4], NULL);

    return ptr;
}

void* thread_d(void* ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "d" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    // wait for thread E to finish
    pthread_join(tid[3], NULL);
    // wait for thread F to finish
    //pthread_join(tid[5], NULL);

    err = pthread_create(&tid[6], NULL, thread_k, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[7], NULL, thread_m, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[9], NULL, thread_h, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "d" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    
    err = pthread_create(&tid[10], NULL, thread_i, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
    err = pthread_create(&tid[8], NULL, thread_g, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;


    // wait for thread G to finish
    pthread_join(tid[8], NULL);
    // wait for thread K to finish
    pthread_join(tid[6], NULL);

    sem_post(&semH);
    // wait for thread M to finish
    pthread_join(tid[7], NULL);
    //wait for thread H to finish
    pthread_join(tid[9], NULL);
    //wait for thread I to finish
    pthread_join(tid[10], NULL);
    return ptr;
}

void* thread_e(void* ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "e" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }

    // wait for thread F to finish
    pthread_join(tid[5], NULL);

    return ptr;
}

void* thread_f(void* ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "f" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }

    return ptr;
}

void* thread_g(void* ptr)
{
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "g" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

void* thread_h(void* ptr)
{
    // perform computations
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "h" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    
    
    // perform computations
        for (int i = 0; i < 3; ++i) {
        sem_wait(&semH);
        pthread_mutex_lock(&lock);
        std::cout << "h" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
        sem_post(&semI);
    }
    
    //sem_post(&semI);
    return ptr;
}

void* thread_m(void* ptr)
{
    // perform computations
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "m" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }

    // perform computations
    for (int i = 0; i < 3; ++i) {
        sem_wait(&semM);
        pthread_mutex_lock(&lock);
        std::cout << "m" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
        sem_post(&semH);
    }

    return ptr;
}

void* thread_i(void* ptr)
{
    
    // perform computations
    for (int i = 0; i < 3; ++i) {
        sem_wait(&semI);
        pthread_mutex_lock(&lock);
        std::cout << "i" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
        sem_post(&semM);
    }
    
    return ptr;
}

void* thread_k(void* ptr)
{
    // perform computations
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "k" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

void* thread_n(void* ptr)
{
    // perform computations
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&lock);
        std::cout << "n" << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
    return ptr;
}

int lab2_init()
{
    // initilize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        std::cerr << "Mutex init failed" << std::endl;
        return 1;
    }
    if (pthread_mutex_init(&lock2, NULL) != 0) {
        std::cerr << "Mutex init failed" << std::endl;
        return 1;
    }
    // initialize semaphores
    // THIS CODE WILL NOT RUN ON MacOS!
    // MacOS doesn't support unnamed semaphores, so named semaphores should be used instead
    if (sem_init(&semH, 0, 0) != 0) {
        std::cerr << "Semaphore #1 init failed" << std::endl;
        return 1;
    }
    if (sem_init(&semI, 0, 0) != 0) {
        std::cerr << "Semaphore #2 init failed" << std::endl;
        return 1;
    }
    if (sem_init(&semM, 0, 0) != 0) {
        std::cerr << "Semaphore #2 init failed" << std::endl;
        return 1;
    }

    // start the first thread
    err = pthread_create(&tid[0], NULL, thread_a, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    // ... and wait for it to finish
    pthread_join(tid[0], NULL);

    err = pthread_create(&tid[11], NULL, thread_n, NULL);
    if (err != 0)
        std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

    // wait for thread N to finish
    pthread_join(tid[11], NULL);

    // free resources
    pthread_mutex_destroy(&lock);
    sem_destroy(&semH);
    sem_destroy(&semI);
    sem_destroy(&semM);
    std::cout << std::endl;
    // success
    return 0;
}
