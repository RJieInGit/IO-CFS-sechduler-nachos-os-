#include "kernel.h"
#include "main.h"
#include "thread.h"
//#include "../lib/rbtree.h"

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
     int check_insert=0;    // "插入"动作的检测开关(0，关闭；1，打开)
     int check_remove=0;    // "删除"动作的检测开关(0，关闭；1，打开)
     int i;
     int ilen = (sizeof(a)) / (sizeof(a[0])) ;
     RBTree<int>* tree=new RBTree<int>();
 
     cout << "== 原始数据: ";
     for(i=0; i<ilen; i++)
         cout << a[i] <<" ";
     cout << endl;
 
     for(i=0; i<ilen; i++) 
     {
         tree->insert(a[i]);
         // 设置check_insert=1,测试"添加函数"
         if(check_insert)
         {
             cout << "== 添加节点: " << a[i] << endl;
             cout << "== 树的详细信息: " << endl;
             tree->print();
             cout << endl;
         }
 
     }
 
     cout << "== 前序遍历: ";
     tree->preOrder();
 
     cout << "\n== 中序遍历: ";
     tree->inOrder();
 
     cout << "\n== 后序遍历: ";
     tree->postOrder();
     cout << endl;
 
     cout << "== 最小值: " << tree->minimum() << endl;
     cout << "== 最大值: " << tree->maximum() << endl;
     cout << "== 树的详细信息: " << endl;
     tree->print();
 
     // 设置check_remove=1,测试"删除函数"
     if(check_remove)
     {
         for(i=0; i<ilen; i++)
         {
             tree->remove(a[i]);
 
             cout << "== 删除节点: " << a[i] << endl;
             cout << "== 树的详细信息: " << endl;
             tree->print();
             cout << endl;
         }
     }
 
     // 销毁红黑树
     tree->destroy();
    return;
}

