#测试结果

多进程 和 多线程模型下 对 同一个tcp套接字使用 send 或者 writev 都不是原子的

####第一个测试例子

```
gcc demoServer.c -o demoServer
gcc demoClient.c -o demoClient
```

结果发现服务端本来应该接收到176个字节，结果为176，说明无字节数问题

####第二个测试例子
```
gcc demoClientServerv.c -o demoServerv
gcc demoClientWritev.c -o demoClientv
```

结果发现服务端本来应该接收到176个字节，结果为176，说明无字节数问题


又继续测试了多线程版本
```
gcc demoClientServerv.c -o demoServer
gcc multiThreadClient.c -o demoClient -lpthread
```

结果发现服务端本来应该接收到176个字节，结果为176，说明无字节数问题