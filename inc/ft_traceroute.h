/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 10:55:55 by ybarbier          #+#    #+#             */
/*   Updated: 2016/04/27 16:40:37 by ybarbier         ###   ########.fr       */
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
# define BUFLEN 32
# define PORT 33434

typedef unsigned char	t_bool;

enum	e_flags
{
	FLAGS_V = 1 << 0,
	FLAGS_H = 1 << 1,
	FLAGS_N = 1 << 2
};


typedef struct	s_env {
	unsigned int		hops;
	unsigned int		nqueries;
	unsigned int		ttl_count;
	unsigned int		timeout;
	int					flags;
	// SOCKET
	struct addrinfo		hints;
	struct addrinfo		*res;
	// SEND
	char				buf[BUFLEN];
	char				*host_src;
	char				*host_tmp;
	char				*host_dst;
	char				*hostname_dst;
	// RECIEVE
	char				buf_r[BUFLEN];
}				t_env;

// t_env	env;

/*
** Name: pg_connect
** Desc: Configure and open socket
*/
int		tr_open_socket(t_env *env, unsigned short ttl, unsigned int port);
int		tr_open_socket_receive(void);

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

/*
** Name: pg_helper
** Desc: Helpers Functions
*/

//unsigned short	pg_icmp_checksum(unsigned short *buf, int len);
char	*tr_get_ip_from_hostname(char *hostname);
char	*tr_get_hostname_from_ip(struct in_addr ip);

#endif
