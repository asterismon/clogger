#ifndef Logger_Base
#include <iostream>
#include <fstream>
#include <time.h>
#include <io.h>
class Logger_Base
{
    private:
        time_t raw_time;
        struct tm *time_info;
        std::string log_name;
        std::string __CALLER;
        std::string __FILE;
        unsigned int __COLOR;
        unsigned int __BG_COLOR;
        char log_filename[100];
        char __TIME[40];
        char __DATE[40];
        unsigned int __LINE;
        std::ofstream log_file;

    public:
        Logger_Base(const std::string& log_name, const std::string& __CALLER, const std::string& __FILE, unsigned int __LINE):
            log_name(log_name),
            __CALLER(__CALLER),
            __FILE(__FILE),
            __LINE(__LINE)
        {
            if(_access(".\\logs",0) == -1) system("mkdir .\\logs");
        }
        ~Logger_Base() {};
        void operator()(const std::string& _message, bool no_print = false, bool save = true) {
            time( &raw_time );
            time_info = localtime( &raw_time );
            strftime(__DATE, 40, "%Y-%m-%d",time_info);
            strftime(__TIME, 40, "%H:%M:%S",time_info);
            if (not no_print){
                std::cout << __TIME << " [" << log_name << "] <" << __CALLER << "> in " << __FILE << ", line " << __LINE << ": " << _message << std::endl;
            }
            if (save){
                sprintf(log_filename, "%s%s%s", "./logs/", __DATE, ".log");
                log_file.open(log_filename,std::ios_base::app);
                log_file << __TIME << " [" << log_name << "] <" << __CALLER << "> in " << __FILE << ", line " << __LINE << ": " << _message << std::endl;
                log_file.close();
            }
        }
};
#endif
namespace logger {
    #define info Logger_Base("INFO",__FUNCTION__,__FILE__,__LINE__)
    #define warning Logger_Base("WARNING",__FUNCTION__,__FILE__,__LINE__)
    #define error Logger_Base("ERROR",__FUNCTION__,__FILE__,__LINE__)
    #define finnal Logger_Base("FINAL",__FUNCTION__,__FILE__,__LINE__)
};