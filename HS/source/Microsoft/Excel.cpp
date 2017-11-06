// April 19, 2013

#include "C:\SDK\HS\include\Microsoft\Excel.h"
#include "C:\SDK\KAA\include\convert.h"
#include "C:\SDK\KAA\include\nullptr.h"
#include "C:\SDK\KAA\include\std.h"

#include <algorithm>
#include <map>

#define EXCEL_IID "Excel.Application"

/*sheet->Range["A1"]->FormulaR1C1 = L"=10*RAND()";
sheet->Range["A2"]->Value = 3.14159f;
sheet->Range["A2"]->Formula = L"10";*/

namespace // internal processing
{
	std::map<unsigned long, std::wstring> column_name;
	std::map<KAA::Spreadsheet::cell_format_t, std::wstring> s_cell_format;

	void SetupColumn(void)
	{
		column_name[1L] = L"A";
		column_name[2L] = L"B";
		column_name[3L] = L"C";
		column_name[4L] = L"D";
		column_name[5L] = L"E";
		column_name[6L] = L"F";
		column_name[7L] = L"G";
		column_name[8L] = L"H";
		column_name[9L] = L"I";
		column_name[10L] = L"J";
		column_name[11L] = L"K";
		column_name[12L] = L"L";
		column_name[13L] = L"M";
		column_name[14L] = L"N";
		column_name[15L] = L"O";
		column_name[16L] = L"P";
		column_name[17L] = L"Q";
		column_name[18L] = L"R";
		column_name[19L] = L"S";
		column_name[20L] = L"T";
		column_name[21L] = L"U";
		column_name[22L] = L"V";
		column_name[23L] = L"W";
		column_name[24L] = L"X";
		column_name[25L] = L"Y";
		column_name[26L] = L"Z";
		column_name[27L] = L"AA";
		column_name[28L] = L"AB";
		column_name[29L] = L"AC";
		column_name[30L] = L"AD";
		column_name[31L] = L"AE";
		column_name[32L] = L"AF";
		column_name[33L] = L"AG";
		column_name[34L] = L"AH";
		column_name[35L] = L"AI";
		column_name[36L] = L"AJ";
		column_name[37L] = L"AK";
		column_name[38L] = L"AL";
		column_name[39L] = L"AM";
		column_name[40L] = L"AN";
		column_name[41L] = L"AO";
		column_name[42L] = L"AP";
		column_name[43L] = L"AQ";
		column_name[44L] = L"AR";
		column_name[45L] = L"AS";
		column_name[46L] = L"AT";
		column_name[47L] = L"AU";
		column_name[48L] = L"AV";
		column_name[49L] = L"AW";
		column_name[50L] = L"AX";
		column_name[51L] = L"AY";
		column_name[52L] = L"AZ";
		// ...
		// FUTURE: KAA: Base26(...)
	}

	void SetupCellFormat(void)
	{
		using namespace KAA::Spreadsheet;
		s_cell_format[CF_NUMBER] = L"0";
		s_cell_format[CF_PERCENT] = L"0%";
		s_cell_format[CF_DECIMAL] = L"0.0";
		s_cell_format[CF_DATE] = L"DD.MM.YYYY";
	}

	const std::wstring& GetCellFormat(KAA::Spreadsheet::cell_format_t format)
	{
		static bool s_initialized = false;
		return KAA::GetValue(s_cell_format, format, s_initialized, SetupCellFormat);
	}

	std::wstring variant_to_wstring(const _variant_t& value)
	{
		const _bstr_t temp = value;
		return std::wstring(static_cast<std::wstring::value_type*>(temp));
	}
}  // internal processing

namespace KAA
{
	namespace Spreadsheet
	{
		const std::wstring Column(column_index index)
		{
			static bool isReady = false;
			return GetValue(column_name, index, isReady, SetupColumn);
			/*if(isReady)
				return GetValue(column_name, index);
			else
			{
				SetupColumn();
				isReady = true;
				return GetValue(column_name, index);
			}*/
		}

		const std::wstring Row(row_index index)
		{
			return KAA::Convert::long_to_wstring(index);
		}

		class FFindKey : std::unary_function<std::map<unsigned long, std::wstring>::value_type, bool>
		{
		public:
			FFindKey(const argument_type::second_type& value) : m_value(value) {}
			result_type operator () (const argument_type& value)
			{ return m_value == value.second ? true : false; }
		private:
			const argument_type::second_type& m_value;
			FFindKey& operator = (const FFindKey&);
		};

		column_index Column(const std::wstring& column)
		{
			return std::find_if(column_name.begin(), column_name.end(), FFindKey(column))->first;
		}

		row_index Row(const std::wstring& index)
		{
			return KAA::Convert::wstring_to_long(index);
		}
	} // namespace Spreadsheet

	using Spreadsheet::column_index;
	using Spreadsheet::row_index;

	CExcel::CExcel() :
	m_pExcel(EXCEL_IID)
	{}

	CExcel::~CExcel()
	{
		m_pExcel->DisplayAlerts[0] = VARIANT_FALSE;
		m_pExcel->Quit();
	}

	void CExcel::Show(bool isShow)
	{
		m_pExcel->Visible[0] = isShow;
	}

	void CExcel::AddWorkbook(const std::wstring& wstrTemplate)
	{
		m_pCurrentWorkbook = wstrTemplate.empty() ? m_pExcel->Workbooks->Add() : m_pExcel->Workbooks->Add(wstrTemplate.c_str());
	}

	void CExcel::OpenWorkbook(const std::wstring& wstrPath, bool isReadOnly)
	{
		const _variant_t vUpdateLinks(0); // don't update
		m_pCurrentWorkbook = m_pExcel->Workbooks->Open(wstrPath.c_str(), vUpdateLinks, isReadOnly);
	}

	void CExcel::SaveWorkbook(void)
	{
		m_pCurrentWorkbook->Save();
	}

	void CExcel::SaveWorkbookAs
	(
		const std::wstring& wstrPath,
		Excel::XlFileFormat eFormat,
		const std::wstring& wstrPassword,
		bool isReadOnlyRecommended,
		bool isCreateBackup,
		Excel::XlSaveAsAccessMode eMode
	)
	{
		const _variant_t password(wstrPassword.empty() ? vtMissing : wstrPassword.c_str());
		m_pCurrentWorkbook->SaveAs(wstrPath.c_str(), eFormat, password, vtMissing, isReadOnlyRecommended, isCreateBackup, eMode);
	}

	void CExcel::CloseWorkbook(bool isSaveChanges, const std::wstring& wstrPath)
	{
		const _variant_t path(wstrPath.empty() ? vtMissing : wstrPath.c_str());
		m_pCurrentWorkbook->Close(isSaveChanges, path);
	}

	void CExcel::SelectWorksheet(unsigned long uIndex)
	{
		m_pCurrentSheet = m_pCurrentWorkbook->Worksheets->Item[uIndex];
	}

	void CExcel::SetWorksheetName(const std::wstring& wstrName)
	{
		m_pCurrentSheet->Name = wstrName.c_str();
	}

	void CExcel::AutoFilter(const std::wstring& wstrCell, const std::wstring& wstrCriteria)
	{
		_variant_t vField(1); // leftmost
		_variant_t vCriteria(wstrCriteria.c_str());
		Excel::XlAutoFilterOperator eOperator = Excel::xlFilterValues;
		m_pCurrentSheet->Range[wstrCell.c_str()]->AutoFilter(vField, vCriteria, eOperator);
	}

	row_index CExcel::GetUsedRows(void) const
	{
		Excel::RangePtr pRange = m_pCurrentSheet->UsedRange;
		return pRange->Rows->Count;
	}

	Spreadsheet::column_index CExcel::GetUsedColumns(void) const
	{
		Excel::RangePtr pRange = m_pCurrentSheet->UsedRange;
		return pRange->Columns->Count;
	}

	std::wstring CExcel::GetValue(row_index row, column_index column)
	{
		return variant_to_wstring(GetCell(row, column)->GetValue());
	}

	void CExcel::InsertFormula(row_index row, column_index column, const std::wstring& formula)
	{
		GetCell(row, column)->Formula = formula.c_str();
	}

	void CExcel::InsertValue(row_index row, column_index column, const _variant_t& value)
	{
		GetCell(row, column)->Value = value;
	}

	void CExcel::SetFormat(row_index row, column_index column, Spreadsheet::cell_format_t format)
	{
		GetCell(row, column)->NumberFormat = GetCellFormat(format).c_str();
	}

	void CExcel::SetFormat(row_index row, column_index column, const std::wstring& format)
	{
		GetCell(row, column)->NumberFormat = format.c_str();
	}

	std::wstring CExcel::GetFormat(row_index row, column_index column)
	{
		//const std::wstring& format = variant_to_wstring(GetCell(row, column)->GetNumberFormatLocal());
		return variant_to_wstring(GetCell(row, column)->GetNumberFormatW());
	}

	void CExcel::SetFont(row_index row, column_index column, const std::wstring& name, unsigned short size, bool bold, bool italic, bool underline)
	{
		Excel::FontPtr font = GetCell(row, column)->Font;
		font->Name = name.c_str();
		font->Size = size;
		font->Bold = bold;
		font->Italic = italic;
		font->Underline = underline;
	}

	unsigned long CExcel::FindRow(unsigned long column, const std::wstring& what)
	{
		const _variant_t after(m_pCurrentSheet->Cells->GetItem(1L, column)); // FUTURE: KAA: Remember that the search begins after this cell; the specified cell isn’t searched until the method wraps back around to this cell.
		Excel::RangePtr pRange = m_pCurrentSheet->Cells->Find(what.c_str(), after, Excel::xlValues, Excel::xlWhole, Excel::xlByColumns, Excel::xlNext);
		return pRange->Row;
	}

	Excel::RangePtr CExcel::GetCell(row_index row, column_index column)
	{
		using namespace KAA::Spreadsheet;
		const _variant_t cell( (Column(column) + Row(row)).c_str() );
		return m_pCurrentSheet->GetRange(cell);
	}
} // namespace KAA