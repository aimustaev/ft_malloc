/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:12:12 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 18:20:36 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdint.h>

void	show_tny(void)
{
	t_tnysml_mmap_header		*cur;
	unsigned int					addr;
	unsigned int					used;
	size_t							i;

	cur = g_info->tny_mmaps;
	while (cur)
	{
		i = 0;
		while (i < g_info->n_tny_allocs_per_mmap)
		{
			addr = (uintptr_t)cur + g_info->tny_mmap_offset +
					((g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) * i);
			used = ((t_tnysml_alloc_header *)
					((uintptr_t)cur + g_info->tny_mmap_offset +
					((g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) * i)))->used;
			if (!(((t_tnysml_alloc_header *)
					((uintptr_t)cur + g_info->tny_mmap_offset +
					((g_info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) * i)))->free))
				ft_printf("%#.8x - %#.8x : %d bytes\n",
						addr, addr + used, used);
			++i;
		}
		cur = cur->next_mmap;
	}
}

void	show_sml(void)
{
	t_tnysml_mmap_header		*cur;
	unsigned int					addr;
	unsigned int					used;
	size_t							i;

	cur = g_info->sml_mmaps;
	while (cur)
	{
		i = 0;
		while (i < g_info->n_sml_allocs_per_mmap)
		{
			addr = (uintptr_t)cur + g_info->sml_mmap_offset +
					((g_info->tnysml_alheadr_siz + SML_ALLOC_SIZE) * i);
			used = ((t_tnysml_alloc_header *)
					((uintptr_t)cur + g_info->sml_mmap_offset +
					((g_info->tnysml_alheadr_siz + SML_ALLOC_SIZE) * i)))->used;
			if (!(((t_tnysml_alloc_header *)
					((uintptr_t)cur + g_info->sml_mmap_offset +
					((g_info->tnysml_alheadr_siz + SML_ALLOC_SIZE) * i)))->free))
				ft_printf("%#.8x - %#.8x : %d bytes\n",
						addr, addr + used, used);
			++i;
		}
		cur = cur->next_mmap;
	}
}

void	show_lrg(void)
{
	t_lrg_alloc_header		*cur;
	unsigned int					addr;
	unsigned int					used;

	cur = g_info->lrg_allocs;
	while (cur)
	{
		addr = (uintptr_t)cur + g_info->lrg_alheadr_siz;
		used = cur->used;
		ft_printf("%#.8x - %#.8x : %d bytes\n", addr, addr + used, used);
		cur = cur->next_alloc;
	}
}

void	show_alloc_mem(void)
{
	ft_printf("TINY: %#.8x\n", g_info->tny_mmaps);
	show_tny();
	ft_printf("SMALL: %#.8x\n", g_info->sml_mmaps);
	show_sml();
	ft_printf("LARGE: %#.8x\n", g_info->lrg_allocs);
	show_lrg();
}
