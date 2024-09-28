/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:56:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/28 15:07:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_incr_var(pthread_mutex_t *mutex, int *var)
{
	pthread_mutex_lock(mutex);
	*var += 1;
	pthread_mutex_unlock(mutex);
}

void	ph_modif_var(pthread_mutex_t *mutex, int *dest, int src)
{
	pthread_mutex_lock(mutex);
	*dest = src;
	pthread_mutex_unlock(mutex);
}

size_t	ph_actualtime(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
	{
		printf(LERR_GETTIME);
		return (0);
	}
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}

/*	> programme logs:

	timestamp_in_ms X has taken a fork
	timestamp_in_ms X is eating
	timestamp_in_ms X is sleeping
	timestamp_in_ms X is thinking
	timestamp_in_ms X died

	Replace timestamp_in_ms with the current timestamp in milliseconds
	and X with the philosopher number.
*/
