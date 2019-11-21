//=========================================================================
//	FILE:	[TestMain]
//	AUTH:	
//	DATE:	
//	CITY:	
//	DESC:	����������ļ�
//=========================================================================
 
#include <iostream>
#include "TraceLog.h"
 
using namespace std;
 
void main()
{
	TraceLog::GetInstance()->SetTraceLevel(ETL_ALL);
	TraceLog::GetInstance()->SetLogOutType(ETL_OT_FILE | ETL_OT_CONSOLE);
	TraceTest("����һ��:%d", 9527);
	TraceNormal("Test TraceNormal:%d", 6520);
	TraceWarning("Test TraceWarning:%d", 41);
	TraceError("Test TraceError:%d", 2758);
	TraceBase("Test TraceBase:%d", 41);
 
	return;
}
