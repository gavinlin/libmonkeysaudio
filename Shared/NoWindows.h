#pragma once

#if !defined(PLATFORM_WINDOWS)

// we treat BOOL as a global type, so don't declare it in the namespace
typedef signed char BOOL;

namespace APE
{

#define FALSE    0
#define TRUE     1

#define NEAR
#define FAR

typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef void *              HANDLE;
typedef unsigned int        UINT;
typedef unsigned int        WPARAM;
typedef long                LPARAM;
typedef const char *        LPCSTR;
typedef char *              LPSTR;
typedef long                LRESULT;

#define ZeroMemory(POINTER, BYTES) memset(POINTER, 0, BYTES);
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

#define __stdcall
#define CALLBACK

#define _T(x) L ## x

#define _strnicmp strncasecmp
#define _wtoi(x) wcstol(x, NULL, 10)
#define _tcscat wcscat
#define _totlower towlower
#define _totupper towupper

#define _FPOSOFF(fp) (fp)
#define MAX_PATH    260

}

#endif // #ifndef _WIN32
