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

/*int	phb_check_printf_verif(t_epis *epis)
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

int	phb_speaking(t_epis *epis, int id, char *message)
{
	unsigned long	st_time;

	st_time = *epis->st_time;
	if (ph_check_printf_verif(epis))
		return (1);
	pthread_mutex_lock(&epis->mtx_printf);
	printf("%ld %d %s", (ph_actualtime() - st_time), id, message);
	pthread_mutex_unlock(&epis->mtx_printf);
	return (0);
}*/

void	phb_speaking(t_sympos *sympos, int philo_id, char *msg)
{
	sem_wait(sympos->sem_one_death);
	sem_wait(sympos->sem_log);

	unsigned long t = phb_actualtime() - sympos->philos[0].agal->st_time;
	printf("%lu %d %s", t, philo_id, msg);
	fflush(stdout);

	sem_post(sympos->sem_log);
	sem_post(sympos->sem_one_death);
}

void phb_speaking_for_dead(t_sympos *sympos, int philo_id)
{
	sem_wait(sympos->sem_one_death);
	sem_wait(sympos->sem_log);
	unsigned long t = phb_actualtime() - sympos->philos[0].agal->st_time;
	printf("%lu %d died\n", t, philo_id);
	fflush(stdout);
	sem_post(sympos->sem_log);
}

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

void	phb_waiting(unsigned long time)
{
	unsigned long	init_time;

	init_time = phb_actualtime();
	while ((phb_actualtime() - init_time) < time)
	{
		usleep(time / 100);
	}
}
