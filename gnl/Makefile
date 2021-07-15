GNL = gnl.a

SRCS = ./get_next_line.c ./get_next_line_utils.c

HEADER = ./get_next_line.h

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: ${GNL}

${GNL}: ${HEADER} ${OBJS}
	ar rcs ${GNL} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${GNL}

re: fclean all

.PHONY: all clean fclean re
