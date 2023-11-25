// DataManager.cpp
#include "../include/datamanager.h"
#include <iostream>

DataManager::DataManager(SQLManager& sqlManager) : sqlManager(sqlManager) {
    // Constructor
}

DataManager::~DataManager() {
    // Destructor
}

void DataManager::fetchDataAndProcess() {
    // Implementación para recuperar datos utilizando sqlManager
    sqlManager.executeQuery("SELECT * FROM tabla_datos");
    // Procesar los datos recuperados
    std::cout << "Procesando los datos recuperados..." << std::endl;
}
