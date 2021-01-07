// string_calculator.cpp
#include <iostream>
#include "my_string.h"
#include "./string_calculator.h"

using std::cout, std::endl;

unsigned int digit_to_decimal(char digit) {
    if (digit == '0') {
        return 0;
    }
    if (digit == '1') {
        return 1;
    }
    if (digit == '2') {
        return 2;
    }
    if (digit == '3') {
        return 3;
    }
    if (digit == '4') {
        return 4;
    }
    if (digit == '5') {
        return 5;
    }
    if (digit == '6') {
        return 6;
    }
    if (digit == '7') {
        return 7;
    }
    if (digit == '8') {
        return 8;
    }
    if (digit == '9') {
        return 9;
    }
    else {
        throw std::invalid_argument("Circus side show");
    }
    return 0;
}

char decimal_to_digit(unsigned int decimal) {
    if (decimal == 0) {
        return '0';
    }
    if (decimal == 1) {
        return '1';
    }
    if (decimal == 2) {
        return '2';
    }
    if (decimal == 3) {
        return '3';
    }
    if (decimal == 4) {
        return '4';
    }
    if (decimal == 5) {
        return '5';
    }
    if (decimal == 6) {
        return '6';
    }
    if (decimal == 7) {
        return '7';
    }
    if (decimal == 8) {
        return '8';
    }
    if (decimal == 9) {
        return '9';
    }
    else {
        throw std::invalid_argument("clowncourse");
    }
    return '\0';
}
/*
my_string trim_leading_zeros(const my_string& num) {
    // TODO(student): put your existing implementation here
    int strLen = num.length();
    bool is_neg = false;
    //use a for loop to check each charecter of the string and remove leading zeros
    for (int i = 0; i < strLen; i++){
        if (num[i] == "-"){
            num = num.replace(0,1,"");
            i--;
            is_neg = true;
        }
        else if (num[i] == "0"){
            num = num.replace(0,1,"");
            i--;
            //strLen = num.length();
        }
        else{
            if (num == ""){
                num = "0";
            }
            if (is_neg){
                num.insert(0, "-");
            }
            if (num == "-0"){
                num = "0";
            }
            return num;
        }
            
        }
    return num;
}

my_string add(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    bool both_are_neg = false;
    const my_string zero = "0";
    const my_string negative = "-";
    if (operator==(lhs, zero) || operator==(rhs, zero)){
   // if (lhs == "0" || rhs == "0") {
        if (operator==(lhs, zero)){
        //if (lhs == "0") {
            return rhs;
        }
        if (operator==(rhs, zero)){
        //if (rhs == "0") {
            return lhs;
        }
    }
    
    else if (lhs[0] == '-' && rhs[0] == '-') {
        lhs.erase(0, std::min(lhs.find_first_not_of('-'), lhs.size()-1));
        rhs.erase(0, std::min(rhs.find_first_not_of('-'), rhs.size()-1));
        both_are_neg = true;
    }
    else if ( (lhs.at(0) != '-') && (rhs.at(0) == '-') ) {
        rhs.erase(rhs.begin());
        return (subtract(lhs, rhs));
    }
    else if ( (lhs.at(0) == '-') && (rhs.at(0) != '-') ) {
        lhs.erase(lhs.begin());
        return (subtract(rhs, lhs));
    }

    my_string sum_string;

    while (lhs.size() < rhs.size()) {
        lhs.operator+=(zero);                              
        lhs = "0" + lhs;
    }

    while (rhs.size() < lhs.size()){
        rhs = "0" + rhs;
    }

    int holder = 0;

    for (int i = 1; i < ((int) lhs.size()+1); ++i) {
        int current_addition = digit_to_decimal(lhs.at(lhs.size() - i)) + digit_to_decimal(rhs.at(rhs.size() - i)) + holder;

        int last_number = current_addition % 10;
        char last_number_string = decimal_to_digit(last_number);

        sum_string = last_number_string + sum_string;
        holder = (current_addition >= 10);

        if (sum_string.size() >= lhs.size() ) {
            char string_holder = decimal_to_digit(holder);
            sum_string = string_holder + sum_string;
        }
    }

    if (both_are_neg) {
        sum_string = "-" + sum_string;
    }

    sum_string = trim_leading_zeros(sum_string);

    return sum_string;
}

my_string subtract(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    bool turn_negative = false;
    bool need_switch = false;

    my_string answer_string;

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    if ( (lhs.at(0) == '-') && (rhs.at(0) != '-') ) {
        lhs.erase(0, std::min(lhs.find_first_not_of('-'), lhs.size()-1));
        rhs.erase(0, std::min(rhs.find_first_not_of('-'), rhs.size()-1));
        return ('-' + add(lhs,rhs) );
    }

    if ( (lhs.at(0) != '-') && (rhs.at(0) == '-') ) {
        lhs.erase(0, std::min(lhs.find_first_not_of('-'), lhs.size()-1));
        rhs.erase(0, std::min(rhs.find_first_not_of('-'), rhs.size()-1));
        return (add(lhs,rhs) );
    }

    if ( (lhs.at(0) == '-') && (rhs.at(0) == '-') ) {
        lhs.erase(0, std::min(lhs.find_first_not_of('-'), lhs.size()-1));
        rhs.erase(0, std::min(rhs.find_first_not_of('-'), rhs.size()-1));
        if (lhs.size() > rhs.size()) {
            turn_negative = true;
        }
        if (lhs.size() < rhs.size()) {
            need_switch = true;
        }
        else if (lhs.size() == rhs.size()){
            need_switch = !(lhs > rhs);
            turn_negative = (lhs > rhs);
        }
    }

    else if ( (lhs.at(0) != '-') && (rhs.at(0) != '-') ) {

        lhs.erase(0, std::min(lhs.find_first_not_of('-'), lhs.size()-1));
        rhs.erase(0, std::min(rhs.find_first_not_of('-'), rhs.size()-1));

        if (lhs.size() < rhs.size()) {
            need_switch = true;
            turn_negative = true;
        }  
        if (lhs.size() == rhs.size() ) {
            need_switch = !(lhs > rhs);
            turn_negative = need_switch;
        }
    }

    while (lhs.size() < rhs.size()) {
        lhs = "0" + lhs;
    }

    while (rhs.size() < lhs.size()){
        rhs = "0" + rhs;
    }
    
    if (need_switch == true) {
        my_string lhs_temp = lhs;
        lhs = rhs;
        rhs = lhs_temp;
    }

    bool carry = false;
    int lhs_size = lhs.size();

    for (int i = 1; i < lhs_size + 1; ++i) {
        int current_top_number = digit_to_decimal(lhs.at(lhs.size()-i));
        int current_bottom_number = digit_to_decimal(rhs.at(rhs.size()-i));

        if (carry == true) {
            current_bottom_number += 1;
        }
        carry = false;

        if (current_top_number >= current_bottom_number) {
            answer_string = decimal_to_digit(current_top_number - current_bottom_number) + answer_string;
        }
        else {
            current_top_number += 10;
            answer_string = decimal_to_digit(current_top_number - current_bottom_number) + answer_string;
            carry = true;
        }
    }

    if (turn_negative == true) {
        answer_string = "-" + answer_string;
    }

    return trim_leading_zeros(answer_string);
    
}

my_string multiply(const my_string& lhs, const my_string& rhs) {
    // TODO(student): put your existing implementation here
    bool single_negative = false;

    if ( (lhs == "0") || (rhs == "0") ) {
        return "0";
    }

    if (  ((lhs.at(0) == '-') && (rhs.at(0) != '-')) || ((rhs.at(0) == '-') && (lhs.at(0) != '-')) ) {
        single_negative = true;
    }

    lhs.erase(0, std::min(lhs.find_first_not_of('-'), lhs.size()-1));
    rhs.erase(0, std::min(rhs.find_first_not_of('-'), rhs.size()-1));

    my_string sum_string;

    while (lhs.size() < rhs.size()) {
        lhs = "0" + lhs;
    }

    while (rhs.size() < lhs.size()){
        rhs = "0" + rhs;
    }

    int holder = 0;
    my_string current_total_sum = "0";
    my_string current_pair_product_string;

    int lhs_size = lhs.size();
    int rhs_size = rhs.size();

    for (int i = 1; i < lhs_size + 1; ++i) {
        for (int j = 1; j < rhs_size + 1; ++j) {
            int current_bottom_digit = digit_to_decimal( lhs.at(lhs.size() - i) );
            int current_top_digit = digit_to_decimal( rhs.at(rhs.size() - j) );
            int current_pair_product = current_bottom_digit * current_top_digit + holder;
            holder = ( (current_pair_product - (current_pair_product%10)) / 10 );
            
            if (j != rhs_size ) {
                current_pair_product_string = decimal_to_digit(current_pair_product % 10) + current_pair_product_string;
            }
            else {
                while (current_pair_product != 0) {
                    current_pair_product_string = decimal_to_digit(current_pair_product % 10) + current_pair_product_string;
                    current_pair_product /= 10;
                }
            }
        }
        
        int k = i;
        while (k != 1) {
            current_pair_product_string = current_pair_product_string + "0";
            k -= 1;
        }

        current_total_sum = add(current_pair_product_string, current_total_sum);
        current_pair_product_string = "";
        holder = 0;
    }

    if (single_negative) {
        current_total_sum = "-" + current_total_sum;
    }

    current_total_sum = trim_leading_zeros(current_total_sum);

    return current_total_sum;
}
*/