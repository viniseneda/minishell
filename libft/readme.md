#libft
my libft implementation for 42 school SP. My "get next line" code is also in this library.

##functions:

####void	*ft_memset(void *s, int c, size_t n);
memset - fill memory with a constant byte

####void	ft_bzero(void *s, size_t n);
bzero, explicit_bzero - zero a byte string

####void	*ft_memcpy(void *dest, const void *src, size_t n);
The  memcpy()  function  copies n bytes from memory area src to memory area dest.  The memory areas must not overlap.  Use memmove(3) if the memory areas do overlap.

####void	*ft_memmove(void *dest, const void *src, size_t n);
The  memmove()  function  copies n bytes from memory area src to memory area dest.  The memory areas may overlap: copying takes place as though the bytes in src are first copied into a temporary array that does not overlap src or dest, and the  bytes  are then copied from the temporary array to dest.

####void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
The  memccpy()  function copies no more than n bytes from memory area src to memory area dest, stopping when the character c is found. If the memory areas overlap, the results are undefined.

####void	*ft_memchr(const void *s, int c, size_t n);
The memchr() function scans the initial n bytes of the memory area pointed to by s for the first instance of c.  Both c and the bytes of the memory area pointed to by s are interpreted as unsigned char. 

The memchr() and memrchr() functions return a pointer to the matching byte or NULL if the character does not occur in the given memory area.

####int	ft_memcmp(const void *s1, const void *s2, size_t n);
The memcmp() function compares the first n bytes (each interpreted as unsigned char) of the memory areas s1 and s2.

The memcmp() function returns an integer less than, equal to, or greater than zero if the first n bytes of s1 is found, respectively, to be less than, to match, or be greater than the first n bytes of s2.

For a nonzero return value, the sign is determined by the sign of the difference between the first pair of  bytes  (interpreted as unsigned char) that differ in s1 and s2.

If n is zero, the return value is zero.

####size_t	ft_strlen(const char *s);

####size_t	ft_strlcpy(char *dst, const char *src, size_t size);
####size_t	ft_strlcat(char *dst, const char *src, size_t size);

The strlcpy() and strlcat() functions copy and concatenate strings respectively.  They are designed to be safer, more consistent, and less error prone replacements for strncpy(3) and strncat(3). 

The strlcpy() function copies up to size - 1 characters from the NUL-terminated string src to dst, NUL-terminating the result.

The strlcat() function appends the NUL-terminated string src to the end of dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the result.

The strlcpy() and strlcat() functions return the total length of the string they tried to create.  For strlcpy() that means the length of src.  For strlcat() that means the initial length of dst plus the length of src.  While this may seem somewhat confusing, it was done to make truncation detection simple.

####char	*ft_strchr(const char *s, int c);
####char	*ft_strrchr(const char *s, int c);

The strchr() function returns a pointer to the first occurrence of the character c in the string s.

The strrchr() function returns a pointer to the last occurrence of the character c in the string s.

####char	*ft_strnstr(const char *big, const char *little, size_t len);
The strnstr() function locates the first occurrence of the null-terminated string little in the string big, where not more than len characters are searched.  Characters that appear after a ‘\0’ character are not searched.  Since the strnstr() function is a FreeBSD specific API, it should only be used when portability is not a concern.

####int	ft_strncmp(const char *s1, const char *s2, size_t n);
The strcmp() function compares the two strings s1 and s2.

• 0, if the s1 and s2 are equal;

• a negative value if s1 is less than s2;

• a positive value if s1 is greater than s2.

The strncmp() function is similar, except it compares only the first (at most) n bytes of s1 and s2.

####int	ft_atoi(const char *nptr);

####char	*ft_itoa(int n);

####int	ft_isalpha(int c);

####int	ft_isdigit(int c);

####int	ft_isalnum(int c);

####int	ft_isascii(int c);

####int	ft_isprint(int c);

####int	ft_toupper(int c);

####int	ft_tolower(int c);

####void	*ft_calloc(size_t nmemb, size_t size);

The calloc() function allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.  The  memory is set to zero.  If nmemb or size is 0, then calloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().  If the multiplication of nmemb and size would result  in  integer  overflow,  then calloc()  returns an error.  By contrast, an integer overflow would not be detected in the following call to malloc(), with the result that an incorrectly sized block of memory would be allocated:

####char	*ft_strdup(const char *s);
The strdup() function returns a pointer to a new string which is a duplicate of the string s.  Memory for the new string is obtained with malloc(3), and can be freed with free(3).

####char	*ft_substr(char const *s, unsigned int start, size_t len);
Allocates (with malloc(3)) and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’

####char	*ft_strjoin(char const *s1, char const*s2);
Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.

####char	**ft_split(char const *s, char c);
Allocates (with malloc(3)) and returns an array of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must be ended by a NULL pointer.

####char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
Applies the function ’f’ to each character of the
string ’s’ to create a new string (with malloc(3))
resulting from successive applications of ’f’.

####void	ft_putchar_fd(char c, int fd);

####void	ft_putstr_fd(char *s, int fd);

####void	ft_putendl_fd(char *s, int fd);
Outputs the string ’s’ to the given file
descriptor, followed by a newline

####void	ft_putnbr_fd(int n, int fd);
Outputs the integer ’n’ to the given file
descriptor.
