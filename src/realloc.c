/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:12:08 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 12:39:46 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdint.h>

size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	*update_zone(unsigned int old_zone, void *header, \
	size_t new_size)
{
	void			*new_ptr;
	unsigned int	old_size;

	new_ptr = malloc(new_size);
	if (old_zone == TINY || old_zone == SMALL)
	{
		old_size = ((t_tnysml_block *)(header))->used;
		new_ptr = ft_memcpy(new_ptr, (void *)((uintptr_t)header + \
				g_info->tnysml_block_size), ft_min(old_size, new_size));
	}
	else
	{
		old_size = ((t_lrg_block *)(header))->used;
		new_ptr = ft_memcpy(new_ptr, (void *)((uintptr_t)header + \
				g_info->lrg_block_size), ft_min(old_size, new_size));
	}
	return (new_ptr);
}

static void	*get_new_ptr(unsigned int zone, void *header, void *ptr, \
	size_t new_size)
{
	void			*new_ptr;

	if ((zone == TINY && new_size <= TNY_ALLOC_SIZE) || \
			(zone == SMALL && new_size > TNY_ALLOC_SIZE && \
			new_size <= SML_ALLOC_SIZE))
	{
		((t_tnysml_block *)(header))->used = new_size;
		new_ptr = (void *)((uintptr_t)header + g_info->tnysml_block_size);
	}
	else if (zone == LARGE && new_size <= \
			((t_lrg_block *)(header))->size)
	{
		((t_lrg_block *)(header))->used = new_size;
		new_ptr = (void *)((uintptr_t)header + g_info->lrg_block_size);
	}
	else
	{
		new_ptr = update_zone(zone, header, new_size);
		free(ptr);
	}
	return (new_ptr);
}

void	*realloc(void *ptr, size_t new_size)
{
	void			*new_ptr;
	void			*header;
	unsigned char	zone;

	lock();
	if (!g_info)
		init_malloc();
	if (!ptr)
	{
		ptr = malloc(new_size);
		unlock();
		return (ptr);
	}
	zone = find_header(ptr, &header);
	if (!zone)
	{
		unlock();
		return (0);
	}
	new_ptr = get_new_ptr(zone, header, ptr, new_size);
	unlock();
	return (new_ptr);
}
