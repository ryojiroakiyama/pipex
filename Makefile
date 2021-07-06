SRCS = pipex.c ft_util.c ft_util2.c ft_util3.c

PIPEX = pipex

HEADER_FILES = pipex.h

OBJS = ${SRCS:.c=.o}

P_OBJS = ${P_SRCS:.c=.o}

C_OBJS = ${C_SRCS:.c=.o}

$(PIPEX): ./libft/libft.a $(OBJS)
	gcc -Wall -Wextra -Werror -o $(PIPEX) $(OBJS) ./libft/libft.a -I libft

./libft/libft.a : 
	$(MAKE) -C ./libft

%.o: %.c ${HEADER_FILES}
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o} -I libft

all: ${PIPEX}

clean:
	rm -f ${OBJS}
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f ${PIPEX}
	$(MAKE) -C ./libft fclean

re:	fclean all

.PHONY: all clean fclean re
