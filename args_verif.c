/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:00:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/27 02:27:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}

static int	ft_atoi_safe(char *str)
{
	long (result) = 0;
	int (i) = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ft_exit(2, "Error: arguments must be only positif int\n", 3);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			ft_exit(2, "Error: arguments must be only digit\n", 4);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX)
		ft_exit(2, "Error: arguments must be lower than int max + 1\n", 5);
	else if (result < 1)
		ft_exit(2, "Error: arguments must be higher than 0\n", 6);
	return ((int)result);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	ft_program_runhelper(int flag)
{
	if(flag == 1)
	{
		ft_exit(2, "./program_name number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"(optional)number_of_times_each_philosopher_must_eat\n"
			"For more details run: ./philo --help++\n", 1);
	}
	else if(flag == 2)
	{
		ft_exit(2, "Here a details about the arguments needed by philo:\n"
			"For run project philo you need 5 or 6 arguments\n\n"
			"1: program_name -> The program name\n"
			"2: number_of_philosophers -> The number of philosopher you want\n"
			"3: time_to_die -> Time max between each philosopher meal\n"
			"4: time_to_eat -> Time needed by a philosopher for eating a meal\n"
			"5: time_to_sleep -> Time spent sleeping\n"
			"6: (optional)number_of_times_each_philosopher_must_eat -> Number of meal for each philo, "
			"when reached program stop, ifndef run until 1 philo die\n\n"
			"All time values are in milliseconds\n"
			"All value most be an int between 1 and int max\n", 1);
	}
}

void	ft_argsverif_and_makecollege(int argc, char ** argv, t_college *college)
{
	t_utils	utils;

	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "--help", 7))
			ft_program_runhelper(1);
		else if (!ft_strncmp(argv[1], "--help++", 9))
			ft_program_runhelper(2);
	}
	if (argc < 5 || argc > 6)
		ft_exit(2, "Error: Bad argument format, for help run: ./philo --help\n", 2);
	utils.n_philos = ft_atoi_safe(argv[1]);
	utils.time_to_die = (size_t)ft_atoi_safe(argv[2]);
	utils.time_to_eat = (size_t)ft_atoi_safe(argv[3]);
	utils.time_to_sleep = (size_t)ft_atoi_safe(argv[4]);
	if (argv[5])
		utils.n_meal = ft_atoi_safe(argv[5]);
	else
		utils.n_meal = 0;
	ft_init_college(utils, college);
}
