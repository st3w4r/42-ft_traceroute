/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:20:09 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/13 18:41:49 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int		tr_open_socket(t_env *env)
{
	int hincl;

	hincl = 1;
	ft_memset(&(env->hints), 0, sizeof(env->hints));
	env->hints.ai_family = AF_INET;
	env->hints.ai_socktype = SOCK_DGRAM;
	env->hints.ai_protocol = IPPROTO_UDP;
	if (getaddrinfo(env->host_dst, "33434", &(env->hints), &(env->res)) < 0)
		ft_error_str_exit("traceroute: unknown host\n");
	if ((env->s = socket(env->res->ai_family, env->res->ai_socktype,
		env->res->ai_protocol)) < 0)
		ft_error_str_exit("Error socket opening\n");
//	if (setsockopt(env->s, IPPROTO_IP, IP_HDRINCL, &hincl, sizeof(hincl)) < 0)
//		ft_error_str_exit("Error setsocket\n");
	return (env->s);
}


