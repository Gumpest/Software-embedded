#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>
#include <pthread.h>  
#include <semaphore.h> 
#include <sys/syscall.h> 
#define gettid() syscall(__NR_gettid)  

void *thread_function_read(void *arg);
void *thread_function_write(void *arg);
pthread_mutex_t write_mutex;  
#define NUM_READER 6  
#define NUM_WRITER 3   
int reader_counter = 0;
int data = 1;

int main(){  
    int res, i, j;
    pthread_t readers[NUM_READER], writers[NUM_WRITER]; 
    void *thread_result;
    
    // 写互斥锁
    res = pthread_mutex_init(&write_mutex, NULL);     
    if (res != 0){
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    // 读者
    for(i = 0; i < NUM_READER; i++){  
        res = pthread_create(&readers[i], NULL, thread_function_read, NULL);
        if (res != 0){
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }  

    // 写者
    for(j = 0; j < NUM_WRITER; j++){  
        res = pthread_create(&writers[j], NULL, thread_function_write, NULL);
        if (res != 0){
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }  
    }  

    pthread_mutex_destroy(&write_mutex);
    exit(EXIT_SUCCESS);
}  

void *thread_function_read(void *args){          
    reader_counter++;   
    if(reader_counter == 1){  
        pthread_mutex_lock(&write_mutex);  
    }  

    printf("Reader_id: %ld, I'm reading the Chapter %d\n", gettid(), data);

    reader_counter--;  
    if(reader_counter == 0){  
        pthread_mutex_unlock(&write_mutex);  
    }
    pthread_exit("read exit\n");  
}  

void *thread_function_write(void *args){        
    pthread_mutex_lock(&write_mutex);  
 
    data = data + 1; 
    printf("Writer_id: %ld, I'm writing the Chapter %d\n", gettid(), data);  
       

    pthread_mutex_unlock(&write_mutex); 
    pthread_exit("write exit\n");  
} 
