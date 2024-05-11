package com.example.myapplication;

import android.util.Log;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

public class MyTcpClient {
    private Socket client;
    private OutputStream out;
    private InputStream in;
    public int serverStatus = 1;  //服务端状态：服务端主动断开其值为-1（需要用InputStream.read来判断）

    public MyTcpClient() {
    }

    public boolean connect(String IP, int Port) {
        boolean isConnect = false;
        try {
            //client = new Socket(IP,Port)
            if (client == null) {
                client = new Socket();
            }
            SocketAddress socketAddress = new InetSocketAddress(IP, Port);  //设置IP和端口
            client.connect(socketAddress, 2000);
            if (client.isConnected()) {
                Log.v("MyTcpClient-------->", "成功连接上服务端");
                isConnect = true;
            }
        } catch (Exception e) {
            Log.v("MyTcpClient-------->", "链接服务端失败" + e.getMessage());
            isConnect = false;
            e.printStackTrace();
        }
        return isConnect;
    }

    //发送消息
    public void sendMsg(String msg) {
        try {
            if (out == null) {
                out = client.getOutputStream();  //获得数据发送通道
            }
            out.write(msg.getBytes());           //发送数据
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //接收消息
    public String rcvMsg() {
        byte[] msg = new byte[128];
        int msg_len;
        String Msg = null;
        try {
            if (in == null) {
                in = client.getInputStream();  //获得数据接收通道
            }
            msg_len = in.read(msg);           //接受数据
            if (msg_len == -1) {                //服务端主动断开
                serverStatus = msg_len;
                Log.v("MyTcpClient-------->", "服务端已断开");
                closeAll();
                return null;
            }
            Msg = new String(msg, 0, msg_len);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return Msg;
    }

    //关闭所有
    public void closeAll() {
        try {
            if (out != null) {
                out.close();
                out = null;
            }
            if (in != null) {
                in.close();
                in = null;
            }
            if (client != null) {
                client.close();
                client = null;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //断开链接
    public void disConnect() {
        closeAll();
    }
}
