/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/26 15:08:22 by gmarquis         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->epis->mtx->mtx_sy_states);
	while (*(philo->epis->kine->sy_states) == OPEN)
	{
		pthread_mutex_unlock(&philo->epis->mtx->mtx_sy_states);
		ph_eating(philo);
		ph_sleeping(philo);
		ph_speaking(&philo->epis->mtx->mtx_printf, philo->epis->agal->st_time,
			philo->id, LPRO_THINK);
		pthread_mutex_lock(&philo->epis->mtx->mtx_sy_states);
	}
	pthread_mutex_unlock(&philo->epis->mtx->mtx_sy_states);
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	int		i;
	t_epis	*epis;

	epis = (t_epis *)tmp;
	epis->agal->st_time = ph_actualtime();
	ph_speaking(&epis->mtx->mtx_printf, epis->agal->st_time, 0, LTEST_TEST_EW);
	ph_open_table(epis);
	i = 0;
	while (*(epis->kine->sy_states) == OPEN)
	{
		while (epis->agal->n_meal > 0 && i < epis->agal->n_philos)
		{
			if (epis->kine->phs_meals[i] == -1)
				i++;
		}
		if (i == epis->agal->n_philos)
			*(epis->kine->sy_states) = CLOSE;
	}
	return (NULL);
}

void	ph_threading(t_sympos *sympos)
{
	int	i;

	ph_init_thread(sympos, &sympos->epis->thread_ep, &ph_routine_epis,
		sympos->epis);
	ph_waiting(1);
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
		ph_speaking(&sympos->epis->mtx->mtx_printf, sympos->epis->agal->st_time,
			i + 1, LTEST_TEST_PL);
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	ph_speaking(&sympos->epis->mtx->mtx_printf, sympos->epis->agal->st_time,
		0, LTEST_TEST_EL);
}