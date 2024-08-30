/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/30 17:59:31 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

void	ft_print_sympos(t_sympos *sympos)
{
	t_sympos	*tmp = sympos;

	int	(i) = 0;
	printf(LU_BLU "\nn_philos: %d\ntt_die: %ld\ntt_eat: %ld\ntt_sleep: %ld\nn_meal: %d\n\n" LU_END,
		tmp->epís->n_philos, tmp->epís->time_to_die,
		tmp->epís->time_to_eat, tmp->epís->time_to_sleep,
		tmp->epís->n_meal);
	while (i < tmp->epís->n_philos)
	{
		printf(LU_YEL "philos[%2d] present at the table\n" LU_END, tmp->philos[i].id);
		printf(LU_YEL "dexi = %p | aris = %p\n" LU_END, (void *)&*tmp->philos[i].dexi_obeli, (void *)&tmp->philos[i].aris_obeli);
		i++;
	}
}
