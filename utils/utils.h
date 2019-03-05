#pragma once

#include <QDebug>

#define LOG(x) qDebug() << x
#define COLOR(r, g, b, a) a << 24 | b << 16 | g << 8 | r

/*
inline static const std::string read_file(const char* filepath) {
    FILE* file = fopen(filepath, "rt");
    fseek(file, 0, SEEK_END);
    unsigned int length = ftell(file);
    char* data = new char[length + 1]();
    fseek(file, 0, SEEK_SET);
    fread(data, 1, length, file);
    fclose(file);
    std::string result(data);
    delete[] data;
    return result;
}
*/
