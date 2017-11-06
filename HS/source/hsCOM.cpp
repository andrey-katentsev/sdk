/* COM [Communication Port] */
/* Programmed by Hyperlink Software®, 2009 */

/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#include "hsCOM.h"

// Открывает указанный порт
BOOL tagCOMMUNICATIONPORT::OpenPort(LPCTSTR lpstrPortName)
{
	DWORD dwSize=0;
	hCOM=CreateFile(lpstrPortName,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,0);
	if(hCOM==INVALID_HANDLE_VALUE) // Невозможно открыть порт
	{ return FALSE; }
 //StringCchCopy((STRSAFE_LPWSTR)wcCOM,8,(STRSAFE_LPCWSTR)lpwcPortName);
 lpstrCOM=lpstrPortName;
	GetCommConfig(hCOM,&cfgCOM,&dwSize);
	GetCommTimeouts(hCOM,&tCOM);
	return TRUE;
}

// Закрывает порт
BOOL tagCOMMUNICATIONPORT::ClosePort(VOID)
{
	if(CloseHandle(hCOM)==FALSE) // Невозможно закрыть порт
	{ return FALSE; }
 lpstrCOM=NULL;
	hCOM=INVALID_HANDLE_VALUE;
	ZeroMemory(&cfgCOM,sizeof(COMMCONFIG));
	ZeroMemory(&tCOM,sizeof(COMMTIMEOUTS));
	//ZeroMemory(&wcCOM,sizeof(wcCOM));
	return TRUE;
}

// Передаёт nBytesToSend байт из области памяти lpBuffer
DWORD tagCOMMUNICATIONPORT::Send(LPCVOID lpBuffer,DWORD nBytesToSend)
{
	DWORD dwBytesWritten=0;
	WriteFile(hCOM,lpBuffer,nBytesToSend,&dwBytesWritten,0);
	return dwBytesWritten;
}

// Принимает nBytesToReceive байт, помещает их в область памяти lpBuffer
DWORD tagCOMMUNICATIONPORT::Receive(LPVOID lpBuffer,DWORD nBytesToReceive)
{
	DWORD dwBytesRead=0;
	ReadFile(hCOM,lpBuffer,nBytesToReceive,&dwBytesRead,0);
	return dwBytesRead;
}

// Очищает указанный в dwFlags буффер
BOOL tagCOMMUNICATIONPORT::ClearPortBuffer(DWORD dwFlags)
{	return PurgeComm(hCOM,dwFlags); }

// Устанавливает параметры порта
BOOL tagCOMMUNICATIONPORT::SetConfig(LPCOMMCONFIG lpCommConfig)
{
 if(!SetCommConfig(hCOM,lpCommConfig,sizeof(COMMCONFIG)))
 { return FALSE; }
 CopyMemory(&cfgCOM,lpCommConfig,sizeof(COMMCONFIG));
 return TRUE;
}

// Устанавливает временные интервалы чтения и записи
BOOL tagCOMMUNICATIONPORT::SetTimeouts(LPCOMMTIMEOUTS lpCommTimeouts)
{
 if(!SetCommTimeouts(hCOM,lpCommTimeouts))
 { return FALSE; }
 CopyMemory(&tCOM,lpCommTimeouts,sizeof(COMMTIMEOUTS));
 return TRUE;
}

// Отображает стандартный (поддерживаемый драйвером) диалог настройки порта и применяет заданные в нем настройки
BOOL tagCOMMUNICATIONPORT::PortConfigDialog(HWND hWnd)
{
	if(!CommConfigDialog(lpstrCOM,hWnd,&cfgCOM))
 { return FALSE; }
 return SetCommConfig(hCOM,&cfgCOM,sizeof(COMMCONFIG));
}

// Формирует список имеющихся в системе COM портов
BYTE tagCOMMUNICATIONPORT::GetPorts(LPCOMMUNICATIONPORTINFO* lpPortInfo)
{
 COMMUNICATIONPORT COM;
	LPBYTE lpPorts=NULL;
	LPPORT_INFO_1 lpPortInfo1=NULL;
	WCHAR wcBuffer[8];
	WCHAR wcPortName[256][8];
	DWORD dwMemorySize=0;
	DWORD dwTotalPorts=0;
 BYTE nCount=0;

	EnumPorts(0,1,lpPorts,0,&dwMemorySize,&dwTotalPorts);
	lpPorts=new BYTE[dwMemorySize];
	if(lpPorts==NULL)
	{ return 0; }
	EnumPorts(0,1,lpPorts,dwMemorySize,&dwMemorySize,&dwTotalPorts);
	lpPortInfo1=(LPPORT_INFO_1)lpPorts;

	for(REGISTER DWORD i=0;i<dwTotalPorts;i++)
	{
		for(REGISTER BYTE nCOM=0;nCOM<0xFF;nCOM++)
		{
			StringCbPrintf(wcBuffer,sizeof(wcBuffer),L"COM%d:",nCOM);
			if(CSTR_EQUAL==CompareString(LOCALE_USER_DEFAULT,NORM_IGNORECASE,lpPortInfo1[i].pName,-1,wcBuffer,-1))
			{
    StringCbPrintf(wcBuffer,sizeof(wcBuffer),L"COM%d",nCOM);
				StringCbCopy((STRSAFE_LPWSTR)&wcPortName[nCount][0],16,wcBuffer);
    nCount++;
			}
		}
	}

 (*lpPortInfo)=new COMMUNICATIONPORTINFO[nCount];
 for(REGISTER BYTE i=0;i<nCount;i++)
 {
  StringCbCopy((*lpPortInfo)[i].wcPort,sizeof((*lpPortInfo)[i].wcPort),(STRSAFE_LPWSTR)&wcPortName[i][0]);
  if(COM.OpenPort((LPCWSTR)&wcPortName[i][0]))
  {
   (*lpPortInfo)[i].bStatus=TRUE;
   COM.ClosePort();
  }
  else
  { (*lpPortInfo)[i].bStatus=FALSE; }
 }
	return nCount;
}

// Конструктор
tagCOMMUNICATIONPORT::tagCOMMUNICATIONPORT()
{
 lpstrCOM=NULL;
	hCOM=INVALID_HANDLE_VALUE;
	ZeroMemory(&cfgCOM,sizeof(COMMCONFIG));
	ZeroMemory(&tCOM,sizeof(COMMTIMEOUTS));
	//ZeroMemory(&wcCOM,sizeof(wcCOM));
}