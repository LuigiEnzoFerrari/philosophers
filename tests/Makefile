LIST=test_list
TIME=test_time

CFLAGS += -Wall -Wextra
INCLUDE_DIRS += -I ./minunit/ -I ../include/
LIBS += -lm

SRCS =../srcs/list.c ../srcs/convert_time.c

MIN = ./minunit/minunit.h

HEADERS = ../include/philo.h

# Os-specific settings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lrt
endif

all: $(LIST) $(TIME)

$(LIST): test_list.c $(MIN) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDE_DIRS) $< -o $@

$(TIME): test_time.c $(MIN) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDE_DIRS) $< -o $@

$(MIN):
	git submodule update --init

clean:
	$(RM) $(LIST) $(TIME)

fclean: clean
