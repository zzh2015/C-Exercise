/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: chargen.cpp
*******************************************************************************/
#include "chargen.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <functional>
#include <boost/bind.hpp>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

ChargenServer::ChargenServer(EventLoop *loop, const InetAddress &listenAddr, bool print)
    : m_Server(loop, listenAddr, "ChargenServer"),
    m_Transferred(0),
    m_StartTime(Timestamp::now())
{
    m_Server.setConnectionCallback(
            std::bind(&ChargenServer::onConnection, this, std::placeholders::_1));
    m_Server.setMessageCallback(
            std::bind(&ChargenServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    m_Server.setWriteCompleteCallback(
            std::bind(&ChargenServer::onWriteComplete, this, std::placeholders::_1));
    if (print) {
        //loop->runEvery(3.0, std::bind(&ChargenServer::printThroughput, this));
    }

    string line;
    for (auto i=33; i<127; ++i) {
        line.push_back(char(i));
    }
    line += line;

    for (auto i=0; i<127-33; ++i) {
        m_Message += line.substr(i, 72) + '\n';
    }
}

void ChargenServer::start()
{
    m_Server.start();
}

void ChargenServer::onConnection(const TcpConnectionPtr &conn)
{
    LOG_INFO << "ChargenServer - " << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected()) {
        conn->setTcpNoDelay(true);
        conn->send(m_Message);
    }
}

void ChargenServer::onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time)
{
    string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " discards " << msg.size()
        << " bytes received at " << time.toString();
}

void ChargenServer::onWriteComplete(const TcpConnectionPtr &conn)
{
    m_Transferred += m_Message.size();
    conn->send(m_Message);
}

void ChargenServer::printThroughput()
{
    Timestamp endTime = Timestamp::now();
    double time = timeDifference(endTime, m_StartTime);
    printf("%4.3f MiB/s\n", static_cast<double>(m_Transferred)/time/1024/1024);
    m_Transferred = 0;
    m_StartTime = endTime;
}
