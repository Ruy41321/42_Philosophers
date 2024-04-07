/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:39:11 by lpennisi          #+#    #+#             */
/*   Updated: 2024/03/09 18:19:40 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exit_handling(t_table *table, char *msg)
{
	printf("%s\n", msg);
	free(table->philos);
	exit (0);
}

int	ft_isdigit(int arg)
{
	if (arg > 47 && arg < 58)
		return (arg);
	return (0);
}

int	is_digitstring(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

int	check_argument(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	while (*(++argv))
		if (!is_digitstring(*argv))
			return (1);
	return (0);
}

void	stamp(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->sem);
	if (!(philo->table->is_over))
		printf("%d %d %s\n", get_program_time(philo->table), philo->id, str);
	pthread_mutex_unlock(&philo->table->sem);
}
