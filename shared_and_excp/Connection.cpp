#include "Connection.h"

#include <iostream>
#include <memory>

using namespace std;

Connection connect(Destination *des)
{
    static int no = 0;
    Connection con;
    

    con.connectionInfo = des->info;
    con.connectionNum = ++no;

    return con;
}

void disconnect(Connection con)
{
    cout << "connection info: " << con.connectionInfo << endl;
    cout << "connection no: " << con.connectionNum << endl;

    cout << "disconnect!" << endl;
}

void end_connection(Connection *p) { disconnect(*p); }

void f(Destination &des)
{
    Connection con = connect(&des);
#ifdef LAM
    shared_ptr<Connection> p(&con, [] (Connection *p) {disconnect(*p);});
#else
    shared_ptr<Connection> p(&con, end_connection);
#endif

    cout << "leave f" << endl;
}

