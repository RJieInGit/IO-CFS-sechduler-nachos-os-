#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "../lib/rbtree.h"

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %d looped %d times\n", which, num);
        kernel->currentThread->Yield();
    }
}

void IObound(int arg){
    io::iowrite(0);
    io::ioread(0);
    io::iowrite(1);
    io::iowrite(2);
    io::ioread(1);
    return;
}
void CPUbound(int arg){
    for(int i=0;i<1000;i++){
    //printf("cpu bound tick at : %d\n",kernel->stats->totalTicks);
    kernel->interrupt->OneTick();
    }
}
void MIXbound(int arg){
    io::iowrite(0);
    printf("%s thread compute start at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
    for(int i=0;i<150;i++){
        kernel->interrupt->OneTick();
    }
    printf("%s thread compute finish at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
    io::ioread(0);
    printf("%s thread compute start at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
     for(int i=0;i<250;i++){
        kernel->interrupt->OneTick();
    }
    printf("%s thread compute finish at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
    io::iowrite(1);
     for(int i=0;i<200;i++){
        kernel->interrupt->OneTick();
    }

}
void
ThreadTest()
{
    Thread *t = new Thread("IObound thread0");
    t->Fork((VoidFunctionPtr) IObound, (void *) 1);
    Thread *t1 =new Thread("CPU bound 0");
    t1->Fork((VoidFunctionPtr)CPUbound,(void*)1);
    Thread *t2 =new Thread("MIX bound 0");
    t2->Fork((VoidFunctionPtr)MIXbound,(void*)1);
    Thread *t3 =new Thread("IO bound 1");
    t3->Fork((VoidFunctionPtr)IObound,(void*)1);
    Thread *t4 =new Thread("CPU bound 1");
    t4->Fork((VoidFunctionPtr)CPUbound,(void*)1);
    Thread *t5 =new Thread("MIX bound 0");
    t5->Fork((VoidFunctionPtr)MIXbound,(void*)1);
     int a[]= {10, 40, 30, 60, 90, 70, 20, 50, 80};
15     int check_insert=0;    // "插入"动作的检测开关(0，关闭；1，打开)
16     int check_remove=0;    // "删除"动作的检测开关(0，关闭；1，打开)
17     int i;
18     int ilen = (sizeof(a)) / (sizeof(a[0])) ;
19     RBTree<int>* tree=new RBTree<int>();
20 
21     cout << "== 原始数据: ";
22     for(i=0; i<ilen; i++)
23         cout << a[i] <<" ";
24     cout << endl;
25 
26     for(i=0; i<ilen; i++) 
27     {
28         tree->insert(a[i]);
29         // 设置check_insert=1,测试"添加函数"
30         if(check_insert)
31         {
32             cout << "== 添加节点: " << a[i] << endl;
33             cout << "== 树的详细信息: " << endl;
34             tree->print();
35             cout << endl;
36         }
37 
38     }
39 
40     cout << "== 前序遍历: ";
41     tree->preOrder();
42 
43     cout << "\n== 中序遍历: ";
44     tree->inOrder();
45 
46     cout << "\n== 后序遍历: ";
47     tree->postOrder();
48     cout << endl;
49 
50     cout << "== 最小值: " << tree->minimum() << endl;
51     cout << "== 最大值: " << tree->maximum() << endl;
52     cout << "== 树的详细信息: " << endl;
53     tree->print();
54 
55     // 设置check_remove=1,测试"删除函数"
56     if(check_remove)
57     {
58         for(i=0; i<ilen; i++)
59         {
60             tree->remove(a[i]);
61 
62             cout << "== 删除节点: " << a[i] << endl;
63             cout << "== 树的详细信息: " << endl;
64             tree->print();
65             cout << endl;
66         }
67     }
68 
69     // 销毁红黑树
70     tree->destroy();
    return;
}

