#include "functions.h"

bool is_valid_range(int a, int b) {
    // TODO(student): validate input range
    if (a > b){
        return false;
    }
    if (b > 10000){
        return false;
    }
    if (a < 0){
        return false;
    }
    
    return true;
    
}

int count_digit_occurrences(int number, int digit) {
  if(number < 0){
      number = -(number);
  }
  int counter = 0;
  // TODO(student): return how many times digit occurs in number
    if (number == 0 && digit == 0){
        counter = 1;
        return counter; 
    }
    else if (number > 0){
        //int counter = 0;
        int numOverTen = number;
        int currentNum = number;
        while(numOverTen > 0){
            currentNum = numOverTen % 10;
            numOverTen = numOverTen / 10;  
            if(currentNum == digit){
                ++counter;
            }
            else if (numOverTen == 0){
                break;
            }
            
        }
        if(counter > 0){
            return counter;
        }
        else{
            return 0;
    }
}
else{
   return counter;
    }
    return 0;
}

bool has_repeated_digits(int number) {
    // TODO(student): return true if number has repeated digits
    bool status = false;
    //int counter = 0;
    int numOverTen = number;
    int currentNum = number;
    //int digits [20] = {};
    //int digitIndex = 0;
    while(numOverTen > 0){
        currentNum = numOverTen % 10;
        numOverTen = numOverTen / 10;  
        //digits[digitIndex] = currentNum;
        //++digitIndex;
        if (count_digit_occurrences(number, currentNum) >= 2){
            status = true;
        }
        if (numOverTen == 0){
          break;
        }
    }
    return status;
}

int count_valid_numbers(int a, int b) {
    // TODO(student): return count of valid numbers in range
    int startNum = a;
    int endNum = b;
    int countValidNums = 0;
    for (startNum = a; startNum <= endNum; startNum++){
        if(has_repeated_digits(startNum) == 1){
            ++countValidNums;
        }
    }
    return countValidNums;
}
