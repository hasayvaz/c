#include "apue.h"
#include <stdarg.h>
#include <errno.h>
#include <sys/wait.h>
#define IN 1
#define OUT 0

void err_doit(int errnoflag, const char *fmt, va_list ap)
{
	int	errno_save;
	char buf[MAXLINE];

	errno_save = errno;		/* value caller might want printed */
	vsprintf(buf, fmt, ap);
	if (errnoflag)
		sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
	return;
}
void err_sys(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	exit(1);
}

static const char *KOMUTLAR[MAXLINE];

void ayikla(char dizgi[]) 
{
	char s[MAXLINE];
	int i, j, h;
	int durum = IN;
	for (j = 0, i = 0, h = 0; i < strlen(dizgi); i++) {
		if (dizgi[i] != ' ') {
			s[j++] = dizgi[i];
			durum = IN;
		}
		if ((durum == IN && dizgi[i] == ' ') || dizgi[i + 1] == '\0') {
			s[j] = '\0';
			KOMUTLAR[h++] = strdup(s);
			durum = IN;
			j = 0;
		}
	}
}
int main() 
{
	char buf[MAXLINE];
	int status;
	pid_t pid;
	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';

		if ((pid = fork()) < 0)
			err_sys("fork error");
		else if (pid == 0) {
			ayikla(buf);
			execlp(KOMUTLAR[0], KOMUTLAR[0], KOMUTLAR[1], KOMUTLAR[2], KOMUTLAR[3], (char *)0);
			err_sys("couldn't execute");
		}
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
exit(0);
}
