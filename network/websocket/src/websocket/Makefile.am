lib_LTLIBRARIES = libzapata-net-websocket.la libzapata-net-websocket-plugin.la

libzapata_net_websocket_la_LIBADD = -lpthread -lzapata-base -lzapata-io-streams	\
-lzapata-net-socket -lzapata-transport
libzapata_net_websocket_la_LDFLAGS = -version-info 2:0:0 -shared
libzapata_net_websocket_la_CPPFLAGS = -O3 @CPP_STD_VERSION@ -Wall -I../../../include -I../../include

libzapata_net_websocket_la_SOURCES = \
./websocket.cpp

libzapata_net_websocket_plugin_la_LIBADD = -lpthread -lzapata-base	\
-lzapata-io-streams -lzapata-net-socket -lzapata-transport			\
libzapata-net-websocket.la
libzapata_net_websocket_plugin_la_LDFLAGS = -version-info 2:0:0 -shared
libzapata_net_websocket_plugin_la_CPPFLAGS = -O3 @CPP_STD_VERSION@ -Wall -I../../../include -I../../include

libzapata_net_websocket_plugin_la_SOURCES = \
./plugin.cpp
