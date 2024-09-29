/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:08:27 by lpennisi          #+#    #+#             */
/*   Updated: 2024/09/29 10:00:17 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_death(t_philo *philo)
{
	while (1)
	{
		if (is_over(philo->table))
		{
			pthread_mutex_unlock(&philo->fork);
			return ;
		}
		usleep(500);
	}
}

int	take_second_fork(t_philo *philo)
{
	if (!is_over(philo->table))
	{
		if (philo->table->num_of_philo % 2 != 0)
		{
			if (philo->next_p)
				pthread_mutex_lock(&philo->next_p->fork);
			else
				return (wait_death(philo), 1);
		}
		else if (!(philo->id % 2))
			pthread_mutex_lock(&philo->fork);
		else if (philo->next_p)
			pthread_mutex_lock(&philo->next_p->fork);
		else
			return (wait_death(philo), 1);
		stamp("has taken a fork\n", philo);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (!is_over(philo->table))
	{
		if (philo->table->num_of_philo % 2 != 0)
			pthread_mutex_lock(&philo->fork);
		else if ((philo->id % 2))
			pthread_mutex_lock(&philo->fork);
		else if (philo->next_p)
			pthread_mutex_lock(&philo->next_p->fork);
	}
	stamp("has taken a fork\n", philo);
	if (take_second_fork(philo))
		return (1);
	if (is_over(philo->table))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next_p->fork);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	int	time;

	if (take_forks(philo))
		return ;
	time = get_time() - philo->table->creation_time;
	pthread_mutex_lock(&philo->table->sem);
	if (time > philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->sem);
		return ;
	}
	pthread_mutex_unlock(&philo->table->sem);
	stamp("is eating\n", philo);
	pthread_mutex_lock(&philo->table->sem);
	philo->time_to_die = get_program_time(philo->table) \
						+ philo->table->time_to_die;
	pthread_mutex_unlock(&philo->table->sem);
	ft_sleep(philo->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->sem);
	philo->meals_num--;
	pthread_mutex_unlock(&philo->table->sem);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next_p->fork);
}

void	philo_sleep(t_philo *philo)
{
	stamp("is sleeping\n", philo);
	ft_sleep(philo->time_to_sleep, philo->table);
}
