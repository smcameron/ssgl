
all:	ssgl_server ssgl_gameclient_example ssgl_gameserver_example

libssglclient.a:	ssgl_sleep.o	ssgl_sanitize.o ssgl_recv_game_servers.o \
	ssgl_connect_to_lobby.o ssgl_socket_io.o ssgl_get_primary_host_ip_addr.o \
	ssgl_register_gameserver.o
	ar -cr libssglclient.a ssgl_sleep.o ssgl_sanitize.o ssgl_recv_game_servers.o \
		ssgl_connect_to_lobby.o ssgl_socket_io.o ssgl_get_primary_host_ip_addr.o \
		ssgl_register_gameserver.o

ssgl_sleep.o:	ssgl_sleep.c
	gcc -g --pedantic -Wall -Werror -pthread -c ssgl_sleep.c

ssgl_socket_io.o:	ssgl_socket_io.c
	gcc -g --pedantic -Wall -Werror -pthread -c ssgl_socket_io.c

ssgl_sanitize.o:	ssgl_sanitize.c ssgl_sanitize.h
	gcc -g --pedantic -Wall -Werror -pthread -c ssgl_sanitize.c

ssgl_recv_game_servers.o:	ssgl_recv_game_servers.c
	gcc -g --pedantic -Wall -Werror -pthread -c ssgl_recv_game_servers.c

ssgl_register_gameserver.o:	ssgl_register_gameserver.c
	gcc -g --pedantic -Wall -Werror -pthread -c ssgl_register_gameserver.c

ssgl_get_primary_host_ip_addr.o:	ssgl_get_primary_host_ip_addr.c
	gcc -g --pedantic -Wall -Werror -pthread -c ssgl_get_primary_host_ip_addr.c

ssgl_connect_to_lobby.o:	ssgl_connect_to_lobby.c
	gcc -g --pedantic -Wall -Werror -pthread -c ssgl_connect_to_lobby.c

ssgl_server:	ssgl_server.c ssgl.h ssgl_sanitize.o ssgl_sleep.o ssgl_socket_io.o
	gcc -g --pedantic -Wall -Werror -pthread ssgl_sanitize.o ssgl_sleep.o ssgl_socket_io.o -o ssgl_server ssgl_server.c

ssgl_gameclient_example:	ssgl.h ssgl_gameclient_example.c libssglclient.a
	gcc -g --pedantic -Wall -Werror -pthread -L. -o ssgl_gameclient_example ssgl_gameclient_example.c -lssglclient

ssgl_gameserver_example:	ssgl.h ssgl_gameserver_example.c libssglclient.a
	gcc -g --pedantic -Wall -Werror -pthread -L. -o ssgl_gameserver_example ssgl_gameserver_example.c -lssglclient

clean:
	rm -fr *.o ssgl_server ssgl_gameclient_example ssgl_gameserver_example libssglclient.a
