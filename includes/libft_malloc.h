/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:35:51 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/07 18:35:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <ft_printf.h>
# include <unistd.h>

# define debug ft_printf("file : %s, line : %d\n", __FILE__, __LINE__);

# define PAGE_SIZE (getpagesize())
# define TINY 1
# define SMALL 2
# define LARGE 2
# define TINY_BLOCK_MAX_SIZE (PAGE_SIZE / 4)
# define TINY_ZONE_SIZE (PAGE_SIZE * 488)
# define SMALL_BLOCK_MAX_SIZE (PAGE_SIZE * 31)
# define SMALL_ZONE_SIZE (PAGE_SIZE * 3906)

typedef struct		s_block
{
	size_t			size;
	void			*data;
	int				free;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

typedef struct		s_zone
{
	int				size_type;
	size_t			size;
	t_block			*block_lst;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_zones_tree
{
	t_zone			*tiny_lst;
	t_zone			*small_lst;
	t_zone			*large_lst;
}					t_zones_tree;

void				*ft_malloc(size_t size);
t_zone				*create_alloc_zones(t_zone **zone_lst, int zone_type,
					size_t zone_size);
int					get_zone_type(size_t size);

#endif
