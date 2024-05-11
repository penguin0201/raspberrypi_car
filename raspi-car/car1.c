/*
键盘上输入w前进，s后退，a左转，d右转，q左前，e右前，x停止
*/

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include<softPwm.h>
#include <stdio.h>  
#include <stdbool.h>
#include <sys/time.h>  


int enab_pin[4]={26,27,28,29}; //使能开启

int Left_motor_go = 6;      //左电机前进方向连接Raspberry的wiringPi编码6口
int Left_motor_back = 10;     //左电机后退方向连接Raspberry的wiringPi编码10口

int Right_motor_go = 31;      //右电机前进方向连接Raspberry的wiringPi编码11口
int Right_motor_back = 11;    //右电机后退方向连接Raspberry的wiringPi编码31口

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
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  //超声波
//   ultraInit(); 
}
void front()
{
  digitalWrite(Left_motor_go,HIGH);
  digitalWrite(Right_motor_go,HIGH);
  printf("The car go straight on!\n");
}

void back()
{
  digitalWrite(Left_motor_back,HIGH);
  digitalWrite(Right_motor_back,HIGH);
  printf("The car back to tail!\n");
}

void left()
{
  digitalWrite(Left_motor_back,HIGH);
  digitalWrite(Right_motor_go,HIGH);
  printf("The car turns left!\n");
}

void right()
{
  digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,HIGH);
  printf("The car turns right!\n");
}
void leftFront()
{
//   digitalWrite(Left_motor_back,HIGH);
  digitalWrite(Right_motor_go,HIGH);
  printf("The car turns left front!\n");
}
void rightFront()
{
//   digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,HIGH);
  printf("The car turns right front!\n");
}
void setOut()
{
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  printf("The Car Stop!\n");
}
void powerOff()
{
  for(int i=0;i<4;i++)
  {
    digitalWrite(enab_pin[i],LOW);
  }
  printf("MOTOR POWER OFF!\n");
}

int main(){
    setUp();
    int modee;
    printf("choose your mode:"); 
    scanf("%d",&modee);
    if(modee==1)
    {
        char ch;
        system("stty -icanon");//关闭缓冲区，输入字符无需按回车键直接接受
        while (ch = getchar())
        {
        if(ch=='x')
        {
            printf("over\n");
            system("stty icanon");//打开缓冲区
            break;
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
                // setOut();
                left();
                delay(1000);
                setOut();
                break;
            case 'd':
                // setOut();
                right();
                delay(1000);
                setOut();
                break;
            case 'w':  
                // setOut();   
                front();
                // delay(1000);
                // setOut();
                break;
            case 's':
                // setOut();
                back();
                delay(1000);
                setOut();
                break;
            case 'q':
                // setOut();
                leftFront();
                delay(1000);
                setOut();
                break;
            case 'e':
                // setOut();
                rightFront();
                delay(1000);
                setOut();
                break;
            default:
                break;
            }
        }
        }
    }
    return 0;   
}
