// DBConnector.cpp
#include "../include/dbconnector.h"

DBConnector::DBConnector(const std::string &connInfo) : connectionInfo(connInfo), connection(nullptr)
{
    // Constructor
}

DBConnector::~DBConnector()
{
    disconnect();
}

bool DBConnector::connect()
{
    connection = PQconnectdb(connectionInfo.c_str());

    if (PQstatus(connection) != CONNECTION_OK)
    {
        disconnect();
        return false;
    }

    return true;
}

void DBConnector::disconnect()
{
    if (connection)
    {
        PQfinish(connection);
        connection = nullptr;
    }
}

PGconn *DBConnector::getConnection() const
{
    return connection;
}