// 本文件是自己写的，书中文版P35，作业题目8:
// 编写一个程序，创建两个子进程，并使用 pipe()系统调用，将一个子进程的标准输
// 出连接到另一个子进程的标准输入。

// 编译：gcc -o hw_8 hw_8.c
// 运行：./hw_8

// 结论：
// 参考： https://dandelioncloud.cn/article/details/1534812573639929857
// 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // 创建管道
    int fd[2];
    int sp = pipe(fd);
    if (sp != 0) {
        // 创建管道失败
        return 0;
    }
    char buf[128];
    int r;
    char *msg = "this is a test\n";
    int pid1, pid2;
    pid1 = fork(); // create first child process
    if (pid1 < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid1 == 0) { // son process
        // p1子进程，写数据到管道
		// 关闭读端
		close(fd[0]);
		char *msg = "Hello world!\n";
		write(fd[1], msg, strlen(msg)); // 向管道写
		close(fd[1]); // 关闭写端
		printf("I am p1, I say \"hello world\" to p2.\n");
		return 0; // p1运行完直接退出；否则p1进程会运行pid_t p2 = fork()
    } else { // parent goes down this path (main)
        pid2 = fork();  // create second child process
        if (pid2 <0 ) {
            fprintf(stderr, "fork failed\n");
            exit(2);
        }
        else if (pid2 == 0) {
            // 等待p1进程完成写操作
            waitpid(pid1, NULL, 0);
            close(fd[1]); // 关闭写端
            char buf[1024];
            int len = read(fd[0], buf, 1024); // 从管道中读数据
            if (len > 0)
            {
                buf[len] = '\0';
                printf("I am p2, p1 say: %s\n", buf);
            }
            return 0;
        }
        else {
            waitpid(pid1, NULL, 0);
	        waitpid(pid2, NULL, 0);
            printf("hello, I am parent of %d and %d (pid:%d)\n", pid1, pid2, (int) getpid());
        }
    }
    return 0;
}