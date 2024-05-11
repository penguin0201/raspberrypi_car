package com.example.myapplication;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Button;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

public class MainActivity extends AppCompatActivity {
    public static MyTcpClient myTcpClient;

    Button Button1,Button2,Button3,Button4,Button5,btn_1,btn_mu1,btn_mu2,btn_mu3;
    WebView webView;

    @SuppressLint({"MissingInflatedId", "SetJavaScriptEnabled"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
//        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
//            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
//            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
//            return insets;
//        });

        Button1=findViewById(R.id.modee1);
        Button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCmd(Button1);
                Intent intent=new Intent();
                intent.setClass(MainActivity.this,Mode1.class);
                startActivity(intent);
            }
        });

        Button2=findViewById(R.id.modee2);
        Button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send_Cmd(" in mode 2 now");
                Intent intent=new Intent();
                intent.setClass(MainActivity.this,Mode2.class);
                startActivity(intent);
            }
        });

        Button3=findViewById(R.id.modee3);
        Button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                intent.setClass(MainActivity.this,Mode3.class);
                startActivity(intent);
            }
        });

        Button4=findViewById(R.id.modee4);
        Button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent();
                intent.setClass(MainActivity.this,Mode4.class);
                startActivity(intent);
            }
        });

        btn_1=findViewById(R.id.lights);
        btn_1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendCmd(btn_1);
            }
        });

        Button5=findViewById(R.id.webskip);
//        final Uri uri = Uri.parse("https://baike.baidu.com/item/%E5%A7%9C%E5%AE%87%E7%BF%94");
        Button5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                MyTcpClient_Init();
//                Intent intent=new Intent(Intent.ACTION_VIEW,uri);
//                startActivity(intent);
            }
        });

        btn_mu1=findViewById(R.id.mus1);
        btn_mu1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send_Cmd("music1");
            }
        });

        btn_mu2=findViewById(R.id.mus2);
        btn_mu2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send_Cmd("music2");
            }
        });

        btn_mu3=findViewById(R.id.mus3);
        btn_mu3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send_Cmd("music3");
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

    public void MyTcpClient_Init(){
        myTcpClient = new MyTcpClient();
        new Thread(() ->{
            if (myTcpClient.connect("192.168.205.124",6969)){    //连接
                rcvMsgHandler();
                for (int i = 0; i < 5; i++){
                    if (myTcpClient.serverStatus != -1){                //防止app闪退
                        try {
                            myTcpClient.sendMsg(" Msg"+" "+(i+1));
                            Thread.sleep(500);
                        } catch (Exception e) {
                            throw new RuntimeException(e);
                        }
                    }else {
                        break;
                    }
                }
            }
        }).start();
    }

    private void rcvMsgHandler(){
        new Thread(() -> {
            while (true){
                if (myTcpClient.serverStatus != -1){
                    String msg = myTcpClient.rcvMsg();
                    if (msg != null){
                        Log.v("接收到服务端的消息：",msg);
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
        } else if (id == R.id.modee1) {
            send_Cmd(" in mode 1 now");
        } else if (id == R.id.lights) {
            send_Cmd("lights");
        }
    }




}

