/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:51:26 by lpennisi          #+#    #+#             */
/*   Updated: 2024/04/10 14:37:28 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_over(t_table *table)
{
	pthread_mutex_lock(&table->sem);
	if (table->is_over)
	{
		pthread_mutex_unlock(&table->sem);
		return (1);
	}
	pthread_mutex_unlock(&table->sem);
	return (0);
}

int	philo_is_dead(t_philo *philo)
{
	int	time;

	if (philo_is_full(philo))
		return (0);
	time = get_time() - philo->table->creation_time;
	pthread_mutex_lock(&philo->table->sem);
	if (time > philo->time_to_die)
	{
		printf("%d %d died\n", time, philo->id);
		philo->table->is_over = 1;
		pthread_mutex_unlock(&philo->table->sem);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->sem);
	return (0);
}

int	check_deads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		if (philo_is_dead(&table->philos[i++]))
			return (1);
	}
	return (0);
}

int	philo_is_full(t_philo *philo)
{
	if (philo->table->meals_num != -1)
	{
		pthread_mutex_lock(&philo->table->sem);
		if (philo->meals_num == 0)
		{
			pthread_mutex_unlock(&philo->table->sem);
			return (1);
		}
		pthread_mutex_unlock(&philo->table->sem);
	}
	return (0);
}

int	is_everyone_full(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
	{
		if (!philo_is_full(&table->philos[i]))
			return (0);
	}
	return (1);
}
