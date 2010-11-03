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

int ssgl_register_gameserver(int sock, struct ssgl_game_server *gameserver)
{
	return ssgl_writesocket(sock, gameserver, sizeof(*gameserver)); 
}

