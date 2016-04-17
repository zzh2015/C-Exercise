/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: sudoku_server.cpp
*******************************************************************************/
#include "sudoku.h"

#include <muduo/base/Atomic.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

#include <algorithm>
#include <functional>

#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class SudokuServer
{
    public:
        SudokuServer(EventLoop *loop, const InetAddress &listenAddr)
            : m_Server(loop, listenAddr, "SudokuServer"),
            m_StartTime(Timestamp::now())
    {
        m_Server.setConnectionCallback(std::bind(&SudokuServer::onConnection, this, std::placeholders::_1));
        m_Server.setMessageCallback(std::bind(&SudokuServer::onMessage, this,
                    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }
        void start()
        {
            m_Server.start();
        }
    private:
        void onConnection(const TcpConnectionPtr &conn)
        {
            LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
                << conn->localAddress().toIpPort() << " is "
                << (conn->connected() ? "UP" : "DOWN");
        }

        void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp)
        {
            LOG_DEBUG << conn->name();

            size_t len = buf->readableBytes();
            while (len >= kCells + 2) {
                const char *crlf = buf->findCRLF();
                if (crlf) {
                    string request(buf->peek(), crlf);
                    buf->retrieveUntil(crlf + 2);
                    len = buf->readableBytes();
                    if (!processRequest(conn, request)) {
                        conn->send("Bad Request!\r\n");
                        conn->shutdown();
                        break;
                    }
                } else if (len > 100) {
                    conn->send("Id too long!\r\n");
                    conn->shutdown();
                    break;
                } else {
                    break;
                }
            }
        }

        bool processRequest(const TcpConnectionPtr &conn, const string &request)
        {
            string id;
            string puzzle;
            bool goodRequest = true;

            auto  colon = std::find(request.begin(), request.end(), ':');
            if (colon != request.end()) {
                id.assign(request.begin(), colon);
                puzzle.assign(colon+1, request.end());
            } else {
                puzzle = request;
            }

            if (puzzle.size() == implicit_cast<size_t>(kCells)) {
                LOG_DEBUG << conn->name();
                string result = solveSudoku(puzzle);
                if (id.empty()) {
                    conn->send(result + "\r\n");
                } else {
                    conn->send(id + ":" + result + "\r\n");
                }
            } else {
                goodRequest = false;
            }

            return goodRequest;
        }

        TcpServer m_Server;
        Timestamp m_StartTime;
};

//b:000000010400000000020000000000050407008000300001090000300400200050100000000806000
//b:693784512487512936125963874932651487568247391741398625319475268856129743274836159
int main()
{
    LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
    EventLoop loop;
    InetAddress listenAddr(9981);
    SudokuServer server(&loop, listenAddr);
    server.start();
    loop.loop();
    return 0;
}



