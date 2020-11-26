#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main(void)
{
    pid_t pid_1 = fork();
    pid_t pid_2;
    char *args[] = {"echo", "A new process Get\n", NULL};

    // 判断是否正常
    if (pid_1 == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if (pid_1 == 0) // 返回0->子进程
    {
        printf("Child Process created pid = %d, ppid = %d\n", getpid(), getppid());
        execve("/bin/echo", args, NULL);
        exit(EXIT_SUCCESS);


    }
    else  // 父进程
    {
        printf("Parent Process created pid = %d, ppid = %d\n", getpid(), getppid());
        wait(&pid_1);
        printf("Child Process OVER!\n");
        exit(EXIT_SUCCESS);
    }
}
