#ifndef __SSGL_H__
#define __SSGL_H__

#define GAMELOBBY_SERVICE_NUMBER 2914
#define GAMELOBBY_SERVICE_NAME "gamelobby"

#pragma pack(1)
struct ssgl_game_server {
	uint32_t ipaddr;
	uint32_t port;
	char game_type[15];		/* What kind of game is this? */
	char game_instance[20];		/* which instance on the server of the game */
	char server_nickname[15];	/* server nickname where game is hosted */
	char location[20]; 
};

struct ssgl_client_filter {
	char game_type[15];
};
#pragma pack()

#define SSGL_GAME_SERVER_TIMEOUT_SECS (20)

#ifdef __SSGL_DEFINE_GLOBALS__
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL int ssgl_gameclient_connect_to_lobby(char *hostname);
GLOBAL int ssgl_register_gameserver(char *lobbyhost, struct ssgl_game_server *gameserver,
	pthread_t *lobby_thread);
GLOBAL int ssgl_recv_game_servers(int sock,
	struct ssgl_game_server **server_list, int *server_count,
	struct ssgl_client_filter *filter);

GLOBAL void ssgl_sleep(int seconds); /* just a thread safe sleep implemented by nanosleep w/ retries */
GLOBAL int ssgl_get_primary_host_ip_addr(uint32_t *ipaddr);

#undef GLOBAL
#endif

