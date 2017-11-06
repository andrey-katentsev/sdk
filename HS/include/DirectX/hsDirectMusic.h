/* Designed and programmed by Hyperlink, 2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

/* DirectMusic class header file */

#ifndef HS_DIRECTMUSIC_CLASS
#define HS_DIRECTMUSIC_CLASS

#include "hsDirectX.h"

#include <windows.h>
#include <dmusici.h>

/* Success codes */
#define DM_OK    S_OK
#define DM_FALSE S_FALSE
/* End success codes */

typedef class tagHSDirectMusic
{
private:
	HWND hWnd;                               // DirectMusic window handle
protected:
	HRESULT CreateLoader();                  // Creates IDirectMusicLoader interface
	HRESULT CreatePerformance();             // Creates IDirectMusicPerformance interface
public:
	IDirectMusicLoader *lpDMLoader;
	IDirectMusicSegment *lpDMSegment;
	IDirectMusicPerformance *lpDMPerformance;

	HRESULT Create(HWND hWnd);
	HRESULT ConfigurePerformance(BOOL bAutoDownload=TRUE,LONG lMasterVolume=100L,FLOAT fMaterTempo=1.0F);
	HRESULT Play(DWORD dwRepeats=0,DWORD dwFlags=DMUS_SEGF_DEFAULT);

	HRESULT LoadMIDI(LPCWSTR lpMIDIFile);
	HRESULT UnloadMIDI();

	HRESULT Release(); // Removes DirectMusic

	tagHSDirectMusic();
} HSDIRECTMUSIC;

typedef HSDIRECTMUSIC *PHSDIRECTMUSIC;
typedef HSDIRECTMUSIC FAR *LPHSDIRECTMUSIC;
typedef HSDIRECTMUSIC NEAR *NPHSDIRECTMUSIC;

#endif