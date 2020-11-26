#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid_1 = fork();
    pid_t pid_2;
    int sum = 100;

    // 判断是否正常
    if (pid_1 == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_1 == 0) // 返回0->子进程
    {
        printf("Child Process created pid = %d, ppid = %d\n", getpid(), getppid());
        sum = sum + 500;
        printf("sum = %d \n\n", sum);
        
        pid_2 = fork(); // 创建 孙子进程
        if(pid_2 == -1){
            perror("fork");
            exit(EXIT_FAILURE);            
        }
        if (pid_2 == 0){
            printf("GrandSon Process created pid = %d, ppid = %d\n", getpid(), getppid());
            sum = sum + 200;
            printf("sum = %d \n\n", sum);
            exit(EXIT_SUCCESS);        
        }
        else{
            exit(EXIT_SUCCESS); 
        }

        exit(EXIT_SUCCESS);


    }
    else  // 父进程
    {
        printf("Parent Process created pid = %d, ppid = %d\n", getpid(), getppid());
        sum = sum + 1000;
        printf("sum = %d \n\n", sum);
        exit(EXIT_SUCCESS);
    }
}
