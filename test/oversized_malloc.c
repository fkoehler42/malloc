/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oversized_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:45:38 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 17:58:41 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	main(void)
{
	void	*str1;
	void	*str2;
	void	*str3;

	str1 = (char*)malloc(MAX_ALLOC_SIZE);
	str2 = (char*)malloc(MAX_ALLOC_SIZE + 1);
	str3 = (char*)malloc(-1);
	ft_putstr("str1 malloc return : 0x");
	ft_put_uintmax((size_t)str1, 16);
	ft_putstr("\nstr2 malloc return : 0x");
	ft_put_uintmax((size_t)str2, 16);
	ft_putstr("\nstr3 malloc return : 0x");
	ft_put_uintmax((size_t)str3, 16);
	return (0);
}
