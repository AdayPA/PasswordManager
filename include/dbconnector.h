// DBConnector.h
#pragma once
#include <string>
#include <libpq-fe.h>

class DBConnector
{
public:
    // Constructor that takes the connection string
    explicit DBConnector(const std::string &connInfo);

    // Destructor responsible for disconnecting upon leaving the scope
    ~DBConnector();

    // Method to establish the connection
    bool connect();

    // Method to disconnect
    void disconnect();

    // Checks if the connection is active
    bool isConnected() const;

    // Retries the connection in case of disconnection
    bool reconnect();

    // Retrieves detailed error messages from PostgreSQL
    const char *getErrorMessage() const;

    // Gets a pointer to the PostgreSQL connection
    PGconn *getConnection() const;

private:
    PGconn *connection;         // Pointer to the PostgreSQL connection
    std::string connectionInfo; // Connection string
};
