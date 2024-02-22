/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:59:44 by uaupetit          #+#    #+#             */
/*   Updated: 2023/05/31 11:19:50 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		main(int ac, char **av, char **envp);
void	pipex(char **av, char **envp);
void	execute(char *av, char **envp);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*find_path(char *cmd, char **envp);
void	parent_process(char **av, char **envp, int *fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	child_process(char **av, char **envp, int *fd);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
void	free_split(char **split);
char	*search_paths(char *cmd, char **paths);
void	child2_process(char **av, int *pipe_fd, char **envp);
void	child1_process(char **av, int *pipe_fd, char **envp);
void	ft_close(int pipe_fd[]);
#endif
