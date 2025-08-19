/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:36:21 by achoukri          #+#    #+#             */
/*   Updated: 2025/08/19 19:43:47 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static void	cleanup_simulation(t_data *rules, t_philo *philos,
				pthread_mutex_t *forks, pthread_t *threads);

static int	initialize_simulation(int ac, char **av, t_data *rules)
{
	int	validate_result;

	validate_result = input_parsing(ac, av);
	if (validate_result == BAD)
		return (ft_error_msg(USAGE_ERROR_MSG), 1);
	else if (validate_result == -1)
		return (0);
	if ((init(ac, av, rules) == BAD))
		return (1);
	pthread_mutex_init(&rules->print_lock, NULL);
	pthread_mutex_init(&rules->state_lock, NULL);
	rules->start_time = ft_now_ms();
	rules->stop = 0;
	return (-1);
}

static int	allocate_resources(t_data *rules, t_philo **philos,
		pthread_mutex_t **forks, pthread_t **threads)
{
	int	n;

	n = rules->number_of_philosophers;
	*philos = malloc(sizeof(t_philo) * n);
	*forks = malloc(sizeof(pthread_mutex_t) * n);
	*threads = malloc(sizeof(pthread_t) * (n + 1));
	if (!*philos || !*forks || !*threads)
	{
		free(*philos);
		free(*forks);
		free(*threads);
		*philos = NULL;
		*forks = NULL;
		*threads = NULL;
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data				rules;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	int					init_status;

	init_status = initialize_simulation(ac, av, &rules);
	if (init_status != -1)
		return (init_status);
	if (allocate_resources(&rules, &philos, &forks, &threads) != 0)
		return (1);
	init_philos_and_forks(&rules, philos, forks);
	if (pthread_create(&threads[0], NULL, monitor_routine, philos) != 0)
	{
		pthread_mutex_lock(&rules.state_lock);
		rules.stop = 1;
		pthread_mutex_unlock(&rules.state_lock);
		cleanup_simulation(&rules, philos, forks, threads);
		return (1);
	}
	spawn_philosophers(&rules, philos, threads + 1);
	pthread_join(threads[0], NULL);
	cleanup_simulation(&rules, philos, forks, threads);
	return (0);
}

static void	cleanup_simulation(t_data *rules, t_philo *philos,
		pthread_mutex_t *forks, pthread_t *threads)
{
	int	i;

	pthread_mutex_lock(&rules->state_lock);
	rules->stop = 1;
	pthread_mutex_unlock(&rules->state_lock);
	i = 1;
	while (i < rules->number_of_philosophers + 1)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->state_lock);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(threads);
	free(philos);
	free(forks);
	return ;
}
