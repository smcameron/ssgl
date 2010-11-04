#ifndef __SSGL_PROTOCOL_ID_H__
#define __SSGL_PROTOCOL_ID_H__

struct ssgl_protocol_id {
	uint32_t protocol_version; /* network byte order */
#define SSGL_PROTOCOL_VERSION (htonl(1))
	char signature[4];
#define SSGL_SIGNATURE_STRING "SsGl"
	char client_type; /* 's' for 'server', 'c' for 'client' */
#define SSGL_GAME_SERVER 's'
#define SSGL_GAME_CLIENT 'c'
};

#endif

