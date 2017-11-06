#include <math.h>
#include <stdio.h>
#include "hsMath.h"
#include "hsBitwise.h"
#include "hsDirectSound.h"
#include "hsWin32NotifyHandlers.h"

HRESULT tagHSDirectSound::Create(HWND hWnd,LPCGUID lpDevice,DWORD dwCooperativeLevel)
{
	this->hWnd=hWnd;
	PROCESS_RESULT(DirectSoundCreate(lpDevice,&lpDS,NULL));
	PROCESS_RESULT(lpDS->SetCooperativeLevel(hWnd,dwCooperativeLevel));
	return DS_OK;
}

#pragma region [PRIMARY BUFFER]
HRESULT tagHSDirectSound::CreatePrimaryBuffer(DWORD dwFlags)
{
	DSBUFFERDESC dsBufferDescriptor;

	ZeroMemory(&dsBufferDescriptor,sizeof(DSBUFFERDESC));

	dsBufferDescriptor.dwSize=sizeof(DSBUFFERDESC);
	dsBufferDescriptor.dwFlags=DSBCAPS_PRIMARYBUFFER|dwFlags;

	CHECK_ACCESS(lpDS);
	PROCESS_RESULT(lpDS->CreateSoundBuffer(&dsBufferDescriptor,&lpDSPrimaryBuffer,NULL));
	return DS_OK;
}

HRESULT tagHSDirectSound::SetPrimaryBufferFormat(WORD wChannels,DWORD dwFrequency,WORD wBitrate)
{
	WAVEFORMATEX wfx;

	ZeroMemory(&wfx,sizeof(WAVEFORMATEX));

	wfx.wFormatTag=WAVE_FORMAT_PCM;
	wfx.nChannels=wChannels;
	wfx.nSamplesPerSec=dwFrequency;
	wfx.wBitsPerSample=wBitrate;
	wfx.nBlockAlign=(wBitrate*wChannels)/8;
	wfx.nAvgBytesPerSec=wfx.nSamplesPerSec*wfx.nBlockAlign;
	wfx.cbSize=0;

	CHECK_ACCESS(lpDSPrimaryBuffer);
	PROCESS_RESULT(lpDSPrimaryBuffer->SetFormat(&wfx));
	return DS_OK;
}
#pragma endregion
#pragma region [SECONDARY BUFFER]
HRESULT tagHSDirectSound::CreateBuffer(DWORD dwBufferIndex,DWORD dwFlags,DWORD dwBufferSize,WORD wChannels,DWORD dwFrequency,WORD wBitrate,GUID DS3DAlgorithm)
{
	DSBUFFERDESC dsBufferDescriptor;
	DS3DBUFFER ds3DBuffer;
	WAVEFORMATEX wfx;

	ZeroMemory(&dsBufferDescriptor,sizeof(DSBUFFERDESC));
	ZeroMemory(&ds3DBuffer,sizeof(DS3DBUFFER));
	ZeroMemory(&wfx,sizeof(WAVEFORMATEX));

	dsBufferDescriptor.dwSize=sizeof(DSBUFFERDESC);
	ds3DBuffer.dwSize=sizeof(DS3DBUFFER);

	wfx.wFormatTag=WAVE_FORMAT_PCM;
	wfx.nChannels=wChannels;
	wfx.nSamplesPerSec=dwFrequency;
	wfx.wBitsPerSample=wBitrate;
	wfx.nBlockAlign=(wBitrate*wChannels)/8;
	wfx.nAvgBytesPerSec=wfx.nSamplesPerSec*wfx.nBlockAlign;
	wfx.cbSize=0;

	dsBufferDescriptor.dwFlags=dwFlags;
	dsBufferDescriptor.lpwfxFormat=&wfx;

#pragma region [STATIC SECONDARY BUFFER]
	if(dwFlags AND DSBCAPS_STATIC)
	{
		dwBufferSize=(dwBufferSize<DSBSIZE_MIN)?DSBSIZE_MIN:dwBufferSize;
		dwBufferSize=(dwBufferSize>DSBSIZE_MAX)?DSBSIZE_MAX:dwBufferSize;
	}
#pragma endregion
#pragma region [STREAM SECONDARY BUFFER]
	else
	{ dwBufferSize=wfx.nAvgBytesPerSec*dwBufferLength; }
#pragma endregion

	dsBufferDescriptor.dwBufferBytes=dwBufferSize;

	if(dwFlags AND DSBCAPS_CTRL3D)
	{ dsBufferDescriptor.guid3DAlgorithm=DS3DAlgorithm; } // <-- DirectSound3D algoritm
	else
	{ dsBufferDescriptor.guid3DAlgorithm=GUID_NULL; }

	CHECK_ACCESS(lpDS);
	PROCESS_RESULT(lpDS->CreateSoundBuffer(&dsBufferDescriptor,&lpDSSecondaryBuffer,NULL));

	if(dwFlags AND DSBCAPS_CTRL3D) // <-- DirectSound3D
	{
		PROCESS_RESULT(lpDSSecondaryBuffer->QueryInterface(IID_IDirectSound3DBuffer,(LPVOID*)&lpDS3DBuffer));

		PROCESS_RESULT(lpDS3DBuffer->GetAllParameters(&ds3DBuffer));
		ds3DBuffer.flMinDistance=(D3DVALUE)1.0;
		ds3DBuffer.flMaxDistance=(D3DVALUE)2.5;
		ds3DBuffer.vPosition.x=(D3DVALUE)RADIUS;
		ds3DBuffer.vPosition.y=(D3DVALUE)RADIUS;
		ds3DBuffer.vPosition.z=(D3DVALUE)0;
		PROCESS_RESULT(lpDS3DBuffer->SetAllParameters(&ds3DBuffer,DS3D_IMMEDIATE));
	}

	this->dwBufferSize=dwBufferSize;
	return DS_OK;
}

HRESULT tagHSDirectSound::SetBufferDataFile(DWORD dwBufferIndex, LPCSTR lpFileName)
{
	if(!hsPCMWave.Open(lpFileName))
	{ return DS_FALSE; }
	return DS_OK;
}

HRESULT tagHSDirectSound::PrepareBuffer(DWORD dwBufferIndex,DWORD dwOffset,DWORD dwBytes,DWORD dwLockFlags,LPDWORD lpBytesRead)
{
	LPVOID lpBlock1=NULL;
	LPVOID lpBlock2=NULL;
	DWORD dwBlockSize1=0;
	DWORD dwBlockSize2=0;

	hsPCMWave.Reset();
	PROCESS_RESULT(lpDSSecondaryBuffer->Lock(dwOffset,dwBytes,&lpBlock1,&dwBlockSize1,&lpBlock2,&dwBlockSize2,dwLockFlags));
	*lpBytesRead=hsPCMWave.Read((PBYTE)lpBlock1,dwBlockSize1);
	PROCESS_RESULT(lpDSSecondaryBuffer->Unlock(lpBlock1,dwBlockSize1,lpBlock2,dwBlockSize2));
	return DS_OK;
}
//lpcsWaveSound=(LPCRITICAL_SECTION)malloc(sizeof(CRITICAL_SECTION));
	//InitializeCriticalSection(lpcsWaveSound);
	
/*#pragma region [PCMWAVEFORMAT -> WAVEFORMATEX]
	wfx.cbSize=0;
	wfx.nAvgBytesPerSec=wfFormat.wf.nAvgBytesPerSec;
	wfx.nBlockAlign=wfFormat.wf.nBlockAlign;
	wfx.nChannels=wfFormat.wf.nChannels;
	wfx.nSamplesPerSec=wfFormat.wf.nSamplesPerSec;
	wfx.wBitsPerSample=wfFormat.wBitsPerSample;
	wfx.wFormatTag=wfFormat.wf.wFormatTag;
#pragma endregion*/

#pragma endregion

HRESULT tagHSDirectSound::CreateNotificationEvent(DWORD dwBufferIndex)
{
	for(register unsigned int cx=0;cx<nEventCount;cx++)
	{
		hEvent[cx]=CreateEvent(NULL,FALSE,FALSE,NULL);
		if(hEvent==INVALID_HANDLE_VALUE)
		{ return DS_FALSE; }
	}

	PROCESS_RESULT(lpDSSecondaryBuffer->QueryInterface(IID_IDirectSoundNotify,(LPVOID*)&lpDSNotify));

	lpDSNotifyPosition[0].dwOffset=0;
	lpDSNotifyPosition[1].dwOffset=dwBufferSize/2;
	for(register unsigned int cx=0;cx<nEventCount;cx++)
	{ lpDSNotifyPosition[cx].hEventNotify=hEvent[cx]; }

	PROCESS_RESULT(lpDSNotify->SetNotificationPositions(nEventCount,lpDSNotifyPosition));

	hThread=CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)hsDirectSoundNotifyHandle,(LPHSDIRECTSOUND)this,NULL,&dwThreadID);
	if(hThread==NULL)
	{ return DS_FALSE; }
	return DS_OK;
}

void tagHSDirectSound::Play(DWORD dwBufferIndex,DWORD dwPlayPosition,DWORD dwPriority,DWORD dwFlags)
{
	lpDSSecondaryBuffer->SetCurrentPosition(dwPlayPosition);
	lpDSSecondaryBuffer->Play(0,dwPriority,dwFlags);
}

HRESULT tagHSDirectSound::PrepareListener()
{
	DS3DLISTENER ds3DListener;

	ZeroMemory(&ds3DListener,sizeof(DS3DLISTENER));
	ds3DListener.dwSize=sizeof(DS3DLISTENER);

	PROCESS_RESULT(lpDSPrimaryBuffer->QueryInterface(IID_IDirectSound3DListener,(LPVOID*)&lpDS3DListener));

	PROCESS_RESULT(lpDS3DListener->GetAllParameters(&ds3DListener));

	ds3DListener.vVelocity.x=0.0;
	ds3DListener.vVelocity.y=0.0;
	ds3DListener.vVelocity.z=0.0;
	ds3DListener.flDopplerFactor=DS3D_MAXDOPPLERFACTOR;
	ds3DListener.flRolloffFactor=1.5;

	PROCESS_RESULT(lpDS3DListener->SetAllParameters(&ds3DListener,DS3D_IMMEDIATE));
	return DS_OK;
}

void tagHSDirectSound::Release()
{
#pragma region [Critical section: csWaveSound]
	if(lpcsWaveSound!=NULL)
	{ EnterCriticalSection(lpcsWaveSound);	}

	// HANDLE
	for(register unsigned int cx=0;cx<nEventCount;cx++)
	{
		if(hEvent!=NULL)
		{
			CloseHandle(hEvent[cx]);
			hEvent[cx]=NULL;
		}
	}

	// HSPCMWAVE
	/*if(lpPCMWave!=NULL)
	{
		free(lpPCMWave);
		lpPCMWave=NULL;
	}*/

	// DS3DLISTNER
	if(lpDS3DListener!=NULL)
	{
		lpDS3DListener->Release();
		lpDS3DListener=NULL;
	}

	// DS3DBUFFER
	if(lpDS3DBuffer!=NULL)
	{
		lpDS3DBuffer->Release();
		lpDS3DBuffer=NULL;
	}

	// SECONDARY BUFFER
	if(lpDSSecondaryBuffer!=NULL)
	{
		lpDSSecondaryBuffer->Release();
		lpDSSecondaryBuffer=NULL;
	}

	// PRIMARY BUFFER
	if(lpDSPrimaryBuffer!=NULL)
	{
		lpDSPrimaryBuffer->Release();
		lpDSPrimaryBuffer=NULL;
	}

	// DIRECT SOUND INTERFACE
	if(lpDS!=NULL)
	{
		lpDS->Release();
		lpDS=NULL;
	}

	if(lpcsWaveSound!=NULL)
	{ LeaveCriticalSection(lpcsWaveSound); }
#pragma endregion

	Sleep(0); // Switch to other threads

	// CRITICAL SECTION
	if(lpcsWaveSound!=NULL)
	{
		DeleteCriticalSection(lpcsWaveSound);
		free(lpcsWaveSound);
		lpcsWaveSound=NULL;
	}
}

void tagHSDirectSound::Stop(DWORD dwBufferIndex)
{	lpDSSecondaryBuffer->Stop(); }

DWORD tagHSDirectSound::GetBufferPlayTime(DWORD dwBufferIndex)
{ return dwBufferLength; }

void tagHSDirectSound::SetBufferPlayTime(DWORD dwBufferIndex,DWORD dwPlayTime)
{ dwBufferLength=dwPlayTime; }

DWORD tagHSDirectSound::GetBufferSize(DWORD dwBufferIndex)
{ return dwBufferSize; }

void tagHSDirectSound::SetBufferSize(DWORD dwBufferIndex,DWORD dwSize)
{ dwBufferSize=dwSize; }

void tagHSDirectSound::NextTick()
{
	HDC hDC;
	RECT rect;
	CHAR str[256];

	static BYTE i=0;
	FLOAT fAngle=0.0f;
	UINT uX=150,uY=80;
	UINT uScaleX=5,uScaleY=5;

	D3DVECTOR d3dVector;

	fAngle=i*5*PI/180;
	d3dVector.x=RADIUS*cos(fAngle);
	d3dVector.y=RADIUS*sin(fAngle);
	d3dVector.z=0.0;

	i=(++i>=72)?0:i;

	if(lpDS3DBuffer!=NULL)
	{ lpDS3DBuffer->SetPosition(d3dVector.x,d3dVector.y,d3dVector.z,DS3D_IMMEDIATE); }

	hDC=GetDC(hWnd);
	GetClientRect(hWnd,&rect);
	PatBlt(hDC,rect.left,rect.top,rect.right,rect.bottom,PATCOPY);

	sprintf(str,"X=%.2f",d3dVector.x);
	TextOut(hDC,10,10,str,(int)strlen(str));

	sprintf(str,"Y=%.2f",d3dVector.y);
	TextOut(hDC,10,30,str,(int)strlen(str));

	sprintf(str,"Z=%.2f",d3dVector.z);
	TextOut(hDC,10,50,str,(int)strlen(str));

	Ellipse(hDC,uX-RADIUS*uScaleX,uY-RADIUS*uScaleY,uX+RADIUS*uScaleX,uY+RADIUS*uScaleY);

	MoveToEx(hDC,uX,uY,NULL);
	LineTo(hDC,uX+d3dVector.x*uScaleX,uY-d3dVector.y*uScaleY);

	ReleaseDC(hWnd,hDC);
}

tagHSDirectSound::tagHSDirectSound()
{
	hWnd=NULL;
	hThread=NULL;
	dwThreadID=0;

	dwBufferSize=0;
	dwBufferLength=10;

	lpDS=NULL;
	lpDSPrimaryBuffer=NULL;
	lpDSSecondaryBuffer=NULL;
	lpDS3DBuffer=NULL;

	lpDS3DListener=NULL;
	lpDSNotify=NULL;
	nEventCount=2;
	for(register unsigned int cx=0;cx<nEventCount;cx++)
	{	hEvent[cx]=NULL; }
	//lpPCMWave=NULL;
	lpcsWaveSound=NULL;
}

tagHSDirectSound::~tagHSDirectSound()
{ this->Release(); }