// main.cpp
#include <iostream>
#include <stdexcept>

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
    return 0;
}