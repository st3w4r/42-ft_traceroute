/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:20:24 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/15 15:22:50 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

// void	tr_send_packet(t_env *env, )

void	tr_receive_response(t_env *env, fd_set rdfs, int ret)
{
//	printf("Count socket: %u\n", rdfs.fd_count);
	if (ret < 0)
		ft_error_str_exit("Error select\n");
	else if (ret > 0)
	{
		ft_putstr("Scoket ready: ");
		ft_putnbr(ret);
		ft_putstr("\n");
//		printf("Socket ready: %d\n", ret);
//		while (rdfs.fd_
	}
	else
		ft_putstr("Timeout\n");
}

int		tr_squeries_once(t_env *env, t_uint ttl)
{
	int s;
	int nb_send;
	// fd_set rdfs;

	s = tr_open_socket(env, ttl);
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
	struct timeval		tv;
	fd_set				rdfs;
	int					max_socket;
	int					s;
	int					arr_sockets[max_ttl * squeries];
	int					ret;
	int					i;

	ttl_count = 1;
	tv.tv_sec = 5;
	i = 0;
	while (ttl_count < max_ttl)
	{
		squeries_count = 0;
		max_socket = 0;
		ret = 0;
		FD_ZERO(&rdfs);
		while (squeries_count < squeries)
		{
			s = tr_squeries_once(env, ttl_count);

			FD_SET(s, &rdfs);
			ft_putstr("Socket: ");
			ft_putnbr(s);
			ft_putstr("\n");

			if (s > max_socket)
				max_socket = s;
			arr_sockets[i] = s;
			squeries_count++;
		}

//		ft_putstr("FD_ISSET: ");
//		ft_putnbr(FD_ISSET(3, &rdfs));
//		ft_putstr("\n");

		ret = select(max_socket + 1, &rdfs, NULL, NULL, &tv);
		ft_putstr("Scoket ready: ");
		ft_putnbr(ret);
		ft_putstr("\n");

//		ret = select(max_socket + 1, &rdfs, NULL, NULL, &tv);
		//tr_receive_response(env, rdfs, ret);
		ttl_count++;
	}
}
