/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/27 04:05:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	ft_print_college(t_college *college)
{
	t_philo	**tmp = college->philos;
	int	(i) = 0;
	printf("n_philos: %d\ntt_die: %ld\ntt_eat: %ld\ntt_sleep: %ld\nn_meal: %d\n",
		college->utils->n_philos, college->utils->time_to_die,
		college->utils->time_to_eat, college->utils->time_to_sleep,
		college->utils->n_meal);
	while (tmp[i])
	{
		printf("philos[%2d] present at the table\n", college->philos[i]->id);
		printf("lc_stick = %p | rc_stick = %p\n", (void *)&college->philos[i]->left_chopstick, (void *)&college->philos[i]->right_chopstick);
		i++;
	}
}
