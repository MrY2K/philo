/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:41:06 by achoukri          #+#    #+#             */
/*   Updated: 2025/09/14 17:29:19 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/structs.h"
#include "include/prototypes.h"

void	drop_forks(t_philo *p)
{
	unlock(p->first_fork);
	unlock(p->second_fork);
}

void	philo_eat(t_philo *p)
{
	if (should_stop(p))
		return ;
	lock(&p->rules->state_lock);
	p->last_meal = ft_now_ms();
	p->eat_count++;
	unlock(&p->rules->state_lock);
	philo_log(p, "is eating");
	precise_sleep(p, p->rules->time_to_eat);
}

void	philo_sleep(t_philo *p)
{
	if (should_stop(p))
		return ;
	philo_log(p, "is sleeping");
	precise_sleep(p, p->rules->time_to_sleep);
}

void	philo_think(t_philo *p)
{
	if (should_stop(p))
		return ;
	philo_log(p, "is thinking");
}

void	philo_log(t_philo *p, const char *msg)
{
	long	timestamp;

	lock(&p->rules->state_lock);
	if (!p->rules->stop)
	{
		timestamp = ft_now_ms() - p->rules->start_time;
		lock(&p->rules->print_lock);
		printf("%ld %d %s\n", timestamp, p->id, msg);
		unlock(&p->rules->print_lock);
	}
	unlock(&p->rules->state_lock);
}
