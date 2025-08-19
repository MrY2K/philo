/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:27:42 by achoukri          #+#    #+#             */
/*   Updated: 2025/08/19 19:47:16 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "includes.h"
# include "structs.h"

// parsing:
int		input_parsing(int ac, char **av);
int		validate_args(int ac, char **av);
int		validate_last_arg(int ac, char **av);

// error handling:
void	ft_error_msg(const char *msg);

// utils:
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi_improved(const char *str, int *flag);
int		num_len(char *num, int *sign);
long	ft_now_ms(void);

// init
int		init(int ac, char **av, t_data *rules);
void	init_philos_and_forks(t_data *rules, t_philo *philos,
			pthread_mutex_t *forks);
void	spawn_philosophers(t_data *rules, t_philo *philos, pthread_t *threads);

// routines:
void	*philo_life(void *arg);
void	*monitor_routine(void *arg);
void	philo_log(t_philo *p, const char *msg);

/* Provided by your parsing code (keep yours) */
int		input_parsing(int ac, char **av);
int		init(int ac, char **av, t_data *rules);

/* helpers in these files */
long	ft_now_ms(void);

void	init_philos_and_forks(t_data *rules, t_philo *philos,
			pthread_mutex_t *forks);
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

int		should_stop(t_philo *p);
void	precise_sleep(t_philo *p, long duration);
void	handle_one_philo(t_philo *p);

#endif