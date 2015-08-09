#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <string>

#define LAM 1

class Destination {
    public:
        std::string info;
        //
        Destination() {info = "unknown";}
        Destination(std::string str) : info(str) {}
};

class Connection {
    public:
        std::string connectionInfo;
        int connectionNum;

        Connection() {}
};

extern Connection connect(Destination *des);

extern void disconnect(Connection con);

extern void end_connection(Connection *p);

extern void f(Destination &des);

#endif

