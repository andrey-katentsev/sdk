#include "hsUtilities.h"

// Translates the text of a specified control in dialog box into a floating point number.
// ������������ ��������:
// ����� � ��������� ������ (������� ��������)
// <�������� ��������>
double hsGetDialogItemDouble(HWND hWnd,int IDC)
{
 TCHAR Data[HS_DOUBLE_PRECISION+3];
 HWND hControl=GetDlgItem(hWnd,IDC);
 UINT nTotal=SendMessage(hControl,WM_GETTEXT,(WPARAM)HS_DOUBLE_PRECISION+3,(LPARAM)Data);
 // �������� ������� �� �����, ���� ����������
 for(register UINT i=0;i<nTotal;i++)
 { Data[i]=(Data[i]==',')?('.'):Data[i]; }
 return (double)hsStringToDouble(Data);
}

#include <vector>

void hsLoadMessageBoxInfoW(HINSTANCE hInstance, UINT uCaptionID, UINT uTextID, std::wstring& strCaption, std::wstring& strText, DWORD dwBufferSize)
{
	std::vector<wchar_t> vecBuffer(dwBufferSize, 0);
	WORD wLength = static_cast<WORD>(LoadString(hInstance, uCaptionID, &vecBuffer[0], vecBuffer.size()));
	strCaption.assign(vecBuffer.begin(), vecBuffer.begin() + wLength); // WARNING: unsafe use of wLength!

	wLength = static_cast<WORD>(LoadString(hInstance, uTextID, &vecBuffer[0], vecBuffer.size()));
	strText.assign(vecBuffer.begin(), vecBuffer.begin() + wLength); // WARNING: unsafe use of wLength!
}

/*#include "hsWin32.h"
#include "hsUtilities.h"
#include <math.h>
#include <stddef.h>

// ������� ����� ������������ � ���� ������� ������
// ���������:
// [in] lpDataSetA - ������ ����� ������
// [in] lpDataSetB - ������ ����� ������
// [in] dwDataSize - ������ ������ � ������ (����� ��������� � ������ ������)
// ������������ ��������:
// ����� ������������
// <�������� ��������>
DWORD32 hsMismatchCount(CONST LPBYTE lpDataSetA,CONST LPBYTE lpDataSetB,DWORD32 dwDataSize)
{
 DWORD32 dwCount=0;
 for(REGISTER DWORD32 i=0;i<dwDataSize;i++)
 { dwCount+=(lpDataSetA[i]==lpDataSetB[i]?0:1); }
 return dwCount;
}

// ������� ����������� ��������� A(x^2) + Bx + C = 0
// ���������:
// ������������ ��� ��������������� ��������
// [in] A
// [in] B
// [in] C
// ������������ ����� ���������
// [out] X1
// [out] X2
// ������������ ��������:
// ����� ������ �������� {0,1,2}
// <�������� ��������>
// <��� �����������>
BYTE hsSolveQuadraticEquation(CONST DOUBLE A,CONST DOUBLE B,CONST DOUBLE C,DOUBLE &X1,DOUBLE &X2)
{
 DOUBLE D=B*B-4.0*A*C; // ������������

 // ������������ ������ ���
 if(D<0.0)
 { return 0; }

 // ���� ������
 if(D==0.0)
 {
  X1=(-B)/(2.0*A);
  X2=X1;
  return 1;
 }

 // ��� �����
 D=sqrt(D);
 X1=((-B)+D)/(2.0*A);
 X2=((-B)-D)/(2.0*A);
 return 2;
}
*/