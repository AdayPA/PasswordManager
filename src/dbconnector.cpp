// DBConnector.cpp
#include "../include/dbconnector.h"

#include <iostream>

DBConnector::DBConnector(const std::string &connInfo) : connection(nullptr), connectionInfo(connInfo) {}

DBConnector::~DBConnector()
{
    disconnect();
}

bool DBConnector::connect()
{
    connection = PQconnectdb(connectionInfo.c_str());

    if (PQstatus(connection) != CONNECTION_OK)
    {
        std::cerr << "Error de conexión: " << PQerrorMessage(connection) << std::endl;
        return false;
    }

    std::cout << "Conexión exitosa a la base de datos" << std::endl;
    return true;
}

void DBConnector::disconnect()
{
    if (connection)
    {
        PQfinish(connection);
        connection = nullptr;
        std::cout << "Desconexión exitosa" << std::endl;
    }
}

bool DBConnector::isConnected() const
{
    return connection && PQstatus(connection) == CONNECTION_OK;
}

bool DBConnector::reconnect()
{
    disconnect();
    return connect();
}

const char *DBConnector::getErrorMessage() const
{
    return PQerrorMessage(connection);
}

PGconn *DBConnector::getConnection() const
{
    return connection;
}