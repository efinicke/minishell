/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/13 13:11:17 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/06 13:22:14 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cmd_export(const int argc, const char **argv, char ***envp, \
	const int outfile)
{
	if (argc > 1)
		return (export_with_argument(argv, envp));
	return (export_without_argument((const char **)*envp, outfile));
}
