[![libft](https://user-images.githubusercontent.com/102623863/185230931-b0ae9c6d-5329-40e2-9873-8da41a4ea032.png)](https://linktr.ee/vtrevisa)


### **Table of Contents**
* [Introduction](#introduction)
* [Part 1](#part-1---libc-functions)
* [Part 2](#part-2---additional-functions)
* [Bonus Part](#bonus-part)

# INTRODUCTION

The LIBFT project consists in personal library in C that contains the functions that we will use along the course. We started with some basic functions and we will adding more functions as we built them. These functions must work a the originals besides the new ones.

## HOW TO USE
* Clone the repo ```git clone https://github.com/vtrevisa/Libft```
* Enter the ***Libft*** directory
* Run **make**
* Include the header ```#include "<path>/libft/src/libft.h"``` in your file.c
* Compile your file.c with ```<path>/libft/libft.a```

# PART 1 - Libc Functions

In the first part of the project we recreated these functions
| FUNCTION NAME  | PROTOTYPE | DESCRIPTION | 
| -------------- | --------- | ----------- |
| [**ft\_atoi**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_atoi.c) | ```int ft_atoi(const char *str);``` | Converts the initial numbers of the string (ignoring isspace) pointed to by **str** to int and returns it. |
| [**ft\_bzero**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_bzero.c) | ```void	ft_bzero(void *s, size_t n);``` | Overwrite **n** bytes of the memory pointed by **s** with zeros ('\0').|
| [**ft\_calloc**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_calloc.c) | ```void	*ft_calloc(size_t nmemb, size_t size);``` |  Allocates memory for **nmemb** x **size** bytes, overwrite the memory with zeros ('\0') and returns a pointer to the allocated memory. |
| [**ft\_isalnum**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_isalnum.c) | ```int ft_isalnum(int c);``` | Checks for an alphanumeric character. |
| [**ft\_isalpha**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_isalpha.c) | ```int ft_isalpha(int c);``` | Checks for an alphabetic character. |
| [**ft\_isascii**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_isascii.c) | ```int ft_isascii(int c);``` | Checks if **c** fits into the ASCII character set. |
| [**ft\_isdigit**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_isdigit.c) | ```int ft_isdigit(int c);``` | Checks for a digit.|
| [**ft\_isprint**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_isprint.c) | ```int ft_isprint(int c);``` | Checks for any printable character. |
| [**ft\_memchr**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_memchr.c) | ```void *ft_memchr(const void *s, int c, size_t n);``` | Scans **n** bytes of the memory area pointed by **s** for the first occurrence of **c**. |
| [**ft\_memcmp**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_memcmp.c) | ```int ft_memcmp(const void *s1, const void *s2, size_t n);``` | Lexicographically compares **n** bytes (each interpreted as unsigned char) of the memory areas poited by s1 and s2 and return its difference. |
| [**ft\_memcpy**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_memcpy.c) | ```void	*ft_memcpy(void *dest, const void *src, size_t n);``` | Copies **n** bytes from memory area poited by **src** to memory area poited by **dest**. The memory areas must not overlap.  Use ft_memmove if they do. |
| [**ft\_memmove**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_memmove.c) | ```void	*ft_memmove(void *dest, const void *src, size_t n);``` | Copies **n** bytes from memory area poited by **src** to memory area poited by **dest**. The two strings may overlap. |
| [**ft\_memset**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_memset.c) | ```void	*ft_memset(void *s, int c, size_t n);``` | Fills **n** bytes of the memory area pointed by **s** with the constant byte **c**. |
| [**ft\_strchr**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strchr.c) | ```char	*ft_strchr(const char *s, int c);``` | Search and returns a pointer to the first occurrence of the character **c** in the string **s**. |
| [**ft\_strdup**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strdup.c) |```char	*ft_strdup(const char *s);``` | Mallocs and create a new string which is a duplicate of the string **s** and returns it. |
| [**ft\_strlcat**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strlcat.c) | ```size_t	ft_strlcat(char *dest, const char *src, size_t size);``` |  Appends **size** - strlen(**dst**) - 1 bytes of the NUL-terminated string **src** to the end of **dst**, NUL-terminating the result. |
| [**ft\_strlcpy**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strlcpy.c) | ```size_t	ft_strlcpy(char *dst, const char *src, size_t size);``` | Copies up to **size** - 1 characters from the NUL-terminated string **src** to **dst**, NUL-terminating the result. |
| [**ft\_strlen**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strlen.c) | ```size_t	ft_strlen(const char *s);``` | Counts and returns the length in bytes of the string **s**. |
| [**ft\_strncmp**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strncmp.c) | ```int		ft_strncmp(const char *s1, const char *s2, size_t n);``` | Lexicographically compares **n** bytes of the the NUL-terminated strings **s1** and **s2** and returns its difference. The comparison is done using unsigned characters. |
| [**ft\_strnstr**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strnstr.c) | ```char	*ft_strnstr(const char *big, const char *little, size_t len);``` | Searches **n** bytes and locates the first occurrence of the NUL-terminated string **little** in the string **big**. |
| [**ft\_strrchr**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strrchr.c) | ```char	*ft_strrchr(const char *s, int c);``` | Search and returns a pointer to the last occurrence of the character **c** in the string **s**. |
| [**ft\_tolower**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_tolower.c) | ```int ft_tolower(int c);``` | Convert uppercase to lowercase. |
| [**ft\_toupper**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_toupper.c) | ```int ft_toupper(int c);``` | Convert lowercase to uppercase. |

[To the top](#table-of-contents)

# PART 2 - Additional functions

| FUNCTIONS NAME | PROTOTYPE | DESCRIPTION |
| -------------- | --------- | ----------- |
| [**ft\_itoa**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_itoa.c) |```char	*ft_itoa(int n);``` | Mallocs and return in a string the integer **n**. Negative numbers are handled. |
| [**ft\_putchar\_fd**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_putchar_fd.c) | ```void	ft_putchar_fd(char c, int fd);``` | Outputs the character **c** to the file descriptor **fd**. |
| [**ft\_putendl\_fd**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_putendl_fd.c) | ```void	ft_putendl_fd(char *s, int fd);``` | Outputs the string **s** to the given file descriptor **fd** followed by a newline. |
| [**ft\_putnbr\_fd**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_putnbr_fd.c) | ```void	ft_putnbr_fd(int n, int fd);``` | Outputs the integer **n** to the given file descriptor **fd**. |
| [**ft\_putstr\_fd**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_putstr_fd.c) | ```void	ft_putstr_fd(char *s, int fd);``` | Outputs the string **s** to the given file descriptor **fd**. |
| [**ft\_split**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_split.c) | ```char	**ft_split(char const *s, char c);``` | Malloc and returns an array of strings obtained by splitting **s** using the character **c** as a delimiter.|
| [**ft\ striteri**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_striteri.c) | ```void	ft_striteri(char *s, void (*f)(unsigned int, char*));``` | Applies the function **f** on each character of the string **s**, passing its index as first argument and each character is passed by address to **f** to be modified if necessary. |
| [**ft\_strjoin**](https://github.com/vtrevisa/Libft/blob/master/Src/libft/ft_strjoin.c) | ```char	*ft_strjoin(char const *s1, char const *s2);``` | Mallocs and returns a new string, which is the result of the concatenation of **s1** and **s2**. |
| [**ft\_strmapi**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strmapi.c) | ```char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));``` | Applies the function **f** to each character of the string **s** to create a new string resulting from successive applications of **f**. |
| [**ft\_strtrim**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_strtrim.c) | ```char	*ft_strtrim(char const *s1, char const *set);``` | Mallocs and returns a copy of **s1** with the characters specified in **set** removed from the beginning and from the end of the string. |
| [**ft\_substr**](https://github.com/vtrevisa/Libft/blob/master/Src/ft_substr.c) | ```char	*ft_substr(char const *s, unsigned int start, size_t len);``` | Mallocs and returns a substring, starting at the position **start** and has a max size of **len** bytes, from the string **s**. |

[To the top](#table-of-contents)

# BONUS PART
These functions are made to manipulate the following truct:
```
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```
| FUNCTION NAME | PROTOTYPE | DECRIPTION |
|---------------|-----------|------------|
| [**ft\_lstnew**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstnew.c) |```t_list	*ft_lstnew(void *content);``` | Mallocs and returns a new element of the s_list. The variable **content** is initialized with the value of the parameter **content**. The variable **next** is initialized to NULL. |
| [**ft\_lstadd_front**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstadd_front.c) | ```void	ft_lstadd_front(t_list **lst, t_list *new);``` | Adds the element **new** at the beginning of the list **lst**. |
| [**ft\_lstsize**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstsize.c) | ```int		ft_lstsize(t_list *lst);``` | Counts the number of elements in the list **lst**. |
| [**ft\_lstlast**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstlast.c) | ```t_list	*ft_lstlast(t_list *lst);``` | Returns the last element of the list **lst**. |
| [**ft\_lstadd_back**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstadd_back.c) | ```void	ft_lstadd_back(t_list **lst, t_list *new);``` | Adds the element **new** at the end of the list **lst**. |
| [**ft\_lstdelone**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstdelone.c) | ```void	ft_lstdelone(t_list *lst, void (*del)(void*));``` | Takes as a parameter an element of the list **lst** and frees the memory of the element’s content using the function **del** given as a parameter and free the element. |
| [**ft\_lstclear**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstclear.c) | ```void	ft_lstclear(t_list **lst, void (*del)(void*));``` | Deletes and frees the given element of the list **lst** and every successor of that element, using the function **del**. The pointer to the list is set to NULL. |
| [**ft\_lstiter**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstiter.c) | ```void	ft_lstiter(t_list *lst, void (*f)(void *));``` | Iterates the list **lst** and applies the function **f** to the content of each element.|
| [**ft\_lstmap**](https://github.com/vcwild/42-libft/tree/main/src/libft/ft_lstmap.c) | ```t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));``` | Iterates the list **lst** and applies the function **f** to the content of each element. Creates a new list resulting of the successive applications of the function **f**. The **del** function is used to delete the content of an element if needed. |

[To the top](#table-of-contents)

***Additional Functions Yet to Come***
