/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:27:42 by achoukri          #+#    #+#             */
/*   Updated: 2025/08/19 18:46:29 by achoukri         ###   ########.fr       */
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

void	philo_pick_forks(pthread_mutex_t *first,
			pthread_mutex_t *second, t_philo *p);
int		check_meal_limit_reached(t_philo *p);
int		check_should_stop(t_philo *p);
void	setup_fork_order(t_philo *p, pthread_mutex_t **first,
			pthread_mutex_t **second);
void	cleanup_resources(t_data *rules, pthread_mutex_t *forks);
void	wait_for_completion(t_data *rules, pthread_t *threads,
			pthread_t *monitor);
void	start_simulation(t_data *rules, t_philo *philos, pthread_t *threads);
// int		validate_input(int ac, char **av);
// int		initialize_rules(int ac, char **av, t_data *rules);

#endif