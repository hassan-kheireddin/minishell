/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheired <hkheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:36:13 by rabdel-f          #+#    #+#             */
/*   Updated: 2024/12/18 13:59:03 by hkheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

size_t		ft_strlen(const char *s);

size_t		ft_strlcat(char *dst, const char *src, size_t size);

size_t		ft_strlcpy(char *dst, const char *src, size_t size);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_atoi(const char *nptr);

int			ft_atoi2(const char *nptr, unsigned long long *nbr);

char		*ft_itoa(int n);

int			ft_putchar_fd(char c, int fd);

int			ft_putendl_fd(char *s, int fd);

int			ft_putnbr_fd(int n, int fd);

int			ft_putstr_fd(char *s, int fd);

char		**ft_split(char const *s, char c);

char		*ft_strjoin(char const *s1, char const *s2);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char		*ft_strtrim(char const *s1, char const *set);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*ft_strjoin_char(char *str, char c);

void		ft_bzero(void *s, size_t n);

void		*ft_calloc(size_t nmemb, size_t size);

int			ft_isalnum(int c);

int			ft_isalpha(int c);

int			ft_isascii(int c);

int			ft_isdigit(int c);

int			ft_isprint(int c);

void		*ft_memccpy(void *dest, const void *src, int c, size_t n);

void		*ft_memchr(const void *s, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		*ft_memcpy(void *dest, const void *src, size_t n);

void		*ft_memmove(void *dest, const void *src, size_t n);

void		*ft_memset(void *s, int c, size_t n);

char		*ft_strchr(const char *s, int c);

int			ft_strchr_i(const char *s, int c);

int			ft_strchars_i(const char *s, char *set);

char		*ft_strrchr(const char *s, int c);

char		*ft_strdup(const char *s);

char		*ft_strnstr(const char *big, const char *little, size_t len);

int			ft_tolower(int c);

int			ft_toupper(int c);

int			ft_nbrlen(long n, int base);

int			ft_strrncmp(const char *s1, const char *s2, size_t n);

int			ft_countchar(char *s, char c);

int			ft_isspace(char c);

void		ft_lstadd_back(t_list **lst, t_list *newnode);

void		ft_lstadd_front(t_list **lst, t_list *newnode);

void		ft_lstclear(t_list **lst, void (*del)(void*));

void		ft_lstdelone(t_list *lst, void (*del)(void*));

void		ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstlast(t_list *lst);

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list		*ft_lstnew(void *content);

int			ft_lstsize(t_list *lst);

t_list		*ft_lstget_at(t_list *lst, int i);

void		ft_free_matrix(char ***m);

char		**ft_dup_matrix(char **m);

int			ft_putmatrix_fd(char **m, int nl, int fd);

int			ft_matrixlen(char **m);

char		**ft_subsplit(char const *s, char *set);

char		**ft_extend_matrix(char **in, char *newstr);

char		**ft_matrix_replace_in(char ***big, char **small, int n);

#endif
