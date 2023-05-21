CC = gcc
CFLAGS = -Wall -Wextra

# Ścieżki do plików źródłowych
SRC_DIR = control
BST_DIR = sp_bst

# Nazwy plików źródłowych i obiektowych
MAIN_SRC = $(SRC_DIR)/main.c
BST_SRC = $(BST_DIR)/sp_bst.c
BST_HEADER = $(BST_DIR)/sp_bst.h
BST_OBJ = $(BST_DIR)/sp_bst.o

# Nazwa wyjściowego pliku wykonywalnego
TARGET = ex

all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(BST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BST_OBJ): $(BST_SRC) $(BST_HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(BST_OBJ)