/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:36:59 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"
#include <sys/wait.h>


void	st_test(t_philo *philo)
{
	printf("philo %d ready\n", philo->id);
	if (philo->id == 60)
		exit (philo->id);
	exit (0);
}

void	phb_forking(t_sympos *sympos)
{
	int i = 0;
	pid_t pid;
	int status = 0;
	while (i < sympos->n_philos)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("safe quit\n");
			return ;
		}
		else if (pid == 0)
		{
			st_test(&sympos->philos[i]);
		}
		i++;
	}
	i = 0;
	while (i < sympos->n_philos)
	{
		waitpid(-1, &status, 2);
		status = WEXITSTATUS(status);
		if (status > 0)
			printf("%d die\n", status);
		i++;
	}
}

/*void	ph_threading(t_sympos *sympos)
{
	int	i;
	int	n_philos;

	n_philos = sympos->epis->n_philos;
	ph_init_thread(sympos, &sympos->epis->thread_ep, &ph_routine_epis,
		sympos->epis);
	usleep(2);
	i = 0;
	while (i < n_philos)
	{
		ph_init_thread(sympos, &sympos->philos[i].thread_ph, &ph_routine_philos,
			&sympos->philos[i]);
		i++;
	}
	i = 0;
	while (i < n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		usleep(2);
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
	usleep(2);
}*/
