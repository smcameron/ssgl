#ifndef __SSGL_CONNECT_TO_LOBBY_H__
#define __SSGL_CONNECT_TO_LOBBY_H__

#ifdef DEFINE_SSGL_CONNECT_TO_LOBBY_GLOBALS
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL int ssgl_connect_to_lobby(char *ssgl_hostname);
GLOBAL int ssgl_gameserver_connect_to_lobby(char *ssgl_hostname);
GLOBAL int ssgl_gameclient_connect_to_lobby(char *ssgl_hostname);

#undef GLOBAL
#endif

