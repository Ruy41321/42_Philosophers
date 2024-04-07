/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:08:27 by lpennisi          #+#    #+#             */
/*   Updated: 2024/03/09 18:20:01 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	if (!is_over(philo->table))
	{
		if (!(philo->id % 2))
			pthread_mutex_lock(&philo->fork);
		else if (philo->next_p)
			pthread_mutex_lock(&philo->next_p->fork);
		else
			pthread_mutex_lock(&philo->fork);
	}
	stamp("has taken a fork\n", philo);
	if (!is_over(philo->table))
	{
		if ((philo->id % 2))
			pthread_mutex_lock(&philo->fork);
		else if (philo->next_p)
			pthread_mutex_lock(&philo->next_p->fork);
		else
			pthread_mutex_lock(&philo->fork);
		stamp("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next_p->fork);
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->sem);
	philo->time_to_die = get_program_time(philo->table) \
						+ philo->table->time_to_die;
	pthread_mutex_unlock(&philo->table->sem);
	stamp("is eating\n", philo);
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
	stamp("is thinking\n", philo);
}
