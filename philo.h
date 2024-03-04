/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjochum <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:35:31 by mjochum           #+#    #+#             */
/*   Updated: 2023/10/15 12:41:19 by mjochum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# define MSG "[ %08lu ] [ philosopher %2lu %-12s ]\n"
# define MSGF "takes forks"
# define MSGE "is eating"
# define MSGS "is sleeping"
# define MSGT "is thinking"
# define MSGD "died :(("
# define ERR "%s [n philo] [ms die] [ms eat] [ms sleep] ([n eat])\n"
# define ERR_IO -10
# define ERR_PHILDEATH -69

typedef struct s_philo	t_philo;
typedef struct s_vars	t_vars;
typedef struct s_fork	t_fork;
typedef struct s_vars {	
	struct timeval	dingdong;
	t_philo			**philo;
	t_fork			**fork;
	pthread_mutex_t	printf_m;
	pthread_mutex_t	time_m;
	pthread_mutex_t	death_m;
	pthread_mutex_t	run_m;
	size_t			run;
	size_t			nphilos;
	size_t			msdie;
	size_t			mseat;
	size_t			mssleep;
	size_t			neat;
	size_t			noneat;
	size_t			starttime;
}			t_vars;

typedef struct s_philo {
	pthread_t	pthread;
	t_vars		*vars;
	size_t		id;
	size_t		left;
	size_t		isalive;
	size_t		lasteat;
	size_t		nextdeath;
	size_t		nmeals;
	size_t		lfork;
	size_t		rfork;
	size_t		nphilos;
	size_t		msdie;
	size_t		mseat;
	size_t		mssleep;
	size_t		neat;
	size_t		noneat;
	size_t		starttime;
}			t_philo;

typedef struct s_fork {
	pthread_mutex_t			mutex;
	size_t					fork;
	size_t					lastid;
}			t_fork;

int		ft_atoi(const char *nptr);
int		ft_run(t_vars *vars);
size_t	ft_currenttime(t_vars *vars);
size_t	ft_elapsedtime(t_philo *philo);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_philosopher(void *arg);
void	ft_exit(int status, t_vars *vars);
void	ft_mrintf(const char *str, t_philo *philo);
void	ft_mutex_fourchette(t_philo *philo, int status);
#endif
