package com.example.myapplication;

import static com.example.myapplication.MainActivity.myTcpClient;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import androidx.appcompat.app.AppCompatActivity;


public class Mode2 extends AppCompatActivity {
    EditText et;
    Button btn_choose,btn_w2,btn_q2,btn_e2,btn_a2,btn_s2,btn_d2,btn_t2;
    RadioGroup radioGroup;
    WebView webView;

    @SuppressLint({"MissingInflatedId", "ClickableViewAccessibility", "SetJavaScriptEnabled"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mode2);

        et=findViewById(R.id.editTextText2);

        radioGroup = findViewById(R.id.level);
        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                RadioButton radioButton = group.findViewById(checkedId);
                send_Cmd("2"+String.valueOf(radioButton.getText().toString().charAt(0)));
            }
        });

        btn_w2=findViewById(R.id.w2);
        btn_w2.setOnTouchListener(new View.OnTouchListener() {
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("2w");
                        et.setText("小车在前进");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("2t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_q2=findViewById(R.id.q2);
        btn_q2.setOnTouchListener(new View.OnTouchListener(){
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("2q");
                        et.setText("小车在左前进");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("2t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_e2=findViewById(R.id.e2);
        btn_e2.setOnTouchListener(new View.OnTouchListener(){
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("2e");
                        et.setText("小车在右前进");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("2t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_a2=findViewById(R.id.a2);
        btn_a2.setOnTouchListener(new View.OnTouchListener(){
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("2a");
                        et.setText("小车在左转");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("2t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_s2=findViewById(R.id.s2);
        btn_s2.setOnTouchListener(new View.OnTouchListener(){
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("2s");
                        et.setText("小车在后退");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("2t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_d2=findViewById(R.id.d2);
        btn_d2.setOnTouchListener(new View.OnTouchListener(){
            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 当触摸动作是按下时，执行方法a
                        send_Cmd("2d");
                        et.setText("小车在前进");
                        break;
                    case MotionEvent.ACTION_UP:
                        // 当触摸动作是松开时，执行方法b
                        send_Cmd("2t");
                        et.setText("小车停止");
                        break;
                }
                return false;
            }
        });

        btn_t2=findViewById(R.id.t2);
        btn_t2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCmd(btn_t2);
                et.setText("小车停止");
            }
        });

        btn_choose =findViewById(R.id.rechoose2);
        btn_choose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCmd(btn_t2);
                sendCmd(btn_choose);
                et.setText("小车停止");
                Intent intent=new Intent();
                intent.setClass(Mode2.this,MainActivity.class);
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


    public void send_Cmd(String msg){
        new Thread(() ->{
            myTcpClient.sendMsg(msg);
        }).start();
    }

    //    @SuppressLint("NonConstantResourceId")
    public void sendCmd(View v) {
        int id = v.getId();
        if (id == R.id.w2) {
            send_Cmd("2w");
        } else if (id == R.id.q2) {
            send_Cmd("2q");
        } else if (id == R.id.e2) {
            send_Cmd("2e");
        } else if (id == R.id.a2) {
            send_Cmd("2a");
        } else if (id == R.id.d2) {
            send_Cmd("2d");
        } else if (id == R.id.t2) {
            send_Cmd("2t");
        } else if (id == R.id.s2) {
            send_Cmd("2s");
        } else if (id == R.id.rechoose2) {
            send_Cmd(" return");
        }
    }


}
