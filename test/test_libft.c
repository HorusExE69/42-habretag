/*
** test_libft.c : tests de la libft (fichier à NE PAS rendre)
**
** Ce dossier doit être à côté du dossier libft :
**     hans/
**       libft/         (le projet)
**       libft_tests/   (ce fichier)
**
** Compilation et lancement, depuis libft_tests :
**     make -C ../libft bonus
**     cc -Wall -Wextra -Werror test_libft.c -I../libft -L../libft -lft -o test_libft
**     ./test_libft
**
** Vérifier les fuites mémoire :
**     Linux : valgrind --leak-check=full ./test_libft
**     Mac   : leaks --atExit -- ./test_libft
**
** Bonus, Linux uniquement : simule un malloc qui échoue au milieu de ft_lstmap
** et ft_split pour vérifier que tout est libéré :
**     cc -Wall -Wextra -Werror -DTEST_MALLOC_FAIL -Wl,--wrap=malloc \
**        test_libft.c -I../libft -L../libft -lft -o test_libft
**     valgrind --leak-check=full ./test_libft
*/

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

/* ------------------------------------------------------------------ */
/* Mini framework de test                                              */
/* ------------------------------------------------------------------ */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

static int			g_fn_ok = 0;
static int			g_fn_ko = 0;
static int			g_fails = 0;
static const char	*g_name = "";

static void	start(const char *name)
{
	g_name = name;
	g_fails = 0;
}

static void	check(int ok, const char *expr, int line)
{
	if (ok)
		return ;
	if (g_fails < 3)
		printf("    " RED "KO" RESET " ligne %d : %s\n", line, expr);
	else if (g_fails == 3)
		printf("    (autres erreurs masquées)\n");
	g_fails++;
}

#define CHECK(cond) check((cond) != 0, #cond, __LINE__)

static void	end(void)
{
	printf("%-18s %s\n", g_name,
		g_fails ? RED "KO" RESET : GREEN "OK" RESET);
	if (g_fails)
		g_fn_ko++;
	else
		g_fn_ok++;
}

/* compare une chaîne allouée au résultat attendu, puis la libère */
static int	str_is(char *got, const char *expected)
{
	int	ok;

	ok = (got != NULL && strcmp(got, expected) == 0);
	if (!ok)
		printf("    obtenu [%s] attendu [%s]\n", got ? got : "NULL", expected);
	free(got);
	return (ok);
}

static int	same_sign(int a, int b)
{
	return ((a > 0) == (b > 0) && (a < 0) == (b < 0));
}

/* ------------------------------------------------------------------ */
/* Implémentations de référence (absentes de la libc Linux)            */
/* ------------------------------------------------------------------ */

static size_t	ref_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	n;

	len = strlen(src);
	if (size)
	{
		n = (len < size - 1) ? len : size - 1;
		memcpy(dst, src, n);
		dst[n] = '\0';
	}
	return (len);
}

static size_t	ref_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;

	dlen = 0;
	while (dlen < size && dst[dlen])
		dlen++;
	if (dlen == size)
		return (size + strlen(src));
	return (dlen + ref_strlcpy(dst + dlen, src, size - dlen));
}

static char	*ref_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;

	nlen = strlen(needle);
	if (nlen == 0)
		return ((char *)hay);
	i = 0;
	while (hay[i] && i + nlen <= len)
	{
		if (strncmp(hay + i, needle, nlen) == 0)
			return ((char *)hay + i);
		i++;
	}
	return (NULL);
}

/* lit ce qu'une fonction ft_put*_fd écrit, grâce à un pipe */
static char	g_out[256];

static void	capture(void (*fn)(int))
{
	int		fds[2];
	ssize_t	n;

	memset(g_out, 0, sizeof(g_out));
	if (pipe(fds) != 0)
		return ;
	fn(fds[1]);
	close(fds[1]);
	n = read(fds[0], g_out, sizeof(g_out) - 1);
	if (n < 0)
		g_out[0] = '\0';
	close(fds[0]);
}

/* ------------------------------------------------------------------ */
/* Partie 1                                                            */
/* ------------------------------------------------------------------ */

static void	test_ctype(void)
{
	int	c;

	start("ft_isalpha");
	for (c = -1; c < 256; c++)
		CHECK(!ft_isalpha(c) == !isalpha(c));
	end();
	start("ft_isdigit");
	for (c = -1; c < 256; c++)
		CHECK(!ft_isdigit(c) == !isdigit(c));
	end();
	start("ft_isalnum");
	for (c = -1; c < 256; c++)
		CHECK(!ft_isalnum(c) == !isalnum(c));
	end();
	start("ft_isascii");
	for (c = -1; c < 256; c++)
		CHECK(!ft_isascii(c) == !(c >= 0 && c <= 127));
	end();
	start("ft_isprint");
	for (c = -1; c < 256; c++)
		CHECK(!ft_isprint(c) == !isprint(c));
	end();
	start("ft_toupper");
	for (c = -1; c < 256; c++)
		CHECK(ft_toupper(c) == toupper(c));
	end();
	start("ft_tolower");
	for (c = -1; c < 256; c++)
		CHECK(ft_tolower(c) == tolower(c));
	end();
}

static void	test_mem(void)
{
	char		a[64];
	char		b[64];
	const char	*src = "0123456789abcdefghij";
	size_t		n;
	int			c;

	start("ft_memset");
	memset(a, 'z', 64);
	memset(b, 'z', 64);
	CHECK(ft_memset(b, 'x', 10) == b);
	memset(a, 'x', 10);
	CHECK(memcmp(a, b, 64) == 0);
	memset(a, 300, 5);
	ft_memset(b, 300, 5);
	CHECK(memcmp(a, b, 64) == 0);
	CHECK(ft_memset(b, 'q', 0) == b && memcmp(a, b, 64) == 0);
	end();

	start("ft_bzero");
	memset(a, 'z', 64);
	memset(b, 'z', 64);
	memset(a, 0, 7);
	ft_bzero(b, 7);
	CHECK(memcmp(a, b, 64) == 0);
	ft_bzero(b, 0);
	CHECK(memcmp(a, b, 64) == 0);
	end();

	start("ft_memcpy");
	memset(a, '.', 64);
	memset(b, '.', 64);
	CHECK(ft_memcpy(b, src, 15) == b);
	memcpy(a, src, 15);
	CHECK(memcmp(a, b, 64) == 0);
	CHECK(ft_memcpy(b, src, 0) == b && memcmp(a, b, 64) == 0);
	end();

	start("ft_memmove");
	for (n = 0; n < 8; n++)
	{
		strcpy(a, src);
		strcpy(b, src);
		memmove(a + n, a + 3, 10);
		CHECK(ft_memmove(b + n, b + 3, 10) == b + n);
		CHECK(memcmp(a, b, 21) == 0);
	}
	strcpy(b, src);
	CHECK(ft_memmove(b, b, 5) == b && strcmp(b, src) == 0);
	end();

	start("ft_memchr");
	for (c = -300; c < 300; c++)
		CHECK(ft_memchr(src, c, 21) == memchr(src, c, 21));
	CHECK(ft_memchr(src, 'a', 5) == NULL);
	CHECK(ft_memchr("ab\0cd", 'c', 5) == memchr("ab\0cd", 'c', 5));
	end();

	start("ft_memcmp");
	CHECK(ft_memcmp("abc", "abc", 3) == 0);
	CHECK(same_sign(ft_memcmp("abc", "abd", 3), memcmp("abc", "abd", 3)));
	CHECK(same_sign(ft_memcmp("abd", "abc", 3), memcmp("abd", "abc", 3)));
	CHECK(ft_memcmp("abc", "xyz", 0) == 0);
	CHECK(same_sign(ft_memcmp("a\200", "a\0", 2), memcmp("a\200", "a\0", 2)));
	CHECK(same_sign(ft_memcmp("ab\0x", "ab\0y", 4), memcmp("ab\0x", "ab\0y", 4)));
	end();
}

static void	test_str(void)
{
	const char	*strs[] = {"", "a", "hello world", "\200\377abc", "aaba"};
	const char	*pairs[][2] = {{"abc", "abd"}, {"abc", "abc"}, {"", ""},
		{"a", ""}, {"", "a"}, {"\200", "\0"}, {"abc", "ab"},
		{"test\200", "test\0"}};
	char		d1[20];
	char		d2[20];
	size_t		k;
	size_t		n;
	int			c;
	char		*dup;

	start("ft_strlen");
	for (k = 0; k < 5; k++)
		CHECK(ft_strlen(strs[k]) == strlen(strs[k]));
	end();

	start("ft_strchr");
	for (k = 0; k < 5; k++)
		for (c = -300; c < 300; c++)
			CHECK(ft_strchr(strs[k], c) == strchr(strs[k], c));
	end();

	start("ft_strrchr");
	for (k = 0; k < 5; k++)
		for (c = -300; c < 300; c++)
			CHECK(ft_strrchr(strs[k], c) == strrchr(strs[k], c));
	end();

	start("ft_strncmp");
	for (k = 0; k < 8; k++)
		for (n = 0; n < 8; n++)
			CHECK(same_sign(ft_strncmp(pairs[k][0], pairs[k][1], n),
					strncmp(pairs[k][0], pairs[k][1], n)));
	end();

	start("ft_strlcpy");
	for (n = 0; n < 15; n++)
	{
		memset(d1, 0, 20);
		memset(d2, 0, 20);
		strcpy(d1, "bonjour");
		strcpy(d2, "bonjour");
		CHECK(ft_strlcpy(d2, "cavapas", n) == ref_strlcpy(d1, "cavapas", n));
		CHECK(memcmp(d1, d2, 20) == 0);
	}
	CHECK(ft_strlcpy(d2, "", 5) == 0 && d2[0] == '\0');
	end();

	start("ft_strlcat");
	for (n = 0; n < 18; n++)
	{
		memset(d1, 0, 20);
		memset(d2, 0, 20);
		strcpy(d1, "bonjour");
		strcpy(d2, "bonjour");
		CHECK(ft_strlcat(d2, "cavapas", n) == ref_strlcat(d1, "cavapas", n));
		CHECK(memcmp(d1, d2, 20) == 0);
	}
	end();

	start("ft_strnstr");
	{
		const char	*hay = "aaabcabcd";
		const char	*nd[] = {"", "abcd", "a", "x", "aabc", "cd",
			"aaabcabcdz", "aaabcabcd"};

		for (k = 0; k < 8; k++)
			for (n = 0; n < 12; n++)
				CHECK(ft_strnstr(hay, nd[k], n)
					== ref_strnstr(hay, nd[k], n));
	}
	end();

	start("ft_atoi");
	{
		const char	*in[] = {"42", "  -42", "\t\n\v\f\r 12abc", "+-1",
			"--1", "+7", "2147483647", "-2147483648", "", "abc",
			"- 5", "0012", "   +0", "1 2"};

		for (k = 0; k < 14; k++)
			CHECK(ft_atoi(in[k]) == atoi(in[k]));
	}
	end();

	start("ft_strdup");
	for (k = 0; k < 5; k++)
	{
		dup = ft_strdup(strs[k]);
		CHECK(dup != NULL && dup != strs[k] && strcmp(dup, strs[k]) == 0);
		free(dup);
	}
	end();
}

static void	test_calloc(void)
{
	unsigned char	*p;
	int				i;
	int				zero;

	start("ft_calloc");
	p = ft_calloc(10, 4);
	CHECK(p != NULL);
	zero = 1;
	for (i = 0; p && i < 40; i++)
		if (p[i] != 0)
			zero = 0;
	CHECK(zero);
	free(p);
	p = ft_calloc(SIZE_MAX, 2);
	CHECK(p == NULL);
	free(p);
	p = ft_calloc(0, 5);
	free(p);
	p = ft_calloc(5, 0);
	free(p);
	end();
}

/* ------------------------------------------------------------------ */
/* Partie 2                                                            */
/* ------------------------------------------------------------------ */

static int	split_is(char **tab, const char **expected)
{
	int	ok;
	int	i;

	if (!tab)
		return (0);
	ok = 1;
	for (i = 0; expected[i]; i++)
		if (!tab[i] || strcmp(tab[i], expected[i]) != 0)
			ok = 0;
	if (tab[i] != NULL)
		ok = 0;
	for (i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
	return (ok);
}

static char	map_upper_even(unsigned int i, char c)
{
	if (i % 2 == 0)
		return ((char)toupper((unsigned char)c));
	return (c);
}

static void	iter_upper_even(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = (char)toupper((unsigned char)*c);
}

static void	put_char(int fd)
{
	ft_putchar_fd('a', fd);
	ft_putchar_fd('\n', fd);
}

static void	put_str(int fd)
{
	ft_putstr_fd("hello", fd);
	ft_putstr_fd("", fd);
	ft_putstr_fd(" 42", fd);
}

static void	put_endl(int fd)
{
	ft_putendl_fd("hi", fd);
	ft_putendl_fd("", fd);
}

static void	put_nbr(int fd)
{
	const int	nb[] = {0, 7, -7, 42, -42, 100, INT_MAX, INT_MIN};
	int			k;

	for (k = 0; k < 8; k++)
	{
		ft_putnbr_fd(nb[k], fd);
		ft_putchar_fd(' ', fd);
	}
}

static void	test_part2(void)
{
	char	s[16];

	start("ft_substr");
	CHECK(str_is(ft_substr("hello", 1, 3), "ell"));
	CHECK(str_is(ft_substr("hello", 0, 100), "hello"));
	CHECK(str_is(ft_substr("hello", 4, 1), "o"));
	CHECK(str_is(ft_substr("hello", 5, 2), ""));
	CHECK(str_is(ft_substr("hello", 400, 2), ""));
	CHECK(str_is(ft_substr("hello", 2, 0), ""));
	CHECK(str_is(ft_substr("", 0, 5), ""));
	end();

	start("ft_strjoin");
	CHECK(str_is(ft_strjoin("ab", "cd"), "abcd"));
	CHECK(str_is(ft_strjoin("", "cd"), "cd"));
	CHECK(str_is(ft_strjoin("ab", ""), "ab"));
	CHECK(str_is(ft_strjoin("", ""), ""));
	end();

	start("ft_strtrim");
	CHECK(str_is(ft_strtrim("  hello  ", " "), "hello"));
	CHECK(str_is(ft_strtrim("   ", " "), ""));
	CHECK(str_is(ft_strtrim("", " "), ""));
	CHECK(str_is(ft_strtrim("hello", ""), "hello"));
	CHECK(str_is(ft_strtrim("xxhixx", "x"), "hi"));
	CHECK(str_is(ft_strtrim("abcba", "ab"), "c"));
	CHECK(str_is(ft_strtrim("  a b  ", " "), "a b"));
	end();

	start("ft_split");
	{
		const char	*e1[] = {"hello", "fellow", "students", NULL};
		const char	*e2[] = {NULL};
		const char	*e3[] = {"abc", NULL};
		const char	*e4[] = {"a", "b", "c", NULL};

		CHECK(split_is(ft_split("*hello*fellow***students*", '*'), e1));
		CHECK(split_is(ft_split("", '*'), e2));
		CHECK(split_is(ft_split("****", '*'), e2));
		CHECK(split_is(ft_split("abc", '*'), e3));
		CHECK(split_is(ft_split("abc", '\0'), e3));
		CHECK(split_is(ft_split("  a b   c ", ' '), e4));
	}
	end();

	start("ft_itoa");
	CHECK(str_is(ft_itoa(0), "0"));
	CHECK(str_is(ft_itoa(9), "9"));
	CHECK(str_is(ft_itoa(-9), "-9"));
	CHECK(str_is(ft_itoa(10), "10"));
	CHECK(str_is(ft_itoa(-1234), "-1234"));
	CHECK(str_is(ft_itoa(INT_MAX), "2147483647"));
	CHECK(str_is(ft_itoa(INT_MIN), "-2147483648"));
	end();

	start("ft_strmapi");
	CHECK(str_is(ft_strmapi("abcdef", map_upper_even), "AbCdEf"));
	CHECK(str_is(ft_strmapi("", map_upper_even), ""));
	end();

	start("ft_striteri");
	strcpy(s, "abcdef");
	ft_striteri(s, iter_upper_even);
	CHECK(strcmp(s, "AbCdEf") == 0);
	s[0] = '\0';
	ft_striteri(s, iter_upper_even);
	CHECK(s[0] == '\0');
	end();

	start("ft_putchar_fd");
	capture(put_char);
	CHECK(strcmp(g_out, "a\n") == 0);
	end();

	start("ft_putstr_fd");
	capture(put_str);
	CHECK(strcmp(g_out, "hello 42") == 0);
	end();

	start("ft_putendl_fd");
	capture(put_endl);
	CHECK(strcmp(g_out, "hi\n\n") == 0);
	end();

	start("ft_putnbr_fd");
	capture(put_nbr);
	CHECK(strcmp(g_out,
			"0 7 -7 42 -42 100 2147483647 -2147483648 ") == 0);
	if (strcmp(g_out, "0 7 -7 42 -42 100 2147483647 -2147483648 ") != 0)
		printf("    obtenu [%s]\n", g_out);
	end();
}

/* ------------------------------------------------------------------ */
/* Bonus                                                               */
/* ------------------------------------------------------------------ */

static int	g_dels = 0;
static int	g_iters = 0;

static void	del_count(void *content)
{
	g_dels++;
	free(content);
}

static void	iter_count(void *content)
{
	(void)content;
	g_iters++;
}

static void	iter_cap(void *content)
{
	char	*str;

	str = content;
	str[0] = (char)toupper((unsigned char)str[0]);
}

static void	*map_upper(void *content)
{
	char	*copy;
	int		i;

	copy = ft_strdup(content);
	for (i = 0; copy && copy[i]; i++)
		copy[i] = (char)toupper((unsigned char)copy[i]);
	return (copy);
}

static t_list	*make_list(void)
{
	const char	*words[] = {"abc", "hi", "ok", "zz"};
	t_list		*lst;
	int			i;

	lst = NULL;
	for (i = 0; i < 4; i++)
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(words[i])));
	return (lst);
}

static void	test_bonus(void)
{
	t_list	*lst;
	t_list	*a;
	t_list	*b;
	t_list	*c;
	t_list	*map;
	int		x;

	start("ft_lstnew");
	a = ft_lstnew(&x);
	CHECK(a && a->content == &x && a->next == NULL);
	free(a);
	a = ft_lstnew(NULL);
	CHECK(a && a->content == NULL && a->next == NULL);
	free(a);
	end();

	lst = NULL;
	a = ft_lstnew(ft_strdup("a"));
	b = ft_lstnew(ft_strdup("b"));
	c = ft_lstnew(ft_strdup("c"));

	start("ft_lstadd_front");
	ft_lstadd_front(&lst, b);
	CHECK(lst == b && b->next == NULL);
	ft_lstadd_front(&lst, a);
	CHECK(lst == a && a->next == b);
	end();

	start("ft_lstadd_back");
	ft_lstadd_back(&lst, c);
	CHECK(b->next == c && c->next == NULL && lst == a);
	map = NULL;
	ft_lstadd_back(&map, ft_lstnew(NULL));
	CHECK(map != NULL && map->next == NULL);
	free(map);
	end();

	start("ft_lstsize");
	CHECK(ft_lstsize(NULL) == 0);
	CHECK(ft_lstsize(lst) == 3);
	CHECK(ft_lstsize(c) == 1);
	end();

	start("ft_lstlast");
	CHECK(ft_lstlast(NULL) == NULL);
	CHECK(ft_lstlast(lst) == c);
	CHECK(ft_lstlast(c) == c);
	end();

	start("ft_lstdelone");
	g_dels = 0;
	b->next = NULL;
	a->next = NULL;
	ft_lstdelone(c, del_count);
	CHECK(g_dels == 1);
	ft_lstdelone(b, del_count);
	ft_lstdelone(a, del_count);
	CHECK(g_dels == 3);
	end();

	start("ft_lstclear");
	lst = make_list();
	g_dels = 0;
	ft_lstclear(&lst, del_count);
	CHECK(lst == NULL && g_dels == 4);
	lst = NULL;
	ft_lstclear(&lst, del_count);
	CHECK(lst == NULL && g_dels == 4);
	end();

	start("ft_lstiter");
	lst = make_list();
	g_iters = 0;
	ft_lstiter(lst, iter_count);
	CHECK(g_iters == 4);
	ft_lstiter(lst, iter_cap);
	CHECK(strcmp(lst->content, "Abc") == 0
		&& strcmp(ft_lstlast(lst)->content, "Zz") == 0);
	ft_lstiter(NULL, iter_count);
	CHECK(g_iters == 4);
	end();

	start("ft_lstmap");
	map = ft_lstmap(lst, map_upper, del_count);
	CHECK(ft_lstsize(map) == 4);
	CHECK(map && strcmp(map->content, "ABC") == 0
		&& strcmp(ft_lstlast(map)->content, "ZZ") == 0);
	CHECK(map != lst && map && map->content != lst->content);
	CHECK(strcmp(lst->content, "Abc") == 0);
	ft_lstclear(&map, del_count);
	CHECK(ft_lstmap(NULL, map_upper, del_count) == NULL);
	ft_lstclear(&lst, del_count);
	end();
}

/* ------------------------------------------------------------------ */
/* Échec de malloc (Linux, avec -DTEST_MALLOC_FAIL -Wl,--wrap=malloc)  */
/* ------------------------------------------------------------------ */

#ifdef TEST_MALLOC_FAIL

void		*__real_malloc(size_t size);
static int	g_fail_at = -1;
static int	g_count = 0;

void	*__wrap_malloc(size_t size)
{
	if (g_fail_at >= 0 && g_count++ == g_fail_at)
		return (NULL);
	return (__real_malloc(size));
}

static void	fail_malloc_at(int n)
{
	g_count = 0;
	g_fail_at = n;
}

static void	test_malloc_fail(void)
{
	t_list	*lst;
	t_list	*map;
	char	**tab;
	int		n;

	printf(BOLD "\nEchecs de malloc simulés" RESET
		" (lancer avec valgrind pour voir les fuites)\n");
	start("ft_split");
	for (n = 0; n < 4; n++)
	{
		fail_malloc_at(n);
		tab = ft_split("aa bb cc", ' ');
		g_fail_at = -1;
		CHECK(tab == NULL);
	}
	end();
	/* allocations de ft_lstmap : f (strdup), maillon, f, maillon...
	** on fait échouer chaque création de maillon (indices impairs) */
	start("ft_lstmap");
	lst = make_list();
	for (n = 1; n < 8; n += 2)
	{
		g_dels = 0;
		fail_malloc_at(n);
		map = ft_lstmap(lst, map_upper, del_count);
		g_fail_at = -1;
		CHECK(map == NULL);
		ft_lstclear(&map, del_count);
	}
	ft_lstclear(&lst, del_count);
	end();
	start("ft_itoa / strdup");
	fail_malloc_at(0);
	CHECK(ft_itoa(42) == NULL);
	fail_malloc_at(0);
	CHECK(ft_strdup("abc") == NULL);
	fail_malloc_at(0);
	CHECK(ft_substr("abc", 0, 2) == NULL);
	fail_malloc_at(0);
	CHECK(ft_strjoin("a", "b") == NULL);
	g_fail_at = -1;
	end();
}
#endif

int	main(void)
{
	printf(BOLD "Partie 1" RESET "\n");
	test_ctype();
	test_mem();
	test_str();
	test_calloc();
	printf(BOLD "\nPartie 2" RESET "\n");
	test_part2();
	printf(BOLD "\nBonus" RESET "\n");
	test_bonus();
#ifdef TEST_MALLOC_FAIL
	test_malloc_fail();
#endif
	printf(BOLD "\nRésultat : %d OK, %d KO" RESET "\n", g_fn_ok, g_fn_ko);
	return (g_fn_ko != 0);
}
