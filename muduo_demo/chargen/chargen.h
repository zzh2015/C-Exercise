/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: chargen.h
*******************************************************************************/
#ifndef _chargen_H_
#define _chargen_H_

#include <muduo/net/TcpServer.h>

class ChargenServer
{
    public:
        ChargenServer(muduo::net::EventLoop *loop,
                const muduo::net::InetAddress &listenAddr,
                bool print = false);
        void start();
    private:
        void onConnection(const muduo::net::TcpConnectionPtr &conn);
        void onMessage(const muduo::net::TcpConnectionPtr &conn,
                muduo::net::Buffer *buf,
                muduo::Timestamp time);
        void onWriteComplete(const muduo::net::TcpConnectionPtr &conn);
        void printThroughput();

        muduo::net::TcpServer m_Server;
        muduo::string m_Message;
        int64_t m_Transferred;
        muduo::Timestamp m_StartTime;
};

#endif
