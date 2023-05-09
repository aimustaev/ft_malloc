/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:09:49 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 11:52:59 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_STRUCT_H
# define MALLOC_STRUCT_H

# include <unistd.h>

/*
**	Структура для блоков размера LARGE
*/
typedef struct s_lrg_block
{
	size_t				used;
	size_t				size;
	struct s_lrg_block	*prev_alloc;
	struct s_lrg_block	*next_alloc;
}						t_lrg_block;

/*
**	Структура для блоков размера TINY/SMALL
*/
typedef struct s_tnysml_block
{
	unsigned char			free;
	unsigned short			used;
	unsigned short			id;
	struct s_tnysml_block	*next_free;
}							t_tnysml_block;

/*
**	Структура с маппингом памяти на вызовы mmap
*/
typedef struct s_map_header
{
	unsigned short		nallocs;
	struct s_map_header	*next_mmap;
}						t_map_header;

/*
**	Глобальная структура со всеми параметрами и состоянием памяти
	- tnysml_alheadr_siz; // Размер заголоввка блока
	- tnysml_mpheadr_siz; // Размер заголоввка блока
	- n_tny_mmaps; // Количество заюзаных блоков
	- n_sml_mmaps; // Количество заюзаных блоков
	- tny_mmap_size; // Общий кусок выделяемой памяти TNY_OVERHEAD * 4кб
	- sml_mmap_size; // Общий кусок выделяемой памяти SML_OVERHEAD * 4кб
	- tny_mmap_padding; // Кусок памяти который не задействован + Заголовок
	- sml_mmap_padding; // Кусок памяти который не задействован + Заголовок
	- tny_mmap_offset; // Кусок памяти который не задествован
	- sml_mmap_offset; // Кусок памяти который не задествован
	- tny_mmap_space; // Кусок памяти который включает количество
	целых блоков * рзмер блока (данные + мета информация)
	- sml_mmap_space; // Кусок памяти который включает количество
	целых блоков * рзмер блока (данные + мета информация)
	- n_tny_block; // Количество целых блоков в tny_mmap_space
	- n_sml_block; // Количество целых блоков в sml_mmap_space
*/
struct						s_malloc
{
	t_map_header		*tny_mmaps;
	t_map_header		*sml_mmaps;
	t_tnysml_block		*free_tny_allocs;
	t_tnysml_block		*free_tny_allocs_tail;
	t_tnysml_block		*free_sml_allocs;
	t_tnysml_block		*free_sml_allocs_tail;
	t_lrg_block			*lrg_allocs;
	size_t				pagesize;
	size_t				lrg_alheadr_siz;
	size_t				tnysml_alheadr_siz;
	size_t				tnysml_mpheadr_siz;
	size_t				n_tny_mmaps;
	size_t				n_sml_mmaps;
	size_t				tny_mmap_size;
	size_t				sml_mmap_size;
	size_t				tny_mmap_padding;
	size_t				sml_mmap_padding;
	size_t				tny_mmap_offset;
	size_t				sml_mmap_offset;
	size_t				tny_mmap_space;
	size_t				sml_mmap_space;
	size_t				n_tny_block;
	size_t				n_sml_block;
};

void					setup_malloc(void);

#endif
