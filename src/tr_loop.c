/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:20:24 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/27 16:45:42 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static t_bool	tr_receive_response(t_env *env, int ret)
{
	if (ret < 0)
		ft_error_str_exit("Error select\n");
	else if (ret)
		return TRUE;
	else
		fprintf(stdout, " *");
	return FALSE;
}

static t_bool	tr_read(t_env *env, int s,
				struct timeval tv_start, struct timeval tv_end)
{
	double	duration;
	struct	ip *ip;
	struct	icmp *icmp;
	t_bool	new_host;
	char	*fqdn;

	duration = 0;
	ft_memset(env->buf_r, 0, sizeof(env->buf_r));
	ip = (struct ip *)env->buf_r;
	icmp = (struct icmp *)(ip + 1);
	if (recvfrom(s, env->buf_r, sizeof(env->buf_r), 0, env->res->ai_addr, &(env->res->ai_addrlen)) < 0)
		ft_error_str_exit("Error recvfrom\n");

	gettimeofday(&tv_end, NULL);
	duration = (((double)tv_end.tv_sec * 1000000.0 + tv_end.tv_usec) - \
		((double)tv_start.tv_sec * 1000000.0 + tv_start.tv_usec)) / 1000;

	new_host = FALSE;
	if (ft_strcmp(env->host_tmp, inet_ntoa(ip->ip_src)) != 0)
	{
		new_host = TRUE;
		if (env->host_tmp != NULL)
			free(env->host_tmp);
		env->host_tmp = ft_strdup(inet_ntoa(ip->ip_src));
	}

	if (env->flags & FLAGS_N)
		fqdn = NULL;
	else
		fqdn = tr_get_hostname_from_ip(ip->ip_src);

	tr_display_response(env, new_host, fqdn, inet_ntoa(ip->ip_src), duration);

	if (ft_strcmp(env->host_dst, inet_ntoa(ip->ip_src)) == 0)
		return TRUE;
	return FALSE;
}

static int		tr_nqueries_once(t_env *env, t_uint ttl, unsigned int port)
{
	int s;
	int nb_send;

	ft_memset(&(env->buf), 0, sizeof(env->buf));
	s = tr_open_socket(env, ttl, port);
	if ((nb_send = sendto(s, env->buf, sizeof(env->buf), 0, env->res->ai_addr,
		env->res->ai_addrlen)) < 0)
		ft_error_str_exit("connect: Invalid argument\n");
	return (s);
}

void	tr_loop(t_env *env, t_uint max_ttl, t_uint nqueries)
{
	unsigned int		nqueries_count;
	struct timeval		tv;
	struct timeval		tv_start;
	struct timeval		tv_end;
	fd_set				rdfs;
	int					s;
	int					s_r;
	int					ret;
	int					port;
	t_bool				finish;

	port = PORT;
	s_r = tr_open_socket_receive();
	tr_display_info(env);
	finish = FALSE;
	while (!finish && env->ttl_count <= max_ttl)
	{
		nqueries_count = 0;
		ret = 0;
		tv.tv_sec = env->timeout;
		env->host_tmp = NULL;
		while (nqueries_count < nqueries)
		{
			gettimeofday(&tv_start, NULL);
			s = tr_nqueries_once(env, env->ttl_count, port++);
			close(s);
			if (nqueries_count == 0)
				printf("%*d ", 2, env->ttl_count);
			FD_ZERO(&rdfs);
			FD_SET(s_r, &rdfs);
			ret = select(s_r + 1, &rdfs, NULL, NULL, &tv);
			if (tr_receive_response(env, ret))
				finish = tr_read(env, s_r, tv_start, tv_end);

			nqueries_count++;
		}
		printf("\n");;
		env->ttl_count++;
	}
}
