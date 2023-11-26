// SQLManager.h
#pragma once
#include "dbconnector.h"
#include <string>
#include "pugixml.hpp"
class SQLManager
{
public:
    SQLManager(DBConnector &dbConnector);
    ~SQLManager();

    bool executeQuery(const std::string &, pugi::xml_document &);

private:
    DBConnector &dbConnector;
};