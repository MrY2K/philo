/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/07/09 23:16:08 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	validate_input(int ac, char **av)
{
	if (input_parsing(ac, av) == BAD)
		return (ft_error_msg(USAGE_ERROR_MSG), 1);
	else if (input_parsing(ac, av) == -1)
		return (0);
	return (-1);
}

int	initialize_rules(int ac, char **av, t_data *rules)
{
	if ((init(ac, av, rules) == BAD))
		return (1);
	pthread_mutex_init(&rules->print_lock, NULL);
	pthread_mutex_init(&rules->state_lock, NULL);
	rules->start_time = ft_now_ms();
	rules->stop = 0;
	return (0);
}

void	start_simulation(t_data *rules, t_philo *philos)
{
	pthread_t	threads[200];
	pthread_t	monitor;
	int			i;

	spawn_philosophers(rules, philos, threads);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_detach(monitor);
	i = -1;
	while (++i < rules->number_of_philosophers)
		pthread_join(threads[i], NULL);
}

void	wait_for_completion(t_data *rules, pthread_t *threads,
				pthread_t *monitor)
{
	int	i;

	pthread_join(*monitor, NULL);
	i = -1;
	while (++i < rules->number_of_philosophers)
		pthread_join(threads[i], NULL);
}

int	main(int ac, char **av)
{
	t_data				rules;
	t_philo				philos[200];
	pthread_mutex_t		forks[200];
	int					validation_result;

	validation_result = validate_input(ac, av);
	if (validation_result != -1)
		return (validation_result);
	if (initialize_rules(ac, av, &rules) != 0)
		return (1);
	init_philos_and_forks(&rules, philos, forks);
	start_simulation(&rules, philos);
	cleanup_resources(&rules, forks);
	return (0);
}
