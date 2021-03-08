CC		:= gcc
CFLAGS	:= -std=c99 -O2
CFLAGS	+= -Wall -Wextra -Wno-unused-parameter 
CFLAGS	+= -Werror=format-security -Werror=implicit-function-declaration
CFLAGS	+= -pipe
CFLAGS	+= -fasynchronous-unwind-tables -fexceptions
CFLAGS	+= -D_FORTIFY_SOURCE=2 
