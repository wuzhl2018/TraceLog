/***********************************************************
**   һ���򵥵���־��¼���ܡ�
**   ��¼��ʽΪ��[MM-DD HH:MM:SS] logStr
**   ������������־����
**   �ɸ��ݲ�ͬ����־���ʣ�
**   ѡ����ò�ͬ�Ľӿڡ�
************************************************************/
//=========================================================================
//	FILE:	[TraceLog]
//	AUTH:	
//	DATE:	
//	CITY:	
//	DESC:	��־���
//=========================================================================
#ifndef __TRACELOG_2014_8_5_H__
#define __TRACELOG_2014_8_5_H__
 
#include <stdlib.h>
#include <string>
using namespace std;
 
// ��־�������
enum ETL_OUT_TYPE
{
	ETL_OT_FILE		= 0x01,		// �����־���ļ�
	ETL_OT_CONSOLE	= 0x02,		// �����־������̨
 
	ETL_OT_END
};
 
// ��־����
enum ETL_LEVEL
{
	ETL_NULL = -1,
 
	ETL_ALL,			// �������
	ETL_TEST,			// ���������Ϣ������
	ETL_NORMAL,			// �����ͨ��־������
	ETL_WARNING,		// ������漰����
	ETL_ERROR,			// �����������
	ETL_BASE,			// ���������Ϣ
 
	ETL_MAX
};
 
// �����־
void TraceTest(const char* formant, ...);
void TraceNormal(const char* formant, ...);
void TraceWarning(const char* formant, ...);
void TraceError(const char* formant, ...);
void TraceBase(const char* formant, ...);
 
// ��־���-����
class TraceLog
{
public:
	// ����
	static TraceLog* GetInstance();
	// ������־����
	void SetTraceLevel(ETL_LEVEL eLevel);
	// ������־��
	void SetLogFileName(const char* strName);
	// ������־�������
	void SetLogOutType(int nType);
	// �����־����ʱ����Ϣ�����
	void Trace(ETL_LEVEL eLevel, const char* log);
 
protected:
	// д��־�ļ�
	void WriteLogfile(ETL_LEVEL eLevel, const char* strLog);
 
private:
	// ����
	TraceLog():m_bFirst(true),m_nOutType(ETL_OT_FILE),m_eLevel(ETL_NORMAL),m_strName("TraceLog.log"){}
	// ��Ա����
	bool		m_bFirst;
	int			m_nOutType;
	ETL_LEVEL	m_eLevel;
	string		m_strName;
};
 
#endif//__TRACELOG_2014_8_5_H__
