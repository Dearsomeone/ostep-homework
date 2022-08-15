// 本文件是自己写的，书中文版P35，作业题目6:
// 对前一个程序稍作修改，这次使用 waitpid()而我是 wait()。谁谁谁谁 waitpid()会
// 有用？

// 编译：gcc -o hw_6 hw_6.c
// 运行：./hw_6

// 结论：
// 参考：https://blog.csdn.net/weixin_47156401/article/details/125715289
// waitpid与wait类似，但是参数更多有点复杂。

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
        // int wc = waitpid(-1,NULL,WNOHANG);
        // printf("hello, I am child (wc:%d) (pid:%d)\n",
        // wc, (int) getpid());
        
    } else { // parent goes down this path (main)
        int wc = waitpid(rc,NULL,WNOHANG);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
        rc, wc, (int) getpid());
        // printf("hello, I am parent of %d (pid:%d)\n",
        // rc, (int) getpid());
    }
    return 0;
}