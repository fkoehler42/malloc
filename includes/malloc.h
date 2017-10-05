/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:35:51 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/05 19:37:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <libft.h>
# include <ft_printf.h>
# include <pthread.h>

# define ERROR_OUT_OF_RANGE 0
# define ERROR_BAD_ADDRESS 0
# define PAGE_SIZE getpagesize()
# define MAX_ALLOC_SIZE (size_t)-1 - (2 * PAGE_SIZE)
# define CANARY(x) (&x + 42)

# define META_BLOCK_SIZE sizeof(t_block)
# define META_ZONE_SIZE sizeof(t_zone)

# define TINY_SIZE (PAGE_SIZE * 30)
# define TINY_MAX_ALLOC (PAGE_SIZE / 16) - META_BLOCK_SIZE
# define TINY_RESOLUTION 8

# define SMALL_SIZE (PAGE_SIZE * 600)
# define SMALL_MAX_ALLOC (PAGE_SIZE * 3) - META_BLOCK_SIZE
# define SMALL_RESOLUTION 16

# define LARGE_RESOLUTION PAGE_SIZE

typedef enum		e_display_flag
{
	ALLOC,
	FREE,
	ALL,
	DUMP
}					t_display_flag;

typedef	enum		e_data_type
{
	BLOCK,
	ZONE,
	NONE
}					t_data_type;

typedef enum		e_size_type
{
	TINY,
	SMALL,
	LARGE,
	UNDEFINED
}					t_size_type;

typedef enum		e_errnum
{
	DATA_CORRUPT,
	NOT_ALLOCATED,
	MAPPING_FAILED,
	ALLOC_OVERSIZED,
	UNMAPPING_FAILED,
	LOCKER_INIT_FAILED
}					t_errnum;

typedef struct		s_block
{
	void			*canary;
	size_t			size;
	int				is_free;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

typedef struct		s_zone
{
	void			*canary;
	t_size_type		type;
	size_t			size;
	t_block			*block_lst;
	struct s_zone	*prev;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_alloc
{
	t_zone			*heap;
	pthread_mutex_t	locker;
	int				locker_init;
}					t_alloc;

extern t_alloc		g_alloc;

void				*malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				free(void *ptr);
void				show_alloc_mem(void);
void				show_mem(t_display_flag display_flag);
void				show_mem_dump(void *address, size_t size);

void				*malloc_unsafe(size_t size);
void				*calloc_unsafe(size_t count, size_t size);
void				*realloc_unsafe(void *ptr, size_t size, int free);
void				free_unsafe(void *ptr);


void				init_locker(void);
void				*get_allocated_ptr(size_t size);
void				deallocate_ptr(void *ptr, t_zone *zone);
void				*realloc_process(void *ptr, size_t size, t_zone *zone);
void				*get_dup_block_ptr(t_block *block, size_t size,
					size_t to_copy);

t_zone				*get_ptr_zone(void *ptr);
t_zone				*create_zone(size_t size);
int					delete_zone(t_zone *zone);

int					is_valid_block(t_block *block, t_zone *zone);
void				check_data_validity(void *data, t_data_type data_type);
void				put_alloc_error(t_errnum errnum, size_t size);
void				put_error(t_errnum errnum, void *address);

t_block				*split_block(t_block *block, size_t size);
void				merge_contiguous_blocks(t_block *block, size_t *zone_size);
t_block				*reduce_block(t_block *block, size_t size,
					size_t *zone_size);
t_block				*enlarge_block(t_block *block, size_t size,
					size_t *zone_size, size_t min_block_size);

t_size_type			get_zone_type(size_t size);
t_size_type			get_block_type(size_t size);
size_t				get_min_block_size(t_size_type type);
size_t				get_rounded_block_size(size_t size);

#endif
