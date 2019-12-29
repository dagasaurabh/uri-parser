#ifndef URI_PARSER_H
#define URI_PARSER_H

#include <stdbool.h>

#define URI_MAX_LEN	512
struct uri {
	char *scheme;
	char *username;
	char *password;
	char *host;
	char *port;
	char *path;
	char *query;
	char *fragment;
	char str[URI_MAX_LEN];
};

bool uri_parse(struct uri *u, const char *uri_str);

#endif
