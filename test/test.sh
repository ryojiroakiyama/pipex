echo xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
echo "----------------------------------------------- ./cp_pipex $1 \"$2\" \"$3\" $4"
./cp_pipex $1 "$2" "$3" $4
cat $4
echo "----------------------------------------------- < $1 $2 | $3"
< $1 $2 | $3 > $4
cat $4
