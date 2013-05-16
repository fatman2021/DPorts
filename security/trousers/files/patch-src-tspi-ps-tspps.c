--- src/tspi/ps/tspps.c.orig	2010-05-02 11:39:11.000000000 +0900
+++ src/tspi/ps/tspps.c	2010-10-24 21:04:04.843557352 +0900
@@ -29,6 +29,11 @@
 #define LE_16 htole16
 #define LE_32 htole32
 #define LE_64 htole64
+#elif defined(HAVE_SYS_ENDIAN_H)
+#include <sys/endian.h>
+#define LE_16 htole16
+#define LE_32 htole32
+#define LE_64 htole64
 #else
 #define LE_16(x) (x)
 #define LE_32(x) (x)
@@ -43,11 +48,26 @@
 #include "tspps.h"
 #include "tsplog.h"
 
+#ifndef LE_16
+static UINT16 htole16(UINT16 x)
+{
+    BYTE *b = &x;
+    return (UINT16) (b[0] + (b[1] << 8));
+}
+#define LE_16 htole16
+#endif
+
+#ifndef LE_32
+static UINT32 htole32(UINT32 x)
+{
+    BYTE *b = &x;
+    return (UINT32) (b[0] + (b[1] << 8) + (b[2] << 16) + (b[3] << 24));
+}
+#define LE_32 htole32
+#endif
+
 static int user_ps_fd = -1;
 static MUTEX_DECLARE_INIT(user_ps_lock);
-#if (defined (__FreeBSD__) || defined (__OpenBSD__))
-static MUTEX_DECLARE_INIT(user_ps_path);
-#endif
 #if defined (SOLARIS)
 static struct flock fl = {
        0,
@@ -70,9 +90,7 @@
 	TSS_RESULT result;
 	char *file_name = NULL, *home_dir = NULL;
 	struct passwd *pwp;
-#if (defined (__linux) || defined (linux) || defined(__GLIBC__))
 	struct passwd pw;
-#endif
 	struct stat stat_buf;
 	char buf[PASSWD_BUFSIZE];
 	uid_t euid;
@@ -82,10 +100,6 @@
 		*file = strdup(file_name);
 		return (*file) ? TSS_SUCCESS : TSPERR(TSS_E_OUTOFMEMORY);
 	}
-#if (defined (__FreeBSD__) || defined (__OpenBSD__))
-	MUTEX_LOCK(user_ps_path);
-#endif
-
 	euid = geteuid();
 
 #if defined (SOLARIS)
@@ -98,32 +112,14 @@
          */
         rc = snprintf(buf, sizeof (buf), "%s/%d", TSS_USER_PS_DIR, euid);
 #else
-	setpwent();
-	while (1) {
-#if (defined (__linux) || defined (linux) || defined(__GLIBC__))
-		rc = getpwent_r(&pw, buf, PASSWD_BUFSIZE, &pwp);
-		if (rc) {
-			LogDebugFn("USER PS: Error getting path to home directory: getpwent_r: %s",
-				   strerror(rc));
-			endpwent();
-			return TSPERR(TSS_E_INTERNAL_ERROR);
-		}
+	rc = getpwuid_r(euid, &pw, buf, PASSWD_BUFSIZE, &pwp);
+	if (rc) {
+		LogDebugFn("USER PS: Error getting path to home directory: "
+			"getpwent_r: %s", strerror(rc));
+		return TSPERR(TSS_E_INTERNAL_ERROR);
+	}
 
-#elif (defined (__FreeBSD__) || defined (__OpenBSD__))
-		if ((pwp = getpwent()) == NULL) {
-			LogDebugFn("USER PS: Error getting path to home directory: getpwent: %s",
-                                   strerror(rc));
-			endpwent();
-			MUTEX_UNLOCK(user_ps_path);
-			return TSPERR(TSS_E_INTERNAL_ERROR);
-		}
-#endif
-		if (euid == pwp->pw_uid) {
-                        home_dir = strdup(pwp->pw_dir);
-                        break;
-                }
-        }
-        endpwent();
+	home_dir = strdup(pwp->pw_dir);
 
 	if (!home_dir)
 		return TSPERR(TSS_E_OUTOFMEMORY);
