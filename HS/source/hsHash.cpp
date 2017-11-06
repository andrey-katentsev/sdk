#include "hsHash.h"
// ������� ��� ���������� �������� ���-������� Peneel-Bosselaers-Govaerts-Vandewalle ��� ��������� ������ ������.
// ���������:
// [in] Data     - ��������� �� ������� ������ � ������� ������������� ������.
// [in] DataSize - ������ ������(*).
// [in] IG       - ��������� ��������.
// [in] IH       - ��������� ��������.
// [out] LHash   - ��������� �� ������� ������, � ������� ������� ��������� ������� 64 ���� �������� ���-�������.
// [out] RHash   - ��������� �� ������� ������, � ������� ������� ��������� ������� 64 ���� �������� ���-�������.
// [in] F        - ������� �������� ��������� ���������� (� ������ ����� � 64 ����).
// ������������ ��������: ���.
// ����������: ������ ������ (DataSize) ������ ���� ������ 16 ������ (128 �����).
// (IG,IH) - ������ �������������.
// <�������� ��������>
void hsPBGV(const LPBYTE Data,UINT DataSize,DWORD64 IG,DWORD64 IH,LPDWORD64 LHash,LPDWORD64 RHash,DWORD64 (*F)(DWORD64 Data,DWORD64 Key))
{
 DWORD64 G,H,Gn,Hn,L,R;
 UINT Index,K=DataSize/16;
 // �������������.
 G=IG;
 H=IH;
 //���������� ���-�������.
 for(UINT i=0;i<K;i++)
 {
  //Index=8*i;
  Index=16*i;

  // ����� ����.
  L=*(LPDWORD64)(&Data[Index]);
  // ������ ����.
  R=*(LPDWORD64)(&Data[Index+8]);

  Gn=F(R^G,L^H)^R^G^H;
  Hn=F(H^G,L^R)^L^G^H;

  G=Gn;
  H=Hn;
 }

 *LHash=G;
 *RHash=H;
}