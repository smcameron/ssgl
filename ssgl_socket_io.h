#ifndef __SSGL_SOCKET_IO_H__
#define __SSGL_SOCKET_IO_H__

#ifdef DEFINE_SSGL_SOCKET_IO_GLOBALS
#define GLOBAL
#else
#define GLOBAL extern
#endif

/* Functions to read/write from a socket, restarting if EINTR... */
GLOBAL int ssgl_readsocket(int fd, void *buffer, int buflen);
GLOBAL int ssgl_writesocket(int fd, void *buffer, int buflen);

#undef GLOBAL
#endif

 
