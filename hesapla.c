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
	if(argc != 4)
		err_quit("kullanımı : ./hesapla arguman1 operator(+,-,*,/) arguman2");
	if((argv[1] || argv[3]) != ' ') {
		if(*argv[2] == '+')
			printf("%s + %s = %d\n", argv[1], argv[3], atoi(argv[1]) + atoi(argv[3]));
		else if(*argv[2] == '-')
			printf("%s - %s = %d\n", argv[1], argv[3], atoi(argv[1]) - atoi(argv[3]));
		else if(*argv[2] == '*')
			printf("%s * %s = %d\n", argv[1], argv[3], atoi(argv[1]) * atoi(argv[3]));
		else if(*argv[2] == '/')
			printf("%s / %s = %d\n", argv[1], argv[3], atoi(argv[1]) / atoi(argv[3]));
		else 
			printf("Kullandığınız operator algılanamadı.Lütfen örnekte verilen operatorleri kullanın.\n");
	}

	exit(0);
}
