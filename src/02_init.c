/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:30:05 by achoukri          #+#    #+#             */
/*   Updated: 2025/09/14 17:54:41 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
#include "include/prototypes.h"

int	init(int ac, char **av, t_data *rules)
{
	rules->number_of_philosophers = ft_atoi_improved(av[1], NULL);
	if (rules->number_of_philosophers > 200)
		return (BAD);
	rules->time_to_die = ft_atoi_improved(av[2], NULL);
	rules->time_to_eat = ft_atoi_improved(av[3], NULL);
	rules->time_to_sleep = ft_atoi_improved(av[4], NULL);
	if (ac == 6)
		rules->number_of_times_each_p_must_eat = ft_atoi_improved(av[5], NULL);
	else
		rules->number_of_times_each_p_must_eat = -1;
	return (GOOD);
}

void	init_philos_and_forks(t_data *rules, t_philo *philos,
			pthread_mutex_t *forks)
{
	int	i;

	rules->start_time = ft_now_ms();
	i = -1;
	while (++i < rules->number_of_philosophers)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < rules->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = ft_now_ms();
		philos[i].eat_count = 0;
		philos[i].rules = rules;
		philos[i].first_fork = &forks[i];
		if (i == rules->number_of_philosophers - 1)
			philos[i].second_fork = &forks[0];
		else
			philos[i].second_fork = &forks[i + 1];
	}
}

void	spawn_philosophers(t_data *rules,
						t_philo *philos,
						pthread_t *threads)
{
	int	i;

	if (rules->number_of_philosophers == 1)
		return ;
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_create(&threads[i], NULL, philo_life, &philos[i]) != 0)
		{
			pthread_mutex_lock(&rules->state_lock);
			rules->stop = 1;
			pthread_mutex_unlock(&rules->state_lock);
			return ;
		}
		i++;
	}
}
