#include "apue.h"
#include <stdarg.h>
#include <errno.h>

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
void err_quit(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end(ap);
	exit(1);
}
void err_sys(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	exit(1);
}
int main(int argc, char *argv[])
{
	char t[] = "./topla";
	char ci[] = "./cikar";
	char ca[] = "./carp";
	char b[] = "./bol";
	if(argc != 3)
		err_quit("kullanımı : işlem arguman1 arguman2");
	if(strcmp(argv[0], t) == 0) {
		if(argc != 3)
			err_quit("kullanımı : ./topla arguman1 arguman2");
		if((argv[1] || argv[2]) != ' ')
			printf("%s + %s = %d\n", argv[1], argv[2], atoi(argv[1]) + atoi(argv[2]));
	}
	else if(strcmp(argv[0], ci) == 0) {
		if(argc != 3)
			err_quit("kullanımı : ./cikar arguman1 arguman2");
		if((argv[1] || argv[2]) != ' ')
			printf("%s - %s = %d\n", argv[1], argv[2], atoi(argv[1]) - atoi(argv[2]));
	}
	else if(strcmp(argv[0], ca) == 0) {
		if(argc != 3)
			err_quit("kullanımı : ./carp arguman1 arguman2");
		if((argv[1] || argv[2]) != ' ')
			printf("%s * %s = %d\n", argv[1], argv[2], atoi(argv[1]) * atoi(argv[2]));
	}
	else if(strcmp(argv[0], b) == 0) {
		if(argc != 3)
			err_quit("kullanımı : ./bol arguman1 arguman2");
		if((argv[1] || argv[2]) != ' ')
			printf("%s / %s = %d\n", argv[1], argv[2], atoi(argv[1]) / atoi(argv[2]));
	}
	else
		printf("operator seçiminiz hatalı.\n");
	exit(0);
}
