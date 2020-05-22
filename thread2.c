#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);
char message[] = "Hello World";
int run_now=1;

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
        }

    int print_count1 = 0;
    while(print_count1++ < 20) {
        if (run_now == 1) {
            //fflush(stdout);
            fputc('1',stdout);
            run_now = 2;
            }
        else {
            sleep(1);
        }
    }

    printf("Waiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
        }
    printf("Thread joined, it returned %s\n", (char *)thread_result);
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}


void *thread_function(void *arg) {
    int print_count2 = 0;
    while(print_count2++ < 20) {
        if (run_now == 2) {
            fputc('2',stdout);
            run_now = 1;
        }
        else {
            sleep(1);
        }
    }

    strcpy(message, "Bye!");
    pthread_exit("Thank you for the CPU time");
}