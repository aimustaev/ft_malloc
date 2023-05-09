/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:59 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 11:39:51 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdint.h>

static void		*malloc_tny(size_t size)
{
	void	*ptr;

	if (!g_info->free_tny_allocs)
		new_tny_mmap();
	ptr = (void *)g_info->free_tny_allocs;
	((t_tnysml_block *)(ptr))->free = 0;
	((t_tnysml_block *)(ptr))->used = size;
	ptr = (void *)((uintptr_t)ptr + g_info->tnysml_alheadr_siz);
	g_info->free_tny_allocs = g_info->free_tny_allocs->next_free;
	return (ptr);
}

static void		*malloc_sml(size_t size)
{
	void	*ptr;

	if (!g_info->free_sml_allocs)
		new_sml_mmap();
	ptr = (void *)g_info->free_sml_allocs;
	((t_tnysml_block *)(ptr))->free = 0;
	((t_tnysml_block *)(ptr))->used = size;
	ptr = (void *)((uintptr_t)ptr + g_info->tnysml_alheadr_siz);
	g_info->free_sml_allocs = g_info->free_sml_allocs->next_free;
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;

	if (!g_info)
		setup_malloc();
	if (size <= TNY_ALLOC_SIZE)
		ptr = malloc_tny(size);
	else if (size <= SML_ALLOC_SIZE)
		ptr = malloc_sml(size);
	else
	{
		new_lrg_mmap(size);
		ptr = (void *)((uintptr_t)g_info->lrg_allocs + g_info->lrg_alheadr_siz);
	}
	return (ptr);
}
