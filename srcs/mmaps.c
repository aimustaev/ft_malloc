/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:12:03 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 18:20:36 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

static void		fill_new_tny_mmap(void *new_mmap)
{
	t_tnysml_alloc_header	*header;
	unsigned int					i;

	header = (t_tnysml_alloc_header *)
			((uintptr_t)new_mmap + g_info->tny_mmap_offset);
	if (!g_info->free_tny_allocs)
		g_info->free_tny_allocs = header;
	else
		g_info->free_tny_allocs_tail->next_free = header;
	header->free = 1;
	i = 1;
	while (i < g_info->n_tny_allocs_per_mmap)
	{
		header->next_free = (t_tnysml_alloc_header *)
				((uintptr_t)header + g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE);
		header = header->next_free;
		header->free = 1;
		header->id = i;
		++i;
	}
	g_info->free_tny_allocs_tail = header;
}

static void		fill_new_sml_mmap(void *new_mmap)
{
	t_tnysml_alloc_header	*header;
	unsigned int					i;

	header = (t_tnysml_alloc_header *)
			((uintptr_t)new_mmap + g_info->sml_mmap_offset);
	if (!g_info->free_sml_allocs)
		g_info->free_sml_allocs = header;
	else
		g_info->free_sml_allocs_tail->next_free = header;
	header->free = 1;
	i = 1;
	while (i < g_info->n_sml_allocs_per_mmap)
	{
		header->next_free = (t_tnysml_alloc_header *)
				((uintptr_t)header + g_info->tnysml_alheadr_siz + SML_ALLOC_SIZE);
		header = header->next_free;
		header->free = 1;
		header->id = i;
		++i;
	}
	g_info->free_sml_allocs_tail = header;
}

void			new_tny_mmap(void)
{
	void							*new_mmap;
	t_tnysml_mmap_header		*new_mpheader;

	new_mmap = mmap(0, g_info->tny_mmap_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_mmap)
		return ;
	new_mpheader = (t_tnysml_mmap_header *)new_mmap;
	new_mpheader->nallocs = 0;
	new_mpheader->next_mmap = 0;
	if (!g_info->tny_mmaps)
		g_info->tny_mmaps = (t_tnysml_mmap_header *)new_mmap;
	fill_new_tny_mmap(new_mmap);
	++g_info->n_tny_mmaps;
}

void			new_sml_mmap(void)
{
	void							*new_mmap;
	t_tnysml_mmap_header		*new_mpheader;

	new_mmap = mmap(0, g_info->sml_mmap_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!new_mmap)
		return ;
	new_mpheader = (t_tnysml_mmap_header *)new_mmap;
	new_mpheader->nallocs = 0;
	new_mpheader->next_mmap = 0;
	if (!g_info->sml_mmaps)
		g_info->sml_mmaps = (t_tnysml_mmap_header *)new_mmap;
	fill_new_sml_mmap(new_mmap);
	++g_info->n_sml_mmaps;
}

void			new_lrg_mmap(size_t used_size)
{
	t_lrg_alloc_header	*new_header;
	void						*new_alloc;
	size_t						size;

	size = ((used_size / g_info->pagesize) + 1) * g_info->pagesize;
	new_alloc = mmap(0, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!new_alloc)
		return ;
	new_header = (t_lrg_alloc_header *)new_alloc;
	new_header->size = size;
	new_header->used = used_size;
	new_header->prev_alloc = 0;
	new_header->next_alloc = 0;
	if (g_info->lrg_allocs)
	{
		g_info->lrg_allocs->prev_alloc = new_header;
		new_header->next_alloc = g_info->lrg_allocs;
	}
	g_info->lrg_allocs = new_header;
}
