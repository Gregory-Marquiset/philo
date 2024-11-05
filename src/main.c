/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:36:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/05 18:56:43 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	main(int argc, char **argv)
{
	t_sympos	*sympos;

	sympos = ph_args_verif_and_make_sympos(argc, argv);
	//ts_print_sympos(sympos);
	ph_threading(sympos);
	ph_quit_philo(sympos, 1, NULL, 0);
}
