/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Defined if LDAP build option enabled */
/* #undef BUILD_LDAP */

/* Define if tools enabled */
#define BUILD_TOOLS 1

/* Define if upnp enabled */
#define BUILD_UPNP 1

/* Define if wizard enabled */
/* #undef BUILD_WIZARD */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#define ENABLE_NLS 1

/* Defined when using gsm at nonstandard rates */
/* #undef ENABLE_NONSTANDARD_GSM */

/* The name of the gettext package name */
#define GETTEXT_PACKAGE "linphone"

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to 1 if you have the <CUnit/CUnit.h> header file. */
/* #undef HAVE_CUNIT_CUNIT_H */

/* defined when CU_curses_run_tests is available */
/* #undef HAVE_CU_CURSES */

/* defined when CU_get_suite is available */
/* #undef HAVE_CU_GET_SUITE */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* If present, the getenv function allows fim to read environment variables.
   */
#define HAVE_GETENV 1

/* Define to 1 if you have the `getifaddrs' function. */
#define HAVE_GETIFADDRS 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define to 1 if you have the `get_current_dir_name' function. */
#define HAVE_GET_CURRENT_DIR_NAME 1

/* Defined when gtk osx is used */
/* #undef HAVE_GTK_OSX */

/* Define to 1 if you have the <history.h> header file. */
/* #undef HAVE_HISTORY_H */

/* Define if you have the iconv() function. */
/* #undef HAVE_ICONV */

/* Tells wheter localisation is possible */
/* #undef HAVE_INTL */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <ldap.h> header file. */
/* #undef HAVE_LDAP_H */

/* Define to 1 if you have the `udev' library (-ludev). */
/* #undef HAVE_LIBUDEV */

/* Define to 1 if you have the <libudev.h> header file. */
/* #undef HAVE_LIBUDEV_H */

/* Defined when LIME support is compiled */
/* #undef HAVE_LIME */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* NOTIFY1 support */
/* #undef HAVE_NOTIFY1 */

/* NOTIFY4 support */
/* #undef HAVE_NOTIFY4 */

/* Define to 1 if you have the <polarssl/gcm.h> header file. */
#define HAVE_POLARSSL_GCM_H 1

/* defined when compiling with readline support */
/* #undef HAVE_READLINE */

/* Define to 1 if you have the <readline.h> header file. */
/* #undef HAVE_READLINE_H */

/* Define to 1 if you have the <readline/history.h> header file. */
/* #undef HAVE_READLINE_HISTORY_H */

/* Define to 1 if you have the <readline/readline.h> header file. */
/* #undef HAVE_READLINE_READLINE_H */

/* Define to 1 if you have the <sasl/sasl.h> header file. */
/* #undef HAVE_SASL_SASL_H */

/* Define if sighandler_t available */
/* #undef HAVE_SIGHANDLER_T */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `stpcpy' function. */
#define HAVE_STPCPY 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <X11/Xlib.h> header file. */
/* #undef HAVE_X11_XLIB_H */

/* ZLIB support */
#define HAVE_ZLIB 1

/* All supported languages */
#define LINPHONE_ALL_LANGS "ar cs de es fr he hu it ja nb_NO nl pl pt_BR ru sr sv tr zh_CN zh_TW"

/* Windows appdata subdir where linphonerc can be found */
#define LINPHONE_CONFIG_DIR "Linphone"

/* path of liblinphone plugins, not mediastreamer2 plugins */
#define LINPHONE_PLUGINS_DIR "/usr/local/lib/liblinphone/plugins"

/* Linphone\'s version number */
#define LINPHONE_VERSION "3.8.5"

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "linphone"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "linphone-developers@nongnu.org"

/* Defines the place where data are found */
#define PACKAGE_DATA_DIR "/usr/local/share"

/* Defines the place where locales can be found */
#define PACKAGE_LOCALE_DIR "/usr/local/share/locale"

/* Define to the full name of this package. */
#define PACKAGE_NAME "linphone"

/* Defines the place where linphone sounds are found */
#define PACKAGE_SOUND_DIR "/usr/local/share/sounds/linphone"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "linphone 3.8.5"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "linphone"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.8.5"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Tells tunnel extension is built-in */
/* #undef TUNNEL_ENABLED */

/* Tell whether date_version.h must be used */
/* #undef USE_BUILDDATE_VERSION */

/* Version number of package */
#define VERSION "3.8.5"

/* defined if video support is available */
/* #undef VIDEO_ENABLED */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Defined if we are compiling for arm processor */
#define __ARM__ 1

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif
