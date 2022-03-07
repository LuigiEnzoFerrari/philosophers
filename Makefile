NAME=philo

SRCS=srcs/list.c srcs/convert_time.c

all: $(NAME)

$(NAME): main.c $(SRCS)
	clang  -g -fsanitize=address main.c $(SRCS) -lpthread -I include/ -o $@

run:
	bash philo

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all