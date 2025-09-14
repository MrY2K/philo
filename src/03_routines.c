/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:29:59 by achoukri          #+#    #+#             */
/*   Updated: 2025/09/14 17:50:31 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	handle_one_philo(t_philo *p)
{
	if (p->rules->number_of_philosophers == 1)
	{
		philo_log(p, "is thinking");
		philo_log(p, "has taken a fork");
		precise_sleep(p, p->rules->time_to_die);
		philo_log(p, "died");
		return ;
	}
}

int	check_death(t_philo *philos, t_data *rules, int i)
{
	long	last;
	long	now;
	int		is_dead;

	lock(&rules->state_lock);
	if (rules->stop)
	{
		unlock(&rules->state_lock);
		return (0);
	}
	last = philos[i].last_meal;
	now = ft_now_ms();
	is_dead = (now - last > rules->time_to_die);
	if (is_dead)
	{
		rules->stop = 1;
		unlock(&rules->state_lock);
		lock(&rules->print_lock);
		printf("%ld %d died\n", now - rules->start_time, philos[i].id);
		unlock(&rules->print_lock);
		return (1);
	}
	unlock(&rules->state_lock);
	return (0);
}

int	check_all_ate(t_philo *philos, t_data *rules)
{
	int	full_count;
	int	i;

	if (rules->number_of_times_each_p_must_eat <= 0)
		return (0);
	lock(&rules->state_lock);
	if (rules->stop)
	{
		unlock(&rules->state_lock);
		return (0);
	}
	full_count = 0;
	i = -1;
	while (++i < rules->number_of_philosophers)
	{
		if (philos[i].eat_count >= rules->number_of_times_each_p_must_eat)
			full_count++;
	}
	if (full_count == rules->number_of_philosophers)
	{
		rules->stop = 1;
		unlock(&rules->state_lock);
		return (1);
	}
	return (unlock(&rules->state_lock), 0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*rules;
	int		i;
	int		should_continue;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		pthread_mutex_lock(&rules->state_lock);
		should_continue = !rules->stop;
		pthread_mutex_unlock(&rules->state_lock);
		if (!should_continue)
			break ;
		i = -1;
		while (++i < rules->number_of_philosophers)
		{
			if (check_death(philos, rules, i))
				return (NULL);
		}
		if (check_all_ate(philos, rules))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

void	*philo_life(void *param)
{
	t_philo	*p;

	p = (t_philo *)param;
	lock(&p->rules->state_lock);
	p->last_meal = ft_now_ms();
	unlock(&p->rules->state_lock);
	if (p->rules->number_of_philosophers == 1)
		return (handle_one_philo(p), NULL);
	if (p->id % 2 == 0)
		philo_sleep(p);
	while (!should_stop(p))
	{
		philo_think(p);
		take_forks(p);
		if (should_stop(p))
		{
			drop_forks(p);
			break ;
		}
		philo_eat(p);
		drop_forks(p);
		philo_sleep(p);
	}
	return (NULL);
}
