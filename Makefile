CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/snake.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/snake_game

all: $(BIN_DIR) $(EXEC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(EXEC)
	$(EXEC)
