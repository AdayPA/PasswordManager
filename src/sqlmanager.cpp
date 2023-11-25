// SQLManager.cpp
#include "../include/sqlmanager.h"

SQLManager::SQLManager(DBConnector& dbConnector) : dbConnector(dbConnector) {
    // Constructor
}

SQLManager::~SQLManager() {
    // Destructor
}

bool SQLManager::executeQuery(const std::string& query) {
    PGconn* connection = dbConnector.getConnection();

    if (!connection) {
        return false; // No se pudo obtener la conexión
    }

    PGresult* result = PQexec(connection, query.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK && PQresultStatus(result) != PGRES_TUPLES_OK) {
        PQclear(result);
        return false; // La ejecución de la consulta no fue exitosa
    }

    PQclear(result);
    return true; // La consulta se ejecutó con éxito
}