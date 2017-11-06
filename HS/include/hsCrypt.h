/* Cryptography API Library */
/* Programmed by Hyperlink Software�, 2009 */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_CRYPTOGRAPHY_API_LIBRARY
#define HS_CRYPTOGRAPHY_API_LIBRARY

#include <windows.h>
//#include "hsWin32Types.h"
#include "hsTypes.h"

// ����� ��������� ����������.
typedef enum tagCipherMode
{
 HS_ENCRYPTION_MODE=0x01,
 HS_DECRYPTION_MODE=0x02
} HS_CIPHER_MODE;

typedef enum tagAESKeySize
{
 HS_AES_128_BIT=16,
 HS_AES_192_BIT=24,
 HS_AES_256_BIT=32
} HS_AES_KEY_SIZE;

#define HS_AES_UNKNOWN_KEY_SIZE 0x00000001

// ���� ��������
#define HS_ERROR_UNKNOWN_MODE 0x0000000000000000;

 // ���������� ���� ���������� �����-������������������ �� �������� �����.
void hsGammaXOR(const LPBYTE Data,LPBYTE EncryptedData,const LPBYTE Key,DWORD32 DataSize);

// S-block (Substitution - ������ [�����������])
// ���� ������ � ����, ��� ��������� ����������� ��������������� ���������� ������� ��������� �� ������ (����-��, ��� ������� ������) �������� ���������� ������ ������������, �������� �� �� ����� ������.

BYTE S(BYTE bByte); // ���������� 8-�� ������ S-���� (�������� ���)

BYTE S4(BYTE bBlock);     // 4-� ������ S-����
BYTE S8(BYTE bBlock);     // 8-�� ������ S-����
WORD S16(WORD wBlock);    // 16-�� ������ S-����
DWORD S32(DWORD dwBlock); // 32-� ������ S-����

// �������� (�� ��������� �������)
DWORD hsCaesarChipher(LPBYTE lpPlainText,LPBYTE lpChipherText,DWORD dwTextSize,BYTE bKey,CONST LPBYTE lpAlphabet,BYTE bAlphabetSize,BOOL bDecode); // ���� ������

/*
- ���� �����
- ���� ������� �����
- ���� �������
*/

// P-block (Permutation - ������������) [������� ������ S-�����, � P-����� �������� ����������� �����]
// ���� ������������ � ����, �������������� ������� ��������� ����� ����� ��� ��������� �����������, ��� ��� �������, ��������� ���� ����� ������ ���� ������� � ���������.

WORD P(WORD wWord); // ���������� 16-�� ������ P-����

WORD P16(WORD wBlock);    // 16-�� ������ P-����
DWORD P32(DWORD dwBlock); // 32-� ������ P-����

// ������� ����� [Block chiphers]
WORD hsSP16(WORD wBlock,BYTE (*S)(BYTE),WORD (*P)(WORD)); // 16-�� ������ SP-��������������. S - ������� ������, P - ������� ������������
DWORD hsSPN16(CONST LPBYTE bPlainText,DWORD dwTextLength,LPBYTE bChipherText,DWORD dwRounds,BYTE (*S)(BYTE),WORD (*P)(WORD)); // SP-���� [Substitution-Permutation Network (SP-Network)]
DWORD hsSPC16(CONST LPBYTE bPlainText,DWORD dwTextLength,LPBYTE bChipherText,WORD wKey,DWORD dwRounds,BYTE (*S)(BYTE),WORD (*P)(WORD)); // ������� ������������ ����������

DWORD64 hsFeistel64(DWORD64 dwData,DWORD32 dwKey,DWORD32 (*F)(DWORD32 dwData,DWORD32 dwKey)); // 64-� ������ �������������� ��������
DWORD64 hsExchange(DWORD64 dwData);

//DWORD32 hsFeistelNetwork(CONST LPDWORD64 dwData,DWORD32 (*K)(DWORD64 dwKey,BYTE bRound),DWORD32 (*F)(DWORD32 dwData,DWORD32 dwKey),DWORD64 dwKey,DWORD32 dwRounds,LPDWORD64 dwChipherText,HS_CIPHER_MODE hsMode);

#include "hsDES.h"
#include "hsRSA.h"

#pragma region Block Cipher Modes of Operation
DWORD64 hsPCBC(LPDWORD64 lpPlaintext,DWORD64 dwSize,DWORD64 dwKey,DWORD64 dwIV,LPDWORD64 lpCiphertext,DWORD64 (*BC)(DWORD64 dwPlaintext,DWORD64 dwKey,HS_CIPHER_MODE hsMode),HS_CIPHER_MODE hsMode);                   // ���������� � ������ ��������� ������ ����������� � ���������������� ������ [Propagating Cipher-Block Chaining (PCBC)]
DWORD64 hsTDEA(LPDWORD64 lpPlaintext,DWORD64 dwSize,DWORD64 dwKeyA,DWORD64 dwKeyB,DWORD64 dwKeyC,LPDWORD64 lpCiphertext,DWORD64 (*BC)(DWORD64 dwPlaintext,DWORD64 dwKey,HS_CIPHER_MODE hsMode),HS_CIPHER_MODE hsMode); // ������� ���������� � ������� ��������� DES [Triple Data Encryption Algorithm (TDEA)]
#pragma endregion

#pragma region GOST
DWORD64 hsGOST(DWORD64 dwData,DWORD32 dwKey[8],HS_CIPHER_MODE hsMode); // ���������� � ������� ��������� ���� 28147-89
DWORD64 hsEncryptFileGOST(LPCTSTR lpSrcFileName,LPCTSTR lpDstFileName,DWORD32 dwKey[8],HS_CIPHER_MODE hsMode);
#pragma endregion

#pragma region Advanced Encryption Standard (AES)
VOID hsSubBytesAES(LPBYTE lpState);
VOID hsShiftRowsAES(LPBYTE lpState);
VOID hsMixColumnsAES(LPBYTE lpState);

VOID hsISubBytesAES(LPBYTE lpState);
VOID hsIShiftRowsAES(LPBYTE lpState);
VOID hsIMixColumnsAES(LPBYTE lpState);

VOID hsAddRoundKeyAES(LPBYTE lpState,LPBYTE lpRoundKey);

LPBYTE* hsKeyScheduleAES(LPBYTE lpCipherKey);

VOID hsRotateWordAES(LPBYTE lpWord);

VOID hsAES(LPBYTE lpState,LPBYTE lpCipherKey,LPBYTE lpCipherText,HS_AES_KEY_SIZE hsKeySize,HS_CIPHER_MODE hsMode);
#pragma endregion

#endif