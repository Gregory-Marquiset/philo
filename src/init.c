/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/26 13:51:28 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_init_thread(t_sympos *sympos, pthread_t *thread, void *fun,
	void *arg)
{
	if (pthread_create(&*(thread), NULL, fun, arg))
		ph_quit_philo(sympos, 2, LERR_PT_CREAT, CERR_PT_CREAT);
}

void	*ph_init_malloc(t_sympos *sympos, int nbr, int var_size)
{
	void	*ptr;

	ptr = malloc(nbr * var_size);
	if (!ptr)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	return (ptr);
}

void	ph_init_mtx(t_sympos *sympos, pthread_mutex_t mtx)
{
	if (pthread_mutex_init(&mtx, NULL))
		ph_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
}

void	ph_init_fork(t_sympos *sympos, t_philo *philo, t_philo *rg_philo,
	int pos)
{
	if (pos == 0)
		ph_init_mtx(sympos, philo->lf_fork);
	else if (pos == 1)
	{
		ph_init_mtx(sympos, philo->lf_fork);
		philo->rg_fork = &(rg_philo->lf_fork);
	}
	else if (pos == 2)
		philo->rg_fork = &(rg_philo->lf_fork);
}

t_sympos	*ph_init_sympos(t_e_agalma *tmp)
{
	t_sympos	*sympos;

	sympos = NULL;
	sympos = ph_init_malloc(sympos, 1, sizeof(t_sympos));
	ph_init_epis(sympos, tmp);
	ph_init_philos(sympos);
	return (sympos);
}
