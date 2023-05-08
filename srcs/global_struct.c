/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:55 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:11:56 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mmaps.h"
#include "struct_tnysml_mmap_header.h"
#include "struct_tnysml_alloc_header.h"
#include "struct_lrg_alloc_header.h"
#include <sys/mman.h>

static void		setup_alignment(void)
{
	info->lrg_alheadr_siz = sizeof(struct s_lrg_alloc_header);
	info->tnysml_alheadr_siz = sizeof(struct s_tnysml_alloc_header);
	info->tnysml_mpheadr_siz = sizeof(struct s_tnysml_mmap_header);
	info->pagesize = getpagesize();
	info->tny_mmap_size = info->pagesize * TNY_OVERHEAD;
	info->sml_mmap_size = info->pagesize * SML_OVERHEAD;
	info->tny_mmap_pad = ((info->tny_mmap_size - info->tnysml_mpheadr_siz) %
			(info->tnysml_alheadr_siz + TNY_ALLOC_SIZE));
	info->sml_mmap_pad = ((info->sml_mmap_size - info->tnysml_mpheadr_siz) %
			(info->tnysml_alheadr_siz + SML_ALLOC_SIZE));
	info->tny_mmap_offset = info->tnysml_mpheadr_siz + info->tny_mmap_pad;
	info->sml_mmap_offset = info->tnysml_mpheadr_siz + info->sml_mmap_pad;
	info->tny_mmap_space = info->tny_mmap_size - info->tny_mmap_offset;
	info->sml_mmap_space = info->sml_mmap_size - info->sml_mmap_offset;
	info->n_tny_allocs_per_mmap = info->tny_mmap_space /
			(info->tnysml_alheadr_siz + TNY_ALLOC_SIZE);
	info->n_sml_allocs_per_mmap = info->sml_mmap_space /
			(info->tnysml_alheadr_siz + SML_ALLOC_SIZE);
}

void			setup_malloc(void)
{
	void				*page;

	page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	info = (struct s_malloc *)page;
	setup_alignment();
	info->lrg_allocs = 0;
	info->n_tny_mmaps = 0;
	info->n_sml_mmaps = 0;
	new_tny_mmap();
	new_sml_mmap();
}
