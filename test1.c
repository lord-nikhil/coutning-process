#include<stdio.h>
int main(void) {
    int fd[2];
    int depth = 0; /* keep track of number of generations from original */
    int i;
    pipe(fd);  /* create a pipe which will be inherited by all children */
    for(i=0; i<4; i++) {
        if(fork() == 0) {  /* fork returns 0 in the child */
            write(fd[1], &i, 1);  /* write one byte into the pipe */
            depth += 1;
        }
    }
    close(fd[1]);  /* exercise for the reader to learn why this is needed */
    if( depth == 0 ) { /* original process */
      i=0;
      while(read(fd[0],&depth,1) != 0)
        i += 1;
      printf( "%d total processes spawned", i*2);
    }

    return 0;
}
