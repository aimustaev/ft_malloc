/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:11:47 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:11:47 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "struct_tnysml_mmap_header.h"
#include "struct_tnysml_alloc_header.h"
#include "struct_lrg_alloc_header.h"
#include <unistd.h>
#include <stdint.h>

static void		*check_tny(void *ptr)
{
	struct s_tnysml_mmap_header		*cur;
	struct s_tnysml_alloc_header	*header;

	cur = info->tny_mmaps;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + info->tny_mmap_offset &&
				(uintptr_t)ptr < (uintptr_t)cur + info->tny_mmap_size &&
				((uintptr_t)ptr - ((uintptr_t)cur + info->tny_mmap_offset)) %
				(info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) >=
				info->tnysml_alheadr_siz)
		{
			header = (struct s_tnysml_alloc_header *)
					((uintptr_t)cur + info->tny_mmap_offset +
					((info->tnysml_alheadr_siz + TNY_ALLOC_SIZE) *
					(((uintptr_t)ptr - ((uintptr_t)cur + info->tny_mmap_offset))
					/ (info->tnysml_alheadr_siz + TNY_ALLOC_SIZE))));
			return ((!header->free) ? header : 0);
		}
		cur = cur->next_mmap;
	}
	return (0);
}

static void		*check_sml(void *ptr)
{
	struct s_tnysml_mmap_header		*cur;
	struct s_tnysml_alloc_header	*header;

	cur = info->sml_mmaps;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + info->sml_mmap_offset &&
				(uintptr_t)ptr < (uintptr_t)cur + info->sml_mmap_size &&
				((uintptr_t)ptr - ((uintptr_t)cur + info->sml_mmap_offset)) %
				(info->tnysml_alheadr_siz + SML_ALLOC_SIZE) >=
				info->tnysml_alheadr_siz)
		{
			header = (struct s_tnysml_alloc_header *)
					((uintptr_t)cur + info->sml_mmap_offset +
					((info->tnysml_alheadr_siz + SML_ALLOC_SIZE) *
					(((uintptr_t)ptr - ((uintptr_t)cur + info->sml_mmap_offset))
					/ (info->tnysml_alheadr_siz + SML_ALLOC_SIZE))));
			return ((!header->free) ? header : 0);
		}
		cur = cur->next_mmap;
	}
	return (0);
}

static void		*check_lrg(void *ptr)
{
	struct s_lrg_alloc_header	*cur;

	cur = info->lrg_allocs;
	while (cur)
	{
		if ((uintptr_t)ptr >= (uintptr_t)cur + info->lrg_alheadr_siz &&
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
