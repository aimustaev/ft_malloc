/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:55 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 11:42:24 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

static void		setup_alignment(void)
{
	g_info->lrg_alheadr_siz = sizeof(t_lrg_block);
	g_info->tnysml_alheadr_siz = sizeof(t_tnysml_block);
	g_info->tnysml_mpheadr_siz = sizeof(t_map_header);
	g_info->pagesize = getpagesize();
	g_info->tny_mmap_size = g_info->pagesize * TNY_OVERHEAD;
	g_info->sml_mmap_size = g_info->pagesize * SML_OVERHEAD;
	g_info->tny_mmap_padding = ((g_info->tny_mmap_size - g_info->tnysml_mpheadr_siz) %
			(g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE));
	g_info->sml_mmap_padding = ((g_info->sml_mmap_size - g_info->tnysml_mpheadr_siz) %
			(g_info->tnysml_alheadr_siz + SML_ALLOC_SIZE));
	g_info->tny_mmap_offset = g_info->tnysml_mpheadr_siz + g_info->tny_mmap_padding;
	g_info->sml_mmap_offset = g_info->tnysml_mpheadr_siz + g_info->sml_mmap_padding;
	g_info->tny_mmap_space = g_info->tny_mmap_size - g_info->tny_mmap_offset;
	g_info->sml_mmap_space = g_info->sml_mmap_size - g_info->sml_mmap_offset;
	g_info->n_tny_block = g_info->tny_mmap_space /
			(g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE);
	g_info->n_sml_block = g_info->sml_mmap_space /
			(g_info->tnysml_alheadr_siz + SML_ALLOC_SIZE);
}

void			setup_malloc(void)
{
	void				*page;

	page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	g_info = (struct s_malloc *)page;
	setup_alignment();
	g_info->lrg_allocs = 0;
	g_info->n_tny_mmaps = 0;
	g_info->n_sml_mmaps = 0;
	new_tny_mmap();
	new_sml_mmap();
}
