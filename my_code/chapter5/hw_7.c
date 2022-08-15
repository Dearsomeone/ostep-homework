// 本文件是自己写的，书中文版P35，作业题目7:
// 编写一个创建子进程的程序，然后在子进程中关闭标准输出（STDOUT_FILENO）。
// 如果子进程在关闭描述符后调用 printf()打印输出，会发生什么？

// 编译：gcc -o hw_7 hw_7.c
// 运行：./hw_7

// 结论：
// printf打印输出不会显示在屏幕上，而是重定向到文件hw7.output中。cat可以查看。

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process),redirect standard output to a file
        close(STDOUT_FILENO);
        open("./hw7.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
    }
    return 0;
}