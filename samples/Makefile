# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# ========

.PHONY : all

all :
	make all -C $(MK_ROOT)glfw3/
	make all -C $(MK_ROOT)sdl3/
	make all -C $(MK_ROOT)sfml/
	make all -C $(MK_ROOT)null/

.PHONY : clean

clean :
	make clean -C $(MK_ROOT)glfw3/
	make clean -C $(MK_ROOT)sdl3/
	make clean -C $(MK_ROOT)sfml/
	make clean -C $(MK_ROOT)null/
	
# ========
