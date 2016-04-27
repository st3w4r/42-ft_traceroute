/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:20:09 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/27 16:17:31 by ybarbier         ###   ########.fr       */
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
	return (s);
}

int		tr_open_socket_receive(void)
{
	int s;

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
		ft_error_str_exit("Error socket opening\n");
	return (s);
}
