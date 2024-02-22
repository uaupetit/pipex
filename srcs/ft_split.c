/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:05:14 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 11:32:04 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_len(const char *s, unsigned int start, char c)
{
	int	i;

	i = 0;
	while (s[start] != c && s[start])
	{
		start++;
		i++;
	}
	return (i);
}

int	ft_nbmots(char const *s, char c)
{
	int	i;
	int	nbmots;

	i = 0;
	nbmots = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nbmots++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nbmots);
}

void	ft_free(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	start;
	int				i;

	i = 0;
	start = 0;
	tab = malloc(sizeof(char *) * (ft_nbmots(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[start])
	{
		if (s[start] != c)
		{
			tab[i] = ft_substr(s, start, ft_len(s, start, c));
			if (!tab[i])
				return (ft_free(tab, i), NULL);
			start += ft_len(s, start, c);
			i++;
		}
		else
			start++;
	}
	tab[i] = 0;
	return (tab);
}