/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxc <fxc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:28:19 by mugenan           #+#    #+#             */
/*   Updated: 2025/09/11 17:29:54 by fxc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ftstrlen(const char *str);
char	*get_next_line(int fd);
char	*get_swap(char *getline);
char	*get_update(char *putline);
char	*ftstrchr(const char *s, int c);
char	*ftstrjoin(char *s1, char const *s2);
char	*get_read(char *getline, int fd);

#endif