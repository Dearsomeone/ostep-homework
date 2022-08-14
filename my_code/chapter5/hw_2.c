// 本文件是自己写的，书中文版P35，作业题目2:
// 编写一个打开文件的程序（使用 open()系统调用），然后调用 fork()创建一个新进程。
// 子进程和父进程都可以访问 open()返回的文件描述符吗？当他们并发（即同谁）写入文件时，
// 会发生？

// 编译：gcc -o hw_2 hw_2.c
// 运行：./hw_2
// 查看结果：cat file

// 结论：
// 子进程和父进程都可以访问 open()返回的文件描述符
// 当它我并发（即同谁）写入文件时，可以正常运行，先后写入 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int fd = open("file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    assert(fd > -1);
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        int rc = write(fd, "hello world in child\n", 22);
        assert(rc == 22);
    } else { // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n",rc, (int) getpid());
        int rc = write(fd, "hello world in parent\n", 23);
        assert(rc == 23);
        close(fd);
    }
    return 0;
}