NAME = philo

LIBFT = ./libft/libft.a

FLAGS = -pthread -Wall -Wextra -Werror -Iincludes

SRCS = main.c srcs/utils1.c srcs/utils2.c srcs/philo_utils.c srcs/philo_actions.c \
		srcs/philo_checks.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: ${NAME}

norm:
	norminette $(SRCS) includes

${NAME}: ${OBJS}
	gcc ${FLAGS} ${OBJS} -g -o ${NAME}

%.o: %.c
	gcc ${FLAGS} -c $< -o $@

clean:
	${RM} ${OBJS} ${OBJS}

fclean: clean
	${RM} ${NAME}
	
re: fclean all
