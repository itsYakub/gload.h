# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -ggdb3

# ========

.PHONY : all

all : null
all : glfw3
all : sdl3

.PHONY : clean

clean : clean-null
clean : clean-glfw3
clean : clean-sdl3
	
# ========

.PHONY : null

null :
	$(CC) $(CFLAGS) $(MK_ROOT)null/sample.c -o $(MK_ROOT)null/sample.out

.PHONY : clean-null

clean-null :
	rm -f $(MK_ROOT)null/sample.out


.PHONY : glfw3

glfw3 :
	$(CC) $(CFLAGS) $(MK_ROOT)glfw3/sample-legacy.c -o $(MK_ROOT)glfw3/sample-legacy.out -lglfw3 -lm
	$(CC) $(CFLAGS) $(MK_ROOT)glfw3/sample-modern33.c -o $(MK_ROOT)glfw3/sample-modern33.out -lglfw3 -lm
	$(CC) $(CFLAGS) $(MK_ROOT)glfw3/sample-modern46.c -o $(MK_ROOT)glfw3/sample-modern46.out -lglfw3 -lm

.PHONY : clean-glfw3 

clean-glfw3 :
	rm -f $(MK_ROOT)glfw3/sample-legacy.out
	rm -f $(MK_ROOT)glfw3/sample-modern33.out
	rm -f $(MK_ROOT)glfw3/sample-modern46.out


.PHONY : sdl3

sdl3 :
	$(CC) $(CFLAGS) $(MK_ROOT)sdl3/sample-legacy.c -o $(MK_ROOT)sdl3/sample-legacy.out -lSDL3
	$(CC) $(CFLAGS) $(MK_ROOT)sdl3/sample-modern33.c -o $(MK_ROOT)sdl3/sample-modern33.out -lSDL3
	$(CC) $(CFLAGS) $(MK_ROOT)sdl3/sample-modern46.c -o $(MK_ROOT)sdl3/sample-modern46.out -lSDL3

.PHONY : clean-sdl3 

clean-sdl3 :
	rm -f $(MK_ROOT)sdl3/sample-legacy.out
	rm -f $(MK_ROOT)sdl3/sample-modern33.out
	rm -f $(MK_ROOT)sdl3/sample-modern46.out

# ========
