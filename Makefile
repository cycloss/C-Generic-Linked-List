HEADER_FILES = node.h list.h
SOURCE_FILES = list.c
TEST_FILES = listTest.c
OS := $(shell uname)

test: $(SOURCE_FILES) $(HEADER_FILES)
	gcc -Wall $(SOURCE_FILES) $(TEST_FILES) -o listTest

ifeq ($(OS), Darwin)

BASENAME = liblist
LIB_NAME = $(BASENAME).a
OBJECT_FILES = list.o node.o
DESTDIR = /usr/local

.PHONY: install
install: $(LIB_NAME) $(HEADER_FILES)
	mv $(LIB_NAME) $(DESTDIR)/lib
	cp $(HEADER_FILES) $(DESTDIR)/include

$(LIB_NAME): $(OBJECT_FILES)
	ar -rcs $(LIB_NAME) $(OBJECT_FILES)
	rm -f $(OBJECT_FILES)

$(OBJECT_FILES): $(SOURCE_FILES)
	gcc -c $(SOURCE_FILES)

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)/lib/$(LIB_NAME)
	rm -f $(addprefix $(DESTDIR)/include/, $(HEADER_FILES))
endif