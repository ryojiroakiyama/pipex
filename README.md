# Usage  
```
$> make
$> ./pipex file1 cmd1 cmd2 file2
```
The execution of the pipex program should do the same as the next shell command:
```
$> < file1 cmd1 | cmd2 > file2
```

## bonus part
```
$> make bonus
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
Must be equivalent to :
```
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```
