/* Linear Feedback Shift Register */
/* Designed and Programmed by Hyperlink Software®, 2009 */
/* © Copyright by Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_LINEAR_FEEDBACK_SHIFT_REGISTER
#define HS_LINEAR_FEEDBACK_SHIFT_REGISTER

#include <windows.h>

#define HS_LINEAR_FEEDBACK_SHIFT_REGISTER_VERSION 0.9

#define HS_LFSR_REGISTER_BITS_MAX 32

// Неприводимые полиномы.
// Polynomials.
#define CRC16_IBM_NORMAL                 0x8005
#define CRC16_IBM_REVERSED               0xA001
#define CRC16_IBM_REVERSE_OF_RECIPROCAL  0xC002

#define CRC32_IEEE_NORMAL                0x04C11DB7
#define CRC32_IEEE_REVERSED              0xEDB88320
#define CRC32_IEEE_REVERSE_OF_RECIPROCAL 0x82608EDB

typedef class tagLFSR32
{
private:
 DWORD dwRegister;  // Регистр
 DWORD dwGenerator; // Генератор [Битовая маска]

 BYTE nSize;        // Разрядность регистра
 BYTE bRandomBit;   // Случайный бит [Выходной бит]

 LPBYTE bRegister;  // Регистр
 LPBYTE bGenerator; // Генератор [Битовая маска]

public:
 tagLFSR32();                                            // Конструктор
 ~tagLFSR32();                                           // Деструктор
 int Set(DWORD dwRegister,DWORD dwGenerator,BYTE nSize); // Инициализация генератора
 int Remove(void);                                       // Деинициализация генератора
 BYTE NextBit(void);                                     // Генерация очередного бита
 BYTE CurrentBit(void);                                  // Получение текущего бита
} LFSR32;

#endif