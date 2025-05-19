1. fork代码验证
- 结果分析
  - 假设父进程为P0，fork()创建子进程C0
  - 进入子进程C0，此时value+=15,**变为20并输出**，父进程P0 value还是不变，会在当子进程结束后输出value为5。第一个循环结束，进入第二个循环
  - fork()创建子进程C1，C1继承父进程C0的value=15，并在此基础上继续+15,**C1中value变为35并输出**。C0和P0中value还分别是20和5，会在各自的子进程结束后输出value
  - 循环结束，C0子进程C1结束，**C0显示parent:value=20**，然后exit。**P0再显示parent:value=5**
- ![alt text](image\image.png)
2. pipe代码
   - ``pipe(pipe1)``和``pipe(pipe2)``创建两对管道，分别用于父子进程通信
   - 子进程关闭不需要的管道端pipe1[1],pipe2[0]，因为子进程只从 pipe1[0] 读取数据，pipe2[1] 写数据。每次pipe1[0]读取后数据加1写入pipe2[1]直到数据大于9，最后关闭
   - 父进程同理关闭pipe1[0],pipe2[1]...
   - 父进程从1开始发送数据，子进程接收后+1再返回父进程，父进程打印子进程返回的数据，每次加1直到10
- ![alt text](image\7639fcb50e17524f09fed7cc1713d5d.png)
3. function代码
- ``fork()``创建两个子进程，分别计算fx和fy，父进程等待两个结果计算并打印fx(x)+fy(y)的结果
- ![alt text](image\3.png)