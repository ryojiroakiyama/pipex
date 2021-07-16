PIPEX = pipex

PIPEX_BONUS = pipex_bonus

SRCS = ./srcs/main.c ./srcs/prepare_command.c ./srcs/free_exit_funcs.c

SRCS_BONUS = ./srcs_bonus/main_bonus.c ./srcs_bonus/prepare_command_bonus.c ./srcs_bonus/free_exit_funcs_bonus.c ./srcs_gnl/get_next_line.c ./srcs_gnl/get_next_line_utils.c

HEADER = ./includes

LIBFT_DIR = ./libft

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I ${LIBFT_DIR} -I ${HEADER}

RM = rm -f

all:
	${MAKE} -C ${LIBFT_DIR}
	@make ${PIPEX}

bonus:
	${MAKE} -C ${LIBFT_DIR}
	@make ${PIPEX_BONUS}

${PIPEX}: ${HEADER} ${OBJS} ${LIBFT_DIR}
	${CC} ${CFLAGS} -o ${PIPEX} ${OBJS} -L ${LIBFT_DIR} -lft

${PIPEX_BONUS}: ${HEADER} ${OBJS_BONUS} ${LIBFT_DIR}
	${CC} ${CFLAGS} -o ${PIPEX_BONUS} ${OBJS_BONUS} -L ${LIBFT_DIR} -lft

clean:
	${MAKE} -C ${LIBFT_DIR} clean
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${MAKE} -C ${LIBFT_DIR} fclean
	${RM} ${PIPEX} ${PIPEX_BONUS}

re: fclean all

.PHONY: all clean fclean re
