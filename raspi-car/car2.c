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

/**
 * Checks if a key has been pressed on the keyboard.
 * 
 * @return true if a key has been pressed, false otherwise.
 */
bool kbhit(void)
{
  struct timeval tv;
  fd_set read_fd;

  tv.tv_sec=0;
  tv.tv_usec=0;

  FD_ZERO(&read_fd);
  FD_SET(0,&read_fd);

  if(select(1, &read_fd, NULL, NULL, &tv) == -1)
    return 0;

  if(FD_ISSET(0,&read_fd))
    return 1;

  return 0;
}

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
//   pinMode(BuzPin,OUTPUT);
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);
  //TCRT
//   pinMode(TCRT_IN_1, INPUT);
//   pinMode(TCRT_IN_2, INPUT);
//   pinMode(TCRT_IN_3, INPUT);
//   pinMode(TCRT_IN_4, INPUT);
  // pinMode(TCRT_IN_5, INPUT);
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
int checkInput(char input) {
  char ch;
  system("stty -icanon"); // Disable input buffering
  ch = getchar();
  system("stty icanon"); // Enable input buffering
  if (ch == input) {
    return 1;
  } else {
    return 0;
  }
}

int main(){
    
    setUp();

    int modee;
    float dis = 0.1;

    // 定义要播放的音频文件路径
    const char *audioFilePath = "warning.mp3";

    // 创建线程属性
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);


  start:
    printf("mode 1:wsadqe控制移动，t停止\n");
    printf("mode 2:wsadqe控制移动,速度可调,距离过近时有警告，并强制停止\n");
    printf("mode 3:超声波避障，w自动前进，t停止，遇障碍物自动左转前进\n");
    printf("mode 4:黑线寻迹\n");
    printf("choose your mode:"); 
    scanf("%d",&modee);
    //mode 1 :wsadqe控制移动
    //mode 2 :超声波避障，w自动前进，t停止，遇障碍物自动左转前进
    //mode 3 ：wsadqe控制移动,速度可调,超声波警告
    //mode 4 : 黑线寻迹
    if(modee==1)
    {
        printf("\n mode 1 now \n");
        char ch;
        system("stty -icanon");//关闭缓冲区，输入字符无需按回车键直接接受
        while (ch = getchar())
        {
        if(ch=='x')
        {
            setOut();
            printf("over\n");
            powerOff();
            system("stty icanon");//打开缓冲区
            break;
        }else if(ch=='r')
        {
            goto start;
        }
        else
        {
            float dis;
            switch (ch)
            {
            case 't':
                setOut();
                break;
            case 'a':
                setOut();
                left();
                // delay(500);
                // setOut();
                break;
            case 'd':
                setOut();
                right();
                // delay(500);
                // setOut();
                break;
            case 'w':  
                setOut();   
                front();
                // delay(500);
                // setOut();
                break;
            case 's':
                setOut();
                back();
                // delay(500);
                // setOut();
                break;
            case 'q':
                setOut();
                leftFront();
                // delay(500);
                // setOut();
                break;
            case 'e':
                setOut();
                rightFront();
                // delay(500);
                // setOut();
                break;
            default:
                break;
            }
        }
        }
    }else if(modee==3){
        printf("\n mode 3 now \n");
        char ch,curch;
        system("stty -icanon");//关闭缓冲区，输入字符无需按回车键直接接受
        while(ch = getchar()){
            // dis = disMeasure();
            // printf("distance = %0.2f cm\n",dis);
            // delay(200);
          if(ch=='x')
          {
              setOut();
              printf("over\n");
              powerOff();
              system("stty icanon");//打开缓冲区
              break;
          }else if(ch == 'r')
          {
            goto start;
          }else if (ch == 'w')
          {
              int startTime = millis();
              while (millis() - startTime < 30000)
              {
                dis = disMeasure();
                printf("distance = %0.2f cm\n",dis);
                if(kbhit()){
                  curch = getchar();
                  if(curch == 't'){
                    setOut();
                    break;
                  }
                }
                if (dis > 30.0)
                {
                  front();
                  delay(200); //转动时间
                } else {

                  // 创建线程
                  if (pthread_create(&thread, &attr, play_audio, (void*)audioFilePath) != 0) {
                      perror("pthread_create");
                      exit(EXIT_FAILURE);
                  }

                  setOut();
                  left();
                  delay(200); //转动时间
                  setOut();

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
              setOut();
          }else if (ch == 'p')
          {
            int startTime = millis();
            while (millis() - startTime < 5000)
            {
              dis = disMeasure();
              printf("distance = %0.2f cm\n",dis);
              delay(200);
              if(kbhit()){
                curch = getchar();
                if(curch == 't'){
                  setOut();
                  break;
                }
              }
            }  
          }
    }
    return 0;   
    }else if (modee == 2)
    {
      printf("\n mode 2 now \n");
        char ch,curch;
        int level = 3;
        printf("choose speed level 1-5:\n");
        system("stty -icanon");//关闭缓冲区，输入字符无需按回车键直接接受
        while (ch = getchar())
        {
        if(ch=='1')
        {
          level = 1;
          printf("level 1 now\n");
        }
        else if(ch=='2')
        {
          level = 2;
          printf("level 2 now\n");
        }
        else if(ch=='3')
        {
          level = 3;
          printf("level 3 now\n");
        }
        else if(ch=='4')
        {
          level = 4;
          printf("level 4 now\n");
        }
        else if(ch=='5')
        {
          level = 5;
          printf("level 5 now\n");
        }
        else if(ch=='x')
        {
            setOut();
            printf("over\n");
            powerOff();
            system("stty icanon");//打开缓冲区
            break;
        }else if(ch=='r')
        {
            goto start;
        }
        else
        {
            float dis;
            switch (ch)
            {
            case 't':
                setOut();
                break;
            case 'a':
                setOut();
                leftPwm(level);
                // delay(500);
                // setOut();
                break;
            case 'd':
                setOut();
                rightPwm(level);
                // delay(500);
                // setOut();
                break;
            case 'w':  
              setOut();
              while (1)
              {
                dis = disMeasure();
                // printf("distance = %0.2f cm\n",dis);
                if(kbhit()){
                  curch = getchar();
                  if(curch == 't'){
                    setOut();
                    break;
                  }
                }
                if (dis > 20.0)
                {
                  frontPwm(level);
                  delay(200); //转动时间
                } else {

                  // 创建线程
                  if (pthread_create(&thread, &attr, play_audio, (void*)audioFilePath) != 0) {
                      perror("pthread_create");
                      exit(EXIT_FAILURE);
                  }

                  back();
                  delay(200); 
                  setOut();

                  // 等待子线程结束
                  void* thread_result;
                  pthread_join(thread, &thread_result);

                  break;
                }
              }
              break;
            case 's':
                setOut();
                backPwm(level);
                // delay(500);
                // setOut();
                break;
            case 'q':
                setOut();
                leftFrontPwm(level);
                // delay(500);
                // setOut();
                break;
            case 'e':
                setOut();
                rightFrontPwm(level);
                // delay(500);
                // setOut();
                break;
            default:
                break;
            }
        }
        }
    }else if(modee==4){
        xunjiInit();
        printf("\n mode 4 now \n");
        char ch,curch;
        int cur = 0, abs_cur = 0;
        system("stty -icanon");//关闭缓冲区，输入字符无需按回车键直接接受
        while(ch = getchar()){
            // dis = disMeasure();
            // printf("distance = %0.2f cm\n",dis);
            // delay(200);
          if(ch=='x')
          {
              setOut();
              printf("over\n");
              powerOff();
              system("stty icanon");//打开缓冲区
              break;
          }else if (ch =='t')
          {
            setOut();
          }else if(ch == 'r')
          {
            goto start;
          }else if (ch == 'w')
          {
              while (1)
              {
                int midValue = digitalRead(mid);
                int left1Value = digitalRead(left1);
                int left2Value = digitalRead(left2);
                int right1Value = digitalRead(right1);
                int right2Value = digitalRead(right2);
                if(kbhit()){
                  curch = getchar();
                  if(curch == 't'){
                    setOut();
                    break;
                  }
                }
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
                // if (midValue ==0)
                // {
                //   front();
                //   delay(200);
                // }else if (left2Value == 0)
                // {
                //   leftFrontPwm(4);
                //   delay(200);
                // }else if (right2Value == 0)
                // {
                //   rightFrontPwm(4);
                //   delay(200);
                // }else if (left1Value == 0){
                //   left();
                //   delay(200);
                // }else if (right1Value == 0)
                // {
                //   right();
                //   delay(200);
                // }else if (midValue == 1 && left1Value == 1 && left2Value == 1 && right1Value == 1 && right2Value == 1)
                // {
                //   mark = 1;
                // }
              }
              // setOut();
          }else if (ch == 'p')
          {
            xunjiRead();
          }
    }
    return 0;   
    }
    
}
