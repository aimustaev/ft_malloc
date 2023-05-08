/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lrg_alloc_header.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:10:12 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:10:13 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_LRG_ALLOC_HEADER_H
# define STRUCT_LRG_ALLOC_HEADER_H

# include <unistd.h>

/*
**	This struct is stored at the front of the allocated memory
**	(All large allocations are 1+ pages.)
*/

struct							s_lrg_alloc_header
{
	size_t						used;
	size_t						size;
	struct s_lrg_alloc_header	*prev_alloc;
	struct s_lrg_alloc_header	*next_alloc;
};

#endif
