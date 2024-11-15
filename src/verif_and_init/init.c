/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/25 09:34:21 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	*ph_init_malloc_mutex(t_sympos *sympos, pthread_mutex_t *mutex,
	int nbr, size_t var_size)
{
	void	*ptr;

	ptr = malloc(nbr * var_size);
	if (!ptr)
	{
		pthread_mutex_unlock(mutex);
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	}
	return (ptr);
}

void	*ph_init_malloc(t_sympos *sympos, int nbr, size_t var_size)
{
	void	*ptr;

	ptr = malloc(nbr * var_size);
	if (!ptr)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	return (ptr);
}

t_sympos	*ph_init_sympos(t_agalma *tmp)
{
	t_sympos	*sympos;

	sympos = NULL;
	sympos = ph_init_malloc(sympos, 1, sizeof(t_sympos));
	ph_init_epis(sympos);
	ph_init_philos(sympos, tmp);
	return (sympos);
}
