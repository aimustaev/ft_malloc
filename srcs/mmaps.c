/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:12:03 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:28:14 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tnysml_mmap_header.h"
#include "struct_tnysml_alloc_header.h"
#include "struct_lrg_alloc_header.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

static void		fill_new_tny_mmap(void *new_mmap)
{
	struct s_tnysml_alloc_header	*header;
	unsigned int					i;

	header = (struct s_tnysml_alloc_header *)
			((uintptr_t)new_mmap + info->tny_mmap_offset);
	if (!info->free_tny_allocs)
		info->free_tny_allocs = header;
	else
		info->free_tny_allocs_tail->next_free = header;
	header->free = 1;
	i = 1;
	while (i < info->n_tny_allocs_per_mmap)
	{
		header->next_free = (struct s_tnysml_alloc_header *)
				((uintptr_t)header + info->tnysml_alheadr_siz + TNY_ALLOC_SIZE);
		header = header->next_free;
		header->free = 1;
		header->id = i;
		++i;
	}
	info->free_tny_allocs_tail = header;
}

static void		fill_new_sml_mmap(void *new_mmap)
{
	struct s_tnysml_alloc_header	*header;
	unsigned int					i;

	header = (struct s_tnysml_alloc_header *)
			((uintptr_t)new_mmap + info->sml_mmap_offset);
	if (!info->free_sml_allocs)
		info->free_sml_allocs = header;
	else
		info->free_sml_allocs_tail->next_free = header;
	header->free = 1;
	i = 1;
	while (i < info->n_sml_allocs_per_mmap)
	{
		header->next_free = (struct s_tnysml_alloc_header *)
				((uintptr_t)header + info->tnysml_alheadr_siz + SML_ALLOC_SIZE);
		header = header->next_free;
		header->free = 1;
		header->id = i;
		++i;
	}
	info->free_sml_allocs_tail = header;
}

void			new_tny_mmap(void)
{
	void							*new_mmap;
	struct s_tnysml_mmap_header		*new_mpheader;

	new_mmap = mmap(0, info->tny_mmap_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_mmap)
		return ;
	new_mpheader = (struct s_tnysml_mmap_header *)new_mmap;
	new_mpheader->nallocs = 0;
	new_mpheader->next_mmap = 0;
	if (!info->tny_mmaps)
		info->tny_mmaps = (struct s_tnysml_mmap_header *)new_mmap;
	fill_new_tny_mmap(new_mmap);
	++info->n_tny_mmaps;
}

void			new_sml_mmap(void)
{
	void							*new_mmap;
	struct s_tnysml_mmap_header		*new_mpheader;

	new_mmap = mmap(0, info->sml_mmap_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_mmap)
		return ;
	new_mpheader = (struct s_tnysml_mmap_header *)new_mmap;
	new_mpheader->nallocs = 0;
	new_mpheader->next_mmap = 0;
	if (!info->sml_mmaps)
		info->sml_mmaps = (struct s_tnysml_mmap_header *)new_mmap;
	fill_new_sml_mmap(new_mmap);
	++info->n_sml_mmaps;
}

void			new_lrg_mmap(size_t used_size)
{
	struct s_lrg_alloc_header	*new_header;
	void						*new_alloc;
	size_t						size;

	size = ((used_size / info->pagesize) + 1) * info->pagesize;
	new_alloc = mmap(0, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new_alloc)
		return ;
	new_header = (struct s_lrg_alloc_header *)new_alloc;
	new_header->size = size;
	new_header->used = used_size;
	new_header->prev_alloc = 0;
	new_header->next_alloc = 0;
	if (info->lrg_allocs)
	{
		info->lrg_allocs->prev_alloc = new_header;
		new_header->next_alloc = info->lrg_allocs;
	}
	info->lrg_allocs = new_header;
}
