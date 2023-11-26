// main.cpp
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../include/password.h"
#include "../include/dbconnector.h"
#include "../include/sqlmanager.h"
#include "../include/datamanager.h"

#ifdef DEVELOPMENT
const std::string dbConnectionString = "host=localhost dbname=password_manager_database user=myuser password=mypassword";
#else
#endif

int main()
{
    DBConnector connectorDirect(dbConnectionString);
    connectorDirect.connect();
    // Crear una instancia de SQLManager utilizando el DBConnector
    SQLManager sqlManager(connectorDirect);

    // Crear un documento XML para almacenar los resultados
    pugi::xml_document resultDocument;

    std::string query = "SELECT * FROM password;";

    // Llamar a executeQuery y verificar si tiene éxito
    if (sqlManager.executeQuery(query, resultDocument))
    {
        // Convertir el documento XML a una cadena para imprimirlo
        std::stringstream ss;
        resultDocument.save(ss, "  "); // 2 espacios de sangría para una presentación más legible
        std::cout << "Resultados XML:\n"
                  << ss.str() << std::endl;
    }
    else
    {
        std::cerr << "La ejecución de la consulta falló." << std::endl;
    }

    return 0;
}