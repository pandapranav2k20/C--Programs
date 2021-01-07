/*
DADA function definitions
*/

#include <iostream>
#include <cmath>
#include "dada.h"
using std::cout, std::endl, std::abs, std::sqrt;

int amax(const double x[], const unsigned int len) {
    //TODO: student implement code here
    if(len == 0){
        return -1;
    }
    double max = x[0];
    int index = 0;
    int maxIndex = 0;
    for(int i = 0; i < len; ++i){
        //check positives
        if(x[i] > max){
            max = x[i];
            maxIndex = index;
        }
        //check negatives
        else if ((x[i] * -1.0) > max){
            max = (x[i] * -1.0);
            maxIndex = index;
        }
        ++index;
    }
    return maxIndex;
}

double asum(const double x[], const unsigned int len) {
    //TODO: student implement code here
    double sum = 0.0;
    for(int i = 0; i < len; ++i){
        if(x[i] < 0){
            sum += -1.0 * x[i];
        }
        else{
            sum += x[i];
        }
    }
    return sum;
}

void axpy(const double a, const double x[], double y[], const unsigned int len) {
    //TODO: student implement code here
    double oldYVal = 0.0;
    for(int i = 0; i < len; ++i){
        oldYVal = y[i];
        y[i] = oldYVal + x[i] * a;
    }
    
}

void copy(const double src[], double dest[], const unsigned int len) {
    //TODO: student implement code here
    for(int i = 0; i < len; ++i){
        dest[i] = src[i];
    }
}

double dot(const double x[], const double y[], const unsigned int len) {
    //TODO: student implement code here
    double runningDot = 0.0;
    double currentDot = 0.0;
    for(int i = 0; i < len; ++i){
        currentDot = x[i] * y[i];
        runningDot += currentDot;
    }
    return runningDot;
}

double norm2(const double x[], const unsigned int len) {
    //TODO: student implement code here
    double sumUnderRoot = 0;
    //add all of the things under the root
    for(int i = 0; i < len; ++i){
        sumUnderRoot += x[i] * x[i];
    }
    //double magnitude = sqrt(sumUnderRoot);
    return sqrt(sumUnderRoot);
}

void scale(const double a, double x[], const unsigned int len) {
    //TODO: student implement code here
    double oldVal = 0.0;
    for(int i = 0; i < len; ++i){
        oldVal = x[i];
        x[i] = a * oldVal;
    }
}

void swap(double x[], double y[], const unsigned int len) {
    //TODO: student implement code here
    double oldX = 0.0;
    double oldY = 0.0;
    for(int i = 0; i < len; ++i){
        oldX = x[i];
        oldY = y[i];
        y[i] = oldX;
        x[i] = oldY;
    }
}
