NAME = philo

SRCS = main.c utils.c utils_2.c safe_access.c routine.c init.c monitoring.c
OBJS = $(SRCS:%.c=%.o)

INC = philo.h

CC = cc
CFLAGS = -Wall -Werror -Wextra
##DFLAG = -g -fsanitize=thread
RM = rm -rf
MAKE = make

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	$(CC) $(DFLAG) $(CFLAGS) $(OBJS) -o $@

$(OBJS): $(SRCS)
	$(CC) $(DFLAG) $(CFLAGS) -c $(SRCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
