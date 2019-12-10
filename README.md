#测试结果

多进程模式下对send的原子性进行测试

####第一个测试例子

```
gcc demoServer.c -o demoServer
gcc demoClient.c -o demoClient
```

单次发送33643个字节，开4个进程每个进程发送10000次，总计40000次，服务端总计收到字节close:1345720000,输出结果完全正确

但是内容出现了混乱，原本有序的css 出现了

ine-height:0@�D{�Ubuf:!important}#csdn_tool_otherPlace .pull-right .gi

这一类错误的字节

说明send写入出现了乱序问题，send不是原子的