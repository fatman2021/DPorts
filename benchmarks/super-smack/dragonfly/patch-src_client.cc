--- src/client.cc.orig	2005-05-30 13:42:52.000000000 +0300
+++ src/client.cc
@@ -33,7 +34,7 @@ using namespace std;
 
 #define MAX_VAR_BUF 512
 
-#if !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !(defined(__MACH__) && defined(__APPLE__))
+#if !defined(__DragonFly__) && !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !(defined(__MACH__) && defined(__APPLE__))
 #if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
        /* union semun is defined by including <sys/sem.h> */
 #else
@@ -56,7 +57,7 @@ using namespace std;
        };
 
 #endif
-#if !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !(defined(__MACH__) && defined(__APPLE__))
+#if !defined(__DragonFly__) && !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !(defined(__MACH__) && defined(__APPLE__))
 #define SUPER_SMACK_RESTART ERESTART
 #else
 #define SUPER_SMACK_RESTART EINTR
