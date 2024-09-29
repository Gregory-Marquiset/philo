/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/29 15:04:25 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	*ph_routine_philos(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	ph_speaking(philo->kine->mtx_printf, philo->epis->agal->st_time,
		philo->id, LPRO_JSYM);
	ph_seat_on_table(philo);
	pthread_mutex_lock(philo->kine->mtx_sy_states);
	while (*(philo->epis->kine->sy_states) == OPEN)
	{
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
		ph_eating(philo);
		ph_sleeping(philo);
		ph_thinking(philo);
		pthread_mutex_lock(philo->kine->mtx_sy_states);
	}
	pthread_mutex_unlock(philo->kine->mtx_sy_states);
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	t_epis *(epis) = (t_epis *)tmp;
	ph_speaking(&epis->mtx->mtx_printf, epis->agal->st_time, 0, LTEST_TEST_EW);
	ph_open_table(epis);
	pthread_mutex_lock(&epis->mtx->mtx_sy_states);
	while (*(epis->kine->sy_states) == OPEN)
	{
		pthread_mutex_unlock(&epis->mtx->mtx_sy_states);
		if (epis->agal->n_meal > 0)
			ph_with_target_meals(epis);
		else
			ph_without_target_meals(epis);
		pthread_mutex_lock(&epis->mtx->mtx_sy_states);
	}
	pthread_mutex_unlock(&epis->mtx->mtx_sy_states);
	pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	if (*(epis->kine->id_dead) != 0)
	{
		pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
		ph_speaking(&epis->mtx->mtx_printf, epis->agal->st_time, *epis->kine->id_dead, LPRO_DIED);
	}
	else
		pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
	return (NULL);
}

void	ph_threading(t_sympos *sympos)
{
	int	i;

	ph_init_thread(sympos, &sympos->epis->thread_ep, &ph_routine_epis,
		sympos->epis);
	i = 0;
	while (i < sympos->epis->agal->n_philos)
	{
		ph_init_thread(sympos, &sympos->philos[i].thread_ph, &ph_routine_philos,
			&sympos->philos[i]);
		i++;
	}
	i = 0;
	while (i < sympos->epis->agal->n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		//ph_speaking(&sympos->epis->mtx->mtx_printf, sympos->epis->agal->st_time,
		//	i + 1, LTEST_TEST_PL);
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	//ph_speaking(&sympos->epis->mtx->mtx_printf, sympos->epis->agal->st_time,
	//	0, LTEST_TEST_EL);
}
