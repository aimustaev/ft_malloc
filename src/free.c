/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:51 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 12:40:15 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

static void	free_tny(void *header)
{
	t_map_header	*page_header;

	page_header = (t_map_header *)
		((uintptr_t)header - (((t_tnysml_block *)header)->id * \
		(g_info->tnysml_block_size + TNY_ALLOC_SIZE)) - \
		(g_info->tny_mmap_off - g_info->tnysml_map_size));
	if (page_header->nallocs == 1 && g_info->n_tny_mmaps > 1)
		munmap(page_header, g_info->tny_mmap_size);
	else
	{
		((t_tnysml_block *)(header))->free = 1;
		((t_tnysml_block *)(header))->used = 0;
		((t_tnysml_block *)(header))->next_free = 0;
		--page_header->nallocs;
		g_info->free_tny_allocs_tail->next_free = header;
		g_info->free_tny_allocs_tail = g_info->free_tny_allocs_tail->next_free;
	}
}

static void	free_sml(void *header)
{
	t_map_header	*page_header;

	page_header = (t_map_header *)
		((uintptr_t)header - (((t_tnysml_block *)header)->id * \
		(g_info->tnysml_block_size + SML_ALLOC_SIZE)) - \
		(g_info->sml_mmap_off - g_info->tnysml_map_size));
	if (page_header->nallocs == 1 && g_info->n_sml_mmaps > 1)
		munmap(page_header, g_info->sml_mmap_size);
	else
	{
		((t_tnysml_block *)(header))->free = 1;
		((t_tnysml_block *)(header))->used = 0;
		((t_tnysml_block *)(header))->next_free = 0;
		--page_header->nallocs;
		g_info->free_sml_allocs_tail->next_free = header;
		g_info->free_sml_allocs_tail = g_info->free_sml_allocs_tail->next_free;
	}
}

static void	free_lrg(void *header)
{
	t_lrg_block	*prev;

	prev = ((t_lrg_block *)(header))->prev_alloc;
	if (!prev)
	{
		if (g_info->lrg_allocs->next_alloc)
		{
			g_info->lrg_allocs = g_info->lrg_allocs->next_alloc;
			g_info->lrg_allocs->prev_alloc = 0;
		}
		else
			g_info->lrg_allocs = 0;
	}
	else
	{
		prev->next_alloc = ((t_lrg_block *)(header))->next_alloc;
	}
	munmap(header, ((t_lrg_block *)(header))->size);
}

void	free(void *ptr)
{
	void			*header;
	unsigned int	zone;

	lock();
	if (!g_info)
		init_malloc();
	zone = find_header(ptr, &header);
	if (zone == TINY)
		free_tny(header);
	else if (zone == SMALL)
		free_sml(header);
	else if (zone == LARGE)
		free_lrg(header);
	unlock();
}
