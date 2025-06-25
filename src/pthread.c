#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RESULT 1000000000000000000LL

typedef struct {
    int base;
    int exponent;
    long long result;
    int thread_id;
} ThreadArgs;

long long calculate_power(int base, int exponent) {
    if (exponent < 0) {
        return -2;
    }
    long long res = 1;
    for (int i = 0; i < exponent; i++) {
        if (base > 0) {
            if (res > MAX_RESULT / base) {
                return -1;
            }
        } else if (base < 0) {
            if (res < -MAX_RESULT / base) {
                if (res > 0 && -base > 0 && res > MAX_RESULT / -base) {
                    return -1;
                }
                if (res < 0 && -base > 0 && res < -MAX_RESULT / -base) {
                    return -1;
                }
            }
        }
        res *= base;
    }
    return res;
}

void *thread_ab_func(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    printf("Thread %d (A^B) dibuat...\n", args->thread_id);
    if ((args->base == 0 && args->exponent < 0) || (args->base == 0 && args->exponent == 0)) {
        args->result = 0;
    } else {
        args->result = calculate_power(args->base, args->exponent);
        printf("Thread %d selesai.\n", args->thread_id);
    }
    return NULL;
}

void *thread_ba_func(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    printf("Thread %d (B^A) dibuat...\n", args->thread_id);
    if ((args->base == 0 && args->exponent < 0) || (args->base == 0 && args->exponent == 0)) {
        args->result = 0;
    } else {
        args->result = calculate_power(args->base, args->exponent);
        printf("Thread %d selesai.\n", args->thread_id);
    }
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
    if (scanf("%d", &A) != 1) {
        fprintf(stderr, "Input A tidak valid! Harus berupa bilangan bulat.\n");
        free(args_ab);
        free(args_ba);
        return 1;
    }
    printf("Masukkan angka B: ");
    if (scanf("%d", &B) != 1) {
        fprintf(stderr, "Input B tidak valid! Harus berupa bilangan bulat.\n");
        free(args_ab);
        free(args_ba);
        return 1;
    }

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
    if ((args_ab->base == 0 && args_ab->exponent < 0) || (args_ab->base == 0 && args_ab->exponent == 0)) {
        if (args_ab->base == 0 && args_ab->exponent < 0)
            printf("Thread 1: %d^%d = tidak terdefinisi\n", args_ab->base, args_ab->exponent);
        else
            printf("Thread 1: %d^%d = tidak terdefinisi\n", args_ab->base, args_ab->exponent);
    } else if (args_ab->result == -2) {
        printf("Thread 1: %d^%d = tidak terdefinisi dalam bilangan bulat\n", args_ab->base, args_ab->exponent);
    } else if (args_ab->result == -1) {
        printf("Thread 1: %d^%d = hasil terlalu besar untuk ditampilkan\n", args_ab->base, args_ab->exponent);
    } else {
        printf("Thread 1: %d^%d = %lld\n", args_ab->base, args_ab->exponent, args_ab->result);
    }
    if ((args_ba->base == 0 && args_ba->exponent < 0) || (args_ba->base == 0 && args_ba->exponent == 0)) {
        if (args_ba->base == 0 && args_ba->exponent < 0)
            printf("Thread 2: %d^%d = tidak terdefinisi\n", args_ba->base, args_ba->exponent);
        else
            printf("Thread 2: %d^%d = tidak terdefinisi\n", args_ba->base, args_ba->exponent);
    } else if (args_ba->result == -2) {
        printf("Thread 2: %d^%d = tidak terdefinisi dalam bilangan bulat\n", args_ba->base, args_ba->exponent);
    } else if (args_ba->result == -1) {
        printf("Thread 2: %d^%d = hasil terlalu besar untuk ditampilkan\n", args_ba->base, args_ba->exponent);
    } else {
        printf("Thread 2: %d^%d = %lld\n", args_ba->base, args_ba->exponent, args_ba->result);
    }

    free(args_ab);
    free(args_ba);

    return 0;
}
