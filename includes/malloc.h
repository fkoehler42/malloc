/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:35:51 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/07 18:35:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <ft_printf.h>
# include <unistd.h>

# define debug ft_printf("file : %s, line : %d\n", __FILE__, __LINE__);

# define TINY_MAX_ALLOC (size_t)(getpagesize() / 4)
# define TINY_SIZE (size_t)(getpagesize() * 488)
# define SMALL_MAX_ALLOC (size_t)(getpagesize() * 31)
# define SMALL_SIZE (size_t)(getpagesize() * 3906)

// typedef enum 		e_zone_type
// {
// 	TINY,
// 	SMALL,
// 	LARGE
// }					t_zone_type;

typedef struct		s_block
{
	size_t			size;
	void			*data;
	int				is_free;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

typedef struct		s_zone
{
	// t_zone_type		zone_type;
	size_t			size;
	t_block			*block_lst;
	struct s_zone	*next;
}					t_zone;

void				*ft_malloc(size_t size);
t_zone				*create_alloc_zone(t_zone **zone_lst, size_t size);
// int					get_zone_type(size_t size);

#endif
