/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:41:31 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 16:47:51 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
** Comment the lines to check the different error cases :
** double free, bad address into/out of mapping range
*/

int	main(void)
{
	char *s;

	s = (char*)malloc(42);
	s[0] = 42;
	free(s);
	free(s);
	free(s + 10);
	free(s - 1000000);
	return (0);
}
