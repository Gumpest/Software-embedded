#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main(void)
{
    pid_t pid;
    pid_t cpid;
    int status;

    // 判断是否正常
    if ((pid = fork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) // 返回0->子进程
    {
        printf("Child Process created pid = %d, ppid = %d\n", getpid(), getppid());
        execl("./execlp", "execlp", NULL);
        printf("error!\n");

    }
    else  // 父进程
    {
        printf("Parent Process created pid = %d, ppid = %d\n", getpid(), getppid());
        cpid = wait(&status);
        if(WIFEXITED(status))printf("Child Process OVER!\n");
        else puts("error 2!\n");
    }
    
    exit(EXIT_SUCCESS);
}
