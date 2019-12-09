#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

#define WORK_NUM 4
int run = 1;
#define SEND_COUNT 1000
int main()
{
    int i = 0;
    pid_t pid;
    pid_t arr[4];
    int count = 0;
    int status;

    int socket_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = connect(socket_fd,(struct sockaddr*)&addr,sizeof(addr));
    if(res < 0)
    {
        printf("%d;%s\n",errno,strerror(errno));
        exit(-1);
    }

    for(i = 0;i<WORK_NUM;i++) {
        pid = fork();
        sigset_t set;
        sigset_t old_set;
        sigfillset(&set);
        sigprocmask(SIG_BLOCK,&set,&old_set);
        //子进程
        if(pid == 0)
        {
            while (1)
            {
                uint32_t data = (count);
                size_t res = send(socket_fd,&data,sizeof(data),0);
                printf("%ld\n",res);
                if(count == SEND_COUNT)
                {
                    break;
                }
                count++;
            }
            _exit(0);
        }else if(pid > 0)
        {
            arr[i] = pid;
        }
    }

    //wait等待子进程执行完毕
    for(i=0;i<WORK_NUM;i++)
    {
        waitpid(arr[i],&status,-1);
    }
    return 0;
}
