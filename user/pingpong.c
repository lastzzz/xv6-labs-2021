#include "kernel/types.h"
#include "user/user.h"


int
main(int argc, char* argv[]){

    int fd1[2], fd2[2];
    char buf[]  = {'a'};
    if(pipe(fd1) < 0) fprintf(2, "pipe create fail\n");
    if(pipe(fd2) < 0) fprintf(2, "pipe create fail\n");
    int pid = fork();
    if(pid == 0){
        
        read(fd2[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(fd1[1], buf, 1);
        exit(0);
    }else if(pid > 0){
        
        write(fd2[1], buf, 1);
        read(fd1[0], buf, 1);
        printf("%d: received pong\n", getpid());
        wait(0);

        exit(0);
    }else{
        exit(1);
    }
   

}