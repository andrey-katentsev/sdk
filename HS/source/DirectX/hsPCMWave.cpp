#include "hsPCMWave.h"

tagHSPCMWave::tagHSPCMWave()
{
	dwCurrentPosition=0;
	dwWaveSize=0;
	lpPCMWaveHeader=NULL;
	pbPCMWaveData=NULL;
}

tagHSPCMWave::~tagHSPCMWave()
{ this->Close(); }

VOID tagHSPCMWave::Close(VOID)
{
	if(pbPCMWaveData!=NULL)
	{
		UnmapViewOfFile(pbPCMWaveData);
		pbPCMWaveData=NULL;
	}

	lpPCMWaveHeader=NULL;
	dwCurrentPosition=0;
	dwWaveSize=0;
}

BOOL tagHSPCMWave::Open(LPCSTR lpFileName)
{
	HANDLE hFile;
	HANDLE hMMFile; // Memory-mapped file
	DWORD dwFileSize;

	Close();

	hFile=CreateFile(lpFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,NULL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{ return FALSE; }

	dwFileSize=GetFileSize(hFile,NULL);

	hMMFile=CreateFileMapping(hFile,NULL,PAGE_READONLY,NULL,dwFileSize,NULL);
	CloseHandle(hFile);
	if(hMMFile==NULL)
	{ return FALSE; }

	pbPCMWaveData=(BYTE*)MapViewOfFile(hMMFile,FILE_MAP_READ,NULL,NULL,NULL);
	CloseHandle(hMMFile);

	if(pbPCMWaveData==NULL)
	{ return FALSE; }

	lpPCMWaveHeader=(LPPCMWAVEFORMAT)(pbPCMWaveData+PCMWAVEFORMAT_OFFSET);

	dwCurrentPosition=WAVE_HEADER_SIZE;
	dwWaveSize=*((DWORD*)(pbPCMWaveData+WAVE_HEADER_SIZE-sizeof(DWORD)));
	return TRUE;
}

DWORD tagHSPCMWave::Read(BYTE *pbWaveData, DWORD nBytesToRead)
{
	DWORD dwBytesReaded;
	DWORD dwBytesLeft=(dwWaveSize+WAVE_HEADER_SIZE)-dwCurrentPosition;

	if(pbWaveData==NULL || dwBytesLeft==0)
	{ return 0; }

	if(nBytesToRead<=dwBytesLeft)
	{
		CopyMemory(pbWaveData,pbPCMWaveData+dwCurrentPosition,nBytesToRead);
		dwCurrentPosition+=nBytesToRead;
		dwBytesReaded=nBytesToRead;
	}
	else
	{
		CopyMemory(pbWaveData,pbPCMWaveData+dwCurrentPosition,dwBytesLeft);
		dwBytesReaded=dwBytesLeft;
		FillMemory(pbWaveData+dwBytesReaded,nBytesToRead-dwBytesReaded,WAVE_PCM_SILENCE(lpPCMWaveHeader->wBitsPerSample));
		dwCurrentPosition+=dwBytesReaded;
	}
	return dwBytesReaded;
}

VOID tagHSPCMWave::Reset(VOID)
{
	if(pbPCMWaveData!=NULL)
	{ dwCurrentPosition=WAVE_HEADER_SIZE; }
}

DWORD tagHSPCMWave::GetWaveSize(VOID)
{ return ((pbPCMWaveData==NULL)?0:dwWaveSize); }

BOOL tagHSPCMWave::GetWaveHeader(LPPCMWAVEFORMAT lpPCMWaveHeader)
{
	if(pbPCMWaveData==NULL)
	{ return FALSE; }

	(*lpPCMWaveHeader)=(*(this->lpPCMWaveHeader));
	return TRUE;
}