/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:39 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 11:31:54 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		lentot;
	char	*s3;

	i = 0;
	j = 0;
	lentot = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(sizeof(char) * lentot + 1);
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*find_path(char *cmd, char **envp)
{
	int		j;
	char	**paths;
	char	*path;

	j = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[j] && strncmp(envp[j], "PATH=", 5) != 0)
		j++;
	if (envp[j] == NULL)
		return (NULL);
	paths = ft_split(envp[j] + 5, ':');
	if (!paths)
		return (NULL);
	path = search_paths(cmd, paths);
	free_split(paths);
	return (path);
}

char	*search_paths(char *cmd, char **paths)
{
	int		i;
	char	*path;
	char	*part_path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		if (access(path, F_OK) == 0)
		{
			free(part_path);
			return (path);
		}
		free(part_path);
		free(path);
		i++;
	}
	return (NULL);
}