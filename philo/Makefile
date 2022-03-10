NAME=philo
CC=clang
CFLAG=-Wall -Werror -Wextra
SANIT = -g -fsanitize=address 

INC=include/

PARTY=eat_or_die.c take_a_nap.c the_party.c take_forks.c
PATH_PARTY= $(addprefix srcs/the_party/, $(PARTY))

PREPARE=list.c convert_time.c prepare_party.c utils.c you_should_not_pass.c
PREPARE_PATH=$(addprefix srcs/, $(PREPARE))

SRCS=main.c $(PREPARE_PATH) $(PATH_PARTY)
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAG) -lpthread $(SANIT) $(OBJS) -I ./include/ -o $@

%.o: %.c
	$(CC) $(CFLAG) -c -I ./include/ $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
