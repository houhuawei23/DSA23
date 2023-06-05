// 信号量数据结构及操作的伪代码
struct seamphone{
  int value;
  PCB* queue;
}


P(seamphone s){
    s.value--;
    if(s.value < 0){
        sleep_on(s.queue);
    }
}

V(seamphone s){
    s.value++;
    if(s.value <= 0){
        wake_up(s.queue);
    }
}

// Lamport 面包店算法实现
do{
    ch
}
// Lamport's Bakery Algorithm
do{
    flag[i] = true;
    label[i] = 1 + max(label[0], label[1], ..., label[n-1]);
    flag[i] = false;
    for(j = 0; j < n; j++){
        while(flag[j]);
        while(label[j] != 0 && (label[j], j) < (label[i], i));
        // label[j] < label[i] || (label[j] == label[i] && j < i)
    } 
    // critical section
    label[i] = 0;
}while(true);