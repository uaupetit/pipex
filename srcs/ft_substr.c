/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:10:38 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 11:31:57 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_fillsub(char const *s, unsigned int start, size_t len, char *s1)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[start] && i++ < len)
		s1[j++] = s[start++];
	s1[j] = '\0';
	return (s1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	slen;

	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len >= slen - start)
		len = slen - start;
	if (start >= slen)
	{
		s1 = malloc(1);
		s1[0] = '\0';
		return (s1);
	}
	s1 = malloc((len + 1) * sizeof(char));
	if (!s1)
		return (NULL);
	return (ft_fillsub(s, start, len, s1));
}
