/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/31 18:38:28 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/proto.h"

static void	ft_init_obeliskos(t_philo *philo, t_philo *dexi_philo, int pos)
{
	if (pos == 0)
		pthread_mutex_init(&philo->aris_obeli, NULL);
	else if (pos == 1)
	{
		pthread_mutex_init(&philo->aris_obeli, NULL);
		philo->dexi_obeli = &dexi_philo->aris_obeli;
	}
	else if (pos == 2)
		philo->dexi_obeli = &dexi_philo->aris_obeli;
}

static void	ft_init_philos(t_sympos *sympos)
{
	int	i;

	i = 0;
	sympos->philos = malloc(sympos->epís->n_philos * sizeof(t_philo));
	if (!sympos->philos)
		ft_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	while (i < sympos->epís->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].thread_ph = 0;
		sympos->philos[i].last_meal = 0;
		sympos->philos[i].count_meal = 0;
		sympos->philos[i].state = 0;
		sympos->philos[i].epís = sympos->epís;
		if (i == 0)
			ft_init_obeliskos(&sympos->philos[i], NULL , 0);
		else
			ft_init_obeliskos(&sympos->philos[i], &sympos->philos[i - 1], 1);
		i++;
	}
	if (sympos->epís->n_philos > 1)
		ft_init_obeliskos(&sympos->philos[0], &sympos->philos[i - 1], 2);
}

static void	ft_init_epis(t_sympos *sympos, t_epís *tmp)
{
	sympos->epís = malloc(sizeof(t_epís));
	if (!sympos->epís)
		ft_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	sympos->epís->meal_stat = malloc(tmp->n_philos * sizeof(int));
	if (!sympos->epís->meal_stat)
		ft_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	if (pthread_mutex_init(&sympos->epís->mprintf, NULL))
		ft_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
	sympos->epís->start_time = 0;
	sympos->epís->thread_ep = 0;
	sympos->epís->id_dead = 0;
	sympos->epís->n_meal = tmp->n_meal;
	sympos->epís->n_philos = tmp->n_philos;
	sympos->epís->time_to_die = tmp->time_to_die;
	sympos->epís->time_to_eat = tmp->time_to_eat;
	sympos->epís->time_to_sleep = tmp->time_to_sleep;
	sympos->epís->end_sympos = 1;
}

t_sympos	*ft_init_sympos(t_epís *tmp)
{
	t_sympos	*sympos;

	sympos = malloc(sizeof(t_sympos));
	if (!sympos)
		ft_quit_philo(NULL, 2, LERR_MALLOC, CERR_MALLOC);
	ft_init_epis(sympos, tmp);
	ft_init_philos(sympos);
	return (sympos);
}
