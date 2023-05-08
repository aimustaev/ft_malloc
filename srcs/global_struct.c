/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:55 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 18:24:58 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

static void		setup_alignment(void)
{
	g_info->lrg_alheadr_siz = sizeof(t_lrg_alloc_header);
	g_info->tnysml_alheadr_siz = sizeof(t_tnysml_alloc_header);
	g_info->tnysml_mpheadr_siz = sizeof(t_tnysml_mmap_header);
	g_info->pagesize = getpagesize();
	g_info->tny_mmap_size = g_info->pagesize * TNY_OVERHEAD;
	g_info->sml_mmap_size = g_info->pagesize * SML_OVERHEAD;
	g_info->tny_mmap_pad = ((g_info->tny_mmap_size - g_info->tnysml_mpheadr_siz) %
			(g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE));
	g_info->sml_mmap_pad = ((g_info->sml_mmap_size - g_info->tnysml_mpheadr_siz) %
			(g_info->tnysml_alheadr_siz + SML_ALLOC_SIZE));
	g_info->tny_mmap_offset = g_info->tnysml_mpheadr_siz + g_info->tny_mmap_pad;
	g_info->sml_mmap_offset = g_info->tnysml_mpheadr_siz + g_info->sml_mmap_pad;
	g_info->tny_mmap_space = g_info->tny_mmap_size - g_info->tny_mmap_offset;
	g_info->sml_mmap_space = g_info->sml_mmap_size - g_info->sml_mmap_offset;
	g_info->n_tny_allocs_per_mmap = g_info->tny_mmap_space /
			(g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE);
	g_info->n_sml_allocs_per_mmap = g_info->sml_mmap_space /
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
