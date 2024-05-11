package com.example.myapplication;

import static com.example.myapplication.MainActivity.myTcpClient;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Switch;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;


public class Mode1 extends AppCompatActivity implements SensorEventListener {

    Button Button1,btn_w1,btn_q1,btn_e1,btn_a1,btn_s1,btn_d1,btn_t1;
    @SuppressLint("UseSwitchCompatOrMaterialCode")
    Switch mySwitch;
    EditText et;
    private SensorManager sensorManager;
    private Sensor rotationVectorSensor;
    private int flag = 0;
    WebView webView;

    @SuppressLint({"MissingInflatedId", "ClickableViewAccessibility", "SetJavaScriptEnabled"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mode1);

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        rotationVectorSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);

        et=findViewById(R.id.editTextText);

        mySwitch = findViewById(R.id.grav);
        mySwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                // isChecked 为 true 表示开关打开，false 表示关闭
                if (isChecked) {
                    flag = 1;
                } else {
                    flag = 0;
                }
            }
        });

        btn_w1=findViewById(R.id.w1);
        btn_w1.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("1w");
                        et.setText("小车在前进");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("1t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_q1=findViewById(R.id.q1);
        btn_q1.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("1q");
                        et.setText("小车在左前进");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("1t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_e1=findViewById(R.id.e1);
        btn_e1.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("1e");
                        et.setText("小车在右前进");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("1t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_a1=findViewById(R.id.a1);
        btn_a1.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("1a");
                        et.setText("小车在左转");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("1t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_s1=findViewById(R.id.s1);
        btn_s1.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("1s");
                        et.setText("小车在后退");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("1t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_t1=findViewById(R.id.t1);
        btn_t1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCmd(btn_t1);
                et.setText("小车停止");
            }
        });

        btn_d1=findViewById(R.id.d1);
        btn_d1.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("1d");
                        et.setText("小车右转");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("1t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        Button1=findViewById(R.id.rechoose);
        Button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCmd(btn_t1);
                sendCmd(Button1);
                et.setText("小车停止");
                Intent intent=new Intent();
                intent.setClass(Mode1.this,MainActivity.class);
                startActivity(intent);
            }
        });

        webView=findViewById(R.id.webcam);
        webView.loadUrl("http://192.168.205.124:8081/");
        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setUseWideViewPort(true);
        webSettings.setLoadWithOverviewMode(true);
        webSettings.setBuiltInZoomControls(true);
        webSettings.setSupportZoom(true);
        webSettings.setLayoutAlgorithm(WebSettings.LayoutAlgorithm.SINGLE_COLUMN);
    }

    @Override
    protected void onResume() {
        super.onResume();
        sensorManager.registerListener(this, rotationVectorSensor, SensorManager.SENSOR_DELAY_NORMAL);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (flag == 1){
            sensorManager.unregisterListener(this);
            flag = 0;
        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR) {
            float[] rotationMatrix = new float[9];
            float[] orientation = new float[3];

            // 将Rotation Vector数据转换为旋转矩阵
            SensorManager.getRotationMatrixFromVector(rotationMatrix, event.values);

            // 将旋转矩阵转换为欧拉角
            SensorManager.getOrientation(rotationMatrix, orientation);

            // orientation数组包含了三个值：azimuth(方位角)，pitch(俯仰角)，roll(翻滚角)
            // 其中，azimuth是绕Z轴的旋转，pitch是绕X轴的旋转，roll是绕Y轴的旋转
            // 根据需要使用这些值
            float azimuth = orientation[0];
            float pitch = orientation[1];
            float roll = orientation[2];

            // 根据pitch和roll的值执行相应的动作
            if (flag == 1){
                handleTilt(pitch, roll);
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // 精度变化的处理，通常可以忽略
    }

    private void handleTilt(float pitch, float roll) {
//        System.out.println(pitch+"  "+roll);
        if (roll > 0.5f) {
            send_Cmd("1w");
        } else if (roll <-0.5f){
            send_Cmd("1s");
        } else if (pitch > 0.5f){
            send_Cmd("1a");
        } else if (pitch < -0.5f){
            send_Cmd("1d");
        }else {
            send_Cmd("1t");
        }
    }

    public void send_Cmd(String msg){
        new Thread(() ->{
            myTcpClient.sendMsg(msg);
        }).start();
    }

    //    @SuppressLint("NonConstantResourceId")
    public void sendCmd(View v) {
        int id = v.getId();
        if (id == R.id.w1) {
            send_Cmd("1w");
        } else if (id == R.id.q1) {
            send_Cmd("1q");
        } else if (id == R.id.e1) {
            send_Cmd("1e");
        } else if (id == R.id.a1) {
            send_Cmd("1a");
        } else if (id == R.id.d1) {
            send_Cmd("1d");
        } else if (id == R.id.t1) {
            send_Cmd("1t");
        } else if (id == R.id.s1) {
            send_Cmd("1s");
        } else if (id == R.id.rechoose) {
            send_Cmd(" return");
        }
    }

}
