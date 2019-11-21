#include "TraceLog.h"
#include <time.h>
#include <stdarg.h>
#include <iostream>
 
// 字符数组最大值
#define TL_TEMPMAX 4096
// 回车换行符
#define TL_RETURN "\r\n"
 
// 输出日志
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
// 单例
TraceLog* TraceLog::GetInstance()
{
	static TraceLog instance;
	return &instance;
}
 
// 设置日志级别
void TraceLog::SetTraceLevel(ETL_LEVEL eLevel)
{
	m_eLevel = eLevel;
}
 
// 设置日志名
void TraceLog::SetLogFileName(const char* strName)
{
	m_strName = strName;
}
 
// 设置日志输出类型
void TraceLog::SetLogOutType(int nType)
{
	m_nOutType = nType;
}
 
//=========================================================================
//	protected
//=========================================================================
// 输出日志（带时间信息输出）
void TraceLog::Trace(ETL_LEVEL eLevel, const char* log)
{
	// 第一次记录日志，先清空
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
 
	// 日志级别不够
	if (eLevel < m_eLevel)
	{
		return;
	}
 
	// 获取日期，输出格式为：[MM-DD HH:MM:SS] logStr
	time_t nowtime;
	struct tm timeinfo;
	time( &nowtime );
	localtime_s(&timeinfo, &nowtime );
 
	char tempOut[4096] = {0};
	_snprintf_s(tempOut, 4096, "[%02d-%02d %02d:%02d:%02d]  %s\r\n", timeinfo.tm_mon + 1, timeinfo.tm_mday, 
		timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, log);
 
	bool bOutFile = (m_nOutType & ETL_OT_FILE) != 0;
	bool bOutConsole = (m_nOutType & ETL_OT_CONSOLE) != 0;
 
	// 输出到日志文件
	if (bOutFile)
	{
		WriteLogfile(eLevel, tempOut);
	}
 
	// 输出到控制台
	if (bOutConsole)
	{
		std::cout << tempOut;
	}
}
 
//=========================================================================
//	private
//=========================================================================
 
// 写日志文件
void TraceLog::WriteLogfile(ETL_LEVEL eLevel, const char* strLog)
{
	// 打开文件
	FILE* pF = NULL;
	fopen_s(&pF, m_strName.c_str(), "a");
	if(pF)
	{
		fwrite(strLog, strlen(strLog), 1, pF);
		fclose(pF);
	}
}
