/* Memory Managment Library */
/* Designed and Programmed by Hyperlink Software�, 2009 */
/* Copyright by � 2009, Hyperlink Software� */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_MEMORY_MANAGMENT_LIBRARY
#define HS_MEMORY_MANAGMENT_LIBRARY

#include <stdlib.h>

#pragma region Memory Management Functions
// Fills a block of memory with zeros.
// ���������:
// [in] MemoryBlock  - ��������� �� ������ ������� ������, ������� ���������� ��������� ������.
// [in] ObjectsCount - ���������� �������� ���� T, ������� ����������� �� ������ MemoryBlock.
// ������������ ��������: ���.
// �� �������������. <�������� ��������>
template <class T> void hsZeroMemory(T *MemoryBlock,size_t ObjectsCount)
{
 for(register size_t i=0;i<ObjectsCount;i++)
 { MemoryBlock[i]=0; }
}

// Copies a block of memory from one location to another.
// ���������:
// [in] Destination  - ��������� �� ������ ������� ������, � ������� ���������� ����������� ������.
// [in] Source       - ��������� �� ������ ������� ������, �� ������� ���������� ����������� ������.
// [in] ObjectsCount - ���������� �������� ���� T, ������� ���������� �����������.
// ������������ ��������: ���.
// <�������� ��������>
template <class T> void hsCopyMemory(T *Destination,const T *Source,size_t ObjectsCount)
{
 for(register size_t i=0;i<ObjectsCount;i++)
 { Destination[i]=Source[i]; }
}
#pragma endregion

#pragma region Memory Allocation
// Allocate block of memory from heap.
// ���������:
// [in] ObjectsCount - ���������� �������� ���� T ��� �������� ������� ���������� �������� ������.
// ������������ ��������:
// ��������� �� ������ ������� ������ � ������� ����� ����������� ObjectsCount �������� ���� T.
// ����� �������������� ������ ������� ���� ����������� �������� hsFree().
// <�������� ��������>
template <class T> T* hsAlloc(size_t ObjectsCount)
{ return new T[ObjectsCount]; }

// Reallocate memory block to new size.
// ���������:
// [in] MemoryBlock  - ��������� �� ������ ������� ����� ���������� ������.
// [in] ObjectsCount - ���������� �������� ���� T ��� �������� ������� ���������� �������� ������.
// ������������ ��������:
// ��������� �� ������ ������� ������ � ������� ����� ����������� ObjectsCount �������� ���� T.
// ����� �������������� ������ ������� ���� ����������� �������� hsFree().
// <�������� ��������> <!>
template <class T> T* hsRealloc(T *MemoryBlock,size_t ObjectsCount)
{
 T *NewBlock;

 if(MemoryBlock==NULL)
 { return hsAlloc<T>(ObjectsCount); }

 NewBlock=hsAlloc<T>(ObjectsCount);

 hsCopyMemory(NewBlock,MemoryBlock,ObjectsCount-1); // <-- ObjectsCount-1 �� ���������! (��� ���������� ����� ��������?)

 delete [] MemoryBlock;

 MemoryBlock=NewBlock;

 return MemoryBlock;
}

// Deallocates or frees a memory block.
// ���������:
// [in] MemoryBlock  - ��������� �� ������ ������� ����� ���������� ������, ������� ����� ����������.
// <�������� ��������>
template <class T> void hsFree(T *MemoryBlock)
{ delete [] MemoryBlock; }
#pragma endregion

#endif