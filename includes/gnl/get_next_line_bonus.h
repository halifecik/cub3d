/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxc <fxc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:21:37 by mugenan           #+#    #+#             */
/*   Updated: 2025/09/11 17:31:40 by fxc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ftstrlen(const char *str);
char	*get_next_line(int fd);
char	*get_swap(char *getline);
char	*get_update(char *putline);
char	*ftstrchr(const char *s, int c);
char	*ftstrjoin(char *s1, char const *s2);
char	*get_read(char *getline, int fd);

#endif