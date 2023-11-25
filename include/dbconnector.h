// DBConnector.h
#pragma once
#include <string>
#include <libpq-fe.h>

// https://www.postgresql.org/docs/8.1/libpq.html

class DBConnector
{
public:
    DBConnector(const std::string &connInfo);
    ~DBConnector();

    bool connect();
    void disconnect();

    PGconn *getConnection() const;

private:
    PGconn *connection;
    std::string connectionInfo;
};
