#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// 线程执行的函数
void* thread_light(void* arg) {
    // 在这里执行系统调用
    system("sudo python3 strip_lights.py");
    // 线程结束
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_lights;
    pthread_attr_t attr_lights;
    pthread_attr_init(&attr_lights);

    // 创建线程
    if (pthread_create(&thread_lights, &attr_lights, thread_light, NULL) != 0) {
        perror("Failed to create thread");
        return EXIT_FAILURE;
    }

    printf("111\n");

    // 线程创建后立即分离
    if (pthread_detach(thread_lights) != 0) {
        perror("Failed to detach thread");
        exit(EXIT_FAILURE);
    }

    printf("222\n");

    return 0;
}