# $FreeBSD$

PORTNAME=	creduce
DISTVERSION=	2.5.0
CATEGORIES=	devel
MASTER_SITES=	http://embed.cs.utah.edu/creduce/

MAINTAINER=	swills@FreeBSD.org
COMMENT=	Produces small test cases

BUILD_DEPENDS=	llvm-config38:devel/llvm38
RUN_DEPENDS=	llvm-config38:devel/llvm38 \
		topformflat:devel/delta \
		astyle:devel/astyle \
		p5-Benchmark-Timer>=0:devel/p5-Benchmark-Timer \
		p5-Exporter-Lite>=0:devel/p5-Exporter-Lite \
		p5-File-Which>=0:sysutils/p5-File-Which \
		p5-Regexp-Common>=0:textproc/p5-Regexp-Common \
		devel/p5-Sys-Cpu>=0:devel/p5-Sys-Cpu \
		p5-Getopt-Tabular>=0:devel/p5-Getopt-Tabular

GNU_CONFIGURE=	yes
CONFIGURE_FLAGS=	--with-llvm=${LOCALBASE}

USES=	gmake perl5

dfly-patch:
	${REINPLACE_CMD} 's,llvm-config,llvm-config38,g' ${WRKSRC}/configure

.include <bsd.port.pre.mk>

.if ${OSVERSION} < 1000000
CONFIGURE_ENV+=	CPPFLAGS="-stdlib=libstdc++ -I${LOCALBASE}/lib/gcc48/include/c++/ -I${LOCALBASE}/lib/gcc48/include/ -I${LOCALBASE}/lib/gcc48/include/c++/${ARCH:C/amd64/x86_64/}-portbld-${OPSYS:tl}${OSREL}/ -L${LOCALBASE}/lib -L${LOCALBASE}/lib/gcc48" \
		LDFLAGS="-L/usr/local/lib/gcc48 -lstdc++"
.endif

.include <bsd.port.post.mk>
