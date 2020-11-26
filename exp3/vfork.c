#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid_1;
    pid_t pid_2;
    int sum = 100;

    // 判断是否正常
    if ((pid_1=vfork()) == -1){
        perror("vfork");
        exit(EXIT_FAILURE);
    }

    else if (pid_1 == 0) // 返回0->子进程
    {
        sum += 500;
        printf("Child Process created pid = %d, ppid = %d\n", getpid(), getppid());
        printf("sum = %d \n\n", sum);    
        
        // 创建 孙子进程
        if((pid_2=vfork()) == -1){
            perror("vfork");
            exit(EXIT_FAILURE);            
        }
        if (pid_2 == 0){
            sum = sum + 200;
            printf("GrandSon Process created pid = %d, ppid = %d\n", getpid(), getppid());
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
        sum += 1000;
        printf("Parent Process created pid = %d, ppid = %d\n", getpid(), getppid());
        printf("sum = %d \n\n", sum);
        exit(EXIT_SUCCESS);;
    }
}
