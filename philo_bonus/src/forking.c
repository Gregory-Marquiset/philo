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

/*
   Fonction pour tuer tous les process encore en vie.
   On parcourt la liste de pids et on envoie un kill.
*/
void    phb_kill_all(t_sympos *sympos)
{
    int i = 0;
    while (i < sympos->n_philos)
    {
        if (sympos->philos[i].pid_philos > 0)
            kill(sympos->philos[i].pid_philos, SIGKILL);
        i++;
    }
}

/*
   La fonction principale dans le parent qui fork() pour chaque philosophe,
   puis attend la fin de l’un d’eux. 
   => Si un process se termine avec un code > 0 => “mort” potentielle
      ou "id du philosophe" => on kill les autres.
   => Si un process se termine avec code 0 => ce philosophe a fini
      (possiblement n_meal atteint).
*/
void    phb_forking(t_sympos *sympos)
{
    int i;
    pid_t pid;
    int status;

    i = 0;
    while (i < sympos->n_philos)
    {
        pid = fork();
        if (pid < 0)
        {
            // Erreur de fork
            phb_quit_philo(sympos, 2, LU_RED1"Error: fork failed\n"LU_END, CERR_PT_CREAT);
        }
        else if (pid == 0)
        {
            // Process fils : lancer la routine
            phb_philo_routine(sympos, &sympos->philos[i]);
            // Normalement, la routine ne retourne jamais => exit(...) inside
            exit(0);
        }
        else
        {
            // Parent : stocker pid si besoin
            sympos->philos[i].pid_philos = pid;
        }
        i++;
    }

    // Parent : attend la fin d’un fils
    i = 0;
    while (i < sympos->n_philos)
    {
        pid_t ended = waitpid(-1, &status, 0);
        if (ended > 0)
        {
            // Récupération du code de sortie
            int exit_code = WEXITSTATUS(status);
            if (exit_code > 0)
            {
                // => un philosophe est mort, exit_code = philo_id
                // On tue tous les autres
                phb_kill_all(sympos);
                break ;
            }
            else
            {
                // => un philosophe a fini ses repas
                // On continue d’attendre les autres
            }
        }
        i++;
    }
    // Pour être propre, on tue tout le monde restant + libération
    phb_kill_all(sympos);
}

/*void	phb_forking(t_sympos *sympos)
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
}*/

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
