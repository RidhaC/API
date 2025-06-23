CC = gcc
CFLAGS = -c 
SRC = insert.c delete.c extract.c
OBJ = $(SRC:.c=.o)
TEST = test
TEST_SRC = test.c
LIBS = -lcheck -lsubunit -lm -lpthread -lrt 

default: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

test: $(TEST_SRC) $(OBJ)
	$(CC) -o $(TEST) $(TEST_SRC) $(OBJ) $(LIBS) 

run: test 
	./$(TEST)

clean:
	rm -f $(OBJ) $(LIB_NAME) $(TEST)