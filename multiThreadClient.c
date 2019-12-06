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
#include <pthread.h>

#define WORK_NUM 2
int run = 1;

int writeBuf(int fd,char* buf,size_t len)
{
    struct iovec iov[1];
    iov[0].iov_len = len;
    iov[0].iov_base = buf;
    return writev(fd,iov,1);
}

int socket_fd;

void* threadProc(void* arg)
{
    int count = 0;
    while (1)
    {
        uint32_t data = (count);
        size_t res = send(socket_fd,&data,sizeof(data),0);
        printf("%ld\n",res);
        if(count == 10)
        {
            break;
        }
        count++;
    }
}

int main()
{
    int i = 0;

    socket_fd = socket(AF_INET,SOCK_STREAM,0);

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
    pthread_t thread_id[WORK_NUM];

    sigset_t set;
    sigset_t old_set;
    sigfillset(&set);
    sigprocmask(SIG_BLOCK,&set,&old_set);


    for(i = 0;i<WORK_NUM;i++) {
        //线程
        pthread_create(&thread_id[i],NULL,threadProc,NULL);
    }

    //wait等待子线程结束
    for(i=0;i<WORK_NUM;i++)
    {
        pthread_join(thread_id[i],NULL);
    }

    close(socket_fd);
    return 0;
}

