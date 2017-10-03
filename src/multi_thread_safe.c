/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread_safe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:07:44 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/03 13:12:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc		g_alloc = {NULL, PTHREAD_MUTEX_INITIALIZER, 0};

void		free(void *ptr)
{
	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	free_unsafe(ptr);
	pthread_mutex_unlock(&g_alloc.locker);
}

void		*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	new_ptr = realloc_unsafe(ptr, size, 0);
	pthread_mutex_unlock(&g_alloc.locker);
	return (new_ptr);
}

void		*reallocf(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	new_ptr = realloc_unsafe(ptr, size, 1);
	pthread_mutex_unlock(&g_alloc.locker);
	return (new_ptr);
}

void		*calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	ptr = calloc_unsafe(count, size);
	pthread_mutex_unlock(&g_alloc.locker);
	return (ptr);
}

void		*malloc(size_t size)
{
	void	*ptr;

	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	ptr = malloc_unsafe(size);
	pthread_mutex_unlock(&g_alloc.locker);
	return (ptr);
}
