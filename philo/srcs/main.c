/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:02:26 by lpennisi          #+#    #+#             */
/*   Updated: 2024/03/09 18:13:02 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	table.philos = NULL;
	if (check_argument(argc, argv))
		exit_handling(&table, "Error: Invalid arguments");
	if (parse_arguments(&table, argv))
		exit_handling(&table, "Error while initialising");
	start_philos(&table);
	while (!is_everyone_full(&table))
	{
		if (check_deads(&table))
			break ;
		usleep(200);
	}
	free(table.philos);
	return (0);
}
