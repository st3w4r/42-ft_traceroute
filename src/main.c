/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 10:56:35 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/19 11:13:20 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void	tr_error_usage(void)
{
	ft_error_str_exit("Usage: ft_traceroute [-hmqf] HOST\n");
}

static void	tr_help(void)
{
	printf("Usage: traceroute [OPTION...] HOST ... \n"
	"\n"
	"Options:\n"
	"   -m max_ttl          "
	"Set the max number of hops (max TTL to bereached). Default is 30\n"
	"   -q nqueries         "
	"Set the number of probes per each hop. Default is 3\n"
	"   -f first_ttl        "
	"Start from the first_ttl hop (instead from 1)\n"
	"\n"
	"   -h                  give this help list\n");
	exit(0);
}

static void	tr_e_i(void)
{
	ft_error_str_exit("ft_traceroute: invalid value\n");
}

int			tr_options(t_env *env, int argc, char **argv)
{
	int opt;
	int value;

	value = 0;
	while ((opt = getopt(argc, argv, "hm:q:f:")) != -1)
	{
		if (opt == 'h')
			tr_help();
		else if (opt == 'm')
		{
			value = ft_atoi(optarg);
			(value > 0 && value <= 255) ? env->hops = value : tr_e_i();
		}
		else if (opt == 'q')
		{
			value = ft_atoi(optarg);
			(value > 0 && value <= 10) ? env->squeries = value : tr_e_i();
		}
		else if (opt == 'f')
		{
			value = ft_atoi(optarg);
			(value > 0 && value <= env->hops) ? env->ttl_count = value : tr_e_i();
		}
		else
			tr_error_usage();
	}
	return (optind);
}

int			main(int argc, char **argv)
{
	int		pos_args;
	t_env	env;

	if (argc <= 1)
		tr_error_usage();
	if (getuid() != 0)
		ft_error_str_exit("ft_ping: Operation not permitted\n");
	env.hops = 30;
	env.squeries = 3;
	env.ttl_count = 1;
	pos_args = tr_options(&env, argc, argv);
	env.hostname_dst = argv[pos_args];
	env.host_dst = tr_get_ip_from_hostname(argv[pos_args]);
	// env.host_dst = argv[pos_args];
	env.host_src = "0.0.0.0";

	tr_loop(&env, env.hops, env.squeries);
	return (0);
}
