#ifndef SqlDll_Interface_h__
#define SqlDll_Interface_h__

#include "DB_SQL.h"

extern "C"
{
	//기본 SQL문
	_declspec(dllexport) CDB_SQL* Create_DB_SQL();//DB_SQL 생성
	_declspec(dllexport) void SQL_Init(CDB_SQL* pDB_SQL, CString strDSN); //데이터베이스 연동
	_declspec(dllexport) void SQL_Delete(CDB_SQL** pDB_SQL); //데이터베이스 해제

	_declspec(dllexport) bool SQL_Connection_Check(CDB_SQL* pDB_SQL); //연결 확인

	_declspec(dllexport) bool SQL_Execute(CDB_SQL* pDB_SQL, CString strSQL); //명령문 실행
	_declspec(dllexport) bool SQL_ReadStart(CDB_SQL* pDB_SQL, CString strSQL); //SELECT문 실행
	_declspec(dllexport) void SQL_ReadEnd(CDB_SQL* pDB_SQL); //SELECT문 종료
	_declspec(dllexport) int SQL_ColCount(CDB_SQL* pDB_SQL); //SELECT문 Col(열) 갯수 
	_declspec(dllexport) bool SQL_SetRowPos(CDB_SQL* pDB_SQL, int iRowPos); //SELECT문 Col(열) 갯수 
	_declspec(dllexport) bool SQL_IsEOF(CDB_SQL* pDB_SQL); //SELECT문 EOF체크 
	_declspec(dllexport) void SQL_MoveNext(CDB_SQL* pDB_SQL); //SELECT문 다음 행
	_declspec(dllexport) bool SQL_GetResult_Index(CDB_SQL* pDB_SQL, CString& strResult, int iCol, bool bNext = false); //데이터 결과값 반환 마지막 bool값은 다음 행으로 변경
	_declspec(dllexport) bool SQL_GetResult_Text(CDB_SQL* pDB_SQL, CString& strResult, CString strCol, bool bNext = false); //데이터 결과값 반환 마지막 bool값은 다음 행으로 변경
	_declspec(dllexport) CRecordset* SQL_RecordSet(CDB_SQL* pDB_SQL); //Recordset 반환

	//고정 SQL문
//	_declspec(dllexport) bool SQL_Insert_MotherBoard(CDB_SQL* pDB_SQL, MB_Data MotherBoard);//PCI_추가
//	_declspec(dllexport) bool SQL_Search_MotherBoard(CDB_SQL* pDB_SQL, MB_Data** MotherBoard, int* iDataCount, CString strName);//PCI_검사

//	void SetMotherBoardData(MB_Data* pData, CString strData, int iDataPos);
}
#endif // Dll_Interface_h__
