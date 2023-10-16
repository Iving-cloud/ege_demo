#include <windows.h>
#include <stdio.h>

// 线程函数，这个函数是线程的执行体
void threadFunction(int threadId) {
    printf("Thread %d is running.\n", threadId);
}

void threadFunction2(void *) {
    for(int i=0;i<100;i++){
        printf("this:%d\n",i);
    }
}
void threadFunction3(void *) {
    for(int i=0;i<100;i+=5){
        printf("this2:%d\n",i);
    }
}

int main() {
    // 创建两个线程
    HANDLE thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadFunction2, NULL, 0, NULL);
    HANDLE thread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadFunction3, NULL, 0, NULL);

    // 等待两个线程完成
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // 关闭线程句柄
    CloseHandle(thread1);
    CloseHandle(thread2);

    return 0;
}