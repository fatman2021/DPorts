# Created by: Brad Lanam <bll@gentoo.com>
# $FreeBSD$

PORTNAME=	di
PORTVERSION=	4.41
CATEGORIES=	sysutils
MASTER_SITES=	http://www.gentoo.com/di/ \
		http://www.cyberbotx.com/di/

MAINTAINER=	cyberbotx@cyberbotx.com
COMMENT=	Disk Information Utility

MAKE_ENV=	prefix="${PREFIX}" DI_NO_NLS=T
MAKE_ARGS=	-e
PLIST_SUB+=	NLS="@comment "

post-patch:
	@${REINPLACE_CMD} -e "s|zoneid_t|zoneId_t|g" ${WRKSRC}/C/di.c

pre-install:
	@${STRIP_CMD} ${WRKSRC}/C/di

.include <bsd.port.mk>
