/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:32:54 by aimustaev         #+#    #+#             */
/*   Updated: 2023/05/09 12:54:25 by aimustaev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

unsigned short	g_is_debug = 0;

void get_env(void)
{
    if(!ft_strncmp(getenv("FT_MALLOC_TYPE"), "debug", 5))
    {
        g_is_debug = 1;
    }
}

void	lock(void)
{
	get_env();
	pthread_mutex_lock(&g_malloc_mutex);
}

void	unlock(void)
{
	pthread_mutex_unlock(&g_malloc_mutex);
}
