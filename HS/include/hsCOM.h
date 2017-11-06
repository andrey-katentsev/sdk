/* COM [Communication Port] */
/* Programmed by Hyperlink Software�, 2009 */

/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_COMMUNICATION_PORT
#define HS_COMMUNICATION_PORT

#define HS_COMMUNICATION_PORT_VERSION 1.0

#include "hsWin32.h"

#define HS_COM_INPUT_BUFFER  PURGE_RXCLEAR
#define HS_COM_OUTPUT_BUFFER PURGE_TXCLEAR

typedef struct tagCOMMUNICATIONPORTINFO
{
 WCHAR wcPort[8]; // ��� �����
 BOOL bStatus;    // TRUE - ��������, FALSE - ����������
} COMMUNICATIONPORTINFO, NEAR* PCOMMUNICATIONPORTINFO, FAR* LPCOMMUNICATIONPORTINFO;

typedef class tagCOMMUNICATIONPORT
{
private:
 //WCHAR wcCOM[8];    // ��� COM ����� [COM1 - COM255]
 LPCTSTR lpstrCOM;  // ��� COM ����� [COM1 - COM255]
 HANDLE hCOM;       // ��������� �� COM ����
 COMMCONFIG cfgCOM; // ������������ COM �����
 COMMTIMEOUTS tCOM; // ��������� ����-���� COM �����
public:
 tagCOMMUNICATIONPORT();
 //~tagCOMMUNICATIONPORT();

 BOOL OpenPort(LPCTSTR lpstrPortName);                 // ��������� ��������� ����
 BOOL ClearPortBuffer(DWORD dwFlags);                  // ������� ��������� � dwFlags ������
 BOOL ClosePort(VOID);                                 // ��������� ����
 DWORD Send(LPCVOID lpBuffer,DWORD nBytesToSend);      // ������� nBytesToSend ���� �� ������� ������ lpBuffer
 DWORD Receive(LPVOID lpBuffer,DWORD nBytesToReceive); // ��������� nBytesToReceive ����, �������� �� � ������� ������ lpBuffer
 BOOL SetConfig(LPCOMMCONFIG lpCommConfig);            // ������������� ��������� �����
 BOOL SetTimeouts(LPCOMMTIMEOUTS lpCommTimeouts);      // ������������� ��������� ��������� ������ � ������
 BOOL PortConfigDialog(HWND hWnd);                     // ���������� ����������� (�������������� ���������) ������ ��������� ����� � ��������� �������� � ��� ���������
 BYTE GetPorts(LPCOMMUNICATIONPORTINFO* lpPortInfo);   // ��������� ������ ��������� � ������� COM ������
} COMMUNICATIONPORT, NEAR *PCOMMUNICATIONPORT, FAR *LPCOMMUNICATIONPORT;

#endif