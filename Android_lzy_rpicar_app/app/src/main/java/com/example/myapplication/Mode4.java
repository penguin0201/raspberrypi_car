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

import androidx.appcompat.app.AppCompatActivity;

public class Mode4 extends AppCompatActivity {
    Button Button1,btn_w4,btn_t4;
    EditText et4;
    WebView webView;
    private Handler handler = new Handler();
    private Runnable runnable = new Runnable() {
        @Override
        public void run() {
            // 调用你想要执行的方法a
            send_Cmd("4w");
            // 每1000毫秒（1秒）后再次执行
            handler.postDelayed(this, 200);
        }
    };

    private boolean isLongPressed = false;

    @SuppressLint({"MissingInflatedId", "ClickableViewAccessibility"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mode4);

        et4=findViewById(R.id.et4);

        webView=findViewById(R.id.webcam);
        webView.loadUrl("http://192.168.205.124:8081/");
        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setUseWideViewPort(true);
        webSettings.setLoadWithOverviewMode(true);
        webSettings.setBuiltInZoomControls(true);
        webSettings.setSupportZoom(true);
        webSettings.setLayoutAlgorithm(WebSettings.LayoutAlgorithm.SINGLE_COLUMN);

        btn_w4 = findViewById(R.id.w4);
        btn_w4.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        et4.setText("小车黑线寻迹中");
                        // 开始长按时，发送消息执行a方法
                        handler.post(runnable);
                        isLongPressed = true;
                        return true; // 表示事件已被消费
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                        // 手指抬起或滑动时，移除消息不再执行a方法
                        handler.removeCallbacks(runnable);
                        send_Cmd("4t");
                        et4.setText("小车停止");
                        isLongPressed = false;
                        return true; // 表示事件已被消费
                }
                return false; // 事件未被消费，将传递给下一个监听器
            }
        });

        btn_t4=findViewById(R.id.t4);
        btn_t4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send_Cmd("4t");
            }
        });

        Button1=findViewById(R.id.rechoose);
        Button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                intent.setClass(Mode4.this,MainActivity.class);
                startActivity(intent);
            }
        });
    }

    public void send_Cmd(String msg){
        new Thread(() ->{
            myTcpClient.sendMsg(msg);
        }).start();
    }
}
