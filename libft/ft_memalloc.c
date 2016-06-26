/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 12:32:01 by simzam            #+#    #+#             */
/*   Updated: 2016/06/24 07:37:47 by simzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	i = -1;
	mem = malloc(sizeof(size_t) * size);
	if (!mem)
		return (NULL);
	while (++i < size)
		*((unsigned char *)mem + i) = '\0';
	return (mem);
}
