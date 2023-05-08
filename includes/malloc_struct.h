/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:09:49 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 18:21:17 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_STRUCT_S_MALLOC_H
# define GLOBAL_STRUCT_S_MALLOC_H

# include <unistd.h>

/*
**	This struct is stored at the front of the allocated memory
**	(All large allocations are 1+ pages.)
*/

typedef struct					s_lrg_alloc_header
{
	size_t						used;
	size_t						size;
	struct s_lrg_alloc_header 	*prev_alloc;
	struct s_lrg_alloc_header	*next_alloc;
}								t_lrg_alloc_header;

/*
**	For tiny/small allocations, the next pointer will only be needed if the
**	space is free. And if so, it will be added to a linked list of other free
**	nodes for quick mallocing.
*/

typedef struct						s_tnysml_alloc_header
{
	unsigned char					free;
	unsigned short					used;
	unsigned short					id;
	struct s_tnysml_alloc_header	*next_free;
}									t_tnysml_alloc_header;

/*
**	Linked list of memory from mmap calls.
*/

typedef struct						s_tnysml_mmap_header
{
	unsigned short					nallocs;
	struct s_tnysml_mmap_header		*next_mmap;
}                                   t_tnysml_mmap_header;
/*
**	Global struct holding heads and tails to the different zones, and also
**	a "stack" of free-for-use allocations
*/
struct								s_malloc
{
	t_tnysml_mmap_header		*tny_mmaps;
	t_tnysml_mmap_header		*sml_mmaps;
	t_tnysml_alloc_header		*free_tny_allocs;
	t_tnysml_alloc_header		*free_tny_allocs_tail;
	t_tnysml_alloc_header		*free_sml_allocs;
	t_tnysml_alloc_header		*free_sml_allocs_tail;
	t_lrg_alloc_header		*lrg_allocs;
	size_t							pagesize;
	size_t							lrg_alheadr_siz;
	size_t							tnysml_alheadr_siz; // Размер заголоввка блока
	size_t							tnysml_mpheadr_siz; // Размер заголоввка блока
	size_t							n_tny_mmaps; // Количество заюзаных блоков
	size_t							n_sml_mmaps;// Количество заюзаных блоков
	size_t							tny_mmap_size; // Общий кусок выделяемой памяти TNY_OVERHEAD * 4кб
	size_t							sml_mmap_size; // Общий кусок выделяемой памяти SML_OVERHEAD * 4кб
	size_t							tny_mmap_pad; // Кусок памяти который не задействован + Заголовок
	size_t							sml_mmap_pad; // Кусок памяти который не задействован + Заголовок
	size_t							tny_mmap_offset; // Кусок памяти который не задествован
	size_t							sml_mmap_offset; // Кусок памяти который не задествован
	size_t							tny_mmap_space; // Кусок памяти который включает количество целых блоков * рзмер блока (данные + мета информация)
	size_t							sml_mmap_space; // Кусок памяти который включает количество целых блоков * рзмер блока (данные + мета информация)
	size_t							n_tny_allocs_per_mmap; // Количество целых блоков в tny_mmap_space
	size_t							n_sml_allocs_per_mmap; // Количество целых блоков в sml_mmap_space
};

void								setup_malloc(void);

#endif
