/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct_s_malloc.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:09:49 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:09:50 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_STRUCT_S_MALLOC_H
# define GLOBAL_STRUCT_S_MALLOC_H

# include "struct_tnysml_mmap_header.h"
# include "struct_tnysml_alloc_header.h"
# include "struct_lrg_alloc_header.h"
# include <unistd.h>

/*
**	Global struct holding heads and tails to the different zones, and also
**	a "stack" of free-for-use allocations
*/
struct								s_malloc
{
	struct s_tnysml_mmap_header		*tny_mmaps;
	struct s_tnysml_mmap_header		*tny_mmaps_tail;
	struct s_tnysml_mmap_header		*sml_mmaps;
	struct s_tnysml_mmap_header		*sml_mmaps_tail;
	struct s_tnysml_alloc_header	*free_tny_allocs;
	struct s_tnysml_alloc_header	*free_tny_allocs_tail;
	struct s_tnysml_alloc_header	*free_sml_allocs;
	struct s_tnysml_alloc_header	*free_sml_allocs_tail;
	struct s_lrg_alloc_header		*lrg_allocs;
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
