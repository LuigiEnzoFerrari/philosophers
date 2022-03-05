NAME=test

CFLAGS += -Wall -Wextra
INCLUDE_DIRS += -I ./minunit/ -I ../include/
LIBS += -lm

SRCS=../srcs/list.c

MIN = ./minunit/minunit.h

# Os-specific settings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lrt
endif

$(NAME): main_test.c $(MIN) ../include/philo.h
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDE_DIRS) $< -o $@

$(MIN):
	git submodule update --init

clean:
	$(RM) $(NAME)

