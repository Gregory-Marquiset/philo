/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/24 21:47:16 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/proto.h"

static void	ph_init_fork(t_philo *philo, t_philo *dexi_philo, int pos)
{
	if (pos == 0)
		pthread_mutex_init(&philo->lf_fork, NULL);
	else if (pos == 1)
	{
		pthread_mutex_init(&philo->lf_fork, NULL);
		philo->rg_fork = &dexi_philo->lf_fork;
	}
	else if (pos == 2)
		philo->rg_fork = &dexi_philo->lf_fork;
}

static void	ph_init_philos(t_sympos *sympos)
{
	int	i;

	i = 0;
	sympos->philos = malloc(sympos->epís->n_philos * sizeof(t_philo));
	if (!sympos->philos)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->epís->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].thread_ph = 0;
		sympos->philos[i].last_meal = 0;
		sympos->philos[i].count_meal = 0;
		sympos->philos[i].philo_state = &(sympos->epís->philos_states[i]);
		sympos->philos[i].philo_meal = &(sympos->epís->philos_meals[i]);
		sympos->philos[i].epís = sympos->epís;
		if (i == 0)
			ph_init_fork(&sympos->philos[i], NULL , 0);
		else
			ph_init_fork(&sympos->philos[i], &sympos->philos[i - 1], 1);
		i++;
	}
	if (sympos->epís->n_philos > 1)
		ph_init_fork(&sympos->philos[0], &sympos->philos[i - 1], 2);
}

static void	ph_init_states_meals(t_sympos *sympos)
{
	int	i;

	i = 0;
	sympos->epís->philos_states = malloc(sympos->epís->n_philos * sizeof(int));
	if (!sympos->epís->philos_states)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	sympos->epís->philos_meals = malloc(sympos->epís->n_philos * sizeof(int));
	if (!sympos->epís->philos_meals)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->epís->n_philos)
	{
		sympos->epís->philos_states[i] = GET_READY;
		if (sympos->epís->n_meal == -1)
			sympos->epís->philos_meals[i] = -1;
		else
			sympos->epís->philos_meals[i] = 0;
		i++;
	}

}

static void	ph_init_epis(t_sympos *sympos, t_epís *tmp)
{
	sympos->epís = malloc(sizeof(t_epís));
	if (!sympos->epís)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	sympos->epís->n_philos = tmp->n_philos;
	sympos->epís->n_meal = tmp->n_meal;
	ph_init_states_meals(sympos);
	if (pthread_mutex_init(&sympos->epís->mprintf, NULL))
		ph_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
	sympos->epís->start_time = 0;
	sympos->epís->thread_ep = 0;
	sympos->epís->id_dead = 0;
	sympos->epís->n_philos = tmp->n_philos;
	sympos->epís->time_to_die = tmp->time_to_die;
	sympos->epís->time_to_eat = tmp->time_to_eat;
	sympos->epís->time_to_sleep = tmp->time_to_sleep;
	sympos->epís->end_sympos = 1;
}

t_sympos	*ph_init_sympos(t_epís *tmp)
{
	t_sympos	*sympos;

	sympos = malloc(sizeof(t_sympos));
	if (!sympos)
		ph_quit_philo(NULL, 2, LERR_MALLOC, CERR_MALLOC);
	ph_init_epis(sympos, tmp);
	ph_init_philos(sympos);
	return (sympos);
}
