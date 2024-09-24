/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/24 19:22:35 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/proto.h"

void	ph_seat_on_table(void)
{
	int (i) = 0;

	while (i != 50)
	{
		i++;
	}
}

void	ph_speaking(pthread_mutex_t *mutex, int start_time, int id, char *message)
{
	pthread_mutex_lock(mutex);
	if (id == 0)
		printf("%-10d %s", (int)ph_actualtime() - start_time, message);
	else
		printf("%-10d %-4d %s", (int)ph_actualtime() - start_time, id, message);
	pthread_mutex_unlock(mutex);
}
