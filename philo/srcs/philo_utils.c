/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:54:42 by lpennisi          #+#    #+#             */
/*   Updated: 2024/04/10 14:08:09 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(int time, t_table *table)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time && !table->is_over)
		usleep(50);
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_over(philo->table))
			break ;
		eat(philo);
		if (philo_is_full(philo) || is_over(philo->table))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}

void	start_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
	{
		pthread_create(&(table->philos[i].tid), NULL, \
					&philo_routine, (void *)&table->philos[i]);
	}
}
