#include "kernel/types.h"
#include "user/user.h"


void primes(int p[2]){
    close(p[1]);
    int prime, j;
    int p1[2];
    
    if(read(p[0], &prime, 4) == 0){
        close(p[0]);
        fprintf(2, "read error\n");
        exit(1);
    }
    printf("prime %d\n", prime);
    pipe(p1);
    int fo = fork();
    if(fo == 0){
        close(p[0]);
        primes(p1);
    }else if(fo > 0){
        close(p1[0]);
        while(1){   
            if(read(p[0], &j, 4) == 0) break;
            if((j % prime) != 0) write(p1[1], &j, 4);
        }
        close(p[0]);
        close(p1[1]);
        wait(0);
    }else{
        exit(1);
    }
}






int main(int argc, char* argv[]){
    int fd[2];
    pipe(fd);
    int f = fork();
    if(f == 0){
        primes(fd);
    }else if(f > 0){
        close(fd[0]);
        for(int i = 2; i <= 35; i++){
            write(fd[1], &i, 4);
        }
        close(fd[1]);
        wait(0);

    }else{
        exit(1);
    }
    exit(0);
}