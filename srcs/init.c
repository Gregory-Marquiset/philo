/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 10:42:55 by gmarquis         ###   ########.fr       */
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
	sympos->philos = malloc(sympos->epis->n_philos * sizeof(t_philo));
	if (!sympos->philos)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->epis->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].thread_ph = 0;
		sympos->philos[i].last_meal = 0;
		sympos->philos[i].count_meal = 0;
		sympos->philos[i].philo_state = &(sympos->epis->philos_states[i]);
		*(sympos->philos[i].philo_state) = READY;
		sympos->philos[i].philo_meal = &(sympos->epis->philos_meals[i]);
		sympos->philos[i].epis = sympos->epis;
		if (i == 0)
			ph_init_fork(&sympos->philos[i], NULL , 0);
		else
			ph_init_fork(&sympos->philos[i], &sympos->philos[i - 1], 1);
		i++;
	}
	if (sympos->epis->n_philos > 1)
		ph_init_fork(&sympos->philos[0], &sympos->philos[i - 1], 2);
	sympos->epis->sympos_states = OPEN;
}

static void	ph_init_states_meals(t_sympos *sympos)
{
	int	i;

	i = 0;
	sympos->epis->philos_states = malloc(sympos->epis->n_philos * sizeof(int));
	if (!sympos->epis->philos_states)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	sympos->epis->philos_meals = malloc(sympos->epis->n_philos * sizeof(int));
	if (!sympos->epis->philos_meals)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->epis->n_philos)
	{
		sympos->epis->philos_states[i] = GET_READY;
		if (sympos->epis->n_meal == -1)
			sympos->epis->philos_meals[i] = -1;
		else
			sympos->epis->philos_meals[i] = 0;
		i++;
	}

}

static void	ph_init_epis(t_sympos *sympos, t_epis *tmp)
{
	sympos->epis = malloc(sizeof(t_epis));
	if (!sympos->epis)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	sympos->epis->n_philos = tmp->n_philos;
	sympos->epis->n_meal = tmp->n_meal;
	ph_init_states_meals(sympos);
	if (pthread_mutex_init(&sympos->epis->mprintf, NULL))
		ph_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
	sympos->epis->start_time = 0;
	sympos->epis->thread_ep = 0;
	sympos->epis->id_dead = 0;
	sympos->epis->n_philos = tmp->n_philos;
	sympos->epis->time_to_die = tmp->time_to_die;
	sympos->epis->time_to_eat = tmp->time_to_eat;
	sympos->epis->time_to_sleep = tmp->time_to_sleep;
	sympos->epis->sympos_states = SETING;
}

t_sympos	*ph_init_sympos(t_epis *tmp)
{
	t_sympos	*sympos;

	sympos = malloc(sizeof(t_sympos));
	if (!sympos)
		ph_quit_philo(NULL, 2, LERR_MALLOC, CERR_MALLOC);
	ph_init_epis(sympos, tmp);
	ph_init_philos(sympos);
	return (sympos);
}
