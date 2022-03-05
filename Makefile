NAME=philo

all: $(NAME)

$(NAME): main.c
	clang main.c -lpthread -I include/ -o $@

run:
	bash philo

clean:
	$(RM) $(NAME)
