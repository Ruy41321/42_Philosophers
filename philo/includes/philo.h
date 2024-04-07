/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:58:37 by lpennisi          #+#    #+#             */
/*   Updated: 2024/03/09 16:11:21 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	struct s_table	*table;
	pthread_t		tid;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_num;
	pthread_mutex_t	fork;
	struct s_philo	*next_p;
}	t_philo;

typedef struct s_table
{
	int				num_of_philo;
	t_philo			*philos;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				meals_num;
	int				is_over;
	pthread_mutex_t	sem;
	int				creation_time;
}	t_table;

void	exit_handling(t_table *table, char *msg);
int		parse_arguments(t_table *table, char **argv);
int		check_argument(int argc, char **argv);
void	think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	eat(t_philo *philo);
void	ft_sleep(int time, t_table *table);
int		philo_is_full(t_philo *philo);
int		is_everyone_full(t_table *table);
int		get_time(void);
int		get_program_time(t_table *table);
int		check_deads(t_table *table);
int		is_over(t_table *table);
void	start_philos(t_table *table);
void	stamp(char *str, t_philo *philo);

#endif
