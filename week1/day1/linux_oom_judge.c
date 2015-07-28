#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <time.h>

/* Log levels */
#define REDIS_DEBUG 0
#define REDIS_NOTICE 1
#define REDIS_WARNING 2

struct __log_setting {
	char *logfile;
	uint8_t verbosity;
} log_setting = { .logfile = NULL, .verbosity = REDIS_DEBUG };

static void redisLog(int level, const char *fmt, ...)
{
	va_list ap;
	FILE *fp;

	fp = (log_setting.logfile == NULL) ? stdout : fopen(log_setting.logfile,
							    "a");
	if (!fp)
		return;

	va_start(ap, fmt);
	if (level >= log_setting.verbosity) {
		char *c = ".-*";
		char buf[64];
		time_t now;

		now = time(NULL);
		strftime(buf, 64, "%d %b %H:%M:%S", localtime(&now));
		fprintf(fp, "%s %c ", buf, c[level]);
		vfprintf(fp, fmt, ap);
		fprintf(fp, "\n");
		fflush(fp);
	}
	va_end(ap);

	if (log_setting.logfile)
		fclose(fp);
}

int linuxOvercommitMemoryValue(void)
{
	FILE *fp = fopen("/proc/sys/vm/overcommit_memory", "r");
	char buf[64];

	if (!fp)
		return -1;
	if (fgets(buf, 64, fp) == NULL) {
		fclose(fp);
		return -1;
	}
	fclose(fp);

	return atoi(buf);
}

void linuxOvercommitMemoryWarning(void)
{
	if (linuxOvercommitMemoryValue() == 0) {
		redisLog(REDIS_WARNING,
			 "WARNING overcommit_memory is set to 0! Background save may fail under low condition memory. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.");
	}
}

int main()
{
	linuxOvercommitMemoryWarning();

	return 0;
}
