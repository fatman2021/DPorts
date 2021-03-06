# Created by: Sven Moeller <smoeller@nichthelfer.de>
# $FreeBSD$

PORTNAME=	megaglest
PORTVERSION=	3.12.0
CATEGORIES=	games

MAINTAINER=	monwarez@mailoo.org
COMMENT=	Open source 3D real-time strategy game

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/docs/gnu_gpl_3.0.txt

LIB_DEPENDS=	libcurl.so:ftp/curl \
		libpng.so:graphics/png \
		libxerces-c.so:textproc/xerces-c3 \
		libftgl.so:graphics/ftgl \
		libvorbis.so:audio/libvorbis
BUILD_DEPENDS=	${LOCALBASE}/include/libircclient.h:irc/libircclient \
		${LOCALBASE}/include/miniupnpc/miniupnpc.h:net/miniupnpc
RUN_DEPENDS=	${DATADIR}/tutorials/2_basic_tutorial/2_basic_tutorial.xml:games/megaglest-data

USE_GITHUB=	yes
GH_ACCOUNT=	MegaGlest
GH_PROJECT=	megaglest-source

SUB_FILES=	pkg-message

USES=		cmake compiler:c++11-lib display:build dos2unix jpeg lua \
		openal:al,alut pkgconfig
USE_GL=		glew gl glu
USE_SDL=	sdl2
USE_WX=		3.0
USE_CXXSTD=	c++11

CFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib -lssl -lcrypto

OPTIONS_DEFINE=	EDITOR DOCS VIEWER
OPTIONS_SUB=	yes
EDITOR_DESC=	Install MegaGlest Editor
VIEWER_DESC=	Install Megaglest G3D viewer

post-patch:
	@${REINPLACE_CMD} -e 's,/usr/local/include/lua51,${LUA_INCDIR},g ; \
		s,/usr/local/lib/lua51,${LUA_LIBDIR},g ; \
		s,lua5.2,lua-${LUA_VER},g' \
		${WRKSRC}/mk/cmake/Modules/FindLUA.cmake
	@${REINPLACE_CMD} -e 's|__FreeBSD__|__DragonFly__|g' \
		${WRKSRC}/source/glest_game/facilities/game_util.cpp \
		${WRKSRC}/source/glest_game/main/main.cpp \
		${WRKSRC}/source/shared_lib/sources/feathery_ftp/ftpTargetPosix.c \
		${WRKSRC}/source/shared_lib/sources/platform/posix/socket.cpp \
		${WRKSRC}/source/shared_lib/sources/platform/common/platform_common.cpp \
		${WRKSRC}/source/shared_lib/include/util/leak_dumper.h

do-install:
	@${MKDIR} ${STAGEDIR}${DATADIR}
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/pixmaps
	${INSTALL_DATA} ${WRKSRC}/mk/shared/megaglest.ico ${STAGEDIR}${PREFIX}/share/pixmaps/
	${INSTALL_PROGRAM} ${WRKSRC}/source/glest_game/megaglest ${STAGEDIR}${PREFIX}/bin/${PORTNAME}
.for f in mk/linux/glest.ini mk/shared/glestkeys.ini mk/shared/servers.ini
	${INSTALL_DATA} ${WRKSRC}/${f} ${STAGEDIR}${DATADIR}
.endfor

do-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for f in docs/AUTHORS.source_code.txt docs/CHANGELOG.txt docs/README.txt docs/COPYRIGHT.source_code.txt
	${INSTALL_DATA} ${WRKSRC}/${f} ${STAGEDIR}${DOCSDIR}
.endfor

do-install-EDITOR-on:
	${INSTALL_PROGRAM} ${WRKSRC}/source/glest_map_editor/megaglest_editor ${STAGEDIR}${PREFIX}/bin/megaglest_editor
	${INSTALL_DATA} ${WRKSRC}/mk/shared/editor.ico ${STAGEDIR}${PREFIX}/share/pixmaps/

do-install-VIEWER-on:
	${INSTALL_PROGRAM} ${WRKSRC}/source/g3d_viewer/megaglest_g3dviewer ${STAGEDIR}${PREFIX}/bin/megaglest_g3dviewer
	${INSTALL_DATA} ${WRKSRC}/mk/shared/g3dviewer.ico ${STAGEDIR}${PREFIX}/share/pixmaps/

.include <bsd.port.mk>
