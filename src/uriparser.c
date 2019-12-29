#include "uriparser.h"
#include <string.h>

/* 
 * uni syntax 
 * scheme:[//[user[:password]@]host[:port]][/path][?query][#fragment]
 */

static char * find_and_terminate(char * str, char find)
{
	str = strchr(str, find);

	if(str == NULL) return NULL;

	*str = '\0';
	return str + 1;
}

static bool is_relative(char * s)
{
	return (*s == '/') ? true:false;
}

static char * find_fragment(char * s)
{
	return find_and_terminate(s, '#');
}

static char * find_query(char * s)
{
	return find_and_terminate(s, '?');
}

static char * find_path(char * s)
{
	return find_and_terminate(s, '/');
}
static char * parse_scheme(char * str)
{
	char * s = NULL;
	s =  strchr(str, ':');

	if(!s || s == str) return NULL;

	if(s[1] == '\0' || s[1] != '/') return NULL;

	if(s[2] == '\0' || s[2] != '/') return NULL;

	*s = '\0';

	return s + 3;
}
static char * parse_username(char * str)
{
	char * s = strchr(str, ':');
}
static char * parse_userinfo(struct uri * u, char * str)
{
	char * s = NULL;

	u->username = str;
	s = find_and_terminate(str, '@');

	if(s == NULL)
	{
		u->username = NULL;
	}
	else
	{
		if(*(u->username) == '\0') 
		{
			u->username = NULL;
			return NULL;
		}

		u->password = find_and_terminate(u->username, ':');
	}

	return s ? s : str;
}
static bool parse_authority(struct uri * u, char *str)
{
	char *s = parse_userinfo(u, str);

	if(s == NULL || *s == '\0') return false;

	u->host = s;
	u->port = find_and_terminate(s, ':');

	return true;
}

bool uri_parse(struct uri * u, const char * src)
{
	if(!src || !u ) return false;

	bool rc = false;
	char *str = NULL;

	memset(u, 0, sizeof(struct uri));

	strncpy(u->str, src, URI_MAX_LEN);

	str = u->str;

	u->fragment = find_fragment(str);
	u->query = find_query(str);

	if(is_relative(str))
	{
		u->path = find_path(str);
		rc = true;
	}
	else
	{
		u->scheme = str;
		str = parse_scheme(str);

		if(str == NULL || *str == '\0') 
		{
			goto uri_parse_end;
		}

		u->path = find_path(str);

		if(!parse_authority(u, str))
		{
			goto uri_parse_end;
		}
		rc = true;
	}
uri_parse_end:
	return rc;
}
