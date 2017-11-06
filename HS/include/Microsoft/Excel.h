// April 19, 2013

#pragma once

#include <string>

// Microsoft® Office 2003 ..\\OFFICE11
// Microsoft® Office 2007 ..\\OFFICE12
// Microsoft® Office 2010 ..\\OFFICE13
// Microsoft® Office 2012 ..\\OFFICE14

#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE12\MSO.DLL" rename("SearchPath", "_SearchPath") rename("RGB", "_RGB") rename("DocumentProperties", "_DocumentProperties")
#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
//#import "C:\Program Files\Common Files\Microsoft Shared\DAO\DAO360.DLL" rename("EOF", "EndOfFile") rename("BOF", "BegOfFile")
//#import "C:\Program Files\Microsoft Office\Office12\XL5EN32.OLB" rename("CopyFile", "_CopyFile") rename("DialogBox", "_DialogBox") rename("ReplaceText", "_ReplaceText")
#import "C:\Program Files\Microsoft Office\OFFICE12\EXCEL.EXE" rename("CopyFile", "_CopyFile") rename("DialogBox", "_DialogBox") rename("ReplaceText", "_ReplaceText") rename("RGB", "_RGB"), exclude("IFont", "IPicture")

/*
1987 Excel 2.0 for Windows
1990 Excel 3.0
1992 Excel 4.0
1993 Excel 5.0 (Office 4.2 & 4.3, also a 32-bit version for Windows NT only on the x86, PowerPC, Alpha, and MIPS architectures) This version of Excel includes a DOOM-like game as an Easter Egg.
1995 Excel for Windows 95 (version 7.0) included in Office 95
1997 Excel 97 (version 8.0) included in Office 97 (for x86 and Alpha). This version of Excel includes a flight simulator as an Easter Egg.
1999 Excel 2000 (version 9.0) included in Office 2000
2001 Excel 2002 (version 10) included in Office XP
2003 Office Excel 2003 (version 11) included in Office 2003
2007 Office Excel 2007 (version 12) included in Office 2007
2010 Excel 2010 (version 14) included in Office 2010
2013 Excel 2013 (version 15) included in Office 2013
*/

namespace KAA
{
	namespace Spreadsheet
	{
		enum cell_format_t
		{
			CF_NUMBER, // 0
			CF_PERCENT, // 0%
			CF_DECIMAL, // 0.0
			CF_DATE, // DD.MM.YYYY
			CF_CUSTOM
		};

		typedef unsigned long row_index;
		typedef unsigned long column_index;

		const std::wstring Column(column_index);
		const std::wstring Row(row_index);

		column_index Column(const std::wstring&);
		row_index Row(const std::wstring&);
	} // namespace Spreadsheet

	class CExcel
	{
	public:
		CExcel();
		~CExcel();

		enum EFileFormat
		{
			OFFICE2007 = Excel::xlExcel12,
			WORKBOOK_DEFAULT = Excel::xlWorkbookDefault
		};

		void Show(bool isShow = true);

		void AddWorkbook(const std::wstring& wstrTemplate = std::wstring());
		void OpenWorkbook(const std::wstring& wstrPath, bool isReadOnly = false);
		void SaveWorkbook(void);

		void SaveWorkbookAs
		(
			const std::wstring& wstrPath,
			Excel::XlFileFormat eFormat = Excel::xlWorkbookDefault,
			const std::wstring& wstrPassword = std::wstring(),
			bool isReadOnlyRecommended = false,
			bool isCreateBackup = false,
			Excel::XlSaveAsAccessMode eMode = Excel::xlNoChange
		);

		void CloseWorkbook(bool isSaveChanges = false, const std::wstring& wstrPath = std::wstring());

		void SelectWorksheet(unsigned long);
		void SetWorksheetName(const std::wstring&);

		void AutoFilter(const std::wstring& wstrCell, const std::wstring& wstrCriteria);

		Spreadsheet::row_index GetUsedRows(void) const;
		Spreadsheet::column_index GetUsedColumns(void) const;

		std::wstring GetValue(Spreadsheet::row_index, Spreadsheet::column_index);
		void InsertFormula(Spreadsheet::row_index, Spreadsheet::column_index, const std::wstring& formula);
		void InsertValue(Spreadsheet::row_index, Spreadsheet::column_index, const _variant_t&);
		void SetFormat(Spreadsheet::row_index, Spreadsheet::column_index, Spreadsheet::cell_format_t);
		void SetFormat(Spreadsheet::row_index, Spreadsheet::column_index, const std::wstring& format);
		std::wstring GetFormat(Spreadsheet::row_index, Spreadsheet::column_index);

		void SetFont(Spreadsheet::row_index, Spreadsheet::column_index, const std::wstring& name, unsigned short size = 8, bool bold = false, bool italic = false, bool underline = false);

		unsigned long FindRow(unsigned long column, const std::wstring& what);

	private:
		Excel::_ApplicationPtr m_pExcel;
		Excel::_WorkbookPtr m_pCurrentWorkbook;
		Excel::_WorksheetPtr m_pCurrentSheet;

		Excel::RangePtr GetCell(Spreadsheet::row_index, Spreadsheet::column_index);
	};
}