
/*
C++ ��־ϵͳ
debug,info,warn,error fatal

����
1.��־�洢
2.��־����
3.��־����
4.��־����

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
	// time ������ȡ��ǰʱ�䣬��NULL��������ʱ��,
	// ������һ��time_t��ָ�뽫�������ڴ�������
	struct tm ptn;
	localtime_s(&ptn,&ticks);
	//��ȡ��ǰʱ��
	char timestamp[64];
	memset(timestamp, 0, sizeof(timestamp));
	//��ʼ�� �׵�ַ��ֵ���ܵ�ַ��С
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &ptn);
	//��ʱ���ʽ�������(��ֵ)Ŀ�����飨ָ��)

	const char* ftm = "%s %s %s:%d";
	int size = snprintf(NULL, 0, ftm, timestamp, s_level[int(Level)], filename, line);
	// cout << timestamp << endl;
	// cout <<"--" << filename << "--" << line << "--"<<format<< endl;
	//����˵������Դ�������ַ���Ŀ�괮�У��ɹ��󷵻��ַ���������
	if (size > 0)
	{
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, ftm, timestamp, s_level[int(Level)], filename, line);
		//�����ݵĸ�ʽ֧���������Ƶ�buffer
		//��ʱbuffer �൱��"%s %s %s:%d" ,timestamp,
		//s_level[int(Level)](debug)->array[index](str),filename,line(int)
		buffer[size] =0;
		cout << buffer<<endl;
		m_fout<<buffer<<'\t';
		m_len += size;
		delete[] buffer;
		//��֧����<<m_fout (osftream),cout<<,log�ĳ�������
	}

	va_list arg_ptr;//�洢�ɱ����
	va_start(arg_ptr, format);
	size = vsnprintf(nullptr,0,format,arg_ptr); //������й�
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
		//���ڿɱ�����ļ�¼����д��ǰ��ļ�¼
	}
	m_fout << "\n";
	m_fout.flush();

	if (m_len >= m_max && m_max > 0)
	{
		//��־д�����ļ�
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
	//д�����ļ���
}



