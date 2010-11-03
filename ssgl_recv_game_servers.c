#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ssgl.h"
#include "ssgl_socket_io.h"
#include "ssgl_sanitize.h"

int ssgl_recv_game_servers(int sock,
	struct ssgl_game_server **server_list, int *server_count,
	struct ssgl_client_filter *filter)
{
	uint32_t server_count_be;
	int rc, i;

	/* Send our filter to the lobby server... */
	rc = ssgl_writesocket(sock, filter, sizeof(*filter));
	if (rc < 0)
		return rc;

	/* Get count of results from the lobby server... */
	rc = ssgl_readsocket(sock, &server_count_be, sizeof(server_count_be));
	if (rc < 0)
		return rc;

	*server_count = ntohl(server_count_be);
	if (*server_count < 0 || *server_count > 5000)
		return -1;

	if (*server_count > 0) {
		*server_list = malloc(sizeof(**server_list) * *server_count);
		rc = ssgl_readsocket(sock, *server_list, sizeof(**server_list) * *server_count); 
		if (rc) {
			free(*server_list);
			*server_list = NULL;
			return rc;
		}
	}

	/* If any item in the list cannot be sanitized, the lobby server is suspect.
	 * so we ignore the whole thing.
	 */
	for (i = 0; i < *server_count; i++) {
		rc = ssgl_sanitize_game_server_entry(&(*server_list)[i]);
		if (rc)
			return rc;
	}
	return 0;	
}

