/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 10:55:55 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/19 14:55:44 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <netdb.h>
# include <signal.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netinet/udp.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <float.h>
# include <math.h>

# define TRUE 1
# define FALSE 0
# define BUFLEN 100

typedef unsigned char	t_bool;

enum	e_flags
{
	FLAGS_V = 1 << 0,
	FLAGS_H = 1 << 1
};


typedef struct	s_env {
	unsigned int	hops;
	unsigned int	nqueries;
	unsigned int	ttl_count;
/*
	int						flags;
	unsigned int			count;
	unsigned int			interval;
	unsigned int			timeout;
	unsigned int			ttl;
	t_bool					timeout_flag;
	t_bool					df_flag;
	pid_t					pid;
	unsigned int			packets_send;
	unsigned int			packets_receive;
	unsigned short			seq;
	double					min;
	double					max;
	double					cumul;
	double					cumul_s;
*/
	// SOCKET
//	int						s;
	struct addrinfo			hints;
	struct addrinfo			*res;
	// SEND
	char					buf[BUFLEN];
	char					buf_r[BUFLEN];
	char					*host_src;
	char					*host_tmp;
	char					*host_dst;
	char					*hostname_dst;
	struct ip				*ip;
	struct udphdr			*udp;
	// RECIEVE
/*
	struct iovec			iov[1];
	struct msghdr			msg;
	char					buf_control[1000];
*/
}				t_env;

// t_env	env;

/*
** Name: pg_connect
** Desc: Configure and open socket
*/
int		tr_open_socket(t_env *env, unsigned short ttl, unsigned int port);
int		tr_open_socket_receive(void);
void	tr_configure_header(t_env *env);
void	tr_configure_send(t_env *env, unsigned short id, unsigned short seq,
	unsigned short ttl, unsigned int port);
/*
void	pg_configure_receive(t_env *env);
*/
/*
** Name: pg_loop
** Desc: Loop to send ICMP ECHO and receive ICMP REPLY
*/

void	tr_loop(t_env *env, t_uint max_ttl, t_uint nqueries);

/*
** Name: pg_display
** Desc: Functions to display informations
*/
void	tr_display_info(t_env *env);
void	tr_display_response(t_env *env, t_bool new_host, char *fqdn, char *host,
				double duration);
//void	pg_display_response(t_env *env, int bytes_receive, int seq,
//		double duration);
//void	pg_display_stats(t_env *env);

/*
** Name: pg_helper
** Desc: Helpers Functions
*/

//unsigned short	pg_icmp_checksum(unsigned short *buf, int len);
//void	pg_sig_handler(int sig);
char	*tr_get_ip_from_hostname(char *hostname);
char	*tr_get_hostname_from_ip(struct in_addr ip);
//void	pg_duration_stats(t_env *env, double duration);

#endif
