#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/uio.h>
#include <fcntl.h>

#define EVENT_NUM 1

//设置套接字为非阻塞
int set_fd_nonblock(int fd)
{
    int val;
    int res;
    val = fcntl(fd,F_GETFL,0);
    if(val == -1)
    {
        printf("%d\n;%s",errno,strerror(errno));
        return  -1;
    }

    res = fcntl(fd,F_SETFL,(val | O_NONBLOCK));
    if(res == -1)
    {
        printf("%d\n;%s",errno,strerror(errno));
        return  -1;
    }
}

int run = 1;

int readBuf(int fd,char* buf,size_t buf_len);

int main()
{
    size_t read_size;
    int res;
    int client_fd;
    int fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr,client_addr;
    int n;
    socklen_t len;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_addr.sin_port = htons(5000);
    server_addr.sin_family = AF_INET;
    //绑定端口
    res = bind(fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(res < 0)
    {
        printf("errno:%d,errno:%s\n",errno,strerror(errno));
        exit(-1);
    }
    //监听端口
    res = listen(fd,60);
    if(res < 0)
    {
        printf("errno:%d,errno:%s;file:%s;line:%d\n",errno,strerror(errno),__FILE__,__LINE__);
        exit(-1);
    }
    char buf[BUFSIZ];
    //计数器
    int count = 0;

    int i = 0;

    struct epoll_event event;
    //集合
    struct epoll_event eventCollect[EVENT_NUM];

    //创建一个epoll集合
    int epoll_fd = epoll_create(EVENT_NUM);

    int file_fd;
    unlink("cache2.log");
    file_fd = open("cache2.log",O_WRONLY|O_CREAT,S_IRWXU);
    printf("file_fd:%d\n",file_fd);

    //将监听套接字加入
    event.data.fd = fd;
    event.events = EPOLLIN|EPOLLET;

    //把监听的套接字加入集合
    res = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&event);

    while(run)
    {
        n = epoll_wait(epoll_fd,eventCollect,3,-1);
        if(n < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
        }else if(n > 0)
        {
            for(i = 0;i<n;i++)
            {
                //server
                if(eventCollect[i].data.fd == fd)
                {
                    len = sizeof(client_addr);
                    client_fd = accept(eventCollect[i].data.fd,(struct sockaddr *)&client_addr,&len);
                    if(client_fd < 0)
                    {
                        continue;
                    }else{
                        bzero(&event,sizeof(event));
                        event.data.fd = client_fd;
                        event.events = EPOLLIN|EPOLLET;
                        res = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_fd,&event);
                        set_fd_nonblock(client_fd);
                    }
                }else{
                    //client
                    client_fd = eventCollect[i].data.fd;
                    bzero(buf,sizeof(buf));
//                    read_size = recv(client_fd,buf,sizeof(buf),0);
                    while((read_size = readBuf(client_fd,buf,sizeof(buf)))) {
                        if (read_size == -1) {
                            if (errno == EINTR) {
                                continue;
                            } else if(errno == EAGAIN) {
                                break;
                            }else{
                                printf("errno:%d,errno:%s\n", errno, strerror(errno));
                            }
                        } else if (read_size > 0) {
                            //数据报可能出现粘包问题
                            //查看接收结果

//                            write(file_fd,buf,sizeof(buf));
                            count += read_size;
                            int res = write(file_fd,buf,read_size);
                            printf("%d\n",res);
                            bzero(buf,read_size);
                        }
                    }

                    if(read_size == 0) {
                        //客户端套接字已经关闭了
                        printf("size:%d\n", count);

                        count = 0;

                        close(client_fd);
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

int readBuf(int fd,char* buf,size_t buf_len)
{
    struct iovec iov[1];
    ssize_t n;
    iov[0].iov_base = buf;
    iov[0].iov_len = buf_len;
    return readv(fd,iov,1);
}
