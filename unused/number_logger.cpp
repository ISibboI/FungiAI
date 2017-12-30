#include "number_logger.h"

using namespace std;

NumberLogger::NumberLogger(string file) {
    output_stream.open(file, ios::trunc);
}

NumberLogger::~NumberLogger() {
    output_stream.close();
}

void NumberLogger::log_number(double number) {
    output_stream << number << "\n";
}
