/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/27 17:46:53 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void	ft_chopstick_init(t_philo *philo, t_philo *l_philo, int the_last)
{
	/*if (!l_philo && !the_last)
	{
		pthread_mutex_init(&philo->left_chopstick, NULL);
		pthread_mutex_init(&philo->right_chopstick, NULL);
	}
	else if (l_philo && !the_last)
	{
		philo->left_chopstick = l_philo->right_chopstick;
		pthread_mutex_init(&philo->right_chopstick, NULL);
	}
	else if (l_philo && the_last)
	{
		philo->left_chopstick = l_philo->right_chopstick;
		philo->right_chopstick = l_philo->left_chopstick;
	}*/
	if (!l_philo && !the_last)
	{
		philo->right_chopstick = &philo->left_chopstick;
		pthread_mutex_init(&philo->right_chopstick, NULL);
	}

}

static void	ft_init_philos(t_college *college)
{
	int	i;

	i = 0;
	while (i < college->utils->n_philos)
	{
		college->philos[i] = malloc(sizeof(t_philo));
		if (!college->philos[i])
			ft_leave_table(college, 2, "Error: echec malloc college->philos[n]\n", 52);
		college->philos[i]->id = i + 1;
		college->philos[i]->thread = 0;
		college->philos[i]->last_meal = 0;
		college->philos[i]->count_meal = 0;
		college->philos[i]->state = 0;
		if (i == 0)
			ft_chopstick_init(college->philos[i], NULL , 0);
		else if (i == college->utils->n_philos - 1)
			ft_chopstick_init(college->philos[i], college->philos[0], 1);
		else
			ft_chopstick_init(college->philos[i], college->philos[i - 1], 0);
		i++;
	}
}

void	ft_init_college(t_utils utils, t_college *college)
{
	college->philos = malloc(utils.n_philos * sizeof(t_philo *) + 1);
	if (!college->philos)
		ft_exit(2, "Error: echec malloc college->philos\n", 52);
	college->philos[utils.n_philos] = NULL;
	college->utils = malloc(sizeof(t_utils));
	if (!college->utils)
		ft_leave_table(college, 2, "Error: echec malloc college->utils\n", 52);
	*college->utils = utils;
	ft_init_philos(college);
}
