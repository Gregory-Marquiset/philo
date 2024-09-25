/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 19:00:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	*ph_routine_philos(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	ph_seat_on_table(philo);
	ph_speaking(&philo->epis->mprintf, philo->epis->agal->st_time,
		philo->id, LPRO_JSYM);
	while (philo->epis->kine->sy_states == OPEN)
	{
		if (philo->epis->kine->sy_states == OPEN)
			ph_eating(philo);
		if (philo->epis->kine->sy_states == OPEN)
			ph_sleeping(philo);
		if (philo->epis->kine->sy_states == OPEN)
			ph_speaking(&philo->epis->mprintf, philo->epis->agal->st_time,
				philo->id, LPRO_THINK);
	}
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	int		i;
	t_epis	*epis;

	epis = (t_epis *)tmp;
	epis->agal->st_time = ph_actualtime();
	ph_speaking(&epis->mprintf, epis->agal->st_time, 0, LTEST_TEST_EW);
	ph_open_table(epis);
	i = 0;
	while (epis->kine->sy_states == OPEN)
	{
		while (epis->agal->n_meal > 0 && i < epis->agal->n_philos)
		{
			if (epis->kine->phs_meals[i] == -1)
				i++;
		}
		if (i == epis->agal->n_philos)
			epis->kine->sy_states = CLOSE;
	}
	return (NULL);
}

void	ph_threading(t_sympos *sympos)
{
	int (i) = 0;
	if (pthread_create(&sympos->epis->thread_ep, NULL, &ph_routine_epis,
			sympos->epis))
		ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
	ph_waiting(1);
	while (i < sympos->epis->agal->n_philos)
	{
		if (pthread_create(&sympos->philos[i].thread_ph, NULL,
				&ph_routine_philos, &sympos->philos[i]))
			ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
		i++;
	}
	i = 0;
	while (i < sympos->epis->agal->n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		ph_speaking(&sympos->epis->mprintf, sympos->epis->agal->st_time,
			i + 1, LTEST_TEST_PL);
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	ph_speaking(&sympos->epis->mprintf, sympos->epis->agal->st_time,
		0, LTEST_TEST_EL);
}
