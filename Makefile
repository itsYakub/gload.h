# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= gload

# ========

TARGET		= $(MK_ROOT)$(MK_NAME).h
GENERATOR	= $(MK_ROOT)gen/$(MK_NAME)-gen.py

# ========

.PHONY : all

all : generate install

.PHONY : gen

gen :
	python3 $(GENERATOR) -o $(TARGET)

.PHONY : install

install :
	mkdir /usr/local/include/$(MK_NAME)/
	cp -f $(TARGET) /usr/local/include/$(MK_NAME)/
	ln -s /usr/local/include/$(MK_NAME)/$(MK_NAME).h /usr/local/include/$(MK_NAME).h

.PHONY : remove

remove :
	rm -rf /usr/local/include/$(MK_NAME)
	rm -f /usr/local/include/$(MK_NAME).h

# ========
