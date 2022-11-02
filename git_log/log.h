#pragma once

#include <string>
#include <fstream>

using namespace std;

namespace yazi
{
namespace utility {

#define debug(format, ...) \
Logger::instance()->log(Logger::level::DEBUG,__FILE__, __LINE__, format,##__VA_ARGS__)

#define info(format, ...)\
Logger::instance()->log(Logger::level::INFO,__FILE__, __LINE__,format,##__VA_ARGS__)

#define warn(format, ...)\
Logger::instance()->log(Logger::level::WARN,__FILE__, __LINE__,format,##__VA_ARGS__)

#define error(format, ...)\
Logger::instance()->log(Logger::level::ERROR,__FILE__, __LINE__,format,##__VA_ARGS__)

#define fatal(format, ...)\
Logger::instance()->log(Logger::level::FATAL,__FILE__, __LINE__,format,##__VA_ARGS__)


	class Logger
	{
	public:
		enum class level
		{
			DEBUG = 0,
			INFO = 1,
			WARN = 2,
			ERROR = 3,
			FATAL = 4,
			LEVEL_COUNT = 5

		};

		void log(Logger::level Level, const char* file, int line, const char* format, ...);
		static Logger* instance();
		void open(const string& filename);
		void close();
		void max(int bytes);
		void level_(Logger::level Level);
		void log_roate();

	private:
		Logger() :m_max(0), m_len(0),m_Level(Logger::level::DEBUG) {};
		~Logger();
	private:
		string m_filename;
		ofstream  m_fout;
		static const char* s_level[int(level::LEVEL_COUNT)];
		static Logger* m_instance;
		int m_max;
		int m_len;
		Logger::level m_Level;
		
	};





}
}