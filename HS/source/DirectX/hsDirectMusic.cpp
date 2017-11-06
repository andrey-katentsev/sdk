#include "hsDirectMusic.h"
#include <wchar.h>

HRESULT tagHSDirectMusic::Create(HWND hWnd)
{
	CHECK_ACCESS(hWnd);

	this->hWnd=hWnd;
	PROCESS_RESULT(CoInitialize(NULL)); // COM library initialize
	PROCESS_RESULT(CreateLoader());
	PROCESS_RESULT(CreatePerformance());
	return DM_OK;
}

HRESULT tagHSDirectMusic::CreateLoader()
{
	PROCESS_RESULT(CoCreateInstance(CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,IID_IDirectMusicLoader,(LPVOID*)&lpDMLoader));
	return DM_OK;
}

HRESULT tagHSDirectMusic::CreatePerformance()
{
	PROCESS_RESULT(CoCreateInstance(CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,IID_IDirectMusicPerformance,(LPVOID*)&lpDMPerformance));
	return DM_OK;
}

HRESULT tagHSDirectMusic::ConfigurePerformance(BOOL bAutoDownload,LONG lMasterVolume,FLOAT fMasterTempo)
{
	SET_IN_RANGE(fMasterTempo,DMUS_MASTERTEMPO_MIN,DMUS_MASTERTEMPO_MAX);

	CHECK_ACCESS(lpDMPerformance);
	PROCESS_RESULT(lpDMPerformance->Init(NULL,NULL,NULL)); // Default initialization
	PROCESS_RESULT(lpDMPerformance->SetGlobalParam(GUID_PerfAutoDownload,&bAutoDownload,sizeof(BOOL)));
	PROCESS_RESULT(lpDMPerformance->SetGlobalParam(GUID_PerfMasterVolume,&lMasterVolume,sizeof(LONG)));
	PROCESS_RESULT(lpDMPerformance->SetGlobalParam(GUID_PerfMasterTempo,&fMasterTempo,sizeof(FLOAT)));
	PROCESS_RESULT(lpDMPerformance->AddPortA(NULL));
	return DM_OK;
}

HRESULT tagHSDirectMusic::Play(DWORD dwRepeats,DWORD dwFlags)
{
	CHECK_ACCESS(lpDMSegment);
	PROCESS_RESULT(lpDMSegment->SetRepeats(dwRepeats));

	CHECK_ACCESS(lpDMPerformance);
	PROCESS_RESULT(lpDMPerformance->PlaySegment(lpDMSegment,dwFlags,0,NULL));
	return DM_OK;
}

HRESULT tagHSDirectMusic::LoadMIDI(LPCWSTR lpMIDIFile)
{
	DMUS_OBJECTDESC DMObjectDescriptor;
	WCHAR wszDirectory[MAX_PATH];

	ZeroMemory(&DMObjectDescriptor,sizeof(DMUS_OBJECTDESC));
	ZeroMemory(&wszDirectory,sizeof(wszDirectory));

	DMObjectDescriptor.dwSize=sizeof(DMUS_OBJECTDESC);

	GetCurrentDirectoryW(MAX_PATH,wszDirectory);
	wcscat_s(wszDirectory,MAX_PATH,L"\\mid");

	CHECK_ACCESS(lpDMLoader);
	PROCESS_RESULT(lpDMLoader->SetSearchDirectory(GUID_DirectMusicAllTypes,wszDirectory,FALSE));

	DMObjectDescriptor.guidClass=CLSID_DirectMusicSegment;
	wcscpy_s(DMObjectDescriptor.wszFileName,MAX_PATH,lpMIDIFile);
	DMObjectDescriptor.dwValidData=DMUS_OBJ_CLASS|DMUS_OBJ_FILENAME;

	PROCESS_RESULT(lpDMLoader->GetObjectA(&DMObjectDescriptor,IID_IDirectMusicSegment,(LPVOID*)&lpDMSegment));
	return DM_OK;
}

HRESULT tagHSDirectMusic::UnloadMIDI()
{	return DM_FALSE; }

HRESULT tagHSDirectMusic::Release()
{
	if(lpDMSegment!=NULL)
	{
		lpDMSegment->Release();
		lpDMSegment=NULL;
	}

	if(lpDMPerformance!=NULL)
	{
		PROCESS_RESULT(lpDMPerformance->Stop(NULL,NULL,NULL,NULL)); // Stop all
		PROCESS_RESULT(lpDMPerformance->CloseDown());
		lpDMPerformance->Release();
		lpDMPerformance=NULL;
	}

	if(lpDMLoader!=NULL)
	{
		lpDMLoader->Release();
		lpDMLoader=NULL;
	}

	CoUninitialize(); // COM library uninitialize
	return DM_OK;
}

tagHSDirectMusic::tagHSDirectMusic()
{
	hWnd=NULL;

	lpDMLoader=NULL;
	lpDMSegment=NULL;
	lpDMPerformance=NULL;
}