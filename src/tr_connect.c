/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:20:09 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/14 18:21:31 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int		tr_open_socket(t_env *env)
{
	int hincl;
	int s;

	hincl = 1;
	ft_memset(&(env->hints), 0, sizeof(env->hints));
	env->hints.ai_family = AF_INET;
	env->hints.ai_socktype = SOCK_DGRAM;
	env->hints.ai_protocol = IPPROTO_UDP;
	if (getaddrinfo(env->host_dst, NULL, &(env->hints), &(env->res)) < 0)
		ft_error_str_exit("traceroute: unknown host\n");
	if ((s = socket(env->res->ai_family, env->res->ai_socktype,
		env->res->ai_protocol)) < 0)
		ft_error_str_exit("Error socket opening\n");
	if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, &hincl, sizeof(hincl)) < 0)
		ft_error_str_exit("Error setsocket\n");
	return (s);
}

void	tr_configure_header(t_env *env)
{
	env->ip = (struct ip *)env->buf;
	env->udp = (struct udphdr*)(env->ip + 1);
}

void	tr_configure_send(t_env *env, unsigned short id, unsigned short seq, unsigned short ttl)
{
	ft_memset(&(env->buf), 0, sizeof(env->buf));
	env->ip->ip_v = 4;
	env->ip->ip_hl = sizeof(*(env->ip)) >> 2;
	env->ip->ip_tos = 0;
	env->ip->ip_len = htons(sizeof(env->buf));
	env->ip->ip_id = 0;
	env->ip->ip_off |= htons(IP_DF);
	env->ip->ip_ttl = ttl;
	env->ip->ip_p = env->res->ai_protocol;
	env->ip->ip_sum = 0;
	inet_pton(env->res->ai_family, env->host_src, &(env->ip->ip_src.s_addr));
	inet_pton(env->res->ai_family, env->host_dst, &(env->ip->ip_dst.s_addr));
	//UDP Header
	/*
	env->udp->source = 0;
	env->udp->dest = port_dst;
	env->udp->len = sizeof(*(env->udp));
	env->udp->check = 0;
	*/
}
