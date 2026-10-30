/*
** cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -I../get_next_line \
**   test_gnl.c ../get_next_line/get_next_line.c \
**   ../get_next_line/get_next_line_utils.c -o test_gnl
** ./test_gnl
**
** Bonus : ajouter -DBONUS et utiliser les fichiers _bonus.c.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#ifdef BONUS
# include "get_next_line_bonus.h"
#else
# include "get_next_line.h"
#endif

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define DIR "gnl_files"

static int	g_ok = 0;
static int	g_ko = 0;

static void	result(const char *name, int ok, const char *detail)
{
	if (ok)
	{
		g_ok++;
		printf("  " GREEN "OK" RESET " %s\n", name);
	}
	else
	{
		g_ko++;
		printf("  " RED "KO" RESET " %s%s%s\n", name,
			detail ? " : " : "", detail ? detail : "");
	}
}

/* ------------------------------------------------------------------ */
/* Création des fichiers de test                                      */
/* ------------------------------------------------------------------ */

static char	*make_content(const char *name, size_t *len)
{
	char	*s;
	size_t	n;
	size_t	i;
	size_t	bs;

	bs = (BUFFER_SIZE > 200000) ? 200000 : (size_t)BUFFER_SIZE;
	s = malloc(4 * bs + 300000);
	n = 0;
	if (!strcmp(name, "vide"))
		;
	else if (!strcmp(name, "un_seul_nl"))
		s[n++] = '\n';
	else if (!strcmp(name, "que_des_nl"))
		while (n < 5)
			s[n++] = '\n';
	else if (!strcmp(name, "un_caractere"))
		s[n++] = 'a';
	else if (!strcmp(name, "sans_nl_final"))
		n = sprintf(s, "abc\ndef\nghi");
	else if (!strcmp(name, "avec_nl_final"))
		n = sprintf(s, "abc\ndef\nghi\n");
	else if (!strcmp(name, "lignes_vides"))
		n = sprintf(s, "\n\na\n\n\nb\n\n");
	else if (!strcmp(name, "ligne_20000"))
	{
		while (n < 20000)
			s[n++] = 'x';
		s[n++] = '\n';
		n += sprintf(s + n, "fin");
	}
	else if (!strcmp(name, "10000_lignes"))
		for (i = 0; i < 10000; i++)
			n += sprintf(s + n, "ligne %zu\n", i);
	else if (!strcmp(name, "taille_buffer"))
	{
		for (i = 0; i + 1 < bs; i++)
			s[n++] = 'a';
		s[n++] = '\n';
		for (i = 0; i < bs; i++)
			s[n++] = 'b';
		s[n++] = '\n';
		for (i = 0; i <= bs; i++)
			s[n++] = 'c';
		s[n++] = '\n';
	}
	else if (!strcmp(name, "caracteres_speciaux"))
		n = sprintf(s, "\t tab\r\n\v\f\nhéllo wörld €\n\x7f\x01\n");
	*len = n;
	return (s);
}

static void	write_file(const char *path, const char *s, size_t len)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || write(fd, s, len) != (ssize_t)len)
		perror(path);
	close(fd);
}

/* ------------------------------------------------------------------ */
/* Vérification : les lignes recollées doivent redonner le fichier    */
/* ------------------------------------------------------------------ */

static const char	*check_fd(int fd, const char *ref, size_t len)
{
	char	*line;
	size_t	pos;
	size_t	l;
	char	*nl;

	pos = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		l = strlen(line);
		nl = strchr(line, '\n');
		if (l == 0)
			return (free(line), "ligne vide renvoyée (\"\" au lieu de NULL ?)");
		if (pos + l > len || memcmp(ref + pos, line, l) != 0)
			return (free(line), "contenu d'une ligne différent du fichier");
		if (nl && nl != line + l - 1)
			return (free(line), "plusieurs \\n dans une même ligne");
		if (!nl && pos + l != len)
			return (free(line), "ligne sans \\n alors que ce n'est pas la fin");
		pos += l;
		free(line);
	}
	if (pos != len)
		return ("NULL renvoyé avant la fin du fichier");
	line = get_next_line(fd);
	if (line != NULL)
	{
		free(line);
		return ("un appel après la fin ne renvoie pas NULL");
	}
	return (NULL);
}

static void	test_files(void)
{
	const char	*names[] = {"vide", "un_seul_nl", "que_des_nl",
		"un_caractere", "sans_nl_final", "avec_nl_final", "lignes_vides",
		"ligne_20000", "10000_lignes", "taille_buffer",
		"caracteres_speciaux", NULL};
	char		path[256];
	char		*content;
	const char	*err;
	size_t		len;
	int			fd;
	int			k;

	printf(BOLD "Fichiers" RESET "\n");
	for (k = 0; names[k]; k++)
	{
		content = make_content(names[k], &len);
		snprintf(path, sizeof(path), DIR "/%s.txt", names[k]);
		write_file(path, content, len);
		fd = open(path, O_RDONLY);
		if (fd < 0)
			result(names[k], 0, "impossible de créer le fichier de test");
		else
		{
			err = check_fd(fd, content, len);
			result(names[k], err == NULL, err);
			close(fd);
		}
		free(content);
	}
}

/* ---------------------------------------------------------------------- */
/* Descripteurs qui ne sont pas des fichiers : pipe, écriture en morceaux */
/* ---------------------------------------------------------------------- */

static void	test_pipe(void)
{
	const char	*msg = "un\ndeux\ntrois sans nl";
	int			p[2];
	pid_t		pid;
	const char	*err;

	printf(BOLD "\nPipe (comme l'entrée standard)" RESET "\n");
	if (pipe(p) != 0)
		return ;
	write(p[1], msg, strlen(msg));
	close(p[1]);
	err = check_fd(p[0], msg, strlen(msg));
	result("tout le texte disponible d'un coup", err == NULL, err);
	close(p[0]);
	if (pipe(p) != 0)
		return ;
	fflush(stdout);
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		write(p[1], "un", 2);
		usleep(100000);
		write(p[1], "\nde", 3);
		usleep(100000);
		write(p[1], "ux\ntrois sans nl", 16);
		close(p[1]);
		_exit(0);
	}
	close(p[1]);
	err = check_fd(p[0], msg, strlen(msg));
	result("texte qui arrive en plusieurs morceaux", err == NULL, err);
	close(p[0]);
	waitpid(pid, NULL, 0);
}

/* ------------------------------------------------------------------ */
/* Erreurs                                                            */
/* ------------------------------------------------------------------ */

static void	test_errors(void)
{
	char	*line;
	int		fd;

	printf(BOLD "\nErreurs" RESET "\n");
	line = get_next_line(-1);
	result("fd = -1 renvoie NULL", line == NULL, NULL);
	free(line);
	line = get_next_line(4242);
	result("fd non ouvert (4242) renvoie NULL", line == NULL, NULL);
	free(line);
	line = get_next_line(1000000);
	result("fd énorme (1000000) renvoie NULL sans planter", line == NULL,
		NULL);
	free(line);
	fd = open(DIR, O_RDONLY);
	line = get_next_line(fd);
	result("lire un dossier (read échoue) renvoie NULL", line == NULL,
		NULL);
	free(line);
	close(fd);
}

/* ------------------------------------------------------------------ */
/* Bonus : plusieurs fd en alternance                                 */
/* ------------------------------------------------------------------ */

#ifdef BONUS

static int	expect(int fd, const char *expected)
{
	char	*line;
	int		ok;

	line = get_next_line(fd);
	if (expected == NULL)
		ok = (line == NULL);
	else
		ok = (line != NULL && strcmp(line, expected) == 0);
	if (!ok)
		printf("    fd %d : obtenu [%s] attendu [%s]\n", fd,
			line ? line : "NULL", expected ? expected : "NULL");
	free(line);
	return (ok);
}

static void	test_bonus(void)
{
	int	a;
	int	b;
	int	c;
	int	ok;

	printf(BOLD "\nBonus : plusieurs fd en même temps" RESET "\n");
	write_file(DIR "/a.txt", "a1\na2\na3\n", 9);
	write_file(DIR "/b.txt", "b1\nb2", 5);
	write_file(DIR "/c.txt", "c1\nc2\nc3\nc4\n", 12);
	a = open(DIR "/a.txt", O_RDONLY);
	b = open(DIR "/b.txt", O_RDONLY);
	c = open(DIR "/c.txt", O_RDONLY);
	ok = expect(a, "a1\n") & expect(b, "b1\n") & expect(c, "c1\n")
		& expect(a, "a2\n") & expect(b, "b2") & expect(c, "c2\n")
		& expect(a, "a3\n") & expect(b, NULL) & expect(c, "c3\n")
		& expect(a, NULL) & expect(b, NULL) & expect(c, "c4\n")
		& expect(c, NULL);
	result("alternance a, b, c, a, b, c...", ok, NULL);
	close(a);
	close(b);
	close(c);
	a = open(DIR "/a.txt", O_RDONLY);
	c = open(DIR "/c.txt", O_RDONLY);
	ok = expect(c, "c1\n") & expect(c, "c2\n") & expect(a, "a1\n")
		& expect(c, "c3\n") & expect(-1, NULL) & expect(a, "a2\n")
		& expect(c, "c4\n") & expect(a, "a3\n") & expect(a, NULL)
		& expect(c, NULL);
	result("ordre irrégulier + un fd invalide au milieu", ok, NULL);
	close(a);
	close(c);
	ok = expect(FD_MAX, NULL);
	result("fd = FD_MAX renvoie NULL sans sortir du tableau", ok, NULL);
}

#endif

int	main(void)
{
	mkdir(DIR, 0755);
	printf(BOLD "=== get_next_line, BUFFER_SIZE = %d ===" RESET "\n\n",
		(int)BUFFER_SIZE);
	test_files();
	test_pipe();
	test_errors();
#ifdef BONUS
	test_bonus();
#endif
	if (g_ko == 0)
		printf("\n" BOLD GREEN "Tout est bon : %d/%d" RESET "\n", g_ok, g_ok);
	else
		printf("\n" BOLD RED "%d test(s) KO sur %d" RESET "\n", g_ko,
			g_ok + g_ko);
	return (g_ko != 0);
}
