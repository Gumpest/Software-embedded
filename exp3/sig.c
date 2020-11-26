#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

void Child_handler(int signum){
    if (signum == SIGINT)printf("Ctrl_C has been Captured\n");
    if (signum == SIGTSTP)printf("Ctrl_Z has been Captured\n");
}
int main(void)
{
    pid_t pid_1 = fork();
    pid_t pid_2;

    // 判断是否正常
    if (pid_1 == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_1 == 0) // 返回0->子进程
    {
        printf("Child Process created pid = %d, ppid = %d\n", getpid(), getppid());
        signal(SIGTSTP, Child_handler);
        signal(SIGINT, Child_handler);
                
        pid_2 = fork(); // 创建 孙子进程
        if(pid_2 == -1){
            perror("fork");
            exit(EXIT_FAILURE);            
        }
        if (pid_2 == 0){
            printf("GrandSon Process created pid = %d, ppid = %d\n", getpid(), getppid());
            raise(SIGSTOP); // 停止孙子进程的执行
            
            exit(EXIT_SUCCESS);        
        }
        else{
            wait(&pid_2);
            printf("Receive STOP, GrandSon Process Dead\n");
            exit(EXIT_SUCCESS); 
        }

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
