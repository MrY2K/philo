#include "include/philo.h"

static int validate_input(int ac, char **av)
{
	if (input_parsing(ac, av) == BAD)
		return (ft_error_msg(USAGE_ERROR_MSG), 1);
	else if (input_parsing(ac, av) == -1)
		return (0);
	return (-1);
}

/* initialize rules struct (calls your init) */
static int initialize_rules(int ac, char **av, t_data *rules)
{
	if ((init(ac, av, rules) == BAD))
		return (1);
	pthread_mutex_init(&rules->print_lock, NULL);
	pthread_mutex_init(&rules->state_lock, NULL);
	rules->start_time = ft_now_ms();
	rules->stop = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_data				rules;
	t_philo				*philos = NULL;
	pthread_mutex_t		*forks = NULL;
	pthread_t			*threads = NULL;
	pthread_t			monitor;
	int					n;
	int					vr;

	vr = validate_input(ac, av);
	if (vr != -1)
		return (vr);
	if (initialize_rules(ac, av, &rules) != 0)
		return (1);

	n = rules.number_of_philosophers;

	philos  = malloc(sizeof(t_philo) * n);
	forks   = malloc(sizeof(pthread_mutex_t) * n);
	threads = malloc(sizeof(pthread_t) * n);
	if (!philos || !forks || !threads)
	{
		free(philos);
		free(forks);
		free(threads);
		return (1);
	}

	/* set up philosopher structs and forks */
	init_philos_and_forks(&rules, philos, forks);

	/* spawn philosopher threads (joinable) */
	spawn_philosophers(&rules, philos, threads);

	/* start monitor (joinable) */
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
	{
		/* monitor creation failed: signal stop and join threads */
		pthread_mutex_lock(&rules.state_lock);
		rules.stop = 1;
		pthread_mutex_unlock(&rules.state_lock);
	}

	/* wait for monitor to finish (monitor sets rules.stop) */
	pthread_join(monitor, NULL);

	/* ensure stop is set (monitor usually sets it) */
	pthread_mutex_lock(&rules.state_lock);
	rules.stop = 1;
	pthread_mutex_unlock(&rules.state_lock);

	/* join all philosopher threads for a clean exit */
	for (int i = 0; i < n; ++i)
		pthread_join(threads[i], NULL);

	/* cleanup: destroy mutexes then free */
	pthread_mutex_destroy(&rules.print_lock);
	pthread_mutex_destroy(&rules.state_lock);
	for (int i = 0; i < n; ++i)
		pthread_mutex_destroy(&forks[i]);

	free(threads);
	free(philos);
	free(forks);
	return (0);
}
