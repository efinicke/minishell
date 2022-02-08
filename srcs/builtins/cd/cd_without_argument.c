/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   cd_without_argument.c                              :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/19 12:21:16 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/07 11:19:08 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cd_without_argument(char ***envp, const int outfile)
{
	const char	*home = ft_getenv("HOME", (const char **)*envp);

	if (!(home))
	{
		cd_error_msg("HOME", " not set");
		return (1);
	}
	return (cd_with_argument(home, envp, outfile));
}
