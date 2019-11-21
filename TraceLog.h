/***********************************************************
**   一个简单的日志记录功能。
**   记录格式为：[MM-DD HH:MM:SS] logStr
**   其中设置有日志级别，
**   可根据不同的日志性质，
**   选择调用不同的接口。
************************************************************/
//=========================================================================
//	FILE:	[TraceLog]
//	AUTH:	
//	DATE:	
//	CITY:	
//	DESC:	日志输出
//=========================================================================
#ifndef __TRACELOG_2014_8_5_H__
#define __TRACELOG_2014_8_5_H__
 
#include <stdlib.h>
#include <string>
using namespace std;
 
// 日志输出类型
enum ETL_OUT_TYPE
{
	ETL_OT_FILE		= 0x01,		// 输出日志到文件
	ETL_OT_CONSOLE	= 0x02,		// 输出日志到控制台
 
	ETL_OT_END
};
 
// 日志级别
enum ETL_LEVEL
{
	ETL_NULL = -1,
 
	ETL_ALL,			// 输出所有
	ETL_TEST,			// 输出测试信息及以上
	ETL_NORMAL,			// 输出普通日志及以上
	ETL_WARNING,		// 输出警告及以上
	ETL_ERROR,			// 输出错误级以上
	ETL_BASE,			// 输出基础信息
 
	ETL_MAX
};
 
// 输出日志
void TraceTest(const char* formant, ...);
void TraceNormal(const char* formant, ...);
void TraceWarning(const char* formant, ...);
void TraceError(const char* formant, ...);
void TraceBase(const char* formant, ...);
 
// 日志输出-单例
class TraceLog
{
public:
	// 单例
	static TraceLog* GetInstance();
	// 设置日志级别
	void SetTraceLevel(ETL_LEVEL eLevel);
	// 设置日志名
	void SetLogFileName(const char* strName);
	// 设置日志输出类型
	void SetLogOutType(int nType);
	// 输出日志（带时间信息输出）
	void Trace(ETL_LEVEL eLevel, const char* log);
 
protected:
	// 写日志文件
	void WriteLogfile(ETL_LEVEL eLevel, const char* strLog);
 
private:
	// 构造
	TraceLog():m_bFirst(true),m_nOutType(ETL_OT_FILE),m_eLevel(ETL_NORMAL),m_strName("TraceLog.log"){}
	// 成员变量
	bool		m_bFirst;
	int			m_nOutType;
	ETL_LEVEL	m_eLevel;
	string		m_strName;
};
 
#endif//__TRACELOG_2014_8_5_H__
