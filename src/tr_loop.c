/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:20:24 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/14 18:39:49 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// void	tr_send_packet(t_env *env, )

int		tr_squeries_once(t_env *env, fd_set *rdfs, t_uint ttl)
{
	int s;
	int nb_send;
	// fd_set rdfs;

	s = tr_open_socket(env, ttl);
	FD_SET(s, rdfs);
	// tr_configure_send(env, 42, 24, ttl);
	if ((nb_send = sendto(s, env->buf, sizeof(env->buf), 0, env->res->ai_addr,
		env->res->ai_addrlen)) < 0)
		ft_error_str_exit("Error sendto\n");
	return (s);
}

void	tr_loop(t_env *env, t_uint max_ttl, t_uint squeries)
{
	unsigned int		ttl_count;
	unsigned int		squeries_count;
	struct timeval	tv;
	fd_set					rdfs;
	int							max_socket;
	int							s;

	ttl_count = 1;
	tv.tv_sec = 1;
	max_socket = 0;
	while (ttl_count < max_ttl)
	{
		squeries_count = 0;
		while (squeries_count < squeries)
		{
			FD_ZERO(&rdfs);
			s = tr_squeries_once(env, &rdfs, ttl_count);
			if (s > max_socket)
				max_socket = s;
			squeries_count++;
		}
		select(max_socket + 1, &rdfs, NULL, NULL, &tv);
		ttl_count++;
	}
}
