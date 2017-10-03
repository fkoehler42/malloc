/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory_dump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 15:25:29 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/03 16:56:49 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "malloc.h"

 void	show_mem_dump(void *address, size_t size)
 {
	 size_t			i;
	 unsigned char	*bytes;

	 i = 0;
	 bytes = (unsigned char*)address;
	 while (i < size)
	 {
		 if (bytes[i] < 16)
			 ft_putchar('0');
		 ft_put_uintmax((size_t)bytes[i], 16);
		 ft_putchar(' ');
		 i++;
	 }
	 ft_putchar('\n');
 }
