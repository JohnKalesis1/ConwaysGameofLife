# paths
LIB = ../../lib
INCLUDE = ../../include
# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = read_line_adv.o  $(LIB)/k08.a 

# Το εκτελέσιμο πρόγραμμα
EXEC = read_line_adv

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

$(LIB)/k08.a:
	$(MAKE) -C $(LIB) k08.a

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) 
