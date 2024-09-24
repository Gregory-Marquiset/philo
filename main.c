/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:36:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/24 17:58:44 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/proto.h"

/*	> External fonction:
	memset, printf, malloc, free, write,

	TIME:
	usleep, gettimeofday,

	THREAD:
	pthread_create, pthread_detach, pthread_join,

	MUTEX:
	pthread_mutex_init,	pthread_mutex_destroy,
	pthread_mutex_lock, pthread_mutex_unlock
*/

/*	> Special case

	1 PHILO:
	If there is only one philosopher,
	there should be only one fork on the table.
*/

int	main(int argc, char **argv)
{
	t_sympos	*sympos;

	sympos = ph_args_verif_and_make_sympos(argc, argv);
	printf(LTEST_SUCC_IN);
	ph_print_sympos(sympos);
	ph_threading(sympos);
	ph_quit_philo(sympos, 1, LTEST_SUCC_OUT, 0);
}

/*	simple thread + mutex
void	*ft_thlock_right(void *right_chopstick)
{
	pthread_mutex_t *chopstick = (pthread_mutex_t *)right_chopstick;

	if(pthread_mutex_lock(chopstick))
	{
		printf("Error: mutex lock echec\n");
		exit (1);
	}
	else
	{
		printf("meal eaten\n");
		pthread_mutex_unlock(chopstick);
		return (NULL);
	}
}

void	ft_philo_init(t_philosophe *philo)
{
	philo->count_meal = 0;
	philo->max_life_time = 0;
	philo->id = 0;
	philo->last_meal = 0;
	philo->state = 0;
}

int	main(int argc, char **argv)
{
	if (argc > 1 && argv)
	{
		printf("Error: too many argument\n");
		return (1);
	}
	t_philosophe	philo;
	ft_philo_init(&philo);

	pthread_mutex_init(&philo.right_chopstick, NULL);
	pthread_create(&philo.thread_r, NULL, &ft_thlock_right, &philo.right_chopstick);

	printf("thread created\n");

	pthread_join(philo.thread_r, NULL);
	pthread_mutex_destroy(&philo.right_chopstick);

	printf("thread destroy\n");
	return (0);
}*/

/*	multi thread loop + mutex
int	meal_l = 0;
int	meal_r = 0;

void	*ft_thlock_left(void *left_chopstick)
{
	pthread_mutex_t *chopstick = (pthread_mutex_t *)left_chopstick;

	if(pthread_mutex_lock(chopstick))
	{
		printf("Error: mutex lock echec\n");
		exit (1);
	}
	else
	{
		printf("left meal eaten\n");
		meal_l++;
		pthread_mutex_unlock(chopstick);
		return (NULL);
	}
}

void	*ft_thlock_right(void *right_chopstick)
{
	pthread_mutex_t *chopstick = (pthread_mutex_t *)right_chopstick;

	if(pthread_mutex_lock(chopstick))
	{
		printf("Error: mutex lock echec\n");
		exit (1);
	}
	else
	{
		printf("right meal eaten\n");
		meal_r++;
		pthread_mutex_unlock(chopstick);
		return (NULL);
	}
}

void	ft_philo_init(t_philosophe *philo)
{
	philo->count_meal = 0;
	philo->max_life_time = 0;
	philo->id = 0;
	philo->last_meal = 0;
	philo->state = 0;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: 2 argument needed\n");
		return(10);
	}
	int	i = 0;
	int	n = ft_atoi(argv[1]);
	t_philosophe college[n];
	if (argc)
	{
		while (i < n)
		{
			ft_philo_init(&college[i]);
			pthread_mutex_init(&college[i].left_chopstick, NULL);
			pthread_mutex_init(&college[i].right_chopstick, NULL);
			printf("philo[%d] created\n", i);
			if (pthread_create(&college[i].thread_l, NULL, &ft_thlock_left, &college[i].left_chopstick))
				return (1);
			if (pthread_create(&college[i].thread_r, NULL, &ft_thlock_right, &college[i].right_chopstick))
				return (2);
			i++;
		}
		i = 0;
		printf("meal_l = %d | meal_r = %d\n", meal_l, meal_r);
		while (i < n)
		{
			if (pthread_join(college[i].thread_l, NULL))
				return (3);
			if (pthread_join(college[i].thread_r, NULL))
				return (4);
			printf("philo[%d] finish eating\n", i);
			i++;
		}
		i = 0;
		while (i < n)
		{
			pthread_mutex_destroy(&college[i].left_chopstick);
			pthread_mutex_destroy(&college[i].right_chopstick);
			i++;
		}
	}
	printf("meal_l = %d | meal_r = %d\n", meal_l, meal_r);
	return (0);
}*/
