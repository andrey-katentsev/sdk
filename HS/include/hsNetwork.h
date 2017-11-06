/* Network Utilities Library */
/* Designed and Programmed by Hyperlink Software�, 2009 */
/* �2009, Hyperlink Software� */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_NETWORK_UTILITIES_LIBRARY
#define HS_NETWORK_UTILITIES_LIBRARY

#include <windows.h>

#pragma region Windows Sockets
// Function retrieves the address of the peer to which a socket is connected.
CHAR* hsGetPeerIPv4(SOCKET Peer);
#pragma endregion

#pragma region HTTP
// ���� �������� ��������� HTTP
#define HTTP_OK              "200 OK"
#define HTTP_NOT_FOUND       "404 Not Found"
#define HTTP_FORBIDDEN       "403 Forbidden"
#define HTTP_SERER_ERROR     "500 Internal Server Error"
#define HTTP_NOT_IMPLEMENTED "501 Not Implemented"

/*
������������� ������-����� HTTP
1�� - ��������������. ������ ������, ������� ������������. 
2�� - �����. ��������� ���� ������� �������. 
3�� - ���������������. ��� ���������� ������� ���������� ���������� ��� ��������. 
4�� - ������ �������. ������ �������� �������������� ������ � �� ����� ���� ������������. 
5�� - ������ �������. ������ �� ����� ��������� ������� ���������� ������. 

200 OK - ������ ������������. 
301 Moved Permanently - �������������� ������� �������� ����� ���������� URL. 
302 Moved Temporarily - ������������� ������ �������� ��������� �� ������ URL. 
400 Bad Request - ������ �������� �������������� ������ � �� ����� ���� ������ ��������. 
401 Unauthorized - ������ ������� �������������� ������������. 
403 Forbidden - ������ ����� �������� �� �� ����� ���� ������ �� �������������� ��������. 
404 Not Found - ������ �� ����� ������, ��� ����� �� ��������������� URI �������. ������ �� ��������� �������� �� ��� �������� ���������� ��� ���������. 
407 Proxy Authentication Required - ������-������ (firewaal) ������� �����������. ��� ������ ����� ��������� � ������, ���� ������-������ ����������. 
500 Internal Server Error - ������ �������. ������ ���������� � ��������������� ����������������, ������� �� ��������� ��� ��������� ������. 
501 Not Implemented - ������ �� �������� �������������, ������������ ��� ���������� �������. 
502 Bad Gateway - ������ ������� ������������ ����� �� �����, � �������� �� ���������, ������� ��������� ������.
*/

// ���������
#define HTTP_HEADER "HTTP/1.1 %s\r\nServer: %s\r\nAccept-Ranges: bytes\r\nContent-Length: %I32u\r\nConnection: close\r\nContent-Type: %s\n\n"

// ���� �����������
#define HTTP_MIME_TYPE_HTML   "text/html"
#define HTTP_MIME_TYPE_MSWORD "application/msword"
#define HTTP_MIME_TYPE_JPEG   "image/jpeg"
#define HTTP_MIME_TYPE_ICON   "image/vnd.microsoft.icon"

DWORD hsGetContentType(LPCTSTR szFileName,LPTSTR szContentType);
#pragma endregion

#endif