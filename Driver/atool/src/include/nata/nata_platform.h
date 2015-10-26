/*
 * $Id: nata_platform.h.in 86 2012-07-30 05:33:07Z m-hirano $
 */
#ifndef __NATA_PLATFORM_H__
#define __NATA_PLATFORM_H__

#define NATA_OS_LINUX
#define NATA_CPU_X86_64
#define NATA_API_POSIX

#ifdef WORDS_BIGENDIAN
#define NATA_BIG_ENDIAN
#else
#define NATA_LITTLE_ENDIAN
#endif /* WORDS_BIGENDIAN */

#ifdef NATA_API_WIN32API
#include <nata/nata_win32api.h>
#endif /* NATA_API_WIN32API */
#ifndef _REENTRANT
#define _REENTRANT
#endif /* ! _REENTRANT */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* ! _GNU_SOURCE */

#endif /* ! __NATA_PLATFORM_H__ */
