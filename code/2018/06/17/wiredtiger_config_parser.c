#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <errno.h>

#include <wiredtiger.h>

// XXX(DOC): This is an example demonstrating how to parse WiredTiger compatible
// configuration strings.

#define error_check(call)                                                      \
	do {                                                                   \
		int __r;                                                       \
		if ((__r = (call)) != 0 && __r != ENOTSUP)                     \
			abort();                                               \
	} while (0)

int main(int argc, char *argv[])
{
	int ret;

	(void)argc; /* Unused variable */

	{
		/*! [Create a configuration parser] */
		WT_CONFIG_ITEM k, v;
		WT_CONFIG_PARSER *parser;
		const char *config_string =
		    "path=/dev/"
		    "loop,page_size=1024,log=(archive=true,file_max=20MB)";

		error_check(wiredtiger_config_parser_open(
		    NULL, config_string, strlen(config_string), &parser));
		error_check(parser->close(parser));
		/*! [Create a configuration parser] */

		error_check(wiredtiger_config_parser_open(
		    NULL, config_string, strlen(config_string), &parser));

		{
			/*! [get] */
			int64_t my_page_size;
			/*
			 * Retrieve the value of the integer configuration
			 * string "page_size".
			 */
			error_check(parser->get(parser, "page_size", &v));
			my_page_size = v.val;
			/*! [get] */

			error_check(parser->close(parser));
			(void)my_page_size; /* Unused variable */
		}

		{
			error_check(wiredtiger_config_parser_open(
			    NULL, config_string, strlen(config_string),
			    &parser));
			/*! [next] */
			/*
			 * Retrieve and print the values of the configuration
			 * strings.
			 */
			while ((ret = parser->next(parser, &k, &v)) == 0) {
				printf("%.*s:", (int)k.len, k.str);
				if (v.type == WT_CONFIG_ITEM_NUM)
					printf("%" PRId64 "\n", v.val);
				else
					printf("%.*s\n", (int)v.len, v.str);
			}
			assert(ret == WT_NOTFOUND);
			/*! [next] */
			error_check(parser->close(parser));
		}

		error_check(wiredtiger_config_parser_open(
		    NULL, config_string, strlen(config_string), &parser));

		/*! [nested get] */
		/*
		 * Retrieve the value of the nested log file_max configuration
		 * string using dot shorthand. Utilize the configuration parsing
		 * automatic conversion of value strings into an integer.
		 */
		v.type = WT_CONFIG_ITEM_NUM;
		error_check(parser->get(parser, "log.file_max", &v));
		printf("log file max: %" PRId64 "\n", v.val);
		/*! [nested get] */
		error_check(parser->close(parser));

		error_check(wiredtiger_config_parser_open(
		    NULL, config_string, strlen(config_string), &parser));
		/*! [nested traverse] */
		{
			WT_CONFIG_PARSER *sub_parser;
			while ((ret = parser->next(parser, &k, &v)) == 0) {
				if (v.type == WT_CONFIG_ITEM_STRUCT) {
					printf("Found nested configuration: "
					       "%.*s\n",
					       (int)k.len, k.str);
					error_check(
					    wiredtiger_config_parser_open(
						NULL, v.str, v.len,
						&sub_parser));
					while ((ret = sub_parser->next(
						    sub_parser, &k, &v)) == 0)
						printf("\t%.*s\n", (int)k.len,
						       k.str);
					assert(ret == WT_NOTFOUND);
					error_check(
					    sub_parser->close(sub_parser));
				}
			}
			assert(ret == WT_NOTFOUND);
			/*! [nested traverse] */
			error_check(parser->close(parser));
		}
	}

	return (EXIT_SUCCESS);
}
