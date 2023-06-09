/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:47 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 12:15:20 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdint.h>

void	*checker(t_tnysml_block *header)
{
	if (!header->free)
		return (header);
	return (0);
}

void	*check_tny(void *ptr)
{
	t_map_header		*cur;
	t_tnysml_block		*header;

	cur = g_info->tny_mmaps;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + g_info->tny_mmap_off && \
				(uintptr_t)ptr < (uintptr_t)cur + g_info->tny_mmap_size && \
				((uintptr_t)ptr - ((uintptr_t)cur + g_info->tny_mmap_off)) % \
				(g_info->tnysml_block_size + TNY_ALLOC_SIZE) >= \
				g_info->tnysml_block_size)
		{
			header = (t_tnysml_block *)
				((uintptr_t)cur + g_info->tny_mmap_off + \
				((g_info->tnysml_block_size + TNY_ALLOC_SIZE) * \
				(((uintptr_t)ptr - ((uintptr_t)cur + g_info->tny_mmap_off)) / \
				(g_info->tnysml_block_size + TNY_ALLOC_SIZE))));
			return (checker(header));
		}
		cur = cur->next_mmap;
	}
	return (0);
}

static void	*check_sml(void *ptr)
{
	t_map_header		*cur;
	t_tnysml_block		*header;

	cur = g_info->sml_mmaps;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + g_info->sml_mmap_off && \
				(uintptr_t)ptr < (uintptr_t)cur + g_info->sml_mmap_size && \
				((uintptr_t)ptr - ((uintptr_t)cur + g_info->sml_mmap_off)) % \
				(g_info->tnysml_block_size + SML_ALLOC_SIZE) >= \
				g_info->tnysml_block_size)
		{
			header = (t_tnysml_block *) \
					((uintptr_t)cur + g_info->sml_mmap_off + \
					((g_info->tnysml_block_size + SML_ALLOC_SIZE) * \
					(((uintptr_t)ptr - ((uintptr_t)cur + g_info->sml_mmap_off)) \
					/ (g_info->tnysml_block_size + SML_ALLOC_SIZE))));
			return (checker(header));
		}
		cur = cur->next_mmap;
	}
	return (0);
}

static void	*check_lrg(void *ptr)
{
	t_lrg_block	*cur;

	cur = g_info->lrg_allocs;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + g_info->lrg_block_size && \
				(uintptr_t)ptr <= (uintptr_t)cur + cur->size)
		{
			return (cur);
		}
		cur = cur->next_alloc;
	}
	return (0);
}

unsigned int	find_header(void *ptr, void **header)
{
	*header = 0;
	*header = check_tny(ptr);
	if (*header)
		return (TINY);
	*header = check_sml(ptr);
	if (*header)
		return (SMALL);
	*header = check_lrg(ptr);
	if (*header)
		return (LARGE);
	return (0);
}
