function excute(){
	echo "---------------------------------./pipex $1 \"$2\" \"$3\" $4"
	echo "" > $4
	./cp_pipex $1 "$2" "$3" $4
	cat $4
#	echo status:`echo $?`
	echo ""
	echo "" > $4
	`< $1 $2 | $3 > $4`
	cat $4
#	echo status:`echo $?`
}

excute infile "ls -l" "wc -l" outfile
excute infile "grep a1" "wc -w" outfile
excute infile "cat -e" "cat -n" outfile
excute infile "cat" "wc -s" outfile
excute infile "ca" "wc -l" outfile
excute infile "./no_exec_authority" "wc -l" outfile
excute infile "cat" "ca" outfile
excute infile "cat" "./no_exec_authority" outfile
excute infil "ls -l" "wc -l" outfile
