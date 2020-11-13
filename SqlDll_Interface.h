#ifndef SqlDll_Interface_h__
#define SqlDll_Interface_h__

#include "DB_SQL.h"

extern "C"
{
	//�⺻ SQL��
	_declspec(dllexport) CDB_SQL* Create_DB_SQL();//DB_SQL ����
	_declspec(dllexport) void SQL_Init(CDB_SQL* pDB_SQL, CString strDSN); //�����ͺ��̽� ����
	_declspec(dllexport) void SQL_Delete(CDB_SQL** pDB_SQL); //�����ͺ��̽� ����

	_declspec(dllexport) bool SQL_Connection_Check(CDB_SQL* pDB_SQL); //���� Ȯ��

	_declspec(dllexport) bool SQL_Execute(CDB_SQL* pDB_SQL, CString strSQL); //��ɹ� ����
	_declspec(dllexport) bool SQL_ReadStart(CDB_SQL* pDB_SQL, CString strSQL); //SELECT�� ����
	_declspec(dllexport) void SQL_ReadEnd(CDB_SQL* pDB_SQL); //SELECT�� ����
	_declspec(dllexport) int SQL_ColCount(CDB_SQL* pDB_SQL); //SELECT�� Col(��) ���� 
	_declspec(dllexport) bool SQL_SetRowPos(CDB_SQL* pDB_SQL, int iRowPos); //SELECT�� Col(��) ���� 
	_declspec(dllexport) bool SQL_IsEOF(CDB_SQL* pDB_SQL); //SELECT�� EOFüũ 
	_declspec(dllexport) void SQL_MoveNext(CDB_SQL* pDB_SQL); //SELECT�� ���� ��
	_declspec(dllexport) bool SQL_GetResult_Index(CDB_SQL* pDB_SQL, CString& strResult, int iCol, bool bNext = false); //������ ����� ��ȯ ������ bool���� ���� ������ ����
	_declspec(dllexport) bool SQL_GetResult_Text(CDB_SQL* pDB_SQL, CString& strResult, CString strCol, bool bNext = false); //������ ����� ��ȯ ������ bool���� ���� ������ ����
	_declspec(dllexport) CRecordset* SQL_RecordSet(CDB_SQL* pDB_SQL); //Recordset ��ȯ

	//���� SQL��
//	_declspec(dllexport) bool SQL_Insert_MotherBoard(CDB_SQL* pDB_SQL, MB_Data MotherBoard);//PCI_�߰�
//	_declspec(dllexport) bool SQL_Search_MotherBoard(CDB_SQL* pDB_SQL, MB_Data** MotherBoard, int* iDataCount, CString strName);//PCI_�˻�

//	void SetMotherBoardData(MB_Data* pData, CString strData, int iDataPos);
}
#endif // Dll_Interface_h__
