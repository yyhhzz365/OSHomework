# include <pthread.h>
# include <stdio.h>

void* printHello(void* arg) {
    printf("Hello from thread %d\n");
    return NULL;
}

void* printWorld(void* arg) {
    printf("World from thread %d\n");
    return NULL;
}

int main(){
    pthread_t t1, t2;
    if(pthread_create(&t1, NULL, printHello, NULL)!= 0) {
        perror("Failed to create thread 1");
        return 1;
    }
    if(pthread_create(&t2, NULL, printWorld, NULL)!= 0) {
        perror("Failed to create thread 2");
        return 1;
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
