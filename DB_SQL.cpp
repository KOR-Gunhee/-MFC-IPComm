#include "stdafx.h"
#include "DB_SQL.h"

CDB_SQL::CDB_SQL()
	: m_bOpen(false)
	, m_RecordSet(nullptr)
{
}


CDB_SQL::~CDB_SQL()
{
}

void CDB_SQL::Init(CString strDSN)
{
	m_strDSN = strDSN;

	if (!m_bOpen)
	{
		CString strConnectDSN;
		strConnectDSN.Format(_T("DSN=%s"),m_strDSN);
		m_bOpen = m_database.Open(strDSN);
	}
}

void CDB_SQL::Release()
{
	Sql_ReadError();

	if (m_bOpen)
		m_database.Close();
}

bool CDB_SQL::Connection_Check()
{
	if (!m_bOpen)
		Init(m_strDSN);

	return m_bOpen;
}

bool CDB_SQL::Sql_Execute(CString strSQL)
{
	if (!Connection_Check())
		return false;

	try
	{
		m_database.ExecuteSQL(strSQL);
		return true;
	}
	catch (CException* e)
	{
		e->ReportError();
		return false;
	}
}

bool CDB_SQL::Sql_ReadStart(CString strSQL)
{
	if (!Connection_Check())
		return false;

	Sql_ReadError();
	
	try
	{
		if (!m_RecordSet)
			m_RecordSet = new CRecordset(&m_database);

		if (FALSE == m_RecordSet->Open(CRecordset::forwardOnly, strSQL, CRecordset::readOnly))
		{
			Sql_ReadError();
			return false;
		}
	}
	catch (CException* e)
	{
		e->ReportError();
		Sql_ReadError();
		return false;
	}

	return true;
}

void CDB_SQL::Sql_ReadEnd()
{
	if (nullptr != m_RecordSet)
	{
		m_RecordSet->Close();
		delete m_RecordSet;
		m_RecordSet = nullptr;
	}
}

void CDB_SQL::Sql_ReadError()
{
	if (nullptr != m_RecordSet)
	{
		delete m_RecordSet;
		m_RecordSet = nullptr;
	}
}

int CDB_SQL::Sql_ColCount()
{
	try
	{
		if (nullptr != m_RecordSet)
			return m_RecordSet->GetODBCFieldCount();
	}
	catch (CException* e)
	{
		e->ReportError();
		return 0;
	}
	
	return 0;
}

bool CDB_SQL::Sql_SetRowPos(int iRow)
{
	if (!m_RecordSet)
		return false;

	try
	{
		m_RecordSet->SetAbsolutePosition(iRow);
		return true;
	}
	catch (CException* e)
	{
		e->ReportError();
		return false;
	}
}

bool CDB_SQL::Sql_IsEOF()
{
	if (!m_RecordSet)
		return false;
	try
	{
		return m_RecordSet->IsEOF();
	}
	catch (CException* e)
	{
		e->ReportError();
		return false;
	}
}

void CDB_SQL::Sql_MoveNext()
{
	if (!m_RecordSet)
		return;

	try 
	{
		m_RecordSet->MoveNext();
	}
	catch (CException* e)
	{
		e->ReportError();
	}
}

bool CDB_SQL::Get_SqlResult(CString& strResult, int iCol, bool bNext)
{
	if (!m_RecordSet)
		return false;

	try
	{
		m_RecordSet->GetFieldValue(iCol, strResult);

		if (bNext)
			m_RecordSet->MoveNext();

		return true;
	}
	catch (CException* e)
	{
		e->ReportError();
		return false;
	}

	return false;
}

bool CDB_SQL::Get_SqlResult(CString& strResult, CString strCol, bool bNext /*= false*/)
{
	if (!m_RecordSet)
		return false;

	try
	{
		m_RecordSet->GetFieldValue(strCol, strResult);

		if (bNext)
			m_RecordSet->MoveNext();

		return true;
	}
	catch (CException* e)
	{
		e->ReportError();
		return false;
	}

	return false;
}

CDB_SQL* CDB_SQL::Create()
{
	CDB_SQL* pDB_Sql = new CDB_SQL();
	return pDB_Sql;
}
