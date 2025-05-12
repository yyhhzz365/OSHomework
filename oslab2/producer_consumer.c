
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCT_NUM 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

void* producer(void* arg) {
    for (int i = 0; i < PRODUCT_NUM; i++) {
        usleep(rand() % 1000000);    //随机延迟
        pthread_mutex_lock(&mutex);  
        while ((in + 1) % BUFFER_SIZE == out) {   //如果in+1==out说明缓冲区满了
            pthread_cond_wait(&empty, &mutex);    //如果满了生产者线程将阻塞，等待empty
        }
        buffer[in] = rand() % 100;
        printf("Producer produced: %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;
        pthread_cond_signal(&full);       //通知消费者有产品
        pthread_mutex_unlock(&mutex);     
    }
}

void* consumer(void* arg) {
    for (int i = 0; i < PRODUCT_NUM; i++) {
        usleep(rand() % 1000000);
        pthread_mutex_lock(&mutex);  
        while (in == out) {         // 是否空，如果空了消费者线程阻塞等待full
            pthread_cond_wait(&full, &mutex);
        }
        printf("Consumer consumed: %d\n", buffer[out]);
        out = (out + 1) % BUFFER_SIZE;
        pthread_cond_signal(&empty);  // 通知生产者缓冲区有空位
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    srand(time(NULL));

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
