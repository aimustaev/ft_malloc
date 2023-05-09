/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:32:54 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 12:35:28 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	lock(void)
{
	pthread_mutex_lock(&g_malloc_mutex);
}

void	unlock(void)
{
	pthread_mutex_unlock(&g_malloc_mutex);
}
