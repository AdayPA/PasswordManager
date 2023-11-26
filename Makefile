CC = g++
CFLAGS = -std=c++14 -I./include -I./third_party/gtest/googletest/include -I/usr/include/postgresql -I./third_party/pugixml-1.14/src -DDEVELOPMENT
LDFLAGS = -pthread -L/usr/lib/x86_64-linux-gnu -lpq -lssl -lcrypto -L./third_party/pugixml-1.14/build -lpugixml

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = test

GTEST_DIR = third_party/gtest/googletest
DOCKER_CONTAINER_SIZE = psswd-mng-container
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))
TARGET = $(BIN_DIR)/password_manager

TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRC))
TEST_TARGET = $(BIN_DIR)/test

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(filter-out $(BUILD_DIR)/main.o, $(OBJ))
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -L$(GTEST_DIR) -lgtest -lgtest_main

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

list:
	@echo "Opciones disponibles:"
	@echo "  make          : Compila el programa principal"
	@echo "  make run      : Ejecuta el programa principal"
	@echo "  make test     : Ejecuta las pruebas"
	@echo "  make clean    : Elimina archivos generados"

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

docker:
	@if [ -z $$(docker ps -q --filter "name=$(DOCKER_CONTAINER_NAME)") ]; then \
		echo "El contenedor Docker no está en ejecución. Iniciando..."; \
		docker stop psswd-mng-container; \
		docker rm psswd-mng-container; \
		docker run -d -p 5432:5432 --name psswd-mng-container psswd-mng-postgre; \
	else \
		echo "El contenedor Docker ya está en ejecución."; \
	fi
.PHONY: all clean run test
