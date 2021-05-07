#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void	error(char* error1, char* error2, int ex)
{
	for (int i = 0; error1 && error1[i]; i++)
		write(2, &error1[i], 1);
	for (int i = 0; error2 && error2[i]; i++)
		write(2, &error2[i], 1);
	write(2, "\n", 1);
	if (ex)
		exit(ex);
}

void	cd(char **argv, int* i)
{
	int start = *i;
	for (; argv[*i] && strcmp(argv[*i], ";") && strcmp(argv[*i], "|"); (*i)++) {}
	if (*i - start != 2)
		error("error: cd: bad arguments", NULL, 0);
	else if (chdir(argv[start+1]) == -1)
		error("error: cd: cannot change directory to ", argv[start+1], 0);
}

int		execute(char** argv, int* i, int* prevFD, char **env) {
	int start = *i;
	int tmp = *prevFD;
	int fd[2] = { 0, 1 };
	int pipeCount = 0;

	for (; argv[*i] && strcmp(argv[*i], ";") && strcmp(argv[*i], "|"); (*i)++) {}
	if (argv[*i] && !strcmp(argv[*i], "|"))	{
		pipeCount++;
		pipe(fd);
	}
	argv[*i] = NULL;
	*prevFD = fd[0];
	fd[0] = tmp;
	int pid = fork();
	if (pid == -1)
		error("fatal error", NULL, 1);
	else if (!pid) {
		if (fd[0] != 0) {
			if (dup2(fd[0], 0) == -1)
				error("fatal error", NULL, 1);
			if (close(fd[0]) == -1)
				error("fatal error", NULL, 1);
		}
		if (fd[1] != 1) {
			if (dup2(fd[1], 1) == -1)
				error("fatal error", NULL, 1);
			if (close(fd[1]) == -1)
				error("fatal error", NULL, 1);
		}
		if (execve(argv[start], argv + start, env) == -1)
			error("error: cannot execute ", argv[start], 1);
	}
	if (fd[0] != 0 && close(fd[0]) == -1)
		error("fatal error", NULL, 1);
	if (fd[1] != 1 && close(fd[1]) == -1)
		error("fatal error", NULL, 1);
	return (pipeCount);
}

int		main(int argc, char** argv, char** env) {
	int prevFD = 0;
	int pids = 0;

	for (int i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "cd"))
			cd(argv, &i);
		else if (strcmp(argv[i], ";")) {
			pids++;
			if (!execute(argv, &i, &prevFD, env))
				for (; pids; pids--)
					waitpid(-1, NULL, 0);
		}
	}
	for (; pids; pids--)
		waitpid(-1, NULL, 0);
	return (0);
}