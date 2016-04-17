/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 16:08:12 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/12 16:39:46 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

char	*tr_get_ip_from_hostname(char *hostname)
{
	struct addrinfo			hints;
	struct addrinfo			*res;
	struct sockaddr_in	*sa_in;
	char								*ip_share;

	ft_memset(&(hints), 0, sizeof(hints));
	hints.ai_family = AF_INET;
	if ((ip_share = malloc(INET_ADDRSTRLEN)) < 0)
		ft_error_str_exit("Error malloc");
	if (getaddrinfo(hostname, NULL, &hints, &(res)) < 0)
		ft_error_str_exit("tracerout: unknown host\n");
	sa_in = (struct sockaddr_in *)res->ai_addr;
	// ip_share = inet_ntoa(sa_in->sin_addr);
	inet_ntop(res->ai_family, &(sa_in->sin_addr), ip_share, INET_ADDRSTRLEN);
	// printf("IP: %s\n", ip_share);
	return (ip_share);
}

char	*tr_get_hostname_from_ip(struct in_addr ip)
{
	struct hostent *hostent;

	hostent = gethostbyaddr(&ip, sizeof(ip), AF_INET);
	if (hostent)
		return (hostent->h_name);
	return (inet_ntoa(ip));
}
