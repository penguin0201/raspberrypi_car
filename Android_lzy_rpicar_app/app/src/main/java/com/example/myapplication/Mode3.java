package com.example.myapplication;

import static com.example.myapplication.MainActivity.myTcpClient;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;


public class Mode3 extends AppCompatActivity {
    Button Button1,btn_w3,btn_p3,btn_t3;
    EditText et3,dis;
    String distance;
    WebView webView;
    private Handler handler = new Handler();
    private Handler handler2 = new Handler();
    private Runnable runnable = new Runnable() {
        @Override
        public void run() {
            // 调用你想要执行的方法a
            send_Cmd("3p");
            rcvMsgHandler();
            dis.setText(distance);
            // 每1000毫秒（1秒）后再次执行
            handler.postDelayed(this, 500);
        }
    };
    private Runnable runnable2 = new Runnable() {
        @Override
        public void run() {
            // 调用你想要执行的方法a
            send_Cmd("3w");
            rcvMsgHandler();
            dis.setText(distance);
            // 每1000毫秒（1秒）后再次执行
            handler2.postDelayed(this, 200);
        }
    };
    private boolean isLongPressed = false;

    @SuppressLint({"MissingInflatedId", "ClickableViewAccessibility", "SetJavaScriptEnabled"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mode3);

        et3=findViewById(R.id.et3);
        dis=findViewById(R.id.dis);

        webView=findViewById(R.id.webcam);
        webView.loadUrl("http://192.168.205.124:8081/");
        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setUseWideViewPort(true);
        webSettings.setLoadWithOverviewMode(true);
        webSettings.setBuiltInZoomControls(true);
        webSettings.setSupportZoom(true);
        webSettings.setLayoutAlgorithm(WebSettings.LayoutAlgorithm.SINGLE_COLUMN);

        Button1=findViewById(R.id.rechoose);
        Button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                intent.setClass(Mode3.this,MainActivity.class);
                startActivity(intent);
            }
        });

        btn_p3 = findViewById(R.id.p3);
        btn_p3.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 开始长按时，发送消息执行a方法
                        handler.post(runnable);
                        isLongPressed = true;
                        return true; // 表示事件已被消费
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        // 手指抬起或滑动时，移除消息不再执行a方法
                        handler.removeCallbacks(runnable);
//                        send_Cmd("PPP");
                        isLongPressed = false;
                        return true; // 表示事件已被消费
                }
                return false; // 事件未被消费，将传递给下一个监听器
            }
        });

        btn_w3 = findViewById(R.id.w3);
        btn_w3.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // 开始长按时，发送消息执行a方法
                        handler2.post(runnable2);
                        isLongPressed = true;
                        return true; // 表示事件已被消费
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        // 手指抬起或滑动时，移除消息不再执行a方法
                        handler2.removeCallbacks(runnable2);
                        send_Cmd("3t");
                        isLongPressed = false;
                        return true; // 表示事件已被消费
                }
                return false; // 事件未被消费，将传递给下一个监听器
            }
        });

        btn_t3=findViewById(R.id.t3);
        btn_t3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                new UdpStopThread().start();
                send_Cmd("3t");
            }
        });
    }

    private void rcvMsgHandler(){
        new Thread(() -> {
            while (true){
                if (myTcpClient.serverStatus != -1){
                    String msg = myTcpClient.rcvMsg();
                    distance = msg;
                    if (msg != null){
                        Log.v("接收到服务端的消息：",msg);
                        System.out.println(msg);
//                        et.setText(msg);
                    }
                }else {
                    break;
                }
            }
        }).start();
    }

    public void send_Cmd(String msg){
        new Thread(() ->{
            myTcpClient.sendMsg(msg);
        }).start();
    }

}
