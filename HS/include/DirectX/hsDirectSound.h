/* Designed and programmed by Hyperlink, 2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

/* DirectSound class header file */

#ifndef HS_DIRECTSOUND_CLASS
#define HS_DIRECTSOUND_CLASS

#include "hsDirectX.h"

#include <windows.h>
#include <dsound.h>

#include "hsPCMWave.h"

/* Buffer format definitions */
/* Channel */
#define HS_DSBF_MONO   1
#define HS_DSBF_STEREO 2
/* Bitrate (bit per second) */
#define HS_DSBF_8BPS   8
#define HS_DSBF_16BPS 16
/* Frequency (sample per second) */
#define HS_DSBF_8KHZ   8000
#define HS_DSBF_11KHZ 11025
#define HS_DSBF_12KHZ 12000
#define HS_DSBF_16KHZ 16000
#define HS_DSBF_22KHZ 22050
#define HS_DSBF_24KHZ 24000
#define HS_DSBF_32KHZ 32000
#define HS_DSBF_44KHZ 44100
#define HS_DSBF_48KHZ 48000
/* End buffer format definitions */

/* Success codes */
#define DS_FALSE S_FALSE
/* End success codes */

#define RADIUS 10.0

typedef class tagHSDirectSound
{
private:
	HWND hWnd;                               // Window handle
	HANDLE hThread;                          // Thread handle
	DWORD dwThreadID;                        // Thread ID

	DWORD dwBufferSize;                      // Buffer size in bytes
	DWORD dwBufferLength;                    // Buffer length in seconds (Default: 10)
public:
	LPDIRECTSOUND lpDS;                      // DirectSound intrface
	LPDIRECTSOUNDBUFFER lpDSPrimaryBuffer;   // Primary DirectSound buffer
	LPDIRECTSOUNDBUFFER lpDSSecondaryBuffer; // Secondary DirectSound buffer
	LPDIRECTSOUND3DBUFFER lpDS3DBuffer;      // DirectSound3D buffer

	LPDIRECTSOUND3DLISTENER lpDS3DListener;  // DirectSound3D listener

	LPDIRECTSOUNDNOTIFY lpDSNotify;
	DSBPOSITIONNOTIFY lpDSNotifyPosition[2];
	HANDLE hEvent[2];
	UINT nEventCount;

	LPCRITICAL_SECTION lpcsWaveSound;

	HSPCMWAVE hsPCMWave;

	HRESULT Create(HWND hWnd,LPCGUID lpDevice,DWORD dwCooperativeLevel); // Creates DirectSound interface
	HRESULT CreatePrimaryBuffer(DWORD dwFlags);                          // Creates primary DirectSound buffer

	HRESULT CreateBuffer(DWORD dwBufferIndex,DWORD dwFlags,DWORD dwBufferSize,WORD wChannels,DWORD dwFrequency,WORD wBitrate,GUID DS3DAlgorithm); // Creates secondary DirectSound buffer
	HRESULT PrepareBuffer(DWORD dwBufferIndex,DWORD dwOffset,DWORD dwBytes,DWORD dwLockFlags,LPDWORD lpBytesRead); // Write to 'dwBufferIndex' buffer 'dwBytes' of data from 'dwOffset' position
	HRESULT PrepareListener();

	HRESULT CreateNotificationEvent(DWORD dwBufferIndex);

	void Play(DWORD dwBufferIndex,DWORD dwPlayPosition,DWORD dwPriority,DWORD dwFlags);
	void Stop(DWORD dwBufferIndex);                              // Stops playing sound

	HRESULT SetBufferDataFile(DWORD dwBufferIndex,LPCSTR lpFileName); // Associates buffer with data file

	HRESULT SetPrimaryBufferFormat(WORD wChannels,DWORD dwFrequency,WORD wBitrate); // Sets primary buffer format

	DWORD GetBufferPlayTime(DWORD dwBufferIndex);                // Returns buffer length in seconds
	void SetBufferPlayTime(DWORD dwBufferIndex,DWORD dwPlayTime); // Sets buffer length in seconds (Don't change buffer size if buffer already exist. Useful before CreateBuffer method call.)

	DWORD GetBufferSize(DWORD dwBufferIndex);                    // Returns buffer length in bytes
	void SetBufferSize(DWORD dwBufferIndex,DWORD dwSize);         // Sets buffer length in bytes (Don't change buffer size if buffer already exist)

	void NextTick(); // 3D sound demo

	void Release(); // Removes DirectSound interface

	tagHSDirectSound();
	~tagHSDirectSound();
} HSDIRECTSOUND;

typedef HSDIRECTSOUND *PHSDIRECTSOUND;
typedef HSDIRECTSOUND FAR *LPHSDIRECTSOUND;
typedef HSDIRECTSOUND NEAR *NPHSDIRECTSOUND;

#endif