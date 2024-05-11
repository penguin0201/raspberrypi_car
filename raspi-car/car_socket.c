#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>    
#include <stdio.h>  
#include <stdbool.h>
#include <sys/time.h>  
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include <bits/socket.h>

#define Trig	5
#define Echo	4
#define mid 23
#define left1 21
#define left2 22
#define right2 24
#define right1 25


int enab_pin[4]={26,27,28,29}; //使能开启

int Left_motor_go = 31;      //左电机前进方向连接Raspberry的wiringPi编码6口
int Left_motor_back = 11;     //左电机后退方向连接Raspberry的wiringPi编码10口

int Right_motor_go = 6;      //右电机前进方向连接Raspberry的wiringPi编码11口
int Right_motor_back = 10;    //右电机后退方向连接Raspberry的wiringPi编码31口


// 定义线程函数，用于执行SoX命令
void* play_audio(void* arg) {
    const char *audioFilePath = (const char*)arg;
    char command[256];
    snprintf(command, sizeof(command), "sox %s -d &", audioFilePath); // 注意添加了 & 来让SoX命令在后台运行

    // 执行SoX命令
    int result = system(command);
    if (result == -1) {
        perror("system");
        pthread_exit((void*)EXIT_FAILURE);
    } else if (result > 0) {
        fprintf(stderr, "SoX command failed with error code %d\n", result);
        pthread_exit((void*)EXIT_FAILURE);
    }

    pthread_exit((void*)EXIT_SUCCESS);
}
void* play_audio1(void* arg) {
    const char *audioFilePath1 = (const char*)arg;
    char command[256];
    snprintf(command, sizeof(command), "sox %s -d &", audioFilePath1); // 注意添加了 & 来让SoX命令在后台运行

    // 执行SoX命令
    int result = system(command);
    if (result == -1) {
        perror("system");
        pthread_exit((void*)EXIT_FAILURE);
    } else if (result > 0) {
        fprintf(stderr, "SoX command failed with error code %d\n", result);
        pthread_exit((void*)EXIT_FAILURE);
    }

    pthread_exit((void*)EXIT_SUCCESS);
}
void* play_audio2(void* arg) {
    const char *audioFilePath2 = (const char*)arg;
    char command[256];
    snprintf(command, sizeof(command), "sox %s -d &", audioFilePath2); // 注意添加了 & 来让SoX命令在后台运行

    // 执行SoX命令
    int result = system(command);
    if (result == -1) {
        perror("system");
        pthread_exit((void*)EXIT_FAILURE);
    } else if (result > 0) {
        fprintf(stderr, "SoX command failed with error code %d\n", result);
        pthread_exit((void*)EXIT_FAILURE);
    }

    pthread_exit((void*)EXIT_SUCCESS);
}
void* play_audio3(void* arg) {
    const char *audioFilePath3 = (const char*)arg;
    char command[256];
    snprintf(command, sizeof(command), "sox %s -d &", audioFilePath3); // 注意添加了 & 来让SoX命令在后台运行

    // 执行SoX命令
    int result = system(command);
    if (result == -1) {
        perror("system");
        pthread_exit((void*)EXIT_FAILURE);
    } else if (result > 0) {
        fprintf(stderr, "SoX command failed with error code %d\n", result);
        pthread_exit((void*)EXIT_FAILURE);
    }

    pthread_exit((void*)EXIT_SUCCESS);
}
void xunjiInit(void)
{
  pinMode(mid, INPUT);
  pinMode(left1, INPUT);
  pinMode(left2, INPUT);
  pinMode(right1, INPUT);
  pinMode(right2, INPUT);
}
void xunjiRead(){
  int midValue = digitalRead(mid);
  int left1Value = digitalRead(left1);
  int left2Value = digitalRead(left2);
  int right1Value = digitalRead(right1);
  int right2Value = digitalRead(right2);
  printf("\nmidValue = %d\n",midValue);
  printf("left1Value = %d\n",left1Value);
  printf("left2Value = %d\n",left2Value);
  printf("right1Value = %d\n",right1Value);
  printf("right2Value = %d\n",right2Value);
}
void ultraInit(void)
{
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
}
float disMeasure(void)
{
  struct timeval tv1;
  struct timeval tv2;
  long start, stop;
  float dis;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);

  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);	  //发出超声波脉冲
  digitalWrite(Trig, LOW);
  
  while(!(digitalRead(Echo) == 1));
  gettimeofday(&tv1, NULL);		   //获取当前时间

  while(!(digitalRead(Echo) == 0));
  gettimeofday(&tv2, NULL);		   //获取当前时间

  start = tv1.tv_sec * 1000000 + tv1.tv_usec;   //微秒级时间
  stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

  dis = (float)(stop - start) / 1000000 * 34990 / 2;  //距离

  return dis;
}
void setUp()
{
  wiringPiSetup();
  //L298N
  for(int i=0;i<4;i++)
  {
    pinMode(enab_pin[i],OUTPUT);
    printf("enab_pin%d out\n",enab_pin[i]);
    digitalWrite(enab_pin[i],HIGH);
  }
 //BuzPin
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);
  softPwmCreate(Left_motor_go,1,500);
  softPwmCreate(Left_motor_back,1,500);
  softPwmCreate(Right_motor_go,1,500);
  softPwmCreate(Right_motor_back,1,500);
  //超声波
  ultraInit(); 
}
void front()
{
  softPwmWrite(Left_motor_go,300);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,300);
  softPwmWrite(Right_motor_back,0);
  printf("The car go straight on!\n");
}
void back()
{
  softPwmWrite(Left_motor_go,0);
  softPwmWrite(Left_motor_back,300);
  softPwmWrite(Right_motor_go,0);
  softPwmWrite(Right_motor_back,300);
  printf("The car back to tail!\n");
}
void right()
{
  softPwmWrite(Left_motor_go,0);
  softPwmWrite(Left_motor_back,300);
  softPwmWrite(Right_motor_go,300);
  softPwmWrite(Right_motor_back,0);
  printf("The car turns right!\n");
}
void left()
{
  softPwmWrite(Left_motor_go,300);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,0);
  softPwmWrite(Right_motor_back,300);
  printf("The car turns left!\n");
}
void leftFront()
{
  softPwmWrite(Left_motor_go,300);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,150);
  softPwmWrite(Right_motor_back,0);
  printf("The car turns left front!\n");
}
void rightFront()
{
  softPwmWrite(Left_motor_go,150);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,300);
  softPwmWrite(Right_motor_back,0);
  printf("The car turns right front!\n");
}
void setOut()//刹车
{
  softPwmWrite(Left_motor_go,0);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,0);
  softPwmWrite(Right_motor_back,0);
  printf("The Car Stop!\n");
}
void frontPwm(int level) // level from 1 to 5
{
  softPwmWrite(Left_motor_go,level*100);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,level*100);
  softPwmWrite(Right_motor_back,0);
  printf("The car go straight on!\n");
}
void backPwm(int level)
{
  softPwmWrite(Left_motor_go,0);
  softPwmWrite(Left_motor_back,level*100);
  softPwmWrite(Right_motor_go,0);
  softPwmWrite(Right_motor_back,level*100);
  printf("The car back to tail!\n");
}
void rightPwm(int l)
{
  softPwmWrite(Left_motor_go,0);
  softPwmWrite(Left_motor_back,l*100);
  softPwmWrite(Right_motor_go,l*100);
  softPwmWrite(Right_motor_back,0);
  printf("The car turns right!\n");
}
void leftPwm(int l)
{
  softPwmWrite(Left_motor_go,l*100);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,0);
  softPwmWrite(Right_motor_back,l*100);
  printf("The car turns left!\n");
}
void leftFrontPwm(int l)
{
  softPwmWrite(Left_motor_go,l*100);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,l*50);
  softPwmWrite(Right_motor_back,0);
  printf("The car turns left front!\n");
}
void rightFrontPwm(int l)
{
  softPwmWrite(Left_motor_go,l*50);
  softPwmWrite(Left_motor_back,0);
  softPwmWrite(Right_motor_go,l*100);
  softPwmWrite(Right_motor_back,0);
  printf("The car turns right front!\n");
}
void powerOff()
{
  for(int i=0;i<4;i++)
  {
    digitalWrite(enab_pin[i],LOW);
  }
  printf("MOTOR POWER OFF!\n");
}
void warn()
{
  system("play warning.mp3");
}
// 线程执行的函数
void* thread_light(void* arg) {
    // 在这里执行系统调用
    system("sudo python3 strip_lights.py");
    // 线程结束
    pthread_exit(NULL);
}

int main(){
    
    setUp();
    xunjiInit();

    int modee;

    // 定义要播放的音频文件路径
    const char *audioFilePath = "warning.mp3";
    const char *audioFilePath1 = "maka.mp3";
    const char *audioFilePath2 = "banana.mp3";
    const char *audioFilePath3 = "bark.mp3";

    // 创建线程属性
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_t thread_lights;
    pthread_attr_t attr_lights;
    pthread_attr_init(&attr_lights);

    // 创建线程属性
    pthread_t thread_m1;
    pthread_attr_t attr_m1;
    pthread_attr_init(&attr_m1);
        pthread_t thread_m2;
    pthread_attr_t attr_m2;
    pthread_attr_init(&attr_m2);
        pthread_t thread_m3;
    pthread_attr_t attr_m3;
    pthread_attr_init(&attr_m3);
    

    system("sudo libcamerify motion");

    //socket链接
    int Ser_Socket,Cli_Sock;
    struct sockaddr_in Ser_addr,Cli_addr;

    Ser_Socket = socket(AF_INET,SOCK_STREAM,0);
    if (Ser_Socket == -1)
    {
        printf("Socket Creation Failed\n");
        // exit(0);
    }

    Ser_addr.sin_family = AF_INET;
    Ser_addr.sin_addr.s_addr = INADDR_ANY;
    Ser_addr.sin_port = htons(6969);

    if (bind(Ser_Socket,(struct sockaddr*)&Ser_addr,sizeof(Ser_addr)) == -1)
    {
        printf("Binding Failed\n");
        close(Ser_Socket);
        // exit(0);
    }

    printf("Socket Create Success\n");

    listen(Ser_Socket,5);

    socklen_t Cli_len = sizeof(Cli_addr);
    Cli_Sock = accept(Ser_Socket,(struct sockaddr*)&Cli_addr,&Cli_len);
    if (Cli_Sock == -1)
    {
        printf("accept Failed\n");
        close(Ser_Socket);
        // exit(0);
    } else{
        printf("accept Success\n");
    }

    char buffer[100];
    char send_buffer[16] ;
    int speed_level = 3;
    float dis = 50.0;
    int cur = 0, abs_cur = 0;
    while (1)
    {
        printf("   - speed_level = %d\n",speed_level);
        //读取数据
        memset(buffer, 0, sizeof(buffer));
        ssize_t n = read(Cli_Sock,buffer,100);
        if (n > 0)
        {
            printf(" -- receive:%s\n",buffer);
            if(buffer[0] == '1')
            {
              // printf("mode 1:wsadqe控制移动，t停止\n");
              if (buffer[1] == 'x')
              {
                setOut();
                printf("over\n");
                powerOff();
                break;
              }
              else if(buffer[1] == 't')
              {
                setOut();
              }
              else if(buffer[1] == 'w')
              {
                setOut();   
                front();
              }
              else if(buffer[1] == 'a')
              {
                setOut();   
                left();
              }
              else if(buffer[1] == 'd')
              {
                setOut();   
                right();
              }
              else if(buffer[1] == 's')
              {
                setOut();   
                back();
              }
              else if(buffer[1] == 'q')
              {
                setOut();   
                leftFront();
              }
              else if(buffer[1] == 'e')
              {
                setOut();   
                rightFront();
              }
            }
            else if (buffer[0] == '2')
            {
              // printf("mode 2:wsadqe控制移动,速度可调,距离过近时有警告，并强制停止\n");
              if (buffer[1] == 'x')
              {
                setOut();
                printf("over\n");
                powerOff();
                break;
              }
              else if(buffer[1] == '1')
              {
                setOut();
                printf("speed level 1\n");   
                speed_level = 1;
              }
              else if(buffer[1] == '2')
              {
                setOut();   
                printf("speed level 2\n");
                speed_level = 2;
              }
              else if(buffer[1] == '3')
              {
                setOut(); 
                printf("speed level 3\n");  
                speed_level = 3;
              }
              else if(buffer[1] == '4')
              {
                setOut();   
                printf("speed level 4\n");
                speed_level = 4;
              }
              else if(buffer[1] == '5')
              {
                setOut();   
                printf("speed level 5\n");
                speed_level = 5;
              }
              else if(buffer[1] == 't')
              {
                setOut();   
              }
              else if(buffer[1] == 'a')
              {
                setOut();   
                leftPwm(speed_level);
              }
              else if(buffer[1] == 'd')
              {
                setOut();   
                rightPwm(speed_level);
              }
              else if(buffer[1] == 'w')
              {
                setOut();   
                frontPwm(speed_level);

              }
              else if(buffer[1] == 's')
              {
                setOut();   
                backPwm(speed_level);
              }
              else if(buffer[1] == 'q')
              {
                setOut();   
                leftFrontPwm(speed_level);
              }
              else if(buffer[1] == 'e')
              {
                setOut();   
                rightFrontPwm(speed_level);
              }
            }
            else if (buffer[0] == '3')
            {
              // printf("mode 3:超声波避障，w自动前进，t停止，遇障碍物自动左转前进\n");
              if (buffer[1] == 'x')
              {
                setOut();
                printf("over\n");
                powerOff();
                break;
              }
              else if(buffer[1] == 't')
              {
                setOut();   
              }
              else if(buffer[1] == 'w')
              {
                setOut();
                dis = disMeasure();
                sprintf(send_buffer,"%0.2fcm",dis);
                printf("distance = %0.2f cm\n",dis);

                if (dis > 30.0)
                {
                  front();
                  write(Cli_Sock,send_buffer,sizeof(send_buffer));
                } else {

                  // 创建线程
                  if (pthread_create(&thread, &attr, play_audio, (void*)audioFilePath) != 0) {
                      perror("pthread_create");
                      exit(EXIT_FAILURE);
                  }

                  left();
                  write(Cli_Sock,send_buffer,sizeof(send_buffer));

                  // 等待子线程结束
                  void* thread_result;
                  pthread_join(thread, &thread_result);
                  if (thread_result == (void*)EXIT_SUCCESS) {
                      printf("Audio playback finished successfully.\n");
                  } else {
                      printf("Audio playback failed.\n");
                  }
                }
              }
              else if (buffer[1] == 'p')
              {
                setOut();
                dis = disMeasure();
                printf("distance = %0.2f cm\n",dis);
                sprintf(send_buffer,"%0.2fcm",dis);
                write(Cli_Sock,send_buffer,sizeof(send_buffer));
              }  
            }
            else if (buffer[0] == '4')
            {
              // printf("mode 4:黑线寻迹\n");
              if (buffer[1] == 'x')
              {
                setOut();
                printf("over\n");
                powerOff();
                break;
              }  
              else if(buffer[1] == 't')
              {
                setOut();   
              }
              else if(buffer[1] == 'w')
              {
                int startTime = millis();
                while (millis() - startTime < 200) {
                  // setOut(); 
                  int midValue = digitalRead(mid);
                  int left1Value = digitalRead(left1);
                  int left2Value = digitalRead(left2);
                  int right1Value = digitalRead(right1);
                  int right2Value = digitalRead(right2);
                  cur = right1Value + right2Value - left1Value - left2Value;
                  abs_cur = right1Value + right2Value + left1Value + left2Value;
                  if (abs_cur == 4 && midValue == 0) {
                    front();
                  } else if (abs_cur == 0) {
                    continue;
                  } else if (cur < 0) {
                    right();
                  } else if (cur > 0) { 
                    left();
                  }
                  delay(10);
                }
              }
            }
            else if (buffer[0] == 'l' && buffer[1] == 'i' && buffer[2] == 'g' && buffer[3] == 'h' && buffer[4] == 't')
            {
              // 创建线程
              if (pthread_create(&thread_lights, &attr_lights, thread_light, NULL) != 0) {
                  perror("Failed to create thread");
                  return EXIT_FAILURE;
              }

              // 线程创建后立即分离
              if (pthread_detach(thread_lights) != 0) {
                  perror("Failed to detach thread");
                  exit(EXIT_FAILURE);
              }
            }
            else if(buffer[0] == 'm' && buffer[1] == 'u' && buffer[2] == 's' && buffer[3] == 'i' && buffer[4] == 'c' && buffer[5] == '1')
            {
                  // 创建线程
                  if (pthread_create(&thread_m1, &attr_m1, play_audio1, (void*)audioFilePath1) != 0) {
                      perror("pthread_create");
                      exit(EXIT_FAILURE);
                  }
                  // 线程创建后立即分离
                  if (pthread_detach(thread_m1) != 0) {
                      perror("Failed to detach thread");
                      exit(EXIT_FAILURE);
                  }
            }
            else if(buffer[0] == 'm' && buffer[1] == 'u' && buffer[2] == 's' && buffer[3] == 'i' && buffer[4] == 'c' && buffer[5] == '2')
            {
                // 创建线程
                  if (pthread_create(&thread_m2, &attr_m2, play_audio2, (void*)audioFilePath2) != 0) {
                      perror("pthread_create");
                      exit(EXIT_FAILURE);
                  }
                  // 线程创建后立即分离
                  if (pthread_detach(thread_m2) != 0) {
                      perror("Failed to detach thread");
                      exit(EXIT_FAILURE);
                  }
            }
            else if(buffer[0] == 'm' && buffer[1] == 'u' && buffer[2] == 's' && buffer[3] == 'i' && buffer[4] == 'c' && buffer[5] == '3')
            {
                // 创建线程
                  if (pthread_create(&thread_m3, &attr_m3, play_audio3, (void*)audioFilePath3) != 0) {
                      perror("pthread_create");
                      exit(EXIT_FAILURE);
                  }
                  // 线程创建后立即分离
                  if (pthread_detach(thread_m3) != 0) {
                      perror("Failed to detach thread");
                      exit(EXIT_FAILURE);
                  }
            }
            
        } else{
            printf("read failed\n");
            break;
        }
        
        //写入数据
        // char send_buffer[] = {"Hello Client"};
        // write(Cli_Sock,send_buffer,sizeof(send_buffer));

    }

    close(Cli_Sock);
  
}
