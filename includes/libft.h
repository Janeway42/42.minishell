/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:34:34 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:34:36 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	struct s_stack	*next;
	int				val;
	int				index;
	struct s_stack	*prev;
}				t_stack;

int			ft_atoi(const char *nptr);
void		ft_bzero(void *str, size_t n);
void		*ft_calloc(size_t nitems, size_t size);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, char *s2, size_t n);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char *str1, char *str2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
t_stack		*ft_lstnew(int number);
t_stack		*ft_lstlast(t_stack *x);
int			ft_lstsize(t_stack *x);
void		ft_lstadd_back(t_stack **x, t_stack *element);

#endif