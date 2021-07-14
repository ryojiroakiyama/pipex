./pipex infile "cat -e"

cmd_path = /usr/local/bin/cat
cmd[0] = cat
cmd[1] = -e
cmd[2] = <<
cmd[3] = av[1]
execve(cmd_path, cmd, envp)

get_next_line(0, &line);
if (ft_strncmp(line, "LIMITER", 10))
	break;
else
	ft_putstr(pipefd[WRITE], line);

consider about contl+D

dup2(pipefd[READ], 0)
exceve(path, cmd, envp);
