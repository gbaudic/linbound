AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"

bin_PROGRAMS = linbound

linbound_SOURCES = channel.cpp context.cpp db.cpp event.cpp gui_lb.cpp image.cpp init.cpp \
main.cpp map.cpp menu.cpp message.cpp network.cpp player.cpp room.cpp server.cpp serverlist.cpp settings.cpp \
sound.cpp Sprite.cpp update.cpp utils.cpp xml.cpp

noinst_HEADERS = channel.hpp context.hpp db.hpp event.hpp gui_lb.hpp image.hpp init.hpp \
main.hpp map.hpp menu.hpp message.hpp player.hpp protocol.hpp room.hpp server.hpp serverlist.hpp settings.hpp \
sound.hpp Sprite.hpp update.hpp utils.hpp xml.hpp

LDADD = $(LIBINTL)
