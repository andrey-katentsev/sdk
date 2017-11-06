/* Network Utilities Library */
/* Designed and Programmed by Hyperlink Software®, 2009 */
/* ©2009, Hyperlink Software® */

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
// Коды возврата протокола HTTP
#define HTTP_OK              "200 OK"
#define HTTP_NOT_FOUND       "404 Not Found"
#define HTTP_FORBIDDEN       "403 Forbidden"
#define HTTP_SERER_ERROR     "500 Internal Server Error"
#define HTTP_NOT_IMPLEMENTED "501 Not Implemented"

/*
Классификация статус-кодов HTTP
1ХХ - Информационное. Запрос принят, процесс продолжается. 
2ХХ - Успех. Сообщение было успешно принято. 
3ХХ - Перенаправление. Для завершения запроса необходимо произвести ряд действий. 
4ХХ - Ошибка клиента. Запрос содержит синтаксическую ошибку и не может быть удовлетворен. 
5ХХ - Ошибка сервера. Сервер не может выполнить внешний корректный запрос. 

200 OK - Запрос удовлетворен. 
301 Moved Permanently - Запрашиваемому ресурсу присвоен новый постоянный URL. 
302 Moved Temporarily - Запрашиваемый ресурс временно находится по новому URL. 
400 Bad Request - Запрос содержит синтаксическую ошибку и не может быть принят сервером. 
401 Unauthorized - Запрос требует аутентификации пользователя. 
403 Forbidden - Запрос понят сервером но не может быть принят по неопределенным причинам. 
404 Not Found - Сервер не нашел ничего, что могло бы соответствовать URI запроса. Сервер не указывает является ли эта ситуация постоянной или временной. 
407 Proxy Authentication Required - Прокси-сервер (firewaal) требует авторизации. Эта ошибка может возникать в случае, если прокси-сервер неисправен. 
500 Internal Server Error - Ошибка сервера. Сервер столкнулся с непредвиденными обстоятельствами, которые не позволяют ему выполнить запрос. 
501 Not Implemented - Сервер не обладает возможностями, необходимыми для реализации запроса. 
502 Bad Gateway - Сервер получил некорректный ответ от шлюза, к которому он обратился, пытаясь выполнить запрос.
*/

// Заголовок
#define HTTP_HEADER "HTTP/1.1 %s\r\nServer: %s\r\nAccept-Ranges: bytes\r\nContent-Length: %I32u\r\nConnection: close\r\nContent-Type: %s\n\n"

// Типы содержимого
#define HTTP_MIME_TYPE_HTML   "text/html"
#define HTTP_MIME_TYPE_MSWORD "application/msword"
#define HTTP_MIME_TYPE_JPEG   "image/jpeg"
#define HTTP_MIME_TYPE_ICON   "image/vnd.microsoft.icon"

DWORD hsGetContentType(LPCTSTR szFileName,LPTSTR szContentType);
#pragma endregion

#endif