
/*************************************************************************\
* Copyright (c) 2002 The University of Chicago, as Operator of Argonne
*     National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
*     Operator of Los Alamos National Laboratory.
* EPICS BASE Versions 3.13.7
* and higher are distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
\*************************************************************************/

#define VC_EXTRALEAN
#define STRICT
#if _WIN64
#   define _WIN32_WINNT 0x400 /* defining this drops support for W95 */
#endif
#include <windows.h>

/*
 * this was copied directly from an example in visual c++ 7 documentation,
 * except that C++ exceptions were substituted for structured 
 * exceptions (which are not portable to other compilers)
 *
 * Usage: setThreadName (-1, "MainThread");
 */
extern "C" void setThreadName ( DWORD dwThreadID, LPCSTR szThreadName )
{
    typedef struct tagTHREADNAME_INFO
    {
        DWORD dwType; // must be 0x1000
        LPCSTR szName; // pointer to name (in user addr space)
        DWORD dwThreadID; // thread ID (-1=caller thread)
        DWORD dwFlags; // reserved for future use, must be zero
    } THREADNAME_INFO;
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = szThreadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;

    try
    {
        RaiseException ( 0x406D1388, 0, 
            sizeof(info)/sizeof(DWORD), (DWORD*)&info );
    }
    catch ( ... )
    {
    }
}