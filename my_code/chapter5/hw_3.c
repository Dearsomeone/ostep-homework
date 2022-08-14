// 本文件是自己写的，书中文版P35，作业题目3:
// 使用 fork()编写另一个程序。子进程应打印“hello”，父进程应打印“goodbye”。你
// 应该尝试我保子进程始终先打印。你能否不在父进程调用 wait()而做到这一点呢？

// 编译：gcc -o hw_3 hw_3.c
// 运行：./hw_3

// 结论：
// 在子进程中变量初始值继承的父进程的，可以修改父进程的变量, 但是该修改在父进程中是不可见的。
// 在父进程中可以修改父进程的变量。 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello ");
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
        printf("goodbye\n");
    }
    return 0;
}