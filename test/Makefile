PIPEX = ../pipex

CP_PIPEX = ./cp_pipex

DIR = ../

RM = rm -f

all:
	${MAKE} -C ${DIR}
	@make ${CP_PIPEX}

${CP_PIPEX}:
	cp ${PIPEX} ${CP_PIPEX}

run:
	./test.sh ${1} "${2}" "${3}" ${4}

help:
	echo "make run 1=infile 2="cat -e" 3="cat -n" 4=outfile"
clean:
	${MAKE} -C ${DIR} clean

fclean: clean
	${MAKE} -C ${DIR} fclean
	${RM} ${CP_PIPEX}

re: fclean all

.PHONY: all clean fclean re
