# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -ggdb3

# ========

.PHONY : all

all :
	$(CC) $(CFLAGS) $(MK_ROOT)sample-glfw3-legacy.c -o $(MK_ROOT)sample-glfw3-legacy.out -lglfw3 -lm
	$(CC) $(CFLAGS) $(MK_ROOT)sample-glfw3-modern33.c -o $(MK_ROOT)sample-glfw3-modern33.out -lglfw3 -lm
	$(CC) $(CFLAGS) $(MK_ROOT)sample-glfw3-modern46.c -o $(MK_ROOT)sample-glfw3-modern46.out -lglfw3 -lm

.PHONY : clean

clean:
	rm -f $(MK_ROOT)sample-glfw3-legacy.out
	rm -f $(MK_ROOT)sample-glfw3-modern33.out
	rm -f $(MK_ROOT)sample-glfw3-modern46.out

# ========
