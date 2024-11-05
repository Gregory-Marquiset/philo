/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/25 09:55:06 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	st_launch_thread(t_sympos *sympos)
{
	int	i;

	i = 0;
	while (i < sympos->epis->agal->n_philos)
	{
		if ((i + 1) % 2 == 0)
			ph_init_thread(sympos, &sympos->philos[i].thread_ph, &ph_routine_even,
				&sympos->philos[i]);
		else
			ph_init_thread(sympos, &sympos->philos[i].thread_ph, &ph_routine_uneven,
				&sympos->philos[i]);
		i++;
	}
}

void	ph_threading(t_sympos *sympos)
{
	int	i;

	sympos->epis->agal->st_time = ph_actualtime() + 101;
	ph_init_thread(sympos, &sympos->epis->thread_ep, &ph_routine_epis,
		sympos->epis);
	ph_waiting(1);
	pthread_mutex_lock(&sympos->epis->mtx->mtx_phs_states);
	st_launch_thread(sympos);
	pthread_mutex_unlock(&sympos->epis->mtx->mtx_phs_states);
	i = 0;
	while (i < sympos->epis->agal->n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
}
