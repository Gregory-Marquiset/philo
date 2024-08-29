/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:56:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/29 22:19:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

size_t	ft_actualtime(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
	{
		printf(LERR_GETTIME);
		return (0);
	}
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}

void	ft_sleeping(size_t inter)
{
	size_t	init_time;

	init_time = ft_actualtime();
	while (1)
	{
		if(ft_actualtime() - init_time >= inter)
			break ;
	}
}
