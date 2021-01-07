#include <cmath>
#include <iostream>
#include <string>
#include "Stack.h"

//write the functions
// add element to the top of Stack s
// if Stack s is full, resize the underlying array
void push(Stack& s, double element)
{
        if(!std::isnan(element))
        {
                if(s.length == s.capacity)
                {
                        double *temp = s.A;
                        s.A = new double[2*s.capacity];
                        for (int i = 0; i < s.length;++i)
                        {
                                s.A[i] = temp[i];
                        }
                        s.capacity = 2*s.capacity;
                        delete[] temp;
                }
                
                s.A[s.length] = element;
                s.length++;
        }
}
// remove and return the element on top of Stack s
// if Stack s is empty, return NAN
double pop(Stack& s)
{
         if (s.length == 0){
            return NAN;
        }
        double ret = s.A[s.length-1];
        s.A[s.length-1] = NAN;
        s.length--;
        return ret;
}