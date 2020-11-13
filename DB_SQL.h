#ifndef DB_SQL_h__
#define DB_SQL_h__

#include <afxdb.h>
#include <afxcmn.h>
#include <odbcinst.h>
#include <sqlext.h>

class _declspec(dllexport) CDB_SQL
{
private:
	explicit CDB_SQL();
public:
	~CDB_SQL();

public:
	void Init(CString strDSN); //�ʱ� ����
	void Release(); //���� ����

	bool Connection_Check(); //������ ���� Ȯ��

	bool Sql_Execute(CString strSQL); //sql ����

	bool Sql_ReadStart(CString strSQL);
	void Sql_ReadEnd();
	void Sql_ReadError();
	int Sql_ColCount();
	bool Sql_SetRowPos(int iRow);
	bool Sql_IsEOF();
	void Sql_MoveNext();
	bool Get_SqlResult(CString& strResult, int iCol, bool bNext = false);
	bool Get_SqlResult(CString& strResult, CString strCol, bool bNext = false);

	CRecordset* GetRecordSet() { return m_RecordSet; }

public:
	static CDB_SQL* Create();

private:
	CDatabase m_database;
	bool m_bOpen;
	CString m_strDSN;
	CRecordset* m_RecordSet;
};

#endif // DB_SQL_h__
