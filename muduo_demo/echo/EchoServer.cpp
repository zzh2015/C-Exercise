/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: EchoServer.cpp
*******************************************************************************/
#include "EchoServer.h"

#include <muduo/base/Logging.h>

#include <functional>

EchoServer::EchoServer(muduo::net::EventLoop *loop,
        const muduo::net::InetAddress &listenAddr)
    : m_Server(loop, listenAddr, "EchoServer")
{
    m_Server.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
    m_Server.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void EchoServer::start()
{
    m_Server.start();
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr &conn,
        muduo::net::Buffer *buf, muduo::Timestamp time)
{
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
        << " data received at " << time.toString();
    conn->send(msg);
}
