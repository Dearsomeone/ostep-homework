// 本文件是自己写的，书中文版P35，作业题目5:
// 现在编写一个程序，在父进程中使用 wait()，等待子进程完成。 wait()返回什么？如
// 果你在子进程中使用 wait()会发生什么？

// 编译：gcc -o hw_5 hw_5.c
// 运行：./hw_5

// 结论：
// 父进程wait()返回的是子进程的PID
// 如果在子进程中使用 wait()会发生什么,返回值是-1
// 调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续往下执行）；
// 如果没有子进程了，函数立刻返回，返回-1；如果子进程都已经结束了，也会立即返回，返回-1。

// 总结wait的返回值：
// - 成功：返回被回收的子进程的id
// - 失败：-1 (所有的子进程都结束，调用函数失败)

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
        // printf("hello, I am child (pid:%d)\n", (int) getpid());
        int wc = wait(NULL);
        printf("hello, I am child (wc:%d) (pid:%d)\n",
        wc, (int) getpid());
        
    } else { // parent goes down this path (main)
        // int wc = wait(NULL);
        // printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
        // rc, wc, (int) getpid());
        printf("hello, I am parent of %d (pid:%d)\n",
        rc, (int) getpid());
    }
    return 0;
}