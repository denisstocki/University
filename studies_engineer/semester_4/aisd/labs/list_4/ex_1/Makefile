CC = gcc
CFLAGS = -Wall -Wextra

# Ścieżki do plików źródłowych
SRC_DIR = control
BST_DIR = bst

# Nazwy plików źródłowych i obiektowych
MAIN_SRC = $(SRC_DIR)/main.c
BST_SRC = $(BST_DIR)/bs_tree.c
BST_HEADER = $(BST_DIR)/bs_tree.h
BST_OBJ = $(BST_DIR)/bs_tree.o

# Nazwa wyjściowego pliku wykonywalnego
TARGET = ex1

all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(BST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BST_OBJ): $(BST_SRC) $(BST_HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(BST_OBJ)