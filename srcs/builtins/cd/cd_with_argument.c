/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   cd_with_argument.c                                 :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/19 12:21:16 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/07 11:19:07 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	cd_oldpwd(char ***envp, const int outfile)
{
	const char	*oldpwd = ft_getenv("OLDPWD", (const char **)*envp);

	if (!(oldpwd))
	{
		cd_error_msg("OLDPWD", " not set");
		return (1);
	}
	return (slash_or_pwd(oldpwd, NULL, envp, outfile));
}

int	cd_with_argument(const char *cd_string, char ***envp, \
	const int outfile)
{
	if (ft_strlen(cd_string) == 1 && cd_string[0] == '-')
		return (cd_oldpwd(envp, outfile));
	if (cd_string[0] && cd_string[0] == '/')
		return (slash_or_pwd(cd_string, NULL, envp, -1));
	else if (cd_string[0] && cd_string[0] == '.')
		return (slash_or_pwd(cd_string, NULL, envp, -1));
	else
		return (cdpath(cd_string, envp, outfile));
	return (0);
}
