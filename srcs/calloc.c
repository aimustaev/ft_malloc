/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:33 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:11:34 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

void			*calloc(size_t num, size_t size)
{
	void	*ptr;

	if (!num || !size)
		return (0);
	ptr = malloc(num * size);
	// if (ptr)
	// 	ft_bzero(ptr, num * size);
	return (ptr);
}
