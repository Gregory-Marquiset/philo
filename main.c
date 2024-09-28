/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:36:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/28 17:00:20 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/proto.h"

int	main(int argc, char **argv)
{
	t_sympos	*sympos;

	sympos = ph_args_verif_and_make_sympos(argc, argv);
	ts_print_sympos(sympos);
	ph_threading(sympos);
	ph_quit_philo(sympos, 1, LTEST_SUCC_OUT, 0);
}
