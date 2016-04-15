/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 10:56:35 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/15 14:33:35 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void	tr_error_usage(void)
{
	ft_error_str_exit("Usage: ft_traceroute [-h] HOST\n");
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

	while ((opt = getopt(argc, argv, "vhDc:i:W:m:")) != -1)
	{
		if (opt == 'h')
			tr_help();
		else
			tr_error_usage();
	}
	return (optind);
}

int			main(int argc, char **argv)
{
	int		pos_args;

	if (argc <= 1)
		tr_error_usage();
	if (getuid() != 0)
		ft_error_str_exit("ft_ping: Operation not permitted\n");
	pos_args = tr_options(&env, argc, argv);
	env.host_dst = tr_get_ip_from_hostname(argv[pos_args]);
	env.host_src = "0.0.0.0";
	/*
	env.flags = 0;
	env.count = 0;
	env.interval = 1;
	env.timeout = 1;
	env.ttl = 64;
	*/
	pos_args = tr_options(&env, argc, argv);
	env.hostname_dst = argv[pos_args];
	env.host_dst = tr_get_ip_from_hostname(argv[pos_args]);
	env.host_src = "0.0.0.0";
	/*
	env.min = DBL_MAX;
	env.pid = getpid();
	*/
	// tr_open_socket(&env);
	// tr_configure_header(&env);
	//signal(SIGALRM, pg_sig_handler);
	//signal(SIGINT, pg_sig_handler);
	tr_loop(&env, 5, 3);
	return (0);
}
