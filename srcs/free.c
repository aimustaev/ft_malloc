/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:51 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:11:52 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "find_header.h"
#include "struct_tnysml_mmap_header.h"
#include "struct_tnysml_alloc_header.h"
#include "struct_lrg_alloc_header.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

static void		free_tny(void *header)
{
	struct s_tnysml_mmap_header	*page_header;

	page_header = (struct s_tnysml_mmap_header *)
			((uintptr_t)header - (((struct s_tnysml_alloc_header *)header)->id *
			(info->tnysml_alheadr_siz + TNY_ALLOC_SIZE)) -
			(info->tny_mmap_offset - info->tnysml_mpheadr_siz));
	if (page_header->nallocs == 1 && info->n_tny_mmaps > 1)
		munmap(page_header, info->tny_mmap_size);
	else
	{
		((struct s_tnysml_alloc_header *)(header))->free = 1;
		((struct s_tnysml_alloc_header *)(header))->used = 0;
		((struct s_tnysml_alloc_header *)(header))->next_free = 0;
		--page_header->nallocs;
		info->free_tny_allocs_tail->next_free = header;
		info->free_tny_allocs_tail = info->free_tny_allocs_tail->next_free;
	}
}

static void		free_sml(void *header)
{
	struct s_tnysml_mmap_header	*page_header;

	page_header = (struct s_tnysml_mmap_header *)
			((uintptr_t)header - (((struct s_tnysml_alloc_header *)header)->id *
			(info->tnysml_alheadr_siz + SML_ALLOC_SIZE)) -
			(info->sml_mmap_offset - info->tnysml_mpheadr_siz));
	if (page_header->nallocs == 1 && info->n_sml_mmaps > 1)
		munmap(page_header, info->sml_mmap_size);
	else
	{
		((struct s_tnysml_alloc_header *)(header))->free = 1;
		((struct s_tnysml_alloc_header *)(header))->used = 0;
		((struct s_tnysml_alloc_header *)(header))->next_free = 0;
		--page_header->nallocs;
		info->free_sml_allocs_tail->next_free = header;
		info->free_sml_allocs_tail = info->free_sml_allocs_tail->next_free;
	}
}

static void		free_lrg(void *header)
{
	struct s_lrg_alloc_header	*prev;

	prev = ((struct s_lrg_alloc_header *)(header))->prev_alloc;
	if (!prev)
	{
		if (info->lrg_allocs->next_alloc)
		{
			info->lrg_allocs = info->lrg_allocs->next_alloc;
			info->lrg_allocs->prev_alloc = 0;
		}
		else
			info->lrg_allocs = 0;
	}
	else
	{
		prev->next_alloc = ((struct s_lrg_alloc_header *)(header))->next_alloc;
	}
	munmap(header, ((struct s_lrg_alloc_header *)(header))->size);
}

void			free(void *ptr)
{
	void			*header;
	unsigned int	zone;

	if (!info)
		setup_malloc();
	zone = find_header(ptr, &header);
	if (zone == TINY)
		free_tny(header);
	else if (zone == SMALL)
		free_sml(header);
	else if (zone == LARGE)
		free_lrg(header);
}
