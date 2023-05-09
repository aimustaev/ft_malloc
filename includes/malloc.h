/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:09:35 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 12:34:43 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>
# include "libft.h"
# include "malloc_struct.h"
/*
**	:)		CONFIGURE:
**
**	TNY_ALLOC_SIZ	-> size of a tiny allocation
**	SML_ALLOC_SIZ	-> size of a small allocation
**	NPAGES_OVRHEAD	-> How many pages of memory will be added when new pages
**						are required. (keep around approx. 100 allocations)
*/
# define TNY_ALLOC_SIZE 16
# define SML_ALLOC_SIZE 1024
# define TNY_OVERHEAD 1
# define SML_OVERHEAD 26

/*
**	>:(		DO NOT CONFIGURE:
*/
# define TINY 1
# define SMALL 2
# define LARGE 3

struct s_malloc			*g_info;

/*
** multithreading lib
*/
extern pthread_mutex_t	g_malloc_mutex;

void			*malloc(size_t size);
void			*calloc(size_t num, size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);
void			show_alloc_mem(void);

// Helpers
void			new_tny_mmap(void);
void			new_sml_mmap(void);
void			new_lrg_mmap(size_t size);
unsigned int	find_header(void *ptr, void **header);
void            lock();
void            unlock();
#endif
