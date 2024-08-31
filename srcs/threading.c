/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/31 19:12:08 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	*ft_routine_philos(void *tmp)
{
	int	i = 0;
	t_philo *philo = (t_philo *)tmp;
	ft_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_JSYM);
	while (i < philo->epís->n_meal)
	{
		if (philo->epís->end_sympos)
			ft_eating(philo);
		if (philo->epís->end_sympos)
			ft_sleeping(philo);
		if (philo->epís->end_sympos)
			ft_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_THINK);
		i++;
	}
	return (NULL);
}

static void	*ft_routine_epis(void *tmp)
{
	int	i;

	t_epís *epís = (t_epís *)tmp;
	epís->start_time = ft_actualtime();
	ft_speaking(&epís->mprintf, epís->start_time, 0, "epís watch the symposium\n");
	while (epís->end_sympos)
	{
		i = 0;
		while (i < epís->n_meal)
		{
			if (epís->meal_stat[i] == 1)
				i++;
			if (i == epís->n_meal)
			{
				ft_speaking(&epís->mprintf, epís->start_time, 0, LPRO_MEAL);
				epís->end_sympos = 0;
			}
			if (epís->id_dead)
			{
				ft_speaking(&epís->mprintf, epís->start_time, *epís->id_dead, LPRO_DIED);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	ft_threading(t_sympos *sympos)
{
	int	i;

	i = 0;
	if (pthread_create(&sympos->epís->thread_ep, NULL, &ft_routine_epis, sympos->epís))
			ft_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
	while (i < sympos->epís->n_philos)
	{
		if (pthread_create(&sympos->philos[i].thread_ph, NULL, &ft_routine_philos, &sympos->philos[i]))
			ft_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
		i++;
	}
	i = 0;
	while (i < sympos->epís->n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ft_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		ft_speaking(&sympos->epís->mprintf, sympos->epís->start_time, i + 1, "left the symposium\n");
		i++;
	}
	if (pthread_join(sympos->epís->thread_ep, NULL))
		ft_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	ft_speaking(&sympos->epís->mprintf, sympos->epís->start_time, 0, "epís left the symposium\n");
}
