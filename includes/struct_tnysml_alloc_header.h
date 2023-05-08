/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tnysml_alloc_header.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:10:16 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/08 16:10:17 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TNYSML_ALLOC_HEADER_H
# define STRUCT_TNYSML_ALLOC_HEADER_H

/*
**	For tiny/small allocations, the next pointer will only be needed if the
**	space is free. And if so, it will be added to a linked list of other free
**	nodes for quick mallocing.
*/

struct								s_tnysml_alloc_header
{
	unsigned char					free;
	unsigned short					used;
	unsigned short					id;
	struct s_tnysml_alloc_header	*next_free;
};

#endif
