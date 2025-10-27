#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid = -1; 

void handle_sigint(int sig) {
    if (child_pid > 0) {
        kill(child_pid, SIGINT);
        printf("\ncount.sh has stopped\n");
    }
}

int main() {
    printf("Welcome to IT007, I am 24522016!\n");

    signal(SIGINT, handle_sigint);

    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {

        execl("./count.sh", "count.sh", "120", NULL);
        perror("execl"); 
        exit(1);
    } else {

        int status;
        waitpid(child_pid, &status, 0);
    }

    return 0;
}
