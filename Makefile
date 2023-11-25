CC = g++
CFLAGS = -std=c++14 -I./include -I./third_party/gtest/googletest/include -I/usr/include/postgresql
LDFLAGS = -pthread -L/usr/lib/x86_64-linux-gnu -lpq -lssl -lcrypto

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = test

GTEST_DIR = third_party/gtest/googletest

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

.PHONY: all clean run test
