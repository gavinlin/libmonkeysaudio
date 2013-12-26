#include "All.h"
#include "GlobalFunctions.h"
#include "IO.h"
#include "CharacterHelper.h"
#ifdef _MSC_VER
    #include <intrin.h>
#endif

namespace APE
{

int ReadSafe(CIO * pIO, void * pBuffer, int nBytes)
{
    unsigned int nBytesRead = 0;
    int nResult = pIO->Read(pBuffer, nBytes, &nBytesRead);
    if (nResult == ERROR_SUCCESS)
    {
        if (nBytes != int(nBytesRead))
            nResult = ERROR_IO_READ;
    }

    return nResult;
}

int WriteSafe(CIO * pIO, void * pBuffer, int nBytes)
{
    unsigned int nBytesWritten = 0;
    int nResult = pIO->Write(pBuffer, nBytes, &nBytesWritten);
    if (nResult == ERROR_SUCCESS)
    {
        if (nBytes != int(nBytesWritten))
            nResult = ERROR_IO_WRITE;
    }

    return nResult;
}

bool FileExists(wchar_t * pFilename)
{    
    if (0 == wcscmp(pFilename, L"-")  ||  0 == wcscmp(pFilename, L"/dev/stdin"))
        return true;

#ifdef _WIN32

    bool bFound = false;

    WIN32_FIND_DATA WFD;
    HANDLE hFind = FindFirstFile(pFilename, &WFD);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        bFound = true;
        FindClose(hFind);
    }

    return bFound;

#else

    CSmartPtr<char> spFilenameUTF8((char *) CAPECharacterHelper::GetUTF8FromUTF16(pFilename), TRUE);

    struct stat b;

    if (stat(spFilenameUTF8, &b) != 0)
        return false;

    if (!S_ISREG(b.st_mode))
        return false;

    return true;

#endif
}

void * AllocateAligned(int nBytes, int nAlignment)
{
#ifdef _MSC_VER
    return _aligned_malloc(nBytes, nAlignment);
#else
    void * pMemory = NULL;
    posix_memalign(&pMemory, nAlignment, nBytes);
    return pMemory;
#endif
}

void FreeAligned(void * pMemory)
{
#ifdef _MSC_VER
    _aligned_free(pMemory);
#else
    free(pMemory);
#endif
}

bool GetMMXAvailable()
{
	bool bMMX = false;
#ifdef _MSC_VER
	#define CPU_MMX (1 << 23)

	int cpuInfo[4] = { 0 };
	__cpuid(cpuInfo, 0);

	int nIds = cpuInfo[0];
	if (nIds >= 1)
	{
		__cpuid(cpuInfo, 1);
		if (cpuInfo[3] & CPU_MMX)
			bMMX = true;
	}
#endif
	return bMMX;
}

bool GetSSEAvailable()
{
    bool bSSE = false;
#ifdef _MSC_VER
    #define CPU_SSE2 (1 << 26)

    int cpuInfo[4] = { 0 };
    __cpuid(cpuInfo, 0);

    int nIds = cpuInfo[0];
    if (nIds >= 1)
    {
        __cpuid(cpuInfo, 1);
        if (cpuInfo[3] & CPU_SSE2)
			bSSE = true;
    }
#endif
    return bSSE;
}

bool StringIsEqual(const str_utfn * pString1, const str_utfn * pString2, bool bCaseSensitive, int nCharacters)
{
	// wcscasecmp isn't available on OSX 10.6 and sometimes it's hard to find other string comparisons that work reliably on different
	// platforms, so we'll just roll our own simple version here (performance of this function isn't critical to APE performance)

	// default to 'true' so that comparing two empty strings will be a match
	bool bResult = true;

	// if -1 is passed in, compare the entire string
	if (nCharacters == -1)
		nCharacters = 0x7FFFFFFF;

	if (nCharacters > 0)
	{
		// walk string
		str_utfn f, l;
		do
		{
			f = *pString1++;
			l = *pString2++;
			if (bCaseSensitive == false)
			{
				f = _totlower(f);
				l = _totlower(l);
			}
		}
		while ((--nCharacters) && (f != 0) && (f == l));

		// if we're still equal, it's a match
		bResult = (f == l);
	}

	return bResult;
}

}