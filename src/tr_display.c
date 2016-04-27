#include "ft_traceroute.h"

void	tr_display_info(t_env *env)
{
	printf("traceroute to %s (%s), %u hops max, %lu byte packets\n",
			env->hostname_dst, env->host_dst, env->hops,
			sizeof(env->buf) + sizeof(struct ip) + sizeof(struct udphdr));
}

void	tr_display_response(t_env *env, t_bool new_host, char *fqdn,
		char *host, double duration)
{
/*	if (host == NULL)
		printf(" *");
	else
	{*/
		if (new_host && fqdn)
			printf(" %s (%s)", fqdn, host);
		else if (new_host)
			printf(" %s", host);
		printf("  %.3f ms", duration);
/*	}

	if (squeries_count == env->squeries - 1)
		printf("\n");
*/
}
