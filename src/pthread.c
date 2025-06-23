#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int base;
    int exponent;
    long long result;
    int thread_id;
} ThreadArgs;

long long calculate_power(int base, int exponent) {
    long long res = 1;
    for (int i = 0; i < exponent; i++) {
        res *= base;
    }
    return res;
}

void *thread_ab_func(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    
    printf("Thread %d (A^B) dibuat...\n", args->thread_id);
    
    args->result = calculate_power(args->base, args->exponent);
    
    printf("Thread %d selesai.\n", args->thread_id);
    
    return NULL;
}

void *thread_ba_func(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    
    printf("Thread %d (B^A) dibuat...\n", args->thread_id);
    
    args->result = calculate_power(args->base, args->exponent);
    
    printf("Thread %d selesai.\n", args->thread_id);
    
    return NULL;
}

int main() {
    int A, B;
    pthread_t tid[2];
    
    ThreadArgs *args_ab = (ThreadArgs *)malloc(sizeof(ThreadArgs));
    ThreadArgs *args_ba = (ThreadArgs *)malloc(sizeof(ThreadArgs));

    if (args_ab == NULL || args_ba == NULL) {
        fprintf(stderr, "Gagal mengalokasikan memori untuk argumen thread.\n");
        return 1;
    }

    printf("Masukkan angka A: ");
    scanf("%d", &A);
    printf("Masukkan angka B: ");
    scanf("%d", &B);

    args_ab->base = A;
    args_ab->exponent = B;
    args_ab->thread_id = 1;

    args_ba->base = B;
    args_ba->exponent = A;
    args_ba->thread_id = 2;

    if (pthread_create(&tid[0], NULL, thread_ab_func, (void *)args_ab) != 0) {
        fprintf(stderr, "Gagal membuat Thread 1.\n");
        free(args_ab);
        free(args_ba);
        return 1;
    }

    if (pthread_create(&tid[1], NULL, thread_ba_func, (void *)args_ba) != 0) {
        fprintf(stderr, "Gagal membuat Thread 2.\n");
        pthread_join(tid[0], NULL);
        free(args_ab);
        free(args_ba);
        return 1;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    printf("\n--- HASIL KALKULASI ---\n");
    printf("Thread 1: %d^%d = %lld\n", args_ab->base, args_ab->exponent, args_ab->result);
    printf("Thread 2: %d^%d = %lld\n", args_ba->base, args_ba->exponent, args_ba->result);

    free(args_ab);
    free(args_ba);

    return 0;
}
