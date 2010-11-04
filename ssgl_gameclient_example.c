#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h> /* for ntohl */

#include "ssgl.h"

static void usage()
{
	fprintf(stderr, "ssgl_gameclient_example gametype\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	struct ssgl_game_server *game_server = NULL;
	struct ssgl_client_filter filter;
	int game_server_count, rc, i;
	int sock;

	if (argc < 3)
		usage();

	sock = ssgl_gameclient_connect_to_lobby(argv[1]);
	if (sock < 0) {
		fprintf(stderr, "ssgl_connect_to_lobby failed: %s\n", strerror(errno));
		exit(1);
	}

	strncpy(filter.game_type, argv[2], sizeof(filter.game_type)-1);
	printf("filtering games of type '%s'\n", filter.game_type);
	do {
		rc = ssgl_recv_game_servers(sock, &game_server, &game_server_count, &filter);
		if (rc) {
			fprintf(stderr, "ssgl_recv_game_servers failed: %s\n", strerror(errno));
			break;
		}
		printf("IP addr/port       %15s %20s %15s %20s\n",
			"Game Type", "Instance/Map", "Server Nickname", "Location");
		printf("---------------------------------------------------------------------\n");	
		for (i = 0; i < game_server_count; i++) {
			unsigned char *x = (unsigned char *) &game_server[i].ipaddr;
			printf("%d.%d.%d.%d/%d %15s %20s %15s %20s\n",
				x[0], x[1], x[2], x[3],
				ntohl(game_server[i].port),
				game_server[i].game_type,
				game_server[i].game_instance,
				game_server[i].server_nickname,
				game_server[i].location);
				
		}
		printf("\n");	
		if (game_server_count > 0)
			free(game_server);
		ssgl_sleep(5);  /* just a thread safe sleep. */
	} while (1);
	return 0;
}

