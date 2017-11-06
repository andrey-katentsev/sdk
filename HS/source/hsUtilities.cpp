#include "hsUtilities.h"

// Translates the text of a specified control in dialog box into a floating point number.
// Возвращаемое значение:
// Число с плавающей точкой (двойная точность)
// <Контроль качества>
double hsGetDialogItemDouble(HWND hWnd,int IDC)
{
 TCHAR Data[HS_DOUBLE_PRECISION+3];
 HWND hControl=GetDlgItem(hWnd,IDC);
 UINT nTotal=SendMessage(hControl,WM_GETTEXT,(WPARAM)HS_DOUBLE_PRECISION+3,(LPARAM)Data);
 // Заменяем запятую на точку, если необходимо
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

// Подсчёт числа несовпадений в двух наборах данных
// Параметры:
// [in] lpDataSetA - первый набор данных
// [in] lpDataSetB - второй набор данных
// [in] dwDataSize - размер данных в байтах (число элементов в наборе данных)
// Возвращаемое значение:
// Число несовпадений
// <Контроль качества>
DWORD32 hsMismatchCount(CONST LPBYTE lpDataSetA,CONST LPBYTE lpDataSetB,DWORD32 dwDataSize)
{
 DWORD32 dwCount=0;
 for(REGISTER DWORD32 i=0;i<dwDataSize;i++)
 { dwCount+=(lpDataSetA[i]==lpDataSetB[i]?0:1); }
 return dwCount;
}

// Решение квадратного уравнения A(x^2) + Bx + C = 0
// Параметры:
// Коэффициенты при соответствующих степенях
// [in] A
// [in] B
// [in] C
// Вещественные корни уравнения
// [out] X1
// [out] X2
// Возвращаемое значение:
// Число корней уравения {0,1,2}
// <Контроль качества>
// <Без оптимизации>
BYTE hsSolveQuadraticEquation(CONST DOUBLE A,CONST DOUBLE B,CONST DOUBLE C,DOUBLE &X1,DOUBLE &X2)
{
 DOUBLE D=B*B-4.0*A*C; // Дискриминант

 // Вещественных корней нет
 if(D<0.0)
 { return 0; }

 // Один корень
 if(D==0.0)
 {
  X1=(-B)/(2.0*A);
  X2=X1;
  return 1;
 }

 // Два корня
 D=sqrt(D);
 X1=((-B)+D)/(2.0*A);
 X2=((-B)-D)/(2.0*A);
 return 2;
}
*/