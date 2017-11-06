#include "hsHash.h"
// Функция для вычисления значения хэш-функции Peneel-Bosselaers-Govaerts-Vandewalle для заданного набора данных.
// Параметры:
// [in] Data     - указатель на область памяти в которой располагаются данные.
// [in] DataSize - размер данных(*).
// [in] IG       - начальное значение.
// [in] IH       - начальное значение.
// [out] LHash   - указатель на область памяти, в которую следует сохранить младшие 64 бита значения хэш-функции.
// [out] RHash   - указатель на область памяти, в которую следует сохранить старшие 64 бита значения хэш-функции.
// [in] F        - функция блочного алгоритма шифрования (с длиной блока в 64 бита).
// Возвращаемое значение: Нет.
// Примечания: Размер данных (DataSize) должен быть кратен 16 байтам (128 битам).
// (IG,IH) - вектор инициализации.
// <Контроль качества>
void hsPBGV(const LPBYTE Data,UINT DataSize,DWORD64 IG,DWORD64 IH,LPDWORD64 LHash,LPDWORD64 RHash,DWORD64 (*F)(DWORD64 Data,DWORD64 Key))
{
 DWORD64 G,H,Gn,Hn,L,R;
 UINT Index,K=DataSize/16;
 // Инициализация.
 G=IG;
 H=IH;
 //Вычисление хэш-функции.
 for(UINT i=0;i<K;i++)
 {
  //Index=8*i;
  Index=16*i;

  // Левый блок.
  L=*(LPDWORD64)(&Data[Index]);
  // Правый блок.
  R=*(LPDWORD64)(&Data[Index+8]);

  Gn=F(R^G,L^H)^R^G^H;
  Hn=F(H^G,L^R)^L^G^H;

  G=Gn;
  H=Hn;
 }

 *LHash=G;
 *RHash=H;
}