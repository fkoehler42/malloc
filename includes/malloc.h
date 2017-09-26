/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:35:51 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/26 17:28:33 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <libft.h>
# include <ft_printf.h>
# include <unistd.h>

# define debug ft_printf("file : %s, line : %d\n", __FILE__, __LINE__);
# define PAGE_SIZE getpagesize()
# define MAX_ALLOC_SIZE (size_t)-1 - (2 * PAGE_SIZE)
# define CANARY(x) (&x + 42)

# define META_BLOCK_SIZE sizeof(t_block)
# define META_ZONE_SIZE sizeof(t_zone)

# define TINY_SIZE (size_t)(PAGE_SIZE * 100)
# define TINY_MAX_ALLOC (size_t)(PAGE_SIZE / 4) - META_BLOCK_SIZE
# define TINY_RESOLUTION 16

# define SMALL_SIZE (size_t)(PAGE_SIZE * 1700)
# define SMALL_MAX_ALLOC (size_t)(PAGE_SIZE * 15) - META_BLOCK_SIZE
# define SMALL_RESOLUTION 256

# define LARGE_RESOLUTION PAGE_SIZE

typedef enum		e_block_state
{
	ALLOC,
	FREE,
	ALL
}					t_block_state;

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
	FREE_FAILED,
	MAPPING_FAILED,
	UNMAPPING_FAILED
}					t_errnum;

typedef struct		s_block
{
	void			*canary;
	size_t			size; // block content only (no META)
	int				is_free;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

typedef struct		s_zone
{
	void			*canary;
	t_size_type		type;
// full_blocks * (block->size + META_BLOCK_SIZE) + (free_blocks * META_BLOCK_SIZE) + META_ZONE_SIZE
	size_t			size;
	t_block			*block_lst;
	struct s_zone	*prev;
	struct s_zone	*next;
}					t_zone;

t_zone				*g_alloc_start;

void				*ft_malloc(size_t size);
void				*ft_calloc(size_t count, size_t size);
void				*ft_realloc(void *ptr, size_t size);
void				ft_free(void *ptr);
void				show_alloc_mem(void);
void				show_mem(t_block_state block_state);

void				*get_allocated_ptr(size_t size);
int					deallocate_ptr(void *ptr, t_zone *zone);
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
int 				merge_contiguous_blocks(t_block *block, size_t *zone_size);
t_block				*reduce_block(t_block *block, size_t size,
					size_t *zone_size);
t_block				*enlarge_block(t_block *block, size_t size,
					size_t *zone_size, size_t min_block_size);


char				*get_zone_type_str(t_size_type type);
t_size_type			get_zone_type(size_t size);
t_size_type			get_block_type(size_t size);
size_t				get_min_block_size(t_size_type type);
size_t				get_rounded_block_size(size_t size);

#endif
