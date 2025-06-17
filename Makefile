NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
RM = rm -f

SRCS = srcs/philosophers.c srcs/utils.c srcs/game_threads.c \
		srcs/inits.c srcs/parsing.c srcs/philo_threads.c \
		srcs/threads_utils.c 
OBJTS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJTS)
	@$(CC) $(CFLAGS) $(OBJTS) -o $(NAME)

clean:
	@$(RM) $(OBJTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re