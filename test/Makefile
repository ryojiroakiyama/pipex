PIPEX = ../pipex

PIPEX_BONUS = ../pipex_bonus

CP_PIPEX = ./cp_pipex

CP_PIPEX_BONUS = ./cp_pipex_bonus

PIPEX_DIR = ../

RM = rm -f

all:
	${MAKE} -C ${PIPEX_DIR}
	@make ${CP_PIPEX}

bonus:
	${MAKE} -C ${PIPEX_DIR} bonus
	@make ${CP_PIPEX_BONUS}

${CP_PIPEX}: ${PIPEX}
	cp ${PIPEX} ${CP_PIPEX}

${CP_PIPEX_BONUS}: ${PIPEX_BONUS}
	cp ${PIPEX_BONUS} ${CP_PIPEX_BONUS}

run:
#	./test.sh ${1} "${2}" "${3}" ${4}
	./test_mandatory.sh

run_bonus:
	./test_bonus.sh

help:
	echo "make run 1=infile 2="cat -e" 3="cat -n" 4=outfile"

clean:
	${MAKE} -C ${PIPEX_DIR} clean

fclean: clean
	${MAKE} -C ${PIPEX_DIR} fclean
	${RM} ${CP_PIPEX} ${CP_PIPEX_BONUS}

re: fclean all

.PHONY: all clean fclean re
