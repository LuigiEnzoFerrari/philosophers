NAME=philo

PARTY=eat_or_die.c take_a_nap.c the_party.c take_forks.c
PATH_PARTY= $(addprefix srcs/the_party/, $(PARTY))

PREPARE=list.c convert_time.c prepare_party.c
PREPARE_PATH=$(addprefix srcs/, $(PREPARE))

SRCS=$(PREPARE_PATH) $(PATH_PARTY)
SANIT = -fsanitize=address 

all: $(NAME)

$(NAME): main.c $(SRCS)
	clang -g main.c $(SRCS) -lpthread -I include/ -o $@

run:
	bash philo

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all