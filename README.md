1.Logger采用单对象的设计模式
2.logger中成员有文件名，控制输入的，静态的对象，静态数组
3.log的级别用一个枚举类型，对应静态数组(字符串数组）
const char* Logger::s_level[int(Logger::level::LEVEL_COUNT)] = {
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL"
};

4.成员变量中有ofstream的对象 ，成员函数open 
void Logger::open(const string& filename)
{	
	m_filename = filename;
	m_fout.open(filename, ios::app);  //表示写文件
	if (m_fout.fail())
	{
		throw std::logic_error("open file Failed" + filename);
	}
}

5.因为是单例模式，公用一个对象 Logger::instance()
6.成员函数 log 写入文件对内容格式进行调整 void log(Logger::level Level, const char* file, int line, const char* format, ...)
参数分别是枚举类型，文件名，行，不确定格式的内容 
struct tm *localtime(const time_t *timer); 获取时间
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr); 格式化时间

将可变个参数(...)按照format格式化成字符串，然后将其复制到str中。
int snprintf(char *str, size_t size, const char *format, ...)
int size = snprintf(NULL, 0, ftm, timestamp, s_level[int(Level)], filename, line); //可变参数相当于得到可变参数的长度

char* buffer = new char[size + 1];
snprintf(buffer, size + 1, ftm, timestamp, s_level[int(Level)], filename, line);
//将依据的格式支付串，复制到buffer
//这时buffer 相当于"%s %s %s:%d" ,timestamp,
//s_level[int(Level)](debug)->array[index](str),filename,line(int)
	buffer[size] =0;
	cout << buffer<<endl;
	m_fout<<buffer<<'\t';


最后是写入自定义的内容
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
	m_fout << "\n"; 换行刷新
	m_fout.flush();

7.最后用几个宏定义了函数 #define debug(format, ...) \
Logger::instance()->log(Logger::level::DEBUG,__FILE__, __LINE__, format,##__VA_ARGS__)

————FILE————表示当前文件 对应着const char* file
__LINE__对应着 int line
format,##__VA_ARGS__ 对应着format ...

8.使用时，先指定写入文件名 debug("xxx")
