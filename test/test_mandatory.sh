#infile outfile not exist
rm outfile
./for_test_mandatory.sh infile "cat -e" "cat -n" outfile
./for_test_mandatory.sh infilee "ls -l" "wc -l" outfile

#normal
./for_test_mandatory.sh infile "ls -l" "wc -l" outfile
./for_test_mandatory.sh infile "grep a1" "wc -w" outfile
./for_test_mandatory.sh infile "uname" "cat -e -n -s" outfile

#command not exist
./for_test_mandatory.sh infile "ca" "wc -l" outfile
./for_test_mandatory.sh infile "cat" "ca" outfile

#no execute authority
./for_test_mandatory.sh infile "./noauth_execfile" "wc -l" outfile
./for_test_mandatory.sh infile "cat" "./noauth_execfile" outfile

#option not exist
./for_test_mandatory.sh infile "cat" "wc -s" outfile

#file exist and execauthority but not executable file
./for_test_mandatory.sh infile not_executable_file ls outfile

#big file
#./for_test_mandatory.sh ./other_utils/big_file "cat -e" "cat -n" outfile

#env==NULL
echo "==>start<=="
echo "----------------------------------------------- env -i ./cp_pipex infile \"ls -l\" \"wc -l\" outfile"
env -i ./cp_pipex infile "ls -l" "wc -l" outfile
cat outfile
echo "----------------------------------------------- env -i bash < infile ls -l | env -i bash wc -l > outfile"
env -i bash < infile ls -l | env -i bash wc -l > outfile
cat outfile
echo "==>end<=="
echo "\n\n\n"
