/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 10:07:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	*ph_routine_philos(void *tmp)
{
	t_philo *philo = (t_philo *)tmp;
	ph_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_JSYM);
	ph_seat_on_table();
	while (philo->epís->end_sympos)
	{
		if (philo->epís->end_sympos)
			ph_eating(philo);
		if (philo->epís->end_sympos)
			ph_sleeping(philo);
		if (philo->epís->end_sympos)
			ph_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_THINK);
	}
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	int	i;

	t_epís *epís = (t_epís *)tmp;
	epís->start_time = ph_actualtime();
	ph_speaking(&epís->mprintf, epís->start_time, 0, "epís watch the symposium\n");
	i = 0;
	while (epís->end_sympos)
	{
		while (epís->n_meal > 0 && i < epís->n_philos)
		{
			if (epís->philos_meals[i] == -1)
				i++;
		}
		if (i == epís->n_philos)
			epís->end_sympos = 0;
	}
	return (NULL);
}

void	ph_threading(t_sympos *sympos)
{
	int	i;

	i = 0;
	if (pthread_create(&sympos->epís->thread_ep, NULL, &ph_routine_epis, sympos->epís))
			ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
	sleep (1);
	while (i < sympos->epís->n_philos)
	{
		if (pthread_create(&sympos->philos[i].thread_ph, NULL, &ph_routine_philos, &sympos->philos[i]))
			ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
		i++;
	}
	i = 0;
	while (i < sympos->epís->n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		ph_speaking(&sympos->epís->mprintf, sympos->epís->start_time, i + 1, "left the symposium\n");
		i++;
	}
	if (pthread_join(sympos->epís->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	ph_speaking(&sympos->epís->mprintf, sympos->epís->start_time, 0, "epís left the symposium\n");
}
