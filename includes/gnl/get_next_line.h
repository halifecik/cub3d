/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:23:40 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 18:45:43 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*get_swap(char *getline);
char	*get_update(char *getline);
int		ftstrlen(const char *str);
char	*get_read(char *getline, int fd);
char	*ftstrchr(const char *s, int c);
char	*ftstrjoin(char *s1, char const *s2);

#endif