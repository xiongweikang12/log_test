
/*
C++ 日志系统
debug,info,warn,error fatal

需求：
1.日志存储
2.日志内容
3.日志级别
4.日志翻滚

*/

#include "log.h"
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <time.h>
#include <stdarg.h>



using namespace yazi::utility;


const char* Logger::s_level[int(Logger::level::LEVEL_COUNT)] = {
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL"
};

Logger* Logger::m_instance = NULL;
Logger::~Logger()
{

}

Logger* Logger::instance()
{
	if (m_instance == NULL)
	{
		m_instance = new Logger();
	}
	return m_instance;
}

void Logger::open(const string& filename)
{	
	m_filename = filename;
	m_fout.open(filename, ios::app);
	if (m_fout.fail())
	{
		throw std::logic_error("open file Failed" + filename);
	}
}

void Logger::close()
{
	m_fout.close();
}

void Logger::log(level Level, const char* filename, int line, const char* format, ...)
{
	if (m_fout.fail())
	{
		throw std::logic_error("open file failed" + m_filename);
	}
	time_t ticks = time(NULL);
	// time 函数获取当前时间，当NULL返回日历时间,
	// 当传入一个time_t的指针将日历存于存于其中
	struct tm ptn;
	localtime_s(&ptn,&ticks);
	//获取当前时间
	char timestamp[64];
	memset(timestamp, 0, sizeof(timestamp));
	//初始化 首地址，值，总地址大小
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &ptn);
	//将时间格式化后存入(赋值)目标数组（指针)

	const char* ftm = "%s %s %s:%d";
	int size = snprintf(NULL, 0, ftm, timestamp, s_level[int(Level)], filename, line);
	// cout << timestamp << endl;
	// cout <<"--" << filename << "--" << line << "--"<<format<< endl;
	//函数说明，从源串拷贝字符到目标串中，成功后返回字符串串长度
	if (size > 0)
	{
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, ftm, timestamp, s_level[int(Level)], filename, line);
		//将依据的格式支付串，复制到buffer
		//这时buffer 相当于"%s %s %s:%d" ,timestamp,
		//s_level[int(Level)](debug)->array[index](str),filename,line(int)
		buffer[size] =0;
		cout << buffer<<endl;
		m_fout<<buffer<<'\t';
		m_len += size;
		delete[] buffer;
		//将支付串<<m_fout (osftream),cout<<,log的长度增加
	}

	va_list arg_ptr;//存储可变参数
	va_start(arg_ptr, format);
	size = vsnprintf(nullptr,0,format,arg_ptr); //与参数有关
	va_end(arg_ptr);
	if (size > 0)
	{
		char* content = new char[size + 1];
		va_start(arg_ptr, format);
		vsnprintf(content, size + 1, format, arg_ptr);
		va_end(arg_ptr);
		cout << content << endl;
		m_fout << content;
		m_len += size;
		//对于可变参数的记录，续写在前面的记录
	}
	m_fout << "\n";
	m_fout.flush();

	if (m_len >= m_max && m_max > 0)
	{
		//日志写入新文件
	}

}

void Logger::max(int bytes)
{
	m_max = bytes;
}

void Logger::level_(Logger::level Level)
{
	m_Level = Level;
}

void Logger::log_roate()
{
	//写入新文件中
}



