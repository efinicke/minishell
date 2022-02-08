/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2020/11/16 14:35:47 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/07 14:54:46 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(const char c);

char	*ft_itoa(int n);
char	*ft_ullitoa(unsigned long long int n);
int		ft_atoi(const char *nptr);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);

char	**ft_split(char const *s, char c);

#endif
