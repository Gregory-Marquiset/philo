/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:56:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:36:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

unsigned long	phb_actualtime(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
	{
		printf(LERR_GETTIME);
		return (0);
	}
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}
