NAME=philo

PARTY=eat_or_die.c take_a_nap.c the_party.c take_forks.c
PATH_PARTY= $(addprefix srcs/the_party/, $(PARTY))

PREPARE=list.c convert_time.c prepare_party.c utils.c you_should_not_pass.c
PREPARE_PATH=$(addprefix srcs/, $(PREPARE))

SRCS=$(PREPARE_PATH) $(PATH_PARTY)
SANIT = -g -fsanitize=address 

all: $(NAME)

$(NAME): main.c $(SRCS)
	clang $(SANIT) main.c $(SRCS) -lpthread -I include/ -o $@

run:
	bash philo

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all