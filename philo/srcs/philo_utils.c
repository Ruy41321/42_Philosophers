/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:54:42 by lpennisi          #+#    #+#             */
/*   Updated: 2024/09/29 12:45:49 by lpennisi         ###   ########.fr       */
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0 && philo->table->num_of_philo % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->sem);
		pthread_mutex_unlock(&philo->table->sem);
	}
	if (philo->id % 2 == 0 && philo->table->num_of_philo % 2 != 0)
	{
		pthread_mutex_lock(&philo->table->sem);
		pthread_mutex_unlock(&philo->table->sem);
	}
	while (1)
	{
		stamp("is thinking\n", philo);
		if (is_everyone_full(philo->table) || is_over(philo->table))
			break ;
		eat(philo);
		if (is_over(philo->table))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}

void	start_pari(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->sem);
	while (++i < table->num_of_philo)
	{
		if (i % 2 == 0)
			pthread_create(&(table->philos[i].tid), NULL, \
					&philo_routine, (void *)&table->philos[i]);
	}
	i = -1;
	usleep(1000);
	table->creation_time = get_time();
	pthread_mutex_unlock(&table->sem);
	usleep(10000);
	while (++i < table->num_of_philo)
		if (i % 2 != 0)
			pthread_create(&(table->philos[i].tid), NULL, \
					&philo_routine, (void *)&table->philos[i]);
}

void	start_philos(t_table *table)
{
	int	i;

	if (table->num_of_philo % 2 == 0)
		start_pari(table);
	else
	{
		i = -1;
		pthread_mutex_lock(&table->sem);
		while (++i < table->num_of_philo)
		{
			if (i % 2 != 0)
				pthread_create(&(table->philos[i].tid), NULL, \
						&philo_routine, (void *)&table->philos[i]);
		}
		i = -1;
		usleep(1000);
		table->creation_time = get_time();
		pthread_mutex_unlock(&table->sem);
		usleep(10000);
		while (++i < table->num_of_philo)
			if (i % 2 == 0)
				pthread_create(&(table->philos[i].tid), NULL, \
						&philo_routine, (void *)&table->philos[i]);
	}
}
