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
void phb_forking(t_sympos *sympos)
{
    int i;
    int status;
    int finished;
    i = 0;

    while (i < sympos->n_philos)
    {
        pid_t pid = fork();
        if (pid < 0)
            phb_quit_philo(sympos, 2, "fork failed\n", CERR_PT_CREAT);
        else if (pid == 0)
        {
            phb_philo_routine(sympos, &sympos->philos[i]);
            exit(0);
        }
        else
            sympos->philos[i].pid_philos = pid;
        i++;
    }

    finished = 0;
    while (finished < sympos->n_philos)
    {
        pid_t ended = waitpid(-1, &status, 0);
        if (ended <= 0)
            break;
        if (WIFEXITED(status))
        {
            int code = WEXITSTATUS(status);
            if (code > 0)
            {
                phb_kill_all(sympos);
                break ;
            }
            else
                finished++;
        }
    }
    phb_kill_all(sympos);
}