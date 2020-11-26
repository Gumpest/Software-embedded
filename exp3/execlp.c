#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("execlp() create a new shell process\n");
    execlp("ls", "ls", "-l", NULL);
    
    exit(0);
}