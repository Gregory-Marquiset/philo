/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/30 17:57:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_routine(void *philo)
{
	t_philo *tmp = (t_philo *)philo;
	//printf(LU_YEL "%d\n" LU_END, tmp->epís->n_philos);
	pthread_mutex_lock(&tmp->epís->mprintf);
	printf("philos[%d] join the table and take\ndexi = %14p and aris = %14p\n", tmp->id, (void *)&*tmp->dexi_obeli, (void *)&tmp->aris_obeli);
	pthread_mutex_unlock(&tmp->epís->mprintf);
	return (NULL);
}
