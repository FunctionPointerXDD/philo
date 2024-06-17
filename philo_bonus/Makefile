NAME = philo_bonus

SRCS = main_bonus.c init_bonus.c monitoring_bonus.c routine_bonus.c safe_func_bonus.c utils_bonus.c 
OBJS = $(SRCS:%.c=%.o)

INC = philo_bonus.h

CC = cc
CFLAGS = -Wall -Werror -Wextra
##DFLAG = -g -fsanitize=thread
RM = rm -rf
MAKE = make

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	$(CC) $(DFLAG) $(CFLAGS) $(OBJS) -o $@

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
