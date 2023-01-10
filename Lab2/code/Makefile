all: build/ts build/tc build/us build/uc build/mine

build/ts: build tcp_server.c net.h
	gcc -o build/ts tcp_server.c

build/tc: build tcp_client.c net.h
	gcc -o build/tc tcp_client.c

build/us: build udp_server.c net.h
	gcc -o build/us udp_server.c

build/uc: build udp_client.c net.h
	gcc -o build/uc udp_client.c

build/mine: build my_udp_client.c my_udp_server.c net.h
	gcc -o build/my_udp_client my_udp_client.c
	gcc -o build/my_udp_server my_udp_server.c
	gcc -o build/my_tc my_tcp_client.c
	gcc -o build/my_ts my_tcp_server.c
	gcc -o build/commute_client commute_client.c
	gcc -o build/commute_server commute_server.c

build:
	mkdir -p build

clean:
	rm -r build

.PHONY: clean