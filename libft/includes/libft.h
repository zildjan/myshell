/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:12:34 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/06 20:46:28 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define ACTIVE_FT_PRINTF_COLOR 1

# include "color.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <wchar.h>
# include <sys/stat.h>
# include <math.h>

typedef unsigned long long	t_ull;
typedef long long			t_ll;
typedef unsigned long		t_ul;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_printf(const char *format, ...);

/*
**    MEMORY
*/
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memsalloc(size_t size);
void			*ft_memrealloc(void *ptr, size_t size, size_t new_size);
void			ft_memdel(void **ap);

/*
**    STRINGS
*/
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
char			*ft_strrev(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strautosub(char const *s, char start, char end);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
unsigned int	ft_count_word(char const *s, char c);
void			ft_putchartab(char **tab);
void			ft_putchartab_fd(char **tab, int fd);
int				ft_strcheck(char const *s, int (*f)(int));
int				ft_isfullof(char *str, int c);

/*
**    CAHARACTER
*/
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
unsigned int	ft_nbrlen(long long n);
unsigned int	ft_u_nbrlen(unsigned long long n);
unsigned int	ft_nbrlen_base(long long n, int base);
unsigned int	ft_u_nbrlen_base(unsigned long long n, size_t base);
char			ft_isspace(int c);

/*
**    MATHS
*/
int				ft_pow(int n, int pow);
double			ft_degree_to_radian(int angle);

/*
**    FILES
*/
long			ft_get_file_size(char *path);
char			*ft_get_file_size_str(char *path);
char			*ft_get_basename(char *path);
int				ft_is_hidden_file(char *str);
char			ft_get_file_type(char *path);
int				ft_get_file_mode(char *path);
char			**ft_list_dir_content(char *path, char all, char type);
char			*ft_get_dirup(char *path);

/*
**    INFOGRAPHIE
*/
unsigned long	ft_rgbtohex(int r, int g, int b);

/*
**    CONVERIONS
*/
char			*ft_strtoupper(char *str);
char			*ft_itoa(int i);
char			*ft_ltoa(long long i);
char			*ft_ultoa(unsigned long long i);
char			*ft_ultoa_base(unsigned long long i, size_t base);
char			*ft_dtoa(double i, int precision);
int				ft_atoi(const char *str);
int				ft_btoi(const char *str);

/*
**    PUT ASCII
*/
void			ft_putchar(char c);
size_t			ft_putstr(char const *s);
void			ft_putsubstr(char *str, int beg, int size);
void			ft_putendl(char const *s);
size_t			ft_putnbr(long n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(long n, int fd);
void			ft_putnspace(int len);
void			ft_putnchar(int len, char c);

/*
**    WCHAR
*/
int				ft_putwchar(wchar_t c);
int				ft_putwstr(const wchar_t *s);
size_t			ft_wcharlen(wchar_t c);
size_t			ft_wstrlen(const wchar_t *s);
wchar_t			*ft_wstrdup(const wchar_t *s1);
wchar_t			*ft_wstrndup(const wchar_t *s1, size_t n);

/*
**    LIST
*/
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstaddend(t_list **alst, t_list *new);
void			ft_lstadd(t_list **alst, t_list *new);
t_list			*ft_lstsplit(char const *s, char c, int keepc);
void			ft_putlst_str(t_list **alst);
void			ft_lstdelcontent(void *content, size_t content_size);

#endif
