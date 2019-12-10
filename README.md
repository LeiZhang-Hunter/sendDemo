#测试结果

多进程模式下对send的原子性进行测试

####第一个测试例子

```
gcc demoServer.c -o demoServer
gcc demoClient.c -o demoClient
```

单次发送33642个字节，开4个进程每个进程发送10000次，总计40000次，服务端总计收到字节close:1345680000,输出结果完全正确

