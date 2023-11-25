// SQLManager.h
#pragma once
#include "dbconnector.h"
#include <string>

class SQLManager {
public:
    SQLManager(DBConnector& dbConnector);
    ~SQLManager();

    bool executeQuery(const std::string& query);

private:
    DBConnector& dbConnector;
};