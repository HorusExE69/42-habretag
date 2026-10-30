/*
** make -C ../printf
** cc -Wall -Wextra -Werror test_printf.c -L../printf -lftprintf -o test_printf
** ./test_printf
**
** Bonus :
**     make -C ../printf bonus
**     cc -Wall -Wextra -Werror -DBONUS test_printf.c -L../printf -lftprintf -o test_printf
**     ./test_printf
**
** Options :
**     ./test_printf -v     affiche aussi les tests réussis
**     valgrind ./test_printf   vérifie les erreurs mémoire
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdint.h>

#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wunknown-warning-option"

int	ft_printf(const char *format, ...);

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define RESET "\033[0m"
#define BUF_SIZE 8192
#define MAX_SHOWN 8

/* ------------------------------------------------------------------ */
/* Capture de la sortie standard dans un buffer, grâce à un pipe      */
/* ------------------------------------------------------------------ */

static int		g_pipe[2];
static int		g_saved_stdout;
static char		g_out1[BUF_SIZE];
static char		g_out2[BUF_SIZE];
static int		g_len1;
static int		g_len2;
static int		g_ret1;
static int		g_ret2;

static void	capture_begin(void)
{
	fflush(stdout);
	if (pipe(g_pipe) != 0)
		return ;
	g_saved_stdout = dup(1);
	dup2(g_pipe[1], 1);
	close(g_pipe[1]);
}

static int	capture_end(char *buf)
{
	int		total;
	ssize_t	n;

	fflush(stdout);
	dup2(g_saved_stdout, 1);
	close(g_saved_stdout);
	total = 0;
	while (total < BUF_SIZE - 1)
	{
		n = read(g_pipe[0], buf + total, BUF_SIZE - 1 - total);
		if (n <= 0)
			break ;
		total += (int)n;
	}
	buf[total] = '\0';
	close(g_pipe[0]);
	return (total);
}

/* ------------------------------------------------------------------ */
/* Comptage et affichage des résultats                                */
/* ------------------------------------------------------------------ */

static int			g_verbose = 0;
static int			g_sec_ok;
static int			g_sec_ko;
static int			g_total_ok = 0;
static int			g_total_ko = 0;
static const char	*g_sec_name;

static void	show(const char *buf, int len)
{
	int				i;
	unsigned char	c;

	putchar('[');
	for (i = 0; i < len && i < 200; i++)
	{
		c = (unsigned char)buf[i];
		if (c == '\n')
			printf("\\n");
		else if (c == '\t')
			printf("\\t");
		else if (c == '\0')
			printf(DIM "\\0" RESET);
		else if (c < 32 || c >= 127)
			printf(DIM "\\x%02x" RESET, c);
		else
			putchar(c);
	}
	if (len > 200)
		printf("... (%d octets)", len);
	putchar(']');
}

static void	section(const char *name)
{
	g_sec_name = name;
	g_sec_ok = 0;
	g_sec_ko = 0;
	printf(BOLD "%s" RESET "\n", name);
}

static void	section_end(void)
{
	if (g_sec_ko == 0)
		printf("  " GREEN "OK" RESET " %d/%d\n\n", g_sec_ok, g_sec_ok);
	else
		printf("  " RED "KO" RESET " %d/%d réussis\n\n",
			g_sec_ok, g_sec_ok + g_sec_ko);
}

static void	report(const char *label)
{
	int	ok;

	ok = (g_ret1 == g_ret2 && g_len1 == g_len2
			&& memcmp(g_out1, g_out2, (size_t)g_len1) == 0);
	if (ok)
	{
		g_sec_ok++;
		g_total_ok++;
		if (g_verbose)
			printf("  " GREEN "OK" RESET " %s\n", label);
		return ;
	}
	g_sec_ko++;
	g_total_ko++;
	if (g_sec_ko > MAX_SHOWN && !g_verbose)
	{
		if (g_sec_ko == MAX_SHOWN + 1)
			printf("  (autres erreurs de cette section masquées, -v pour tout voir)\n");
		return ;
	}
	printf("  " RED "KO" RESET " %s\n", label);
	printf("     printf    ");
	show(g_out1, g_len1);
	printf(" ret %d\n     ft_printf ", g_ret1);
	show(g_out2, g_len2);
	printf(" ret %d\n", g_ret2);
}

#define T(...) do { \
	capture_begin(); \
	g_ret1 = printf(__VA_ARGS__); \
	g_len1 = capture_end(g_out1); \
	capture_begin(); \
	g_ret2 = ft_printf(__VA_ARGS__); \
	g_len2 = capture_end(g_out2); \
	report(#__VA_ARGS__); \
} while (0)

#define TV(label, fmt, arg) do { \
	capture_begin(); \
	g_ret1 = printf(fmt, arg); \
	g_len1 = capture_end(g_out1); \
	capture_begin(); \
	g_ret2 = ft_printf(fmt, arg); \
	g_len2 = capture_end(g_out2); \
	report(label); \
} while (0)

/* ------------------------------------------------------------------ */
/* Partie obligatoire                                                 */
/* ------------------------------------------------------------------ */

static void	test_text(void)
{
	section("Texte simple et %%");
	T("hello world");
	T("a");
	T("\n");
	T("tab\there\nnewline");
	T("%%");
	T("%%%%");
	T("100%% garanti");
	T("%%c %%s %%d");
	T("%d%%", 42);
	T("%%%d%%", 42);
	T("%s", "");
	T("début %s fin", "");
	section_end();
	section("Format vide");
	capture_begin();
	g_ret2 = ft_printf("");
	g_len2 = capture_end(g_out2);
	g_ret1 = 0;
	g_len1 = 0;
	report("ft_printf(\"\") doit renvoyer 0 et ne rien écrire");
	section_end();
}

static void	test_c(void)
{
	char	c;

	section("%c");
	T("%c", 'a');
	T("%c%c%c", 'a', 'b', 'c');
	T("[%c]", ' ');
	T("[%c]", '\0');
	T("%c%c%c", '\0', 'x', '\0');
	T("%c", '%');
	T("%c", '\n');
	T("%c", 127);
	T("%c", 255);
	T("%c", 128);
	T("%c", 256);
	T("%c", -1);
	T("%c|%c", '0', '9');
	c = 0;
	while (c < 127)
	{
		TV("%c sur tous les ASCII", "%c", (int)c);
		c++;
	}
	section_end();
}

static void	test_s(void)
{
	char	longstr[2001];
	char	*null_str;

	null_str = NULL;
	memset(longstr, 'x', 2000);
	longstr[2000] = '\0';
	section("%s");
	T("%s", "hello");
	T("%s", "");
	T("[%s]", "");
	T("%s%s%s", "a", "", "c");
	T("%s", null_str);
	T("[%s] [%s]", null_str, "ok");
	T("%s", "%d %s %%");
	T("%s", "\t\n\v");
	T("%s", "\200\377 octets hauts");
	T("%s", longstr);
	T("%s %s %s %s %s", "un", "deux", "trois", "quatre", "cinq");
	section_end();
}

static void	test_di(void)
{
	const int	vals[] = {0, 1, -1, 9, -9, 10, -10, 42, -42, 99, 100,
		12345, -12345, 2147483647, -2147483648, 2147483646, -2147483647};
	size_t		k;

	section("%d %i");
	for (k = 0; k < sizeof(vals) / sizeof(*vals); k++)
	{
		TV("%d", "%d", vals[k]);
		TV("%i", "%i", vals[k]);
		TV("[%d]", "[%d]", vals[k]);
	}
	T("%d %i", INT_MAX, INT_MIN);
	T("%d%d%d", 1, 2, 3);
	T("%d %d %d %d", 0, -0, +0, 00);
	T("%i", 0x7f);
	T("%d", (char)-1);
	T("%d", (short)-32768);
	section_end();
}

static void	test_u(void)
{
	const unsigned int	vals[] = {0, 1, 9, 10, 42, 100, 4294967295u,
		2147483648u, 2147483647u, 4294967294u};
	size_t				k;

	section("%u");
	for (k = 0; k < sizeof(vals) / sizeof(*vals); k++)
		TV("%u", "%u", vals[k]);
	T("%u", -1);
	T("%u", -42);
	T("%u", INT_MIN);
	T("%u %u", 0, UINT_MAX);
	section_end();
}

static void	test_xX(void)
{
	const unsigned int	vals[] = {0, 1, 9, 10, 15, 16, 255, 256, 3054,
		0xabcdef, 0xDEADBEEF, 4294967295u, 2147483648u};
	size_t				k;

	section("%x %X");
	for (k = 0; k < sizeof(vals) / sizeof(*vals); k++)
	{
		TV("%x", "%x", vals[k]);
		TV("%X", "%X", vals[k]);
	}
	T("%x %X", -1, -1);
	T("%x %X", INT_MIN, INT_MIN);
	T("%x", -42);
	T("%x%X%x", 10, 11, 12);
	section_end();
}

static void	test_p(void)
{
	int		x;
	char	s[4];
	void	*null_ptr;

	null_ptr = NULL;
	section("%p");
	T("%p", (void *)&x);
	T("%p", (void *)s);
	T("%p %p", (void *)&s[0], (void *)&s[1]);
	T("%p", null_ptr);
	T("[%p] [%p]", null_ptr, (void *)&x);
	T("%p", (void *)1);
	T("%p", (void *)15);
	T("%p", (void *)16);
	T("%p", (void *)0xabcdef);
	T("%p", (void *)ULONG_MAX);
	T("%p", (void *)LONG_MIN);
	T("%p", (void *)LONG_MAX);
	T("%p", (void *)(uintptr_t)UINT_MAX);
	T("%p", (void *)test_p);
	section_end();
}

static void	test_mixed(void)
{
	int	x;

	section("Mélanges et nombreux arguments");
	T("%c%s%d%i%u%x%X%%", 'a', "bc", 1, 2, 3u, 255, 255);
	T("%d %s %c %x %u %p %%", 7, "mix", 'z', 3054, 12u, (void *)&x);
	T("[%s|%d|%c]", "", 0, 'x');
	T("%s%d%s%d", "a", 1, "b", 2);
	T("Je m'appelle %s, j'ai %d ans et %u%% de batterie", "Hans", 20, 85u);
	T("%d %d %d %d %d %d %d %d %d %d", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	T("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20);
	T("%s%s%s%s%s%s%s%s", "a", "b", "c", "d", "e", "f", "g", "h");
	T("%x %X %u %d %i %c %s %p", 0, 0, 0u, 0, 0, '0', "0", (void *)0);
	T("%c %c %c %c %c", 'H', 'e', 'l', 'l', 'o');
	T("%%d %d %%s %s", 1, "deux");
	section_end();
}

/* ------------------------------------------------------------------ */
/* 								BONUS		        				  */
/* ------------------------------------------------------------------ */

#ifdef BONUS

static const char	*g_widths[] = {"", "1", "2", "5", "12"};
static const char	*g_precs[] = {"", ".", ".0", ".1", ".3", ".6", ".12"};

#define NB_WIDTHS 5
#define NB_PRECS 7

static void	build(char *fmt, const char *allowed, int mask,
	const char *spec[3])
{
	int	i;
	int	n;

	n = 0;
	fmt[n++] = '%';
	for (i = 0; allowed[i]; i++)
		if (mask & (1 << i))
			fmt[n++] = allowed[i];
	strcpy(fmt + n, spec[0]);
	strcat(fmt, spec[1]);
	strcat(fmt, spec[2]);
}

#define COMBOS(allowed, use_prec, conv, values, nbval) do { \
	char		fmt_[32]; \
	char		label_[96]; \
	const char	*spec_[3]; \
	int			m_, w_, p_; \
	size_t		v_; \
	for (m_ = 0; m_ < (1 << (int)strlen(allowed)); m_++) \
	for (w_ = 0; w_ < NB_WIDTHS; w_++) \
	for (p_ = 0; p_ < ((use_prec) ? NB_PRECS : 1); p_++) \
	{ \
		spec_[0] = g_widths[w_]; \
		spec_[1] = g_precs[p_]; \
		spec_[2] = conv; \
		build(fmt_, allowed, m_, spec_); \
		strcat(fmt_, "|"); \
		for (v_ = 0; v_ < (nbval); v_++) \
		{ \
			snprintf(label_, sizeof(label_), "\"%s\" (valeur n°%zu)", \
				fmt_, v_); \
			TV(label_, fmt_, (values)[v_]); \
		} \
	} \
} while (0)

static void	test_bonus_combos(void)
{
	const int			ints[] = {0, 1, -1, 7, -7, 42, -42, 12345,
		-12345, INT_MAX, INT_MIN};
	const unsigned int	uints[] = {0, 1, 7, 42, 255, 3054, 0xDEADBEEF,
		UINT_MAX};
	const char			*strs[] = {"", "a", "abc", "hello world"};
	const int			chars[] = {'a', 'Z', '%', '\0'};
	int					x;
	void				*ptrs[3];

	ptrs[0] = &x;
	ptrs[1] = (void *)1;
	ptrs[2] = (void *)ULONG_MAX;
	section("Bonus : %d avec - 0 + espace, largeur, précision");
	COMBOS("-0+ ", 1, "d", ints, sizeof(ints) / sizeof(*ints));
	section_end();
	section("Bonus : %i avec - 0 + espace, largeur, précision");
	COMBOS("-0+ ", 1, "i", ints, sizeof(ints) / sizeof(*ints));
	section_end();
	section("Bonus : %u avec - 0, largeur, précision");
	COMBOS("-0", 1, "u", uints, sizeof(uints) / sizeof(*uints));
	section_end();
	section("Bonus : %x avec - 0 #, largeur, précision");
	COMBOS("-0#", 1, "x", uints, sizeof(uints) / sizeof(*uints));
	section_end();
	section("Bonus : %X avec - 0 #, largeur, précision");
	COMBOS("-0#", 1, "X", uints, sizeof(uints) / sizeof(*uints));
	section_end();
	section("Bonus : %s avec -, largeur, précision");
	COMBOS("-", 1, "s", strs, sizeof(strs) / sizeof(*strs));
	section_end();
	section("Bonus : %c avec -, largeur");
	COMBOS("-", 0, "c", chars, sizeof(chars) / sizeof(*chars));
	section_end();
	section("Bonus : %p avec -, largeur");
	COMBOS("-", 0, "p", ptrs, sizeof(ptrs) / sizeof(*ptrs));
	section_end();
}

static void	test_bonus_tricky(void)
{
	char	*null_str;
	void	*null_ptr;
	int		x;

	null_str = NULL;
	null_ptr = NULL;
	section("Bonus : cas piégeux écrits à la main");
	T("%05d", -42);
	T("%-05d|", -42);
	T("%+05d", 42);
	T("% 05d", 42);
	T("% +d", 42);
	T("%+ d", 42);
	T("%+d %+d %+d", 0, 1, -1);
	T("% d % d % d", 0, 1, -1);
	T("%.0d|%.d|%5.0d|%-5.0d|", 0, 0, 0, 0);
	T("%+.0d|% .0d|", 0, 0);
	T("%08.3d|%-08.3d|", 42, 42);
	T("%.10d", INT_MIN);
	T("%20d|%-20d|%020d", INT_MIN, INT_MIN, INT_MIN);
	T("%1d|%1d", 12345, -12345);
	T("%#x|%#X|%#x", 0, 0, 1);
	T("%#5x|%#-5x|%#05x", 0, 0, 0);
	T("%#.0x|%.0x|%#5.0x|", 0, 0, 0);
	T("%#.3x|%#08x|%#08.3x", 1, 255, 255);
	T("%#x", UINT_MAX);
	T("%.0u|%5.0u|%-5.0u|", 0, 0, 0);
	T("%010u|%-10u|%.10u", UINT_MAX, UINT_MAX, 42u);
	T("%.0s|%.s|%.1s|%.10s", "abc", "abc", "abc", "abc");
	T("%5.2s|%-5.2s|%2.5s|", "hello", "hello", "hello");
	T("%s|%10s|%-10s|%.6s|", null_str, null_str, null_str, null_str);
	T("%.3s|%10.3s|%.0s|", null_str, null_str, null_str);
	T("%5c|%-5c|%1c|", 'a', 'b', 'c');
	T("%5c|%-5c|", '\0', '\0');
	T("%20p|%-20p|", (void *)&x, (void *)&x);
	T("%p|%10p|%-10p|%1p|", null_ptr, null_ptr, null_ptr, null_ptr);
	T("%3p|", (void *)1);
	T("%-+08.3d|%#-08.3x|% 12.5i|", 7, 0xabc, -99);
	T("%--5d|%00005d|%++d|%  d", 1, 2, 3, 4);
	T("%-0-0-5d|", 42);
	T("[%100d]", 1);
	T("[%-100s]", "fin");
	T("%5%|%-5%|%05%|");
	T("%d %5s %-3c %#x %+.2d %%", 1, "ab", 'z', 26, 3);
	section_end();
}

#endif

int	main(int argc, char **argv)
{
	if (argc > 1 && strcmp(argv[1], "-v") == 0)
		g_verbose = 1;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf(BOLD "=== Partie obligatoire ===" RESET "\n\n");
	test_text();
	test_c();
	test_s();
	test_di();
	test_u();
	test_xX();
	test_p();
	test_mixed();
#ifdef BONUS
	printf(BOLD "=== Bonus ===" RESET "\n\n");
	test_bonus_combos();
	test_bonus_tricky();
#else
	printf(DIM "Bonus non testés (compiler avec -DBONUS)" RESET "\n\n");
#endif
	if (g_total_ko == 0)
		printf(BOLD GREEN "Tout est bon : %d/%d" RESET "\n", g_total_ok,
			g_total_ok);
	else
		printf(BOLD RED "%d test(s) KO sur %d" RESET "\n", g_total_ko,
			g_total_ok + g_total_ko);
	return (g_total_ko != 0);
}
