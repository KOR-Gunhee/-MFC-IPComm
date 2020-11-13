#include "stdafx.h"
#include "SqlDll_Interface.h"

CDB_SQL* Create_DB_SQL()
{
	CDB_SQL* pDB_SQL = CDB_SQL::Create();
	return pDB_SQL;
}

void SQL_Init(CDB_SQL * pDB_SQL, CString strDSN)
{
	if (nullptr != pDB_SQL)
		pDB_SQL->Init(strDSN);
}

void SQL_Delete(CDB_SQL** pDB_SQL)
{
	if (nullptr != (*pDB_SQL))
	{
		(*pDB_SQL)->Release();

		delete (*pDB_SQL);
		(*pDB_SQL) = nullptr;
	}
}

bool SQL_Connection_Check(CDB_SQL * pDB_SQL)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Connection_Check();

	return false;
}

bool SQL_Execute(CDB_SQL * pDB_SQL, CString strSQL)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Sql_Execute(strSQL);

	return false;
}

bool SQL_ReadStart(CDB_SQL * pDB_SQL, CString strSQL)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Sql_ReadStart(strSQL);

	return false;
}

void SQL_ReadEnd(CDB_SQL * pDB_SQL)
{
	if (nullptr != pDB_SQL)
		pDB_SQL->Sql_ReadEnd();
}

int SQL_ColCount(CDB_SQL * pDB_SQL)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Sql_ColCount();

	return false;
}

bool SQL_GetResult_Index(CDB_SQL * pDB_SQL, CString & strResult, int iCol, bool bNext)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Get_SqlResult(strResult, iCol,bNext);

	return false;
}

bool SQL_GetResult_Text(CDB_SQL * pDB_SQL, CString & strResult, CString strCol, bool bNext)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Get_SqlResult(strResult, strCol, bNext);

	return false;
}

CRecordset * SQL_RecordSet(CDB_SQL * pDB_SQL)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->GetRecordSet();

	return nullptr;
}

bool SQL_SetRowPos(CDB_SQL* pDB_SQL, int iRowPos)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Sql_SetRowPos(iRowPos);

	return false;
}

bool SQL_IsEOF(CDB_SQL* pDB_SQL)
{
	if (nullptr != pDB_SQL)
		return pDB_SQL->Sql_IsEOF();

	return false;
}

void SQL_MoveNext(CDB_SQL* pDB_SQL)
{
	if (nullptr != pDB_SQL)
		pDB_SQL->Sql_MoveNext();
}

bool SQL_Insert_Card(CDB_SQL* pDB_SQL)
{
	CString strCard, strBin, strWifi;

	//m_edit_card.GetWindowTextA(strCard);
	//m_edit_bin.GetWindowTextA(strBin);

	strWifi.Format(_T("Insert Into CardData value('%s','%s')"), strCard, strBin);

	return SQL_Execute(pDB_SQL, strWifi);
}
//bool SQL_Insert_MotherBoard(CDB_SQL* pDB_SQL, MB_Data MotherBoard)
//{
//	CString strSql;
//	CString strResult;
//	bool bSuccess = false;
//	//동일명 검사
//	strSql.Format(_T("select count(*) from sda.MotherBoardData where Name Like '%s'"), MotherBoard.Name);
//	
//	if (SQL_ReadStart(pDB_SQL, strSql))
//	{
//		bSuccess = SQL_GetResult_Index(pDB_SQL, strResult, 0);
//		SQL_ReadEnd(pDB_SQL);
//
//		if (bSuccess && 0 == _ttoi(strResult))
//		{
//			//마더보드 데이터 추가
//			strSql.Format(_T("Insert Into sda.MotherBoardData value('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"), 
//				MotherBoard.Name, MotherBoard.Serial_Number, MotherBoard.PCI_X_Shift, MotherBoard.PCI_Y_Shift,
//				MotherBoard.PCI_Sprint_Rate, MotherBoard.Reference_Surface_Height, MotherBoard.Lowest_PCI_Depth,
//				MotherBoard.Nominal_ProbeCard_Thickness, MotherBoard.Nominal_ProbeCard_Weight,
//				MotherBoard.PCI_Weight, MotherBoard.Kelvin, MotherBoard.PCI_Vaccum, MotherBoard.PCI_Air,
//				MotherBoard.Pogo_Block_Count, MotherBoard.VENDOR, MotherBoard.Comment, MotherBoard.File_Path);
//
//			return SQL_Execute(pDB_SQL, strSql);
//		}
//	}
//
//	return false;
//}

//bool SQL_Search_MotherBoard(CDB_SQL* pDB_SQL, MB_Data** MotherBoard, int* iDataCount, CString strName)
//{
//	CString strSql;
//	CString strResult;
//	bool bSuccess = false;
//	int iColCount = 0;
//	if (_T("") == strName)
//	{
//		strSql.Format(_T("select count(*) from sda.MotherBoardData"), strName);
//		if (SQL_ReadStart(pDB_SQL, strSql))
//		{
//			bSuccess = SQL_GetResult_Index(pDB_SQL, strResult, 0);
//			SQL_ReadEnd(pDB_SQL);
//
//			if (bSuccess)
//				*iDataCount = _ttoi(strResult);
//			else
//				return false;
//		}
//		else
//			return false;
//
//		(*MotherBoard) = new MB_Data[(*iDataCount)];
//		memset((*MotherBoard), 0, sizeof(MB_Data) * (*iDataCount));
//
//		strSql.Format(_T("select * from sda.MotherBoardData"), strName);
//		if (SQL_ReadStart(pDB_SQL, strSql))
//		{
//			iColCount = SQL_ColCount(pDB_SQL);
//
//			for (int iRow = 0; iRow < *iDataCount; ++iRow)
//			{
//				for(int iCol = 0; iCol < iColCount; ++iCol)
//				{
//					if (SQL_GetResult_Index(pDB_SQL, strResult, 0))
//						SetMotherBoardData((*MotherBoard) + (sizeof(MB_Data) * iRow), strResult, iCol);
//					else
//					{
//						delete[](*MotherBoard);
//						(*MotherBoard) = nullptr;
//
//						SQL_ReadEnd(pDB_SQL);
//						return false;
//					}
//				}
//				SQL_MoveNext(pDB_SQL);
//			}
//			SQL_ReadEnd(pDB_SQL);
//			return true;
//		}
//		else
//		{
//			delete[](*MotherBoard);
//			(*MotherBoard) = nullptr;
//
//			return false;
//		}
//	}
//	else
//	{
//		strSql.Format(_T("select count(*) from sda.MotherBoardData where Name Like '%s'"), strName);
//		if (SQL_ReadStart(pDB_SQL, strSql))
//		{
//			bSuccess = SQL_GetResult_Index(pDB_SQL, strResult, 0);
//			SQL_ReadEnd(pDB_SQL);
//
//			if (bSuccess)
//				*iDataCount = _ttoi(strResult);
//			else
//				return false;
//		}
//		else
//			return false;
//
//		(*MotherBoard) = new MB_Data[(*iDataCount)];
//		memset((*MotherBoard), 0, sizeof(MB_Data) * (*iDataCount));
//
//		strSql.Format(_T("select * ffrom sda.MotherBoardData where Name Like '%s'"), strName);
//		if (SQL_ReadStart(pDB_SQL, strSql))
//		{
//			iColCount = SQL_ColCount(pDB_SQL);
//
//			for (int iRow = 0; iRow < *iDataCount; ++iRow)
//			{
//				for (int iCol = 0; iCol < iColCount; ++iCol)
//				{
//					if (SQL_GetResult_Index(pDB_SQL, strResult, 0))
//						SetMotherBoardData((*MotherBoard) + (sizeof(MB_Data) * iRow), strResult, iCol);
//					else
//					{
//						delete[](*MotherBoard);
//						(*MotherBoard) = nullptr;
//
//						SQL_ReadEnd(pDB_SQL);
//						return false;
//					}
//				}
//				SQL_MoveNext(pDB_SQL);
//			}
//			SQL_ReadEnd(pDB_SQL);
//			return true;
//		}
//		else
//		{
//			delete[](*MotherBoard);
//			(*MotherBoard) = nullptr;
//
//			return false;
//		}
//	}
//
//	return false;
//}

//void SetMotherBoardData(MB_Data* pData,CString strData, int iDataPos)
//{
//	strData = strData.Trim();
//
//	switch (iDataPos)
//	{
//	case 0:
//		lstrcpy(pData->Name, strData);
//		break;
//	case 1:
//		lstrcpy(pData->Serial_Number, strData);
//		break;
//	case 2:
//		lstrcpy(pData->PCI_X_Shift, strData);
//		break;
//	case 3:
//		lstrcpy(pData->PCI_Y_Shift, strData);
//		break;
//	case 4:
//		lstrcpy(pData->PCI_Sprint_Rate, strData);
//		break;
//	case 5:
//		lstrcpy(pData->Reference_Surface_Height, strData);
//		break;
//	case 6:
//		lstrcpy(pData->Lowest_PCI_Depth, strData);
//		break;
//	case 7:
//		lstrcpy(pData->Nominal_ProbeCard_Thickness, strData);
//		break;
//	case 8:
//		lstrcpy(pData->Nominal_ProbeCard_Weight, strData);
//		break;
//	case 9:
//		lstrcpy(pData->PCI_Weight, strData);
//		break;
//	case 10:
//		pData->Kelvin = strData[0];
//		break;
//	case 11:
//		pData->PCI_Vaccum = strData[0];
//		break;
//	case 12:
//		pData->PCI_Air = strData[0];
//		break;
//	case 13:
//		lstrcpy(pData->Pogo_Block_Count, strData);
//		break;
//	case 14:
//		lstrcpy(pData->VENDOR, strData);
//		break;
//	case 15:
//		lstrcpy(pData->Comment, strData);
//		break;
//	case 16:
//		lstrcpy(pData->File_Path, strData);
//		break;
//	}
//}
