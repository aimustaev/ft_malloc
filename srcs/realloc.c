/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:12:08 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 18:24:41 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdint.h>

static void		*update_zone(unsigned int old_zone, void *header,
						size_t new_size)
{
	void			*new_ptr;
	unsigned int	old_size;

	new_ptr = malloc(new_size);
	if (old_zone == TINY || old_zone == SMALL)
	{
		old_size = ((t_tnysml_alloc_header *)(header))->used;
		new_ptr = ft_memcpy(new_ptr, (void *)((uintptr_t)header +
				g_info->tnysml_alheadr_siz),
				((old_size < new_size) ? old_size : new_size));
	}
	else
	{
		old_size = ((t_lrg_alloc_header *)(header))->used;
		new_ptr = ft_memcpy(new_ptr, (void *)((uintptr_t)header +
				g_info->lrg_alheadr_siz),
				((old_size < new_size) ? old_size : new_size));
	}
	return (new_ptr);
}

static void		*get_new_ptr(unsigned int zone, void *header, void *ptr,
						size_t new_size)
{
	void			*new_ptr;

	if ((zone == TINY && new_size <= TNY_ALLOC_SIZE) ||
			(zone == SMALL && new_size > TNY_ALLOC_SIZE &&
			new_size <= SML_ALLOC_SIZE))
	{
		((t_tnysml_alloc_header *)(header))->used = new_size;
		new_ptr = (void *)((uintptr_t)header + g_info->tnysml_alheadr_siz);
	}
	else if (zone == LARGE && new_size <=
			((t_lrg_alloc_header *)(header))->size)
	{
		((t_lrg_alloc_header *)(header))->used = new_size;
		new_ptr = (void *)((uintptr_t)header + g_info->lrg_alheadr_siz);
	}
	else
	{
		new_ptr = update_zone(zone, header, new_size);
		free(ptr);
	}
	return (new_ptr);
}

void			*realloc(void *ptr, size_t new_size)
{
	void			*new_ptr;
	void			*header;
	unsigned char	zone;

	if (!g_info)
		setup_malloc();
	if (!ptr)
	{
		ptr = malloc(new_size);
		return (ptr);
	}
	zone = find_header(ptr, &header);
	if (!zone)
		return (0);
	new_ptr = get_new_ptr(zone, header, ptr, new_size);
	return (new_ptr);
}
