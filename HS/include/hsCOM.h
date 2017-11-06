/* COM [Communication Port] */
/* Programmed by Hyperlink Software®, 2009 */

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
 WCHAR wcPort[8]; // Имя порта
 BOOL bStatus;    // TRUE - доступен, FALSE - недоступен
} COMMUNICATIONPORTINFO, NEAR* PCOMMUNICATIONPORTINFO, FAR* LPCOMMUNICATIONPORTINFO;

typedef class tagCOMMUNICATIONPORT
{
private:
 //WCHAR wcCOM[8];    // Имя COM порта [COM1 - COM255]
 LPCTSTR lpstrCOM;  // Имя COM порта [COM1 - COM255]
 HANDLE hCOM;       // Указатель на COM порт
 COMMCONFIG cfgCOM; // Конфигурация COM порта
 COMMTIMEOUTS tCOM; // Параметры тайм-аута COM порта
public:
 tagCOMMUNICATIONPORT();
 //~tagCOMMUNICATIONPORT();

 BOOL OpenPort(LPCTSTR lpstrPortName);                 // Открывает указанный порт
 BOOL ClearPortBuffer(DWORD dwFlags);                  // Очищает указанный в dwFlags буффер
 BOOL ClosePort(VOID);                                 // Закрывает порт
 DWORD Send(LPCVOID lpBuffer,DWORD nBytesToSend);      // Передаёт nBytesToSend байт из области памяти lpBuffer
 DWORD Receive(LPVOID lpBuffer,DWORD nBytesToReceive); // Принимает nBytesToReceive байт, помещает их в область памяти lpBuffer
 BOOL SetConfig(LPCOMMCONFIG lpCommConfig);            // Устанавливает параметры порта
 BOOL SetTimeouts(LPCOMMTIMEOUTS lpCommTimeouts);      // Устанавливает временные интервалы чтения и записи
 BOOL PortConfigDialog(HWND hWnd);                     // Отображает стандартный (поддерживаемый драйвером) диалог настройки порта и применяет заданные в нем настройки
 BYTE GetPorts(LPCOMMUNICATIONPORTINFO* lpPortInfo);   // Формирует список имеющихся в системе COM портов
} COMMUNICATIONPORT, NEAR *PCOMMUNICATIONPORT, FAR *LPCOMMUNICATIONPORT;

#endif