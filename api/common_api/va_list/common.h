#include<stdalign.h>
#include<stdio.h>


#define LOG(arg...) log_data(0,__FILE__,__LINE__,__FUNCTION__,0,##arg)


void log_data(int is_err,char* path,char* line,char* func,int err,const char*fmt,... );



