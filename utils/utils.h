#pragma once

#include <QDebug>
#include <random>

#define LOG qDebug()
#define COLOR(r, g, b, a) a << 24 | b << 16 | g << 8 | r


inline double d_normal() {
    const double pi = 3.14159265359;
    const double nums = 1;
    double u = 0, v = 0, x = 0;

    srand(rand() + (int) time(NULL));

    for(unsigned int i = 0; i < nums; i++){
        u = rand() / (((double)RAND_MAX) + 1.0);
        v = rand() / (((double)RAND_MAX) + 1.0);
        x = sqrt(-2*log(u)) * cos(2 * pi * v);

        if (std::isfinite(x)){
            //LOG << x <<" ";
        }
    }
    if (x < 4 && x > -4){
        return x/4; // normalize
    }
    else{
        return d_normal();
    }
}

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
