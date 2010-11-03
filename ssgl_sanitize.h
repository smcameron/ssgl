#ifndef __SSGL_SANITIZE_H__
#define __SSGL_SANITIZE_H__

#ifdef DEFINE_SSGL_SANITIZE_GLOBALS
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL int ssgl_sanitize_game_server_entry(struct ssgl_game_server *gs);

#undef GLOBAL
#endif
