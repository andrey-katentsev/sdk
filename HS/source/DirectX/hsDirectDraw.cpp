#include "hsDirectDraw.h"

tagHSDirectDraw::tagHSDirectDraw()
{
	this->dwBackBufferCount=1;
	this->dwOffscreenCount=9;
	/*this->hWnd=NULL;
	this->lpBackBuffer=NULL;
	this->lpDD=NULL;
	this->lpDDPalette=NULL;
	this->lpFPS=NULL;
	//this->lplpOffscreenSurface=NULL;
	this->lpPrimarySurface=NULL;*/
	this->uFrame=0;
}

tagHSDirectDraw::~tagHSDirectDraw()
{ this->Release(); }

HRESULT tagHSDirectDraw::ClearSurface(LPDIRECTDRAWSURFACE7 lpDirectDrawSurface7)
{
	HRESULT hResult;
	DDSURFACEDESC2 ddSurfaceDescriptor;
	UINT uSurfaceWidth;
	UINT uSurfaceHeight;
	PBYTE pBuffer=NULL;

	ZeroMemory(&ddSurfaceDescriptor,sizeof(ddSurfaceDescriptor));
	ddSurfaceDescriptor.dwSize=sizeof(ddSurfaceDescriptor);

	hResult=lpDirectDrawSurface7->Lock(NULL,&ddSurfaceDescriptor,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
	if(FAILED(hResult))
	{ return hResult;	}

	uSurfaceWidth=ddSurfaceDescriptor.lPitch;
	uSurfaceHeight=ddSurfaceDescriptor.dwHeight;

	pBuffer=(PBYTE)ddSurfaceDescriptor.lpSurface;
	ZeroMemory(pBuffer,uSurfaceWidth*uSurfaceHeight);

	lpDirectDrawSurface7->Unlock(NULL);
	if(FAILED(hResult))
	{ return hResult;	}
	return DD_OK;
}

HRESULT tagHSDirectDraw::Create(HWND hWnd,DWORD dwCooperativeLevelFlags,DWORD dwDisplayWidth,DWORD dwDisplayHeight,DWORD dwColorDepth,DWORD dwRefreshRate)
{
	HRESULT hResult;

	this->lpPrimarySurface=NULL;
	this->lpBackBuffer=NULL;
	this->lpDDPalette=NULL;
	for(register unsigned int cx=0;cx<dwOffscreenCount;cx++)
	{ lpOffscreenSurface[cx]=NULL; }

	this->hWnd=hWnd;

	hResult=DirectDrawCreateEx(NULL,(LPVOID*)&lpDD,IID_IDirectDraw7,NULL);
	if(FAILED(hResult))
	{ return hResult; }

	hResult=lpDD->SetCooperativeLevel(this->hWnd,dwCooperativeLevelFlags);
	if(FAILED(hResult))
	{ return hResult; }

	hResult=lpDD->SetDisplayMode(dwDisplayWidth,dwDisplayHeight,dwColorDepth,dwRefreshRate,NULL);
	if(FAILED(hResult))
	{ return hResult; }

	/*
	CreateSurface()'
	PrepareSurface();
	*/
	this->dwDisplayHeight=dwDisplayHeight;
	this->dwDisplayWidth=dwDisplayWidth;
	return DD_OK;
}

HRESULT tagHSDirectDraw::CreateSurface(DWORD dwFlags,DWORD dwCaps,DWORD dwBackBufferCount,DWORD dwOffscreenCount)
{
	HRESULT hResult;
	DDSURFACEDESC2 ddSurfaceDescriptor;
	DDSCAPS2 ddsCaps;

	/* Primary surface */
	ZeroMemory(&ddSurfaceDescriptor,sizeof(ddSurfaceDescriptor));
	ddSurfaceDescriptor.dwSize=sizeof(ddSurfaceDescriptor);

	ddSurfaceDescriptor.dwFlags=dwFlags;
	ddSurfaceDescriptor.ddsCaps.dwCaps=dwCaps;
	ddSurfaceDescriptor.dwBackBufferCount=1;
	//ddSurfaceDescriptor.dwBackBufferCount=dwBackBufferCount;

	hResult=lpDD->CreateSurface(&ddSurfaceDescriptor,&lpPrimarySurface,NULL);
	if(FAILED(hResult))
	{ return hResult; }

	/* Back buffer(s) */
	//lplpBackBuffer=(LPDIRECTDRAWSURFACE7*)malloc(sizeof(LPDIRECTDRAWSURFACE7)*dwBackBufferCount);
	ZeroMemory(&ddsCaps,sizeof(ddsCaps));
	ddsCaps.dwCaps=DDSCAPS_BACKBUFFER;
	//for(register unsigned int cx=0;cx<dwBackBufferCount;cx++)
	//{
		hResult=lpPrimarySurface->GetAttachedSurface(&ddsCaps,&lpBackBuffer);
		if(FAILED(hResult))
		{ return hResult; }
	//}

	/* Offscreen surfaces */
	//lplpOffscreenSurface=(LPDIRECTDRAWSURFACE7*)malloc(sizeof(LPDIRECTDRAWSURFACE7)*dwOffscreenCount);

	for(register unsigned int cx=0;cx<dwOffscreenCount;cx++)
	{
		ZeroMemory(&ddSurfaceDescriptor,sizeof(ddSurfaceDescriptor));
		ddSurfaceDescriptor.dwSize=sizeof(ddSurfaceDescriptor);
		ddSurfaceDescriptor.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
		ddSurfaceDescriptor.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
		ddSurfaceDescriptor.dwWidth=FRAME_WIDTH;
		ddSurfaceDescriptor.dwHeight=FRAME_HEIGHT;
		hResult=lpDD->CreateSurface(&ddSurfaceDescriptor,&lpOffscreenSurface[cx],NULL);
		if(FAILED(hResult))
		{ return hResult; }
	}

	/* FPS surface */
	ZeroMemory(&ddSurfaceDescriptor,sizeof(ddSurfaceDescriptor));
	ddSurfaceDescriptor.dwSize=sizeof(ddSurfaceDescriptor);
	ddSurfaceDescriptor.dwFlags=DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	ddSurfaceDescriptor.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN;
	ddSurfaceDescriptor.dwWidth=FPS_WIDTH;
	ddSurfaceDescriptor.dwHeight=FPS_HEIGHT;
	hResult=lpDD->CreateSurface(&ddSurfaceDescriptor,&lpFPS,NULL);
	if(FAILED(hResult))
	{ return hResult;	}

	/*DDCOLORKEY ddColorKey;
	ddColorKey.dwColorSpaceLowValue=RGB(255,255,255);
	ddColorKey.dwColorSpaceHighValue=RGB(255,255,255);
	for(int cx=0;cx<9;cx++)
	{ this->lpOffscreenSurface[cx]->SetColorKey(DDCKEY_SRCBLT,&ddColorKey); }
	lpFPS->SetColorKey(DDCKEY_SRCBLT,&ddColorKey);*/

	this->dwBackBufferCount=dwBackBufferCount;
	this->dwOffscreenCount=dwOffscreenCount;
	return DD_OK;
}

VOID tagHSDirectDraw::DrawFrame(DWORD dwBackBufferIndex)
{
	RECT rPicture;

	//PrepareFrame();
	ClearSurface(lpBackBuffer);
	SetRect(&rPicture,0,0,FRAME_WIDTH,FRAME_HEIGHT);

	lpBackBuffer->BltFast((dwDisplayWidth-FRAME_WIDTH)/2,(dwDisplayHeight-FRAME_HEIGHT)/2,lpOffscreenSurface[uFrame],&rPicture,DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);
	UpdateFPS();
	SetRect(&rPicture,0,0,FPS_WIDTH,FPS_HEIGHT);
	lpBackBuffer->BltFast((dwDisplayWidth-FPS_WIDTH)/2,20,lpFPS,&rPicture,DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT);

	lpPrimarySurface->Flip(NULL,DDFLIP_WAIT);
}

VOID tagHSDirectDraw::NextFrame(VOID)
{	uFrame=(++uFrame<dwOffscreenCount)?uFrame:0; }

HRESULT tagHSDirectDraw::PrepareSurface(LPCSTR *lpFileName)
{
	/*lpDDPalette=CreateDirectDrawPalette8(lpDD,lpFileName[0]);
	if(lpDDPalette==NULL)
	{ return DD_FALSE; }

	lpPrimarySurface->SetPalette(lpDDPalette);*/

	for(register unsigned int cx=0;cx<dwOffscreenCount;cx++)
	{
		if(!LoadDIB(lpOffscreenSurface[cx],lpFileName[cx]))
		{ return DD_FALSE; }
	}
	ClearSurface(lpFPS);
	return DD_OK;
}

VOID tagHSDirectDraw::PrepareFrame(LPCSTR *lpFileName)
{
	if(lpPrimarySurface->IsLost())
	{
		lpPrimarySurface->Restore();
		lpBackBuffer->Restore();

		for(register unsigned int cx=0;cx<dwOffscreenCount;cx++)
		{
			if(lpOffscreenSurface[cx]->IsLost())
			{
				lpOffscreenSurface[cx]->Restore();
				LoadDIB(lpOffscreenSurface[cx],lpFileName[cx]);
			}
		}

		if(lpFPS->IsLost())
		{
			lpFPS->Restore();
			ClearSurface(lpFPS);
		}
	}
}

VOID tagHSDirectDraw::Release(VOID)
{
	if(lpDD!=NULL)
	{
		if(lpPrimarySurface!=NULL)
		{
			lpPrimarySurface->Release();
			lpPrimarySurface=NULL;
		}
		for(register unsigned int cx=0;cx<dwOffscreenCount;cx++)
		{
			if(lpOffscreenSurface[cx]!=NULL)
			{
				lpOffscreenSurface[cx]->Release();
				lpOffscreenSurface[cx]=NULL;
			}
		}
		if(lpDDPalette!=NULL)
		{
			lpDDPalette->Release();
			lpDDPalette=NULL;
		}
		if(lpFPS!=NULL)
		{
			lpFPS->Release();
			lpFPS=NULL;
		}
		lpDD->Release();
		lpDD=NULL;
	}
}

HRESULT tagHSDirectDraw::SetPalette(DWORD dwColorDepth,LPCSTR lpFileName)
{
	switch(dwColorDepth)
	{
	case 2:  // Monochrome
		{} break;
	case 4:  // 16 color mode
		{ lpDDPalette=CreateDirectDrawPalette4(lpDD,lpFileName); } break;
	case 8:  // 256 color mode
		{ lpDDPalette=CreateDirectDrawPalette8(lpDD,lpFileName); } break;
	case 16: // 65,536 color mode
		{} break;
	case 24: // 16,777,216 color mode
		{} break;
	case 32: // 4,294,967,296 color mode
		{} break;
	default:
		{ return DD_FALSE; }
	}

	if(lpDDPalette==NULL)
	{ return DD_FALSE; }

	return lpPrimarySurface->SetPalette(lpDDPalette);
}

HRESULT tagHSDirectDraw::SetTransparentColor(LPDIRECTDRAWSURFACE7 lpDirectDrawSurface7,DWORD dwColorSpaceHighValue,DWORD dwColorSpaceLowValue,DWORD dwFlags)
{
	DDCOLORKEY ddColorKey;

	ZeroMemory(&ddColorKey,sizeof(ddColorKey));
	ddColorKey.dwColorSpaceHighValue=dwColorSpaceHighValue;
	ddColorKey.dwColorSpaceLowValue=dwColorSpaceLowValue;

	return lpDirectDrawSurface7->SetColorKey(dwFlags,&ddColorKey);
}

VOID tagHSDirectDraw::UpdateFPS(VOID)
{
	HDC hDC;
	CHAR pFPS[16];
	DOUBLE fSeconds;

	static const long lPeriod=10;
	static long lFrameNumber=0;
	static DWORD dwPreviousTime=0;
	static DWORD dwCurrentTime=0;
	static int nFPS=0;

	lFrameNumber+=1;
	if(lFrameNumber==lPeriod)
	{
		dwPreviousTime=dwCurrentTime;
		dwCurrentTime=timeGetTime();

		fSeconds=DOUBLE(dwCurrentTime-dwPreviousTime)/1000.0f;
		nFPS=(int)((DOUBLE)lFrameNumber/fSeconds);

		lFrameNumber=0;

		wsprintf(pFPS,"FPS: %d",nFPS);
		ClearSurface(lpFPS);
		if(SUCCEEDED(lpFPS->GetDC(&hDC)))
		{
			SetTextColor(hDC,RGB(155,155,155));
			TextOut(hDC,0,0,pFPS,(int)strlen(pFPS));
			lpFPS->ReleaseDC(hDC);
		}
	}
}

LPDIRECTDRAWPALETTE CreateDirectDrawPalette4(LPDIRECTDRAW7 lpDD,LPCSTR lpFileName)
{
	HRESULT hResult;
	LPDIRECTDRAWPALETTE lpDirectDrawPalette;
	PALETTEENTRY PaletteEntry[16];
	LPRGBQUAD lpColorTable;
	DWORD nBytesRead;
	UINT uSize=sizeof(RGBQUAD)*16;
	LONG lOffset;

	HANDLE hFile=CreateFile(lpFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,NULL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{ return (LPDIRECTDRAWPALETTE)NULL; }

	lpColorTable=(LPRGBQUAD)malloc(uSize);
	lOffset=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	SetFilePointer(hFile,lOffset,NULL,FILE_BEGIN);
	ReadFile(hFile,lpColorTable,uSize,&nBytesRead,NULL);
	CloseHandle(hFile);

	for(register unsigned int cx=0;cx<256;cx++)
	{
		PaletteEntry[cx].peRed=lpColorTable[cx].rgbRed;
		PaletteEntry[cx].peBlue=lpColorTable[cx].rgbBlue;
		PaletteEntry[cx].peGreen=lpColorTable[cx].rgbGreen;
	}

	hResult=lpDD->CreatePalette(DDPCAPS_4BIT,PaletteEntry,&lpDirectDrawPalette,NULL);
	if(FAILED(hResult))
	{
		free(lpColorTable);
		return (LPDIRECTDRAWPALETTE)NULL;
	}

	free(lpColorTable);
	return lpDirectDrawPalette;
}

LPDIRECTDRAWPALETTE CreateDirectDrawPalette8(LPDIRECTDRAW7 lpDD,LPCSTR lpFileName)
{
	HRESULT hResult;
	LPDIRECTDRAWPALETTE lpDirectDrawPalette;
	PALETTEENTRY PaletteEntry[256];
	LPRGBQUAD lpColorTable;
	DWORD nBytesRead;
	UINT uSize=sizeof(RGBQUAD)*256;
	LONG lOffset;

	HANDLE hFile=CreateFile(lpFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,NULL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{ return (LPDIRECTDRAWPALETTE)NULL; }

	lpColorTable=(LPRGBQUAD)malloc(uSize);
	lOffset=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	SetFilePointer(hFile,lOffset,NULL,FILE_BEGIN);
	ReadFile(hFile,lpColorTable,uSize,&nBytesRead,NULL);
	CloseHandle(hFile);

	for(register unsigned int cx=0;cx<256;cx++)
	{
		PaletteEntry[cx].peRed=lpColorTable[cx].rgbRed;
		PaletteEntry[cx].peBlue=lpColorTable[cx].rgbBlue;
		PaletteEntry[cx].peGreen=lpColorTable[cx].rgbGreen;
	}

	hResult=lpDD->CreatePalette(DDPCAPS_8BIT|DDPCAPS_ALLOW256,PaletteEntry,&lpDirectDrawPalette,NULL);
	if(FAILED(hResult))
	{ lpDirectDrawPalette=NULL;	}

	free(lpColorTable);
	return lpDirectDrawPalette;
}

BOOL LoadDIB(LPDIRECTDRAWSURFACE7 lpDirectDrawSurface7,LPCSTR lpDIBFile)
{
	BYTE *pDIB=NULL;
	BYTE *pData=NULL;
	//DWORD dwDIBSize;
	DWORD dwFileSize;
	DWORD nBytesRead;
	BITMAPINFO *pDIBInfo;
	BITMAPFILEHEADER *pDIBHeader;
	HDC hDC;

	HANDLE hFile=CreateFile(lpDIBFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{ return FALSE; }

	dwFileSize=GetFileSize(hFile,NULL);
	//dwDIBSize=dwFileLength-sizeof(BITMAPFILEHEADER);

	//pDIB=(BYTE*)malloc(dwDIBSize);
	pDIB=(BYTE*)malloc(dwFileSize);
	if(pDIB==NULL)
	{ return FALSE; }

	//SetFilePointer(hFile,sizeof(BITMAPFILEHEADER),NULL,FILE_BEGIN);
	//ReadFile(hFile,&DIBHeader,sizeof(BITMAPFILEHEADER),&nBytesRead,NULL);
	//ReadFile(hFile,pDIB,dwDIBSize,&nBytesRead,NULL);
	ReadFile(hFile,pDIB,dwFileSize,&nBytesRead,NULL);
	CloseHandle(hFile);

	//WORD wOffset=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;

	//pDIBInfo=(BITMAPINFO*)pDIB;
	//pData=pDIB+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
	pDIBHeader=(BITMAPFILEHEADER*)pDIB;
	pDIBInfo=(BITMAPINFO*)(pDIB+sizeof(BITMAPFILEHEADER));
	pData=pDIB+(pDIBHeader->bfOffBits);

	if(SUCCEEDED(lpDirectDrawSurface7->GetDC(&hDC)))
	{
		StretchDIBits(hDC,0,0,FRAME_WIDTH,FRAME_HEIGHT,0,0,FRAME_WIDTH,FRAME_HEIGHT,pData,pDIBInfo,0,SRCCOPY);
		lpDirectDrawSurface7->ReleaseDC(hDC);
	}
	free(pDIB);
	return TRUE;
}