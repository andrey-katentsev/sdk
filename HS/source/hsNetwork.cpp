#include "hsNetwork.h"

#include <tchar.h>

#pragma region Windows Sockets
// ������� �������� ����� ���� ���� ������������� � ���������� ������.
// ���������:
// [in] Peer - ��������� �� ������������ �����.
// ������������ ��������:
// ��������� �� ����������� �����, ���������� ����� �������� � ��������� ���� (����������� �������� �������).
// <�������� ��������>
CHAR* hsGetPeerIPv4(SOCKET Peer)
{
 SOCKADDR_IN SAPeer;
 INT nSize=sizeof(SAPeer);
 PCHAR pIPv4=NULL;
 getpeername(Peer,(SOCKADDR*)&SAPeer,&nSize);
 pIPv4=inet_ntoa(SAPeer.sin_addr);
 return pIPv4;
}
#pragma endregion

#pragma region HTTP
// ������� ���������� MIME-��� �����������.
// ���������:
// [in]  szFileName    - ��� �����, ��� ��� ����������� ����� ����������.
// [out] szContentType - ��������� �� ����� ������, � ������� ���������� ��������� MIME-��� �����������.
// ������������ ��������:
// ���������� ���������� � szContentType ��������. (�� ������� ������������ 0)
// <�������� ��������>
DWORD hsGetContentType(LPCTSTR szFileName,LPTSTR szContentType)
{
 DWORD dwCCH=0;
 TCHAR *pExt;
 pExt=(TCHAR*)_tcsrchr(szFileName,TEXT('.'));
 if(pExt!=NULL)
 {
  pExt++;
  if(_tcscmp(pExt,TEXT("html"))==0)
  {
   _tcscpy(szContentType,TEXT(HTTP_MIME_TYPE_HTML));
   dwCCH=_tcslen(TEXT(HTTP_MIME_TYPE_HTML));
  }
  if(_tcscmp(pExt,TEXT("jpg"))==0)
  {
   _tcscpy(szContentType,TEXT(HTTP_MIME_TYPE_JPEG));
   dwCCH=_tcslen(TEXT(HTTP_MIME_TYPE_JPEG));
  }
  if(_tcscmp(pExt,TEXT("jpeg"))==0)
  {
   _tcscpy(szContentType,TEXT(HTTP_MIME_TYPE_JPEG));
   dwCCH=_tcslen(TEXT(HTTP_MIME_TYPE_JPEG));
  }
  if(_tcscmp(pExt,TEXT("doc"))==0)
  {
   _tcscpy(szContentType,TEXT(HTTP_MIME_TYPE_MSWORD));
   dwCCH=_tcslen(TEXT(HTTP_MIME_TYPE_MSWORD));
  }
  if(_tcscmp(pExt,TEXT("ico"))==0)
  {
   _tcscpy(szContentType,TEXT(HTTP_MIME_TYPE_ICON));
   dwCCH=_tcslen(TEXT(HTTP_MIME_TYPE_ICON));
  }
 }
 return dwCCH;
}
#pragma endregion