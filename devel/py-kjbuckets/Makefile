# Created by: nectar@FreeBSD.org
# $FreeBSD$

PORTNAME=	kjbuckets
PORTVERSION=	1.0.0
PORTREVISION=	1
PORTEPOCH=	1
CATEGORIES=	devel python
MASTER_SITES=	SF/gadfly/gadfly/${PORTVERSION}
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	gadfly-${PORTVERSION}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Graph and set datatypes for Python (C extension)

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/../COPYRIGHT.txt

OPTIONS_DEFINE=	DOCS EXAMPLES

USES=		python
USE_PYTHON=	distutils autoplist
WRKSRC=		${WRKDIR}/${DISTNAME}/kjbuckets

PORTDOCS=	*
PORTEXAMPLES=	*

post-install:
	${STRIP_CMD} ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/kjbuckets.so
post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/../COPYRIGHT.txt ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/../doc/kjbuckets.txt ${STAGEDIR}${DOCSDIR}
post-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/../doc/demo/kjbuckets/*.py ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>
