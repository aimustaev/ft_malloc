/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tnysml_mmap_header.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:10:24 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:10:28 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TNYSML_MMAP_HEADER_H
# define STRUCT_TNYSML_MMAP_HEADER_H

/*
**	Linked list of memory from mmap calls.
*/

struct								s_tnysml_mmap_header
{
	unsigned short					nallocs;
	struct s_tnysml_mmap_header		*next_mmap;
};

#endif
