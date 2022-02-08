/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/19 12:21:16 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/07 11:19:06 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cmd_cd(const int argc, const char **argv, char ***envp, const int outfile)
{
	if (argc > 2)
	{
		cd_error_msg(NULL, "too many arguments");
		return (1);
	}
	else if (argc == 1)
		return (cd_without_argument(envp, outfile));
	else
		return (cd_with_argument(argv[1], envp, outfile));
	return (0);
}
