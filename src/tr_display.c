#include "ft_traceroute.h"

void	tr_display_info(t_env *env)
{
	printf("traceroute to %s (%s), %u hops max, %lu byte packets\n",
					env->hostname_dst, env->host_dst, env->hops, sizeof(env->buf));
}
