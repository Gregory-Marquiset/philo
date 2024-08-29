/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/29 23:21:30 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"
/*
static void	ft_chopstick_init(t_philo *philo, t_philo *l_philo, int pos)
{
	if (pos == 0)
		pthread_mutex_init(&philo->dexiós_obeliskos, NULL);
	else if (pos == 1)
	{
		pthread_mutex_init(&philo->dexi_obeli, NULL);
		philo->aristerós_obeliskos = &l_philo->dexiós_obeliskos;
	}
	else if (pos == 2)
		philo->aristerós_obeliskos = &l_philo->dexiós_obeliskos;
}

static void	ft_init_philos(t_sympos *sympos)
{
	int	i;

	i = 0;
	while (i < symposium->epís->n_philos)
	{
		symposium->philos[i] = malloc(sizeof(t_philo));
		if (!symposium->philos[i])
			ft_leave_table(symposium, 2, "Error: echec malloc symposium->philos[n]\n", 52);
		symposium->philos[i]->id = i + 1;
		symposium->philos[i]->thread = 0;
		symposium->philos[i]->last_meal = 0;
		symposium->philos[i]->count_meal = 0;
		symposium->philos[i]->state = 0;
		if (i == 0)
			ft_chopstick_init(symposium->philos[i], NULL , 0);
		else
			ft_chopstick_init(symposium->philos[i], symposium->philos[i - 1], 1);
		i++;
	}
	if (symposium->epís->n_philos > 1)
		ft_chopstick_init(symposium->philos[0], symposium->philos[i - 1], 2);
}
*/

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
	sympos->epís->id_dead = 0;
	sympos->epís->n_meal = tmp->n_meal;
	sympos->epís->n_philos = tmp->n_philos;
	sympos->epís->time_to_die = tmp->time_to_die;
	sympos->epís->time_to_eat = tmp->time_to_eat;
	sympos->epís->time_to_sleep = tmp->time_to_sleep;
}

t_sympos	*ft_init_sympos(t_epís *tmp)
{
	t_sympos	*sympos;

	sympos = malloc(sizeof(t_sympos));
	if (!sympos)
		ft_quit_philo(NULL, 2, LERR_MALLOC, CERR_MALLOC);
	ft_init_epis(sympos, tmp);

	/*sympos->philos = malloc(epís.n_philos * sizeof(t_philo *) + 1);
	if (!sympos->philos)
		ft_exit(2, "Error: echec malloc symposium->philos\n", 52);
	sympos->philos[epís.n_philos] = NULL;
	sympos->epís = malloc(sizeof(t_epís));
	if (!sympos->epís)
		ft_leave_table(sympos, 2, "Error: echec malloc symposium->utils\n", 52);
	*sympos->epís = epís;
	ft_init_philos(sympos);*/
	return (sympos);
}
