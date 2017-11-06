#include "hsWin32NotifyHandlers.h"

DWORD hsDirectSoundNotifyHandle(LPHSDIRECTSOUND lpDS)
{
	DWORD dwOffset=0;
	DWORD dwBytesRead=0;
	LPVOID lpBlock1=NULL;
	LPVOID lpBlock2=NULL;
	DWORD dwBlockSize1=0;
	DWORD dwBlockSize2=0;
	DWORD dwEventIndex=0;
	DWORD dwBufferSize=lpDS->GetBufferSize(NULL);

/*	while(TRUE)
	{
		dwEventIndex=WaitForMultipleObjects(2,lpDS->hEvent,FALSE,INFINITE);

#pragma region [Critical section: lpcsWaveSound]
		EnterCriticalSection(lpDS->lpcsWaveSound);
		if(lpDS->lphsPCMWave==NULL || lpDS->lpDSSecondaryBuffer==NULL)
		{
			LeaveCriticalSection(lpDS->lpcsWaveSound);
			ExitThread(HS_THREAD_FALSE);
		}

		dwEventIndex-=WAIT_OBJECT_0;
		dwOffset=lpDS->lpDSNotifyPosition[(dwEventIndex==0)?1:0].dwOffset;

		lpDS->lpDSSecondaryBuffer->Lock(dwOffset,dwBufferSize/2,&lpBlock1,&dwBlockSize1,&lpBlock2,&dwBlockSize2,NULL);

		dwBytesRead=lpDS->lphsPCMWave->Read((PBYTE)lpBlock1,dwBlockSize1);
		//if(dwBytesRead<dwBlockSize1)
		//{ lpDS->lphsPCMWave->Reset(); }

		lpDS->lpDSSecondaryBuffer->Unlock(lpBlock1,dwBlockSize1,lpBlock2,dwBlockSize2);
		LeaveCriticalSection(lpDS->lpcsWaveSound);
#pragma endregion
	}*/
	ExitThread(HS_THREAD_FALSE);
}