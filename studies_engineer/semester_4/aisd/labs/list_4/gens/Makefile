CC = gcc
CFLAGS = -Wall -Wextra

# Ścieżki do plików źródłowych
SRC_DIR = .

# Nazwy plików źródłowych i obiektowych
RAND_ARR_SRC = $(SRC_DIR)/rand_arr.c
INC_ARR_SRC = $(SRC_DIR)/inc_arr.c

# Nazwy wyjściowych plików wykonywalnych
RAND_ARR_TARGET = rand_arr
INC_ARR_TARGET = inc_arr

all: $(RAND_ARR_TARGET) $(INC_ARR_TARGET)

$(RAND_ARR_TARGET): $(RAND_ARR_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(INC_ARR_TARGET): $(INC_ARR_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(RAND_ARR_TARGET) $(INC_ARR_TARGET)