#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 10
#define SHM_NAME "/buffer_shm"

typedef unsigned char int1byte;

typedef struct {
    int1byte buffer[SIZE]; 
    int count;    
    int total;      
} shared_data;

int main() {
    srand(time(NULL));

    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    if (ftruncate(fd, sizeof(shared_data)) == -1) {
        perror("ftruncate");
        return 1;
    }

    shared_data *shm = mmap(NULL, sizeof(shared_data),
                             PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    shm->count = 0;
    shm->total = 0;

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // =========================
        // Consumer
        // =========================
        while (1) {
            if (shm->count > 0) {
                int val = shm->buffer[0];

                // Dịch mảng sau khi đọc
                for (int i = 1; i < shm->count; i++)
                    shm->buffer[i - 1] = shm->buffer[i];

                shm->count--;
                shm->total += val;

                printf("Consumer read: %d, total=%d\n", val, shm->total);

                if (shm->total > 100)
                    break;
            } else {
                usleep(100000);
            }
        }

        munmap(shm, sizeof(shared_data));
        close(fd);
        shm_unlink(SHM_NAME);
        exit(0);
    } else {
        // =========================
        // Producer
        // =========================
        while (1) {
            if (shm->count < SIZE) {
                int num = rand() % 11 + 10;  // [10,20]
                shm->buffer[shm->count++] = (int1byte)num;
                printf("Producer wrote: %d\n", num);
                usleep(100000);
            }

            if (shm->total > 100)
                break;
        }

        wait(NULL);
        munmap(shm, sizeof(shared_data));
        close(fd);
    }

    return 0;
}
