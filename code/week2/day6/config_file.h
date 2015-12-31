#ifndef __CONFIG_FILE__
#define __CONFIG_FILE__

#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>

#define CONFIG_MAX_LINE 1024

void trim(std::string &s, std::string &set)
{
	if (s.empty()) {
		return;
	}

	s.erase(0, s.find_first_not_of(set));
	s.erase(s.find_last_not_of(set) + 1);
}

std::map<std::string, std::string>
load_config(const std::string &config_filename)
{
	std::map<std::string, std::string> config;
	char buf[CONFIG_MAX_LINE + 1];
	std::string trim_set(" \t\r\n");

	/* Load the file content */
	if (config_filename.empty()) {
		FILE *fp;

		if (config_filename[0] == '-' && config_filename[1] == '\0') {
			fp = stdin;
		} else {
			if ((fp = fopen(config_filename.c_str(), "r")) ==
			    NULL) {
				/* serverLog(LL_WARNING, */
				/* 		"Fatal error, can't open config
				 * file '%s'", filename); */
				exit(1);
			}
		}
		while (fgets(buf, CONFIG_MAX_LINE + 1, fp) != NULL) {
			/* config = sdscat(config, buf); */
			std::string line(buf);
			trim(line, trim_set);

			/* Skip comments and blank lines */
			if (line[0] == '#' || line.empty()) continue;

		}
		if (fp != stdin)
			fclose(fp);
	}

	return config;
}

#endif // __CONFIG_FILE__
