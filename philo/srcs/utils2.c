/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:18:09 by lpennisi          #+#    #+#             */
/*   Updated: 2024/09/29 10:28:35 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

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

int	set_philos(t_table *table)
{
	int	i;

	i = -1;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->num_of_philo);
	if (!table->philos)
		return (1);
	while (++i < table->num_of_philo)
	{
		table->philos[i].table = table;
		table->philos[i].id = i + 1;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		pthread_mutex_init(&table->philos[i].fork, NULL);
		table->philos[i].meals_num = table->meals_num;
		if (i != 0)
		{
			if (i + 1 == table->num_of_philo)
				table->philos[i].next_p = &(table->philos[0]);
			table->philos[i - 1].next_p = &(table->philos[i]);
		}
		else
			table->philos[0].next_p = NULL;
	}
	return (0);
}

int	parse_arguments(t_table *table, char **argv)
{
	table->meals_num = -1;
	if (argv[5])
		table->meals_num = ft_atoi(argv[5]);
	table->num_of_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&table->sem, NULL);
	table->is_over = 0;
	return (set_philos(table));
}

int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	get_program_time(t_table *table)
{
	return (get_time() - table->creation_time);
}
