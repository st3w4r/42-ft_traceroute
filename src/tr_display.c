#include "ft_traceroute.h"

void	tr_display_info(t_env *env)
{
	printf("traceroute to %s (%s), %u hops max, %lu byte packets\n",
					env->hostname_dst, env->host_dst, env->hops, sizeof(env->buf));
}

void	tr_display_response(t_env *env, char *fqdn, char *host,
				unsigned int squeries_count, double duration)
{
	if (host == NULL)
		printf(" *");
	else
	{
		if (squeries_count == 0)
			printf(" %s (%s)", fqdn, host);
		printf("  %.3f ms", duration);
	}

	if (squeries_count == env->squeries - 1)
		printf("\n");
}
