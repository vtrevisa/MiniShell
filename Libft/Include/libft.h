/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:14:48 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/12 18:01:38 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define MAX_FD_SIZE 1024

/* ------PART 1------ */
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

/* ------part 2------ */
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* ------BONUS PART------*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ------GNL------ */
char		*get_next_line(int fd);
size_t		gn_strlen(const char *s);
char		*gn_strjoin(char *s1, char *s2);
char		*gn_strchr(char *s, int c);

/* ------printf------ */
/*====FILES====*/
int		ft_printf(const char *str, ...);
int		handlechar(va_list ap, int fd);
int		handlestr(va_list ap, int fd);
int		handlepointer(va_list ap, int fd, int flag);
int		handleints(va_list ap, int fd);
int		handleunsigned(va_list ap, int fd);
int		handlehex(va_list ap, int fd, int flag);
void	printpointer_fd(unsigned long int lli, int fd, int flag);

/*====UTILS====*/
int		countdigit(int n);
int		countudigit(unsigned int n);
void	ft_putunbr_fd(unsigned int n, int fd);

/*====PRINTPOINTER_FD====*/
int		hexlen(unsigned long int lli);
char	*htoa(unsigned long int lli, int flag);

/*====FRACT-OL====*/
typedef struct s_lst
{
	double	ret;
	int		p_vir;
	int		i;
	int		temp;
	int		sig;
}	t_lst;

double	ft_atof(const char *str);
#endif
