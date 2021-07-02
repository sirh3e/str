CC	:= gcc
CFLAGS	:= -std=c99 -O2
CFLAGS	+= -Wall -Wextra -Wno-unused-parameter 
CFLAGS	+= -Werror=format-security -Werror=implicit-function-declaration
CFLAGS	+= -pipe
CFLAGS	+= -fasynchronous-unwind-tables -fexceptions
CFLAGS	+= -D_FORTIFY_SOURCE=2 

SRCS	:= $(wildcard *.c) 
OBJS	:= $(SRCS:.c=.o)

TESTS	:= tests

.PHONY: all
all:	$(TESTS)
	@echo running $(TESTS)
	./$(TESTS)

$(TESTS): $(OBJS)
	@echo $(CC) $(CFLAGS) -o $(TESTS) $(OBJS)
	$(CC) $(CFLAGS) -o $(TESTS) $(OBJS)

.c.o:
	@echo $(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: format
format:
	clang-format -i $(SRCS)

.PHONY: clean
clean:
	rm -fv $(TESTS) $(OBJS)
