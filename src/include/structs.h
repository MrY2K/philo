/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:27:44 by achoukri          #+#    #+#             */
/*   Updated: 2025/08/19 18:46:17 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "includes.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define GOOD 0
# define BAD 1

# define USAGE_ERROR_MSG "Error: Usage: <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]"

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_p_must_eat;

	pthread_mutex_t	print_lock;   // serialize prints
	pthread_mutex_t	state_lock;   // protect last_meal, eat_count, stop
	long			start_time;   // ms epoch at sim start
	int				stop;         // 0 = running, 1 = stop

}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;    // ms absolute timestamp
	int				eat_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*rules;
}	t_philo;

/* Provided by your parsing code (keep yours) */
int input_parsing(int ac, char **av);
int init(int ac, char **av, t_data *rules);

/* helpers in these files */
long	ft_now_ms(void);

void	init_philos_and_forks(t_data *rules, t_philo *philos, pthread_mutex_t *forks);
void	spawn_philosophers(t_data *rules, t_philo *philos, pthread_t *threads);

void	*philo_life(void *arg);
void	*monitor_routine(void *arg);
void	philo_log(t_philo *p, const char *msg);


void	lock(pthread_mutex_t *mutex);
void	unlock(pthread_mutex_t *mutex);

void	philo_think(t_philo *p);
void	philo_sleep(t_philo *p);
void	philo_eat(t_philo *p);
void	take_forks(t_philo *p);
void	drop_forks(t_philo *p);

int	should_stop(t_philo *p);
void    precise_sleep(t_philo *p, long duration);
void    handle_one_philo(t_philo *p);
#endif
