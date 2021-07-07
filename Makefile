PIPEX = pipex

LIBFT = ./libft/libft.a

SRCS = main.c

HEADER = pipex.h

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: ${PIPEX}

${PIPEX}: ${HEADER} ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} -o ${PIPEX} ${OBJS} ${LIBFT}

${LIBFT}:
	${MAKE} -C ./libft

clean:
	${RM} ${OBJS}
	${MAKE} -C ./libft clean

fclean: clean
	${RM} ${PIPEX}
	${MAKE} -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
