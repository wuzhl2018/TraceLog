#include "TraceLog.h"
#include <time.h>
#include <stdarg.h>
#include <iostream>
 
// �ַ��������ֵ
#define TL_TEMPMAX 4096
// �س����з�
#define TL_RETURN "\r\n"
 
// �����־
void TraceTest(const char* formant, ...)
{
	char temp[TL_TEMPMAX] = {0};
 
	va_list val;
	va_start(val,formant);
	_vsnprintf_s(temp, TL_TEMPMAX, formant, val); 
	va_end(val); 
 
	TraceLog::GetInstance()->Trace(ETL_TEST, temp);
}
 
void TraceNormal(const char* formant, ...)
{
	char temp[TL_TEMPMAX] = {0};
 
	va_list val;
	va_start(val,formant);
	_vsnprintf_s(temp, TL_TEMPMAX, formant, val); 
	va_end(val); 
 
	TraceLog::GetInstance()->Trace(ETL_NORMAL, temp);
}
 
void TraceWarning(const char* formant, ...)
{
	char temp[TL_TEMPMAX] = {0};
 
	va_list val;
	va_start(val,formant);
	_vsnprintf_s(temp, TL_TEMPMAX, formant, val); 
	va_end(val); 
 
	TraceLog::GetInstance()->Trace(ETL_WARNING, temp);
}
 
void TraceError(const char* formant, ...)
{
	char temp[TL_TEMPMAX] = {0};
 
	va_list val;
	va_start(val,formant);
	_vsnprintf_s(temp, TL_TEMPMAX, formant, val); 
	va_end(val); 
 
	TraceLog::GetInstance()->Trace(ETL_ERROR, temp);
}
 
void TraceBase(const char* formant, ...)
{
	char temp[TL_TEMPMAX] = {0};
 
	va_list val;
	va_start(val,formant);
	_vsnprintf_s(temp, TL_TEMPMAX, formant, val); 
	va_end(val); 
 
	TraceLog::GetInstance()->Trace(ETL_BASE, temp);
}
 
//=========================================================================
//	public
//=========================================================================
// ����
TraceLog* TraceLog::GetInstance()
{
	static TraceLog instance;
	return &instance;
}
 
// ������־����
void TraceLog::SetTraceLevel(ETL_LEVEL eLevel)
{
	m_eLevel = eLevel;
}
 
// ������־��
void TraceLog::SetLogFileName(const char* strName)
{
	m_strName = strName;
}
 
// ������־�������
void TraceLog::SetLogOutType(int nType)
{
	m_nOutType = nType;
}
 
//=========================================================================
//	protected
//=========================================================================
// �����־����ʱ����Ϣ�����
void TraceLog::Trace(ETL_LEVEL eLevel, const char* log)
{
	// ��һ�μ�¼��־�������
	if (m_bFirst)
	{
		m_bFirst = false;
		FILE* pF = NULL;
		fopen_s(&pF, m_strName.c_str(), "w+");
		if (!pF)
		{
			return;
		}
		fclose(pF);
	}
 
	// ��־���𲻹�
	if (eLevel < m_eLevel)
	{
		return;
	}
 
	// ��ȡ���ڣ������ʽΪ��[MM-DD HH:MM:SS] logStr
	time_t nowtime;
	struct tm timeinfo;
	time( &nowtime );
	localtime_s(&timeinfo, &nowtime );
 
	char tempOut[4096] = {0};
	_snprintf_s(tempOut, 4096, "[%02d-%02d %02d:%02d:%02d]  %s\r\n", timeinfo.tm_mon + 1, timeinfo.tm_mday, 
		timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, log);
 
	bool bOutFile = (m_nOutType & ETL_OT_FILE) != 0;
	bool bOutConsole = (m_nOutType & ETL_OT_CONSOLE) != 0;
 
	// �������־�ļ�
	if (bOutFile)
	{
		WriteLogfile(eLevel, tempOut);
	}
 
	// ���������̨
	if (bOutConsole)
	{
		std::cout << tempOut;
	}
}
 
//=========================================================================
//	private
//=========================================================================
 
// д��־�ļ�
void TraceLog::WriteLogfile(ETL_LEVEL eLevel, const char* strLog)
{
	// ���ļ�
	FILE* pF = NULL;
	fopen_s(&pF, m_strName.c_str(), "a");
	if(pF)
	{
		fwrite(strLog, strlen(strLog), 1, pF);
		fclose(pF);
	}
}
