/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:12 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_check_printf_verif(t_epis *epis)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(&epis->mtx_verif);
	tmp = *(epis->verif);
	pthread_mutex_unlock(&epis->mtx_verif);
	if (tmp == -2)
		return (1);
	else
		return (0);
}

int	ph_speaking(t_epis *epis, int id, char *message)
{
	unsigned long	st_time;

	st_time = *epis->st_time;
	if (ph_check_printf_verif(epis))
		return (1);
	pthread_mutex_lock(&epis->mtx_printf);
	printf("%ld %d %s", (ph_actualtime() - st_time), id, message);
	pthread_mutex_unlock(&epis->mtx_printf);
	return (0);
}

void	ph_waiting(unsigned long time, pthread_mutex_t *mutex, int *var)
{
	unsigned long	init_time;

	init_time = ph_actualtime();
	while ((ph_actualtime() - init_time) < time)
	{
		usleep(time / 100);
		if (ph_take_var(mutex, var) != 0)
            break;
	}
}
