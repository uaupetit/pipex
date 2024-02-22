/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:10:07 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 11:31:48 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child1_process(char **av, int *pipe_fd, char **envp)
{
	int	fd1;

	fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		perror("");
	if (dup2(fd1, STDIN_FILENO) < 0)
		perror("");
	close(pipe_fd[0]);
	close(fd1);
	close(pipe_fd[1]);
	execute(av[2], envp);
}

void	child2_process(char **av, int *pipe_fd, char **envp)
{
	int		fd2;

	fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("");
	if (dup2(fd2, STDOUT_FILENO) == -1)
		perror("");
	close(pipe_fd[1]);
	close(fd2);
	close(pipe_fd[0]);
	execute(av[3], envp);
}

void	execute(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		write(2, "command not found\n", 18);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("error");
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	pipex(char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	id1;
	pid_t	id2;
	int		status;

	pipe(pipe_fd);
	id1 = fork();
	if (id1 == -1)
		return (perror("Fork failed: "));
	if (id1 == 0)
	{
		child1_process(av, pipe_fd, envp);
		exit(EXIT_SUCCESS);
	}
	id2 = fork();
	if (id2 == -1)
		return (perror("Fork failed: "));
	if (id2 == 0)
	{
		child2_process(av, pipe_fd, envp);
		exit(EXIT_SUCCESS);
	}
	ft_close(pipe_fd);
	waitpid(id1, NULL, 0);
	waitpid(id2, &status, 0);
}

int	main(int ac, char **av, char **envp)
{
	if (ac == 5)
		pipex(av, envp);
	else
	{
		write (1, "bad argument number\n", 20);
		return (1);
	}
}