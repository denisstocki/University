CC = gcc
CFLAGS = -Wall -Wextra

# Ścieżki do plików źródłowych
SRC_DIR = control
BST_DIR = rb_bst

# Nazwy plików źródłowych i obiektowych
MAIN_SRC = $(SRC_DIR)/main.c
BST_SRC = $(BST_DIR)/rb_bst.c
BST_HEADER = $(BST_DIR)/rb_bst.h
BST_OBJ = $(BST_DIR)/rb_bst.o

# Nazwa wyjściowego pliku wykonywalnego
TARGET = ex3

all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(BST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BST_OBJ): $(BST_SRC) $(BST_HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(BST_OBJ)