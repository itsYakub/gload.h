# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -ggdb3

# ========

.PHONY : all

all :
	$(CC) $(CFLAGS) $(MK_ROOT)null/sample-null.c -o $(MK_ROOT)null/sample-null.out
	
	$(CC) $(CFLAGS) $(MK_ROOT)glfw3/sample-legacy.c -o $(MK_ROOT)glfw3/sample-legacy.out -lglfw3 -lm
	$(CC) $(CFLAGS) $(MK_ROOT)glfw3/sample-modern33.c -o $(MK_ROOT)glfw3/sample-modern33.out -lglfw3 -lm
	$(CC) $(CFLAGS) $(MK_ROOT)glfw3/sample-modern46.c -o $(MK_ROOT)glfw3/sample-modern46.out -lglfw3 -lm

.PHONY : clean

clean:
	rm -f $(MK_ROOT)null/sample-null.out
	
	rm -f $(MK_ROOT)glfw3/sample-legacy.out
	rm -f $(MK_ROOT)glfw3/sample-modern33.out
	rm -f $(MK_ROOT)glfw3/sample-modern46.out

# ========
