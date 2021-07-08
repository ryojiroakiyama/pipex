PIPEX = pipex

SRCS = ./main.c

HEADER = ./pipex.h

LIBFT_DIR = ./libft

LIBFT = ${LIBFT_DIR}/libft.a

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I ${LIBFT_DIR}

RM = rm -f

all: ${LIBFT} ${PIPEX}

${LIBFT}: ${LIBFT_DIR}
	${MAKE} -C ${LIBFT_DIR}

${PIPEX}: ${HEADER} ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} -o ${PIPEX} ${OBJS} -L ${LIBFT_DIR} -lft

clean:
	${RM} ${OBJS}
	${MAKE} -C ./libft clean

fclean: clean
	${RM} ${PIPEX}
	${MAKE} -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
