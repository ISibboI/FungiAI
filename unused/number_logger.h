#ifndef NUMBER_LOGGER_H
#define NUMBER_LOGGER_H

#include <string>
#include <fstream>

class NumberLogger {
public:
    NumberLogger(std::string file);
    ~NumberLogger();
    
    void log_number(double number);
    
private:
    std::ofstream output_stream;
};

#endif // NUMBER_LOGGER_H
