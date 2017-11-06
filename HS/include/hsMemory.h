/* Memory Managment Library */
/* Designed and Programmed by Hyperlink Software®, 2009 */
/* Copyright by © 2009, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_MEMORY_MANAGMENT_LIBRARY
#define HS_MEMORY_MANAGMENT_LIBRARY

#include <stdlib.h>

#pragma region Memory Management Functions
// Fills a block of memory with zeros.
// Параметры:
// [in] MemoryBlock  - указатель на начало участка памяти, которую необходимо заполнить нулями.
// [in] ObjectsCount - количество объектов типа T, которые расположены по адресу MemoryBlock.
// Возвращаемое значение: Нет.
// Не тестировалась. <Контроль качества>
template <class T> void hsZeroMemory(T *MemoryBlock,size_t ObjectsCount)
{
 for(register size_t i=0;i<ObjectsCount;i++)
 { MemoryBlock[i]=0; }
}

// Copies a block of memory from one location to another.
// Параметры:
// [in] Destination  - указатель на начало участка памяти, в которую необходимо скопировать данные.
// [in] Source       - указатель на начало участка памяти, из которой необходимо скопировать данные.
// [in] ObjectsCount - количество объектов типа T, которые необходимо скопировать.
// Возвращаемое значение: Нет.
// <Контроль качества>
template <class T> void hsCopyMemory(T *Destination,const T *Source,size_t ObjectsCount)
{
 for(register size_t i=0;i<ObjectsCount;i++)
 { Destination[i]=Source[i]; }
}
#pragma endregion

#pragma region Memory Allocation
// Allocate block of memory from heap.
// Параметры:
// [in] ObjectsCount - количество объектов типа T для хранения которых необходимо выделить память.
// Возвращаемое значение:
// Указатель на начало участка памяти в которой можно расположить ObjectsCount объектов типа T.
// После использовавния память следует явно освобождать функцией hsFree().
// <Контроль качества>
template <class T> T* hsAlloc(size_t ObjectsCount)
{ return new T[ObjectsCount]; }

// Reallocate memory block to new size.
// Параметры:
// [in] MemoryBlock  - указатель на начало участка ранее выделенной памяти.
// [in] ObjectsCount - количество объектов типа T для хранения которых необходимо выделить память.
// Возвращаемое значение:
// Указатель на начало участка памяти в которой можно расположить ObjectsCount объектов типа T.
// После использовавния память следует явно освобождать функцией hsFree().
// <Контроль качества> <!>
template <class T> T* hsRealloc(T *MemoryBlock,size_t ObjectsCount)
{
 T *NewBlock;

 if(MemoryBlock==NULL)
 { return hsAlloc<T>(ObjectsCount); }

 NewBlock=hsAlloc<T>(ObjectsCount);

 hsCopyMemory(NewBlock,MemoryBlock,ObjectsCount-1); // <-- ObjectsCount-1 не корректно! (Как определить число объектов?)

 delete [] MemoryBlock;

 MemoryBlock=NewBlock;

 return MemoryBlock;
}

// Deallocates or frees a memory block.
// Параметры:
// [in] MemoryBlock  - указатель на начало участка ранее выделенной памяти, которую нужно освободить.
// <Контроль качества>
template <class T> void hsFree(T *MemoryBlock)
{ delete [] MemoryBlock; }
#pragma endregion

#endif