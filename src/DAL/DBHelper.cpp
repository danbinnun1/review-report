#include "DBHelper.hpp"

void Fatal(unqlite *pDb, const char *zMsg)
{
    if (pDb)
    {
        const char *zErr;
        int iLen = 0;
        unqlite_config(pDb, UNQLITE_CONFIG_ERR_LOG, &zErr, &iLen);
        if (iLen > 0)
        {
            puts(zErr);
        }
    }
    else
    {
        if (zMsg)
        {
            puts(zMsg);
        }
    }
    unqlite_lib_shutdown();
    exit(0);
}


#ifdef __WINNT__
#include <Windows.h>
#else
#include <unistd.h>
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

int VmOutputConsumer(const void *pOutput, unsigned int nOutLen, void *pUserData /* Unused */)
{
#ifdef __WINNT__
    BOOL rc;
    rc = WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pOutput, (DWORD)nOutLen, 0, 0);
    if (!rc)
    {
        /* Abort processing */
        return UNQLITE_ABORT;
    }
#else
    ssize_t nWr;
    nWr = write(STDOUT_FILENO, pOutput, nOutLen);
    if (nWr < 0)
    {
        return UNQLITE_ABORT;
    }
#endif /* __WINT__ */

    return UNQLITE_OK;
}