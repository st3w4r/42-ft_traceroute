/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:20:09 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/19 14:55:46 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int		tr_open_socket(t_env *env, unsigned short ttl, unsigned int port)
{
	int s;

	ft_memset(&(env->hints), 0, sizeof(env->hints));
	env->hints.ai_family = AF_INET;
	env->hints.ai_socktype = SOCK_DGRAM;
	env->hints.ai_protocol = IPPROTO_UDP;

	if (getaddrinfo(env->host_dst, ft_itoa(port), &(env->hints), &(env->res)) < 0)
		ft_error_str_exit("traceroute: unknown host\n");
	if ((s = socket(env->res->ai_family, env->res->ai_socktype,
		env->res->ai_protocol)) < 0)
		ft_error_str_exit("Error socket opening\n");
	if (setsockopt(s, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		ft_error_str_exit("Error setsocket ttl\n");
	// printf("PORT: %hu\n", htons(((struct sockaddr_in *)env->res->ai_addr)->sin_port));
	return (s);
}

int		tr_open_socket_receive(void)
{
	int s;

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		ft_error_str_exit("Error socket opening\n");
	return (s);
}
/*
int		tr_binder_socket(int s, struct sockaddr_in sa_in, int port)
{
	if (bind(s, (struct sock_addr *)&sa_in, sizeof(sa_in)) < 0)
		ft_error_str_exit("Error bind\n");
	return (s);
}*/
