// 本文件是自己写的，书中文版P35，作业题目1:
// 编写一个调用 fork()的程序。谁调用 fork()之前，让主进程访问一个变量（例如 x）
// 并将其值设置为某个值（例如 100）。子进程中的变量有什么值？当子进程和父进程都改变
// x 的值时，变量会发生什么？

// 编译：gcc -o hw_1 hw_1.c
// 运行：./hw_1

// 结论：
// 在子进程中变量初始值继承的父进程的，可以修改父进程的变量, 但是该修改在父进程中是不可见的。
// 在父进程中可以修改父进程的变量。 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int x = 100;
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("In child (pid:%d), the x = %d\n", (int) getpid(), x);
        x = 200;
        printf("After change in child, the x = %d in child (pid:%d)\n", x, (int) getpid());
    } else { // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n",rc, (int) getpid());
        printf("After change in child, the x = %d in parent (pid:%d)\n", x, (int) getpid());
        x = 200;
        printf("After change in parent, the x = %d in parent (pid:%d)\n", x, (int) getpid());
    }
    return 0;
}