/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:54:11 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/29 22:20:29 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_muprintf(pthread_mutex_t *mutex, int id, char *message)
{
	pthread_mutex_lock(mutex);
	printf("%d %d %s", (int)ft_actualtime(), id, message);
	pthread_mutex_unlock(mutex);
}
