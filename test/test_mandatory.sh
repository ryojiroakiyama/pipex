./for_test_mandatory.sh infile "ls -l" "wc -l" outfile
./for_test_mandatory.sh infile "grep a1" "wc -w" outfile
./for_test_mandatory.sh infile "cat -e" "cat -n" outfile
./for_test_mandatory.sh infile "cat" "wc -s" outfile
./for_test_mandatory.sh infile "ca" "wc -l" outfile
./for_test_mandatory.sh infile "./no_exec_authority" "wc -l" outfile
./for_test_mandatory.sh infile "cat" "ca" outfile
./for_test_mandatory.sh infile "cat" "./no_exec_authority" outfile
./for_test_mandatory.sh infil "ls -l" "wc -l" outfile
./for_test_mandatory.sh infile not_executable_file cat outfile

echo "\n\n\n"
echo "----------------------------------------------- env -i ./cp_pipex ~~~"
env -i ./cp_pipex infile "ls -l" "wc -l" outfile
echo "----------------------------------------------- env -i bash cat  ~~~"
env -i bash < infile ls -l | wc -l outfile
