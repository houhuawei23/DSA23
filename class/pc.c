/*
模拟生产者-消费者问题
1 建立1个生产者进程，5个消费者进程
2 通过操作同一个文件来建立一个共享缓存区
3 生产者进程依次向缓冲区文件写入整数 0,1,2,...,499
4 每个消费者程从缓冲区文件中读取 100 个数，每读取一个数字就打印到标准输出上
5 缓冲区最多只能保存 10 个数，即缓冲区文件中最多存放 10
所利用的系统调用如下：
sem_t* sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_unlink(const char *name);
*/

int main()
{
    if (fork()) // 生产者进程 父进程
    {
        // 只用了名字和初值两个参数
        // empty为正数时，表示缓冲区剩余空间的大小
        // empty为负数时，表示等待写缓冲区的进程数
        // 缓冲区大小为10，所以empty初始值为10
        // 生产者每次生产一个数，缓冲区剩余空间减小1，empty就减1
        // 消费者每消费一个数，缓冲区剩余孔家增加1，empty就加1
        // 一个生产者申请写缓冲区时，先empty--，再判断empty是否小于0，如果小于0则阻塞
        // 若一个生产者empty--后，empty>=0，则表示缓冲区有空间，生产者将继续执行
        empty = sem_open("empty", 10); 
        // full为正数时，表示缓冲区已经存放的数的个数
        // full为负数时，表示等待读缓冲区的进程数
        // 初始值为0，因为缓冲区为空
        // 生产者每次生产一个数，已占用数增加1，full就加1
        // 消费者每消费一个数，已占用数减1，full就减1
        // 当一个消费者申请读缓冲区时，先full--，再判断full是否小于0，如果小于0则阻塞
        // 若一个消费者full--后，full>=0，则表示缓冲区有数据，消费者将继续执行
        full = sem_open("full", 0);
        // 互斥信号量，初始值为1
        // 当任意一个进程访问缓冲区时，将mutex--
        // 当访问完毕后，将mutex++
        // 当mutex<0时，表示缓冲区正在被访问，进程将阻塞
        // 当mutex>=0时，表示缓冲区没有被访问，进程将继续执行
        mutex = sem_open("mutex", 1);
        for (int i = 0; i < 500; i++)
        {
            sem_wait(empty); // empty--，如果empty<0则阻塞
            sem_wait(mutex); // mutex--，如果mutex<0则阻塞
            // 读写文件的操作;
            sem_post(mutex); // mutex++，如果mutex<=0则唤醒一个等待进程
            sem_post(full); // full++，如果full<=0则唤醒一个等待进程
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (!fork()) // 消费者进程 1-5号进程
            {
                // 直接打开信号量，初值没有使用
                empty = sem_open("empty", 10);
                full = sem_open("full", 0);
                mutex = sem_open("mutex", 1);
                // 每个消费者进程消费100个数
                for (int i = 0; i < 100; i++)
                {
                    sem_wait(full); // full--，如果full<0说明缓冲区为空，本进程将阻塞
                    sem_wait(mutex); // mutex--，如果mutex<0说明缓冲区正在被访问，本进程将阻塞
                    // 读写文件的操作;
                    sem_post(mutex); // mutex++，如果mutex<=0则唤醒一个读/写等待进程
                    sem_post(empty); // empty++，如果empty<=0则唤醒一个等待进程
                }
            }
        }
    }
}
// 有正有负的信号量
// 信号量P操作系统调用
sys_sem_wait(sem_t *sem)
{
    // 进入区代码
    // 关闭中断 or Lamport面包店算法 or 硬件原子等
    cli();
    sem->value--;
    if((sem->value) < 0)
    {
        current->state = SLEEP;
        // 将进程加入信号量的等待队列
        // 调用调度函数
        schedule();
    }
    // 退出区代码，和进入区代码对应
    // 开启中断
    sti(); 
}

// 信号量V操作系统调用
sys_sem_post(sem_t * sem){
    // 进入区代码
    // 关闭中断 or Lamport面包店算法 or 硬件原子等
    cli();
    sem->value++;
    if((sem->value) <= 0)
    {
        // 从信号量的等待队列中取出一个进程p
        // 将该进程加入就绪队列
        p->state = READY;
        // 调用调度函数
        // schedule();
    }
    // 退出区代码，和进入区代码对应
    // 开启中断
    sti(); 
}
// 只有正数的信号量

// 信号量P操作系统调用
sys_sem_wait(sem_t *sem)
{
    // 进入区代码
    // 关闭中断 or Lamport面包店算法 or 硬件原子等
    cli();
    while((sem->value) == 0)
    {
        // 将当前进程加入信号量的等待队列
        // ...
        // 调用调度函数
        schedule();
    }
    sem->value--;
    // 退出区代码，和进入区代码对应
    // 开启中断
    sti(); 
}

// 信号量V操作系统调用
sys_sem_post(sem_t * sem){
    // 进入区代码
    // 关闭中断 or Lamport面包店算法 or 硬件原子等
    cli();
    sem->value++;
    // 让sem->queue中的所有进程都加入就绪队列
    // 开启中断
    sti(); 
}