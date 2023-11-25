// DataManager.h
#pragma once
#include "sqlmanager.h"
#include <string>

class DataManager {
public:
    DataManager(SQLManager& sqlManager);
    ~DataManager();

    void fetchDataAndProcess();

private:
    SQLManager& sqlManager;
};
