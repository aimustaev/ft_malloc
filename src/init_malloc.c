/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:55 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 12:53:32 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

pthread_mutex_t	g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

static void	init_alignment(void)
{
	g_info->lrg_block_size = sizeof(t_lrg_block);
	g_info->tnysml_block_size = sizeof(t_tnysml_block);
	g_info->tnysml_map_size = sizeof(t_map_header);
	g_info->pagesize = getpagesize();
	g_info->tny_mmap_size = g_info->pagesize * TNY_OVERHEAD;
	g_info->sml_mmap_size = g_info->pagesize * SML_OVERHEAD;
	g_info->tny_mmap_pad = ((g_info->tny_mmap_size - g_info->tnysml_map_size) % \
		(g_info->tnysml_block_size + TNY_ALLOC_SIZE));
	g_info->sml_mmap_pad = ((g_info->sml_mmap_size - g_info->tnysml_map_size) % \
		(g_info->tnysml_block_size + SML_ALLOC_SIZE));
	g_info->tny_mmap_off = g_info->tnysml_map_size + g_info->tny_mmap_pad;
	g_info->sml_mmap_off = g_info->tnysml_map_size + g_info->sml_mmap_pad;
	g_info->tny_mmap_space = g_info->tny_mmap_size - g_info->tny_mmap_off;
	g_info->sml_mmap_space = g_info->sml_mmap_size - g_info->sml_mmap_off;
	g_info->n_tny_block = g_info->tny_mmap_space / \
		(g_info->tnysml_block_size + TNY_ALLOC_SIZE);
	g_info->n_sml_block = g_info->sml_mmap_space / \
		(g_info->tnysml_block_size + SML_ALLOC_SIZE);
}

void	init_malloc(void)
{
	void				*page;

	page = mmap(0, getpagesize(), PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
	g_info = (struct s_malloc *)page;
	init_alignment();
	g_info->lrg_allocs = 0;
	g_info->n_tny_mmaps = 0;
	g_info->n_sml_mmaps = 0;
	new_tny_mmap();
	new_sml_mmap();
}
