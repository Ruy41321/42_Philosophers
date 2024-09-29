/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:02:26 by lpennisi          #+#    #+#             */
/*   Updated: 2024/09/27 17:34:55 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	wait_philos(t_table *table);

long	ft_atol(const char *str)
{
	long	sign;
	long	result;

	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

int	are_int(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_atol(argv[i]) >= INT_MAX)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	table.philos = NULL;
	if (check_argument(argc, argv))
		exit_handling(&table, "Error: Invalid arguments");
	if (!are_int(argc, argv))
		exit_handling(&table, "Error: not Int arguments");
	if (parse_arguments(&table, argv))
		exit_handling(&table, "Error while initialising");
	start_philos(&table);
	while (!is_everyone_full(&table))
	{
		if (check_deads(&table))
			break ;
		usleep(200);
	}
	wait_philos(&table);
	free(table.philos);
	return (0);
}

void	wait_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
		pthread_join(table->philos[i++].tid, NULL);
	i = 0;
	while (i < table->num_of_philo)
		pthread_mutex_destroy(&table->philos[i++].fork);
}
