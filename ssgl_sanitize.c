#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include "ssgl.h"

#define DEFINE_SSGL_SANITIZE_GLOBALS
#include "ssgl_sanitize.h"

static void fill_trailing_zeroes(char *buf, int bufsize)
{
	int len;

	buf[bufsize - 1] = '\0';
	len = strlen(buf);
	if (bufsize - len > 0)
		memset(&buf[len], 0, bufsize - len);
}

int ssgl_sanitize_game_server_entry(struct ssgl_game_server *gs)
{
	/* If any bytes of the IP address are 255, reject.
	 * Do not want to get tricked into broadcasting.
	 */
	unsigned char *x = (unsigned char *) &gs->ipaddr;

	if (x[0] == 0xff || x[1] == 0xff ||
		x[2] == 0xff || x[3] == 0xff)
		return -1;

	/* Make sure all the strings are null terminated and that the 
	 * characters following the terminating NULL are also zeroed.
	 */

	fill_trailing_zeroes(gs->game_type, sizeof(gs->game_type));
	fill_trailing_zeroes(gs->game_instance, sizeof(gs->game_instance));
	fill_trailing_zeroes(gs->server_nickname, sizeof(gs->server_nickname));
	fill_trailing_zeroes(gs->location, sizeof(gs->location));
	
	return 0;	
}

