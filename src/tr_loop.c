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
	else if (ret)
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

void	tr_read(t_env *env, int s)
{
	char buf[400];
	// if (recvfrom(s, buf, sizeof(buf), 0, env->res->ai_addr, &(env->res->ai_addrlen)) < 0)
		// ft_error_str_exit("Error recvfrom\n");
	printf("Buffer: %s\n", buf);
}

int		tr_squeries_once(t_env *env, t_uint ttl, unsigned int port)
{
	int s;
	int nb_send;
	// fd_set rdfs;

	ft_memset(&(env->buf), 0, sizeof(env->buf));
	s = tr_open_socket(env, ttl, port);
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
	int					s_r;
	int					arr_sockets[max_ttl * squeries];
	int					ret;
	int					i;
	int					port;

	ttl_count = 1;
	tv.tv_sec = 5;
	i = 0;
	port = 33434;
	while (ttl_count < max_ttl)
	{
		squeries_count = 0;
		max_socket = 0;
		ret = 0;
		FD_ZERO(&rdfs);
		while (squeries_count < squeries)
		{
			s_r = tr_open_socket_receive();
			s = tr_squeries_once(env, ttl_count, port++);
			ft_putstr("Socket: ");
			ft_putnbr(s_r);
			ft_putstr("\n");

			close(s);
			FD_SET(s_r, &rdfs);
			if (s_r > max_socket)
				max_socket = s_r;
			arr_sockets[i] = s_r;
			squeries_count++;
		}

//		ft_putstr("FD_ISSET: ");
//		ft_putnbr(FD_ISSET(3, &rdfs));
//		ft_putstr("\n");
		// while (ret <= 0)
		// printf("MAX Scoket %d\n", s_r);


			ret = select(s_r + 1, &rdfs, NULL, NULL, &tv);
			tr_receive_response(env, rdfs, ret);
		// ft_putstr("Scoket ready: ");
		// ft_putnbr(ret);
		// ft_putstr("\n");
		// tr_read(env, s_r);

//		ret = select(max_socket + 1, &rdfs, NULL, NULL, &tv);
		//tr_receive_response(env, rdfs, ret);
		ttl_count++;
	}
}
