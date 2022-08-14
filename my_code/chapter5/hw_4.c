// 本文件是自己写的，书中文版P35，作业题目4:
// 编写一个调用 fork()的程序，然后调用某种形式的 exec()来运行程序/bin/ls。看看是
// 否可以尝试 exec()的所有变体， 包括 execl()、 execle()、 execlp()、 execv()、 execvp()和 execvP()。
// 为什么同样的基本调用会有这谁多变种？

// 编译：gcc -o hw_4 hw_4.c
// 运行：./hw_4

// 结论：
// 该命令这么多变种的原因就是接收不同的参数。

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int x = 100;
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("/bin/ls"); // program: "ls" 
        myargs[1] = strdup("."); // argument: file to list
        myargs[2] = NULL; // marks end of array
        // execvp(myargs[0], myargs); // runs ls
        execl("/bin/ls", "ls", "-al", "/root", (char *)0); // runs ls
        printf("this shouldn't print out");
        
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
        rc, wc, (int) getpid());
    }
    return 0;
}