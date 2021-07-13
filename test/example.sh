./test.sh infile "ls -l" "wc -l" outfile
./test.sh infile "grep a1" "wc -w" outfile
./test.sh infile "cat -e" "cat -n" outfile
./test.sh infile "cat" "wc -s" outfile
./test.sh infile "ca" "wc -l" outfile
./test.sh infile "./no_exec_authority" "wc -l" outfile
./test.sh infile "cat" "ca" outfile
./test.sh infile "cat" "./no_exec_authority" outfile
./test.sh infil "ls -l" "wc -l" outfile
