// SQLManager.cpp
#include "../include/sqlmanager.h"
#include <iostream>

SQLManager::SQLManager(DBConnector& dbConnector) : dbConnector(dbConnector) {
    // Constructor
}

SQLManager::~SQLManager() {
    // Destructor
}

bool SQLManager::executeQuery(const std::string &query, pugi::xml_document &resultDocument)
{
    PGconn *connection = dbConnector.getConnection();

    if (!connection)
    {
        std::cout << "Cant reach the connection" << std::endl;
        return false; // No se pudo obtener la conexión
    }

    PGresult *result = PQexec(connection, query.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK && PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        PQclear(result);
        return false; // La ejecución de la consulta no fue exitosa
    }

    // Convertir los resultados a formato XML
    int numRows = PQntuples(result);
    int numCols = PQnfields(result);

    pugi::xml_node rootNode = resultDocument.append_child("result");

    for (int i = 0; i < numRows; ++i)
    {
        pugi::xml_node rowNode = rootNode.append_child("row");

        for (int j = 0; j < numCols; ++j)
        {
            const char *fieldName = PQfname(result, j);
            const char *fieldValue = PQgetvalue(result, i, j);

            // Agregar cada campo como un elemento XML
            rowNode.append_child(fieldName).text().set(fieldValue);
        }
    }

    PQclear(result);
    return true; // La consulta se ejecutó con éxito
}