/* Designed and programmed by Hyperlink, 2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

/* Direct Draw class header file */

#ifndef HS_DIRECTDRAW
#define HS_DIRECTDRAW

#define DIRECTX

#include <windows.h>
#include <mmsystem.h>
#include <ddraw.h>

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240

#define FPS_WIDTH 60
#define FPS_HEIGHT 40

LPDIRECTDRAWPALETTE CreateDirectDrawPalette4(LPDIRECTDRAW7 lpDD,LPCSTR lpFileName); // 4-bit color (16 color mode)
LPDIRECTDRAWPALETTE CreateDirectDrawPalette8(LPDIRECTDRAW7 lpDD,LPCSTR lpFileName); // 8-bit color (256 color mode)
BOOL LoadDIB(LPDIRECTDRAWSURFACE7 lpDirectDrawSurface7,LPCSTR lpDIBFile);

typedef class tagHSDirectDraw
{
private:
	HWND hWnd;                                  // DirectDraw window handle
	UINT uFrame;                                // Current frame number
	DWORD dwBackBufferCount;                    // Now 1
	DWORD dwOffscreenCount;                     // Now 9
	DWORD dwDisplayWidth;
	DWORD dwDisplayHeight;
public:
	LPDIRECTDRAW7 lpDD;                         // DirectDraw interface pointer
	LPDIRECTDRAWPALETTE lpDDPalette;            // DirectDraw palette pointer
	LPDIRECTDRAWSURFACE7 lpPrimarySurface;      // Primary surface pointer
	LPDIRECTDRAWSURFACE7 lpBackBuffer;          // Secondary surface pointer
	LPDIRECTDRAWSURFACE7 lpOffscreenSurface[9]; // Offscreen surface poiter
	LPDIRECTDRAWSURFACE7 lpFPS;                 // FPS surface

	tagHSDirectDraw();
	~tagHSDirectDraw();

	HRESULT ClearSurface(LPDIRECTDRAWSURFACE7 lpDirectDrawSurface7);
	HRESULT Create(HWND hWnd,DWORD dwCooperativeLevelFlags,DWORD dwDisplayWidth,DWORD dwDisplayHeight,DWORD dwColorDepth,DWORD dwRefreshRate); // (Modified)
	HRESULT CreateSurface(DWORD dwFlags,DWORD dwCaps,DWORD dwBackBufferCount,DWORD dwOffscreenCount); // (Modified)
	VOID DrawFrame(DWORD dwBackBufferIndex); // (Modified)
	VOID NextFrame(VOID);
	HRESULT PrepareSurface(LPCSTR *lpFileName); // Load data to offscreen surfaces (Modified)
	VOID PrepareFrame(LPCSTR *lpFileName);      // Restore all surfaces in necessary
	VOID Release(VOID);
	HRESULT SetPalette(DWORD dwColorDepth,LPCSTR lpFileName);
	HRESULT SetTransparentColor(LPDIRECTDRAWSURFACE7 lpDirectDrawSurface7,DWORD dwColorSpaceHighValue,DWORD dwColorSpaceLowValue,DWORD dwFlags);
	VOID UpdateFPS(VOID);
} HSDIRECTDRAW;

typedef HSDIRECTDRAW *PHSDIRECTDRAW;
typedef HSDIRECTDRAW FAR *LPHSDIRECTDRAW;
typedef HSDIRECTDRAW NEAR *NPHSDIRECTDRAW;

#endif