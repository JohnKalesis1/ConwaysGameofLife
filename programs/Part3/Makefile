# paths
LIB = ../../lib
INCLUDE = ../../include
# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = memory_line.o  $(LIB)/k08.a  $(LIB)/libbmp.a

# Το εκτελέσιμο πρόγραμμα
EXEC = memory_line

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)
$(LIB)/k08.a:
	$(MAKE) -C $(LIB) k08.a
$(LIB)/libbmp.a:
	$(MAKE) -C $(LIB) libbmp.a

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) 
