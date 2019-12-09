#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/uio.h>

#define WORK_NUM 4
int run = 1;

int writeBuf(int fd,char* buf,size_t len)
{
    struct iovec iov[1];
    iov[0].iov_len = len;
    iov[0].iov_base = buf;
    return writev(fd,iov,1);
}

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
                ssize_t res = writeBuf(socket_fd,(char*)&data,sizeof(data));
                if(res < 0)
                {
                    printf("%d;%s\n",errno,strerror(errno));
                }

                if(count == 10)
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
    printf("%s\n","end");
    return 0;
}

