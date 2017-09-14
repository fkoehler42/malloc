/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:35:51 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/14 15:56:07 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <ft_printf.h>
# include <unistd.h>

# define debug ft_printf("file : %s, line : %d\n", __FILE__, __LINE__);

# define PAGE_SIZE getpagesize()
# define MAX_ALLOC_SIZE (size_t)-1 - (2 * PAGE_SIZE)

# define META_BLOCK_SIZE sizeof(t_block)
# define META_ZONE_SIZE sizeof(t_zone)

# define TINY_SIZE (size_t)(PAGE_SIZE * 488)
# define TINY_MAX_ALLOC (size_t)(PAGE_SIZE / 4) - META_BLOCK_SIZE
# define TINY_RESOLUTION 16

# define SMALL_SIZE (size_t)(PAGE_SIZE * 3906)
# define SMALL_MAX_ALLOC (size_t)(PAGE_SIZE * 31) - META_BLOCK_SIZE
# define SMALL_RESOLUTION 512

# define LARGE_RESOLUTION 4096

typedef enum 		e_size_type
{
	TINY,
	SMALL,
	LARGE
}					t_size_type;

typedef struct		s_block
{
	size_t			size; // block content only (no META)
	int				is_free;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

typedef struct		s_zone
{
	t_size_type		type;
// full_blocks * (block->size + META_BLOCK_SIZE) + free_blocks * META_BLOCK_SIZE
	size_t			size;
	t_block			*block_lst;
	struct s_zone	*next;
}					t_zone;

t_zone				*g_alloc_start;

void				*ft_malloc(size_t size);

t_zone				*create_zone(size_t size);
void				*get_allocated_ptr(size_t size);

t_block				*split_and_add_block(t_block *block, size_t size);

t_size_type			get_zone_type(size_t size);
t_size_type			get_block_type(size_t size);
size_t				get_zone_total_size(t_size_type type);
size_t				get_min_block_size(t_size_type type);
size_t				get_rounded_block_size(size_t size);

#endif
