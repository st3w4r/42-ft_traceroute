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
		fprintf(stdout, "Scoket ready: %d \n", ret);

		// ft_putstr("Scoket ready: ");
		// ft_putnbr(ret);
		// ft_putstr("\n");
//		printf("Socket ready: %d\n", ret);
//		while (rdfs.fd_
	}
	else
		fprintf(stdout, "* ");
		// ft_putstr("* ");
}

void	tr_read(t_env *env, int s)
{
	char buf[400];
	struct ip *ip;
	struct icmp *icmp;

	ip = (struct ip *)buf;
	icmp = (struct icmp *)(ip + 1);
	if (recvfrom(s, buf, sizeof(buf), 0, env->res->ai_addr, &(env->res->ai_addrlen)) < 0)
		ft_error_str_exit("Error recvfrom\n");

	printf("Buffer IP SRC: %s\n", inet_ntoa(ip->ip_src));
	printf("Buffer ICMP TYPE: %u\n", icmp->icmp_type);
	printf("Buffer ICMP CODE: %u\n", icmp->icmp_code);
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
	struct timeval	tv;
	fd_set					rdfs;
	int							max_socket;
	int							s;
	int							s_r;
	// int							arr_sockets[max_ttl * squeries];
	int							ret;
	// int							i;
	int							port;

	ttl_count = 1;
	tv.tv_sec = 5;
	// i = 0;
	port = 33434;
	s_r = tr_open_socket_receive();
	tr_display_info(env);
	while (ttl_count < max_ttl)
	{
		squeries_count = 0;
		max_socket = 0;
		ret = 0;
		// FD_ZERO(&rdfs);
		fprintf(stdout, "%*d  ", 2, ttl_count);
		while (squeries_count < squeries)
		{
			s = tr_squeries_once(env, ttl_count, port++);
			// ft_putstr("Socket: ");
			// ft_putnbr(s_r);
			// ft_putstr("\n");

			close(s);
			FD_ZERO(&rdfs);
			FD_SET(s_r, &rdfs);
			if (s_r > max_socket)
				max_socket = s_r;
			ret = select(s_r + 1, &rdfs, NULL, NULL, &tv);
			tr_receive_response(env, rdfs, ret);
			if (ret > 0)
				tr_read(env, s_r);

			// arr_sockets[i] = s_r;
			squeries_count++;
		}
		fprintf(stdout, "\n");
		// i++;
		// ret = select(s_r + 1, &rdfs, NULL, NULL, &tv);
		// tr_receive_response(env, rdfs, ret);
		// tr_read(env, s_r);
		ttl_count++;
	}
}
