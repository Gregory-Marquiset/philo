/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/29 23:36:26 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

void	ft_print_sympos(t_sympos *sympos)
{
	t_sympos	*tmp = sympos;

	//int	(i) = 0;
	printf(LU_BLU "n_philos: %d\ntt_die: %ld\ntt_eat: %ld\ntt_sleep: %ld\nn_meal: %d\n" LU_END,
		tmp->epís->n_philos, tmp->epís->time_to_die,
		tmp->epís->time_to_eat, tmp->epís->time_to_sleep,
		tmp->epís->n_meal);
	/*while (i < tmp->epís->n_philos)
	{
		printf("philos[%2d] present at the table\n", tmp->philos[i]->id);
		printf("lc_stick = %p | rc_stick = %p\n", (void *)&*tmp->philos[i]->aristerós_obeliskos, (void *)&tmp->philos[i]->dexiós_obeliskos);
		i++;
	}*/
}
