/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 13:46:35 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	*ph_routine_philos(void *tmp)
{
	t_philo *philo = (t_philo *)tmp;
	ph_seat_on_table(philo);
	ph_speaking(&philo->epis->mprintf, philo->epis->start_time, philo->id, LPRO_JSYM);
	while (philo->epis->sympos_states == OPEN)
	{
		if (philo->epis->sympos_states == OPEN)
			ph_eating(philo);
		if (philo->epis->sympos_states == OPEN)
			ph_sleeping(philo);
		if (philo->epis->sympos_states == OPEN)
			ph_speaking(&philo->epis->mprintf, philo->epis->start_time, philo->id, LPRO_THINK);
	}
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	int	i;

	t_epis *epis = (t_epis *)tmp;
	epis->start_time = ph_actualtime();
	ph_speaking(&epis->mprintf, epis->start_time, 0, "epis watch the symposium\n");
	ph_open_table(epis);
	i = 0;
	while (epis->sympos_states == OPEN)
	{
		while (epis->n_meal > 0 && i < epis->n_philos)
		{
			if (epis->philos_meals[i] == -1)
				i++;
		}
		if (i == epis->n_philos)
			epis->sympos_states = CLOSE;
	}
	return (NULL);
}

void	ph_threading(t_sympos *sympos)
{
	int	i;

	i = 0;
	if (pthread_create(&sympos->epis->thread_ep, NULL, &ph_routine_epis, sympos->epis))
			ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
	ph_waiting(1);
	while (i < sympos->epis->n_philos)
	{
		if (pthread_create(&sympos->philos[i].thread_ph, NULL, &ph_routine_philos, &sympos->philos[i]))
			ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
		i++;
	}
	i = 0;
	while (i < sympos->epis->n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		ph_speaking(&sympos->epis->mprintf, sympos->epis->start_time, i + 1, "left the symposium\n");
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	ph_speaking(&sympos->epis->mprintf, sympos->epis->start_time, 0, "epis left the symposium\n");
}
