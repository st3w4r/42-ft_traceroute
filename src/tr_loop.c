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

void	tr_squeries_once(t_env *env, t_uint ttl)
{
	int s;
	int nb_send;

	s = tr_open_socket(env);
	tr_configure_send(env, 4242, 24, ttl);
	if ((nb_send = sendto(s, env->buf, sizeof(env->buf), 0, env->res->ai_addr,
		env->res->ai_addrlen)) < 0)
		ft_error_str_exit("Error sendto\n");
}

void	tr_loop(t_env *env, t_uint max_ttl, t_uint squeries)
{
	u_int ttl_count;
	u_int squeries_count;

	ttl_count = 1;
	squeries_count = 0;
	while (ttl_count < max_ttl)
	{
		while (squeries_count < squeries)
		{
			tr_squeries_once(env, ttl_count);
			squeries_count++;
		}
		ttl_count++;
	}
}
