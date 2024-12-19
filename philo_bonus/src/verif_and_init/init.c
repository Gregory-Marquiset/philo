/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:38 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static void	st_get_tt_start(t_philo *philo, int n_philos)
{
	unsigned long	*tt_start;
	unsigned long	*tt_eat;

	tt_start = &(philo->agal->tt_start);
	tt_eat = &(philo->agal->tt_eat);
	if (philo->id == 1)
		*tt_start = 0;
	else if (philo->id % 2 == 0)
		*tt_start = *tt_eat;
	else if (philo->id % 2 != 0)
	{
		if (n_philos % 2 != 0)
			*tt_start = *tt_eat + *tt_eat;
		else
			*tt_start = 0;
	}
}

static void	st_get_tt_think(t_philo *philo, int n_philos)
{
	unsigned long	*tt_eat;
	unsigned long	*tt_sleep;
	unsigned long	*tt_think;

	tt_eat = &(philo->agal->tt_eat);
	tt_sleep = &(philo->agal->tt_sleep);
	tt_think = &(philo->agal->tt_think);
	if (n_philos % 2 == 0)
	{
		if (*tt_eat > *tt_sleep)
			*tt_think = *tt_eat - *tt_sleep;
		if (*tt_eat <= *tt_sleep)
			*tt_think = 0;
	}
	else if (n_philos % 2 != 0)
	{
		if (*tt_sleep >= (*tt_eat * 2))
			*tt_think = 0;
		else
			*tt_think = (*tt_eat * 2) - *tt_sleep;
	}
}

static void	st_init_philo_agalma(t_sympos *sympos, t_philo *philo,
	t_agalma *tmp)
{
	t_agalma	*agal;

	philo->agal = malloc(1 * sizeof(t_agalma));
	if (!philo->agal)
		phb_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	agal = philo->agal;
	agal->n_meal = tmp->n_meal;
	agal->tt_eat = tmp->tt_eat;
	agal->tt_sleep = tmp->tt_sleep;
	agal->tt_die = tmp->tt_die;
	st_get_tt_start(philo, sympos->n_philos);
	st_get_tt_think(philo, sympos->n_philos);
}

static void	st_init_philos(t_sympos *sympos, t_agalma *tmp)
{
	int	i;

	i = 0;
	sympos->philos = malloc(sympos->n_philos * sizeof(t_philo));
	if (!sympos->philos)
		phb_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].pid_philos = 0;
		st_init_philo_agalma(sympos, &(sympos->philos[i]), tmp);
		i++;
	}
}

t_sympos	*phb_init_sympos(t_agalma *tmp, int n_philos)
{
	t_sympos	*sympos;

	sympos = malloc(1 * sizeof(t_sympos));
	if (!sympos)
		phb_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	memset(sympos, 0, sizeof(t_sympos));
	sympos->n_philos = n_philos;
	st_init_philos(sympos, tmp);
	return (sympos);
}
