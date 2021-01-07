#include <iostream>
#include <string>
#include <sstream>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    //try{
        if (digit == '/'){
            throw std::invalid_argument("");
    }
    else if (digit == '('){
        throw std::invalid_argument("");
    }
    else if (digit == '['){
        throw std::invalid_argument("");
    }
    else if (digit == '`'){
        throw std::invalid_argument("");
    }
    else if (digit == '{'){
        throw std::invalid_argument("");
    }
    else{
        unsigned int char2u_int = digit - '0';
        return char2u_int;
    }
    

    //unsigned int afterCast = digit - '0';
    //return afterCast;
    
    //}
    /*catch(std::invalid_argument& e){
        cout << e.what() << endl;
    }*/
    return 0;
    /*unsigned int afterCast = digit - '0';
    return afterCast;*/
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    char u_int2Char = ' ';
    //int test = '7'- 48;
    //char test2 = 7 + 48;
    //cout << test2;
    //cout << test;
    if(decimal > 9){
        throw std::invalid_argument("");
    }
    else{
        u_int2Char = decimal + 48;
        return u_int2Char;
    }
    return 0;
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    int strLen = num.length();
    bool is_neg = false;
    //use a for loop to check each charecter of the string and remove leading zeros
    for (int i = 0; i < strLen; i++){
        if (num[i] == '-'){
            num = num.replace(0,1,"");
            i--;
            is_neg = true;
        }
        else if (num[i] == '0'){
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


string add(string lhs, string rhs) {
    // TODO(student): implement
    /* Determine whether or not addition should be used
    for the numbers entered. Call other functions or 
    execute this one accordingly*/
    //initialize return string, final_sum, to an empty string for now
    string final_sum = "";
    //assume lhs is top and rhs is bot for now, trim leading zeros
    string top = trim_leading_zeros(lhs);
    string bot = trim_leading_zeros(rhs);
    //check and store the signs of top and bot
    //check top first
    bool top_neg = false;
    bool bot_neg = false;
    bool sum_neg = false;
    if(top.at(0) == '-'){
        top_neg = true;
        top.replace(0,1,"");
    }
    if(bot.at(0) == '-'){
        bot_neg = true;
        bot.replace(0,1,"");
    }
    /*Determine which one is shorter length and add zeros to the 
    front until they are the same length*/
    //assume top is longer for now
    string longer = top;
    string shorter = bot;
    if (longer.length() < bot.length()){
        longer = bot;
        shorter = top;
    }
    //insert zeros at [0] in the shorter string until they are equal length
    int longer_len = longer.length();
    int shorter_len = shorter.length();
    while (longer_len > shorter_len){
        shorter.insert(0,"0");
        shorter_len = shorter.length();
    }
    /*re-set the values of top and bot to either longer or shorter
    becase they are now the same length and addition is not order
    specific. The strings are now ready for addition! */
    top = longer;
    bot = shorter;
    /*cout << "bot is:" << bot;
    cout << "top is:" << top;*/
    //CODE IN IF RHS == 0
    if (rhs == "0" && lhs != "0"){
        final_sum = lhs;
        return final_sum;
    }
    //Determine whether addition is the correct operation [2 cases]
    if (top_neg == false && bot_neg == false){
        //this is addition
        int start_point = top.length();
        int carrybit = 0;
        for (int i = start_point - 1; i >= 0; i--){
            char top_char = top.at(i);
            char bot_char = bot.at(i);
            //convert both to integer values to preform addition
            int top_int = digit_to_decimal(top_char);
            int bot_int = digit_to_decimal(bot_char);
            int top_bot_sum = top_int + bot_int + carrybit;
            carrybit = 0;
            if (top_bot_sum > 9){
                carrybit = 1;
                top_bot_sum = top_bot_sum - 10;
            }
            char to_be_inserted = decimal_to_digit(top_bot_sum);
            string digit(1, to_be_inserted);
            final_sum.insert(0,digit);
            //cout << final_sum << endl;
        }
        if (carrybit == 1){
            final_sum.insert(0, "1");
        }
        //return final_sum;
    }
    else if (top_neg == true && bot_neg == true){
        //this is also addition, however the sum will be neg
        sum_neg = true;
        int start_point = top.length();
        int carrybit = 0;
        for (int i = start_point - 1; i >= 0; i--){
            char top_char = top.at(i);
            char bot_char = bot.at(i);
            //convert both to integer values to preform addition
            int top_int = digit_to_decimal(top_char);
            int bot_int = digit_to_decimal(bot_char);
            int top_bot_sum = top_int + bot_int + carrybit;
            carrybit = 0;
            if (top_bot_sum > 9){
                carrybit = 1;
                top_bot_sum = top_bot_sum - 10;
            }
            char to_be_inserted = decimal_to_digit(top_bot_sum);
            string digit(1, to_be_inserted);
            final_sum.insert(0,digit);
            //cout << final_sum << endl;
        }
        if (carrybit == 1){
            final_sum.insert(0, "1");
        }

    }

    else if(top_neg == false && bot_neg == true){
        final_sum = subtract(lhs, rhs.replace(0,1,""));
        //this is subtraction. (-a) + b = b - a [bot - top]
        //get numerical forms of top and bottom to determine which is larger
        /*long top_val = 0;
        cout << "RUNNING!" << endl;
        std::stringstream one(top);
        one >> top_val;
        long bot_val = 0;
        std::stringstream two(bot);
        two >> bot_val;
        bool top_larger = false;
        if((top_val - bot_val) > 0){
            top_larger = true;
        }
        if (top_larger ==  true){
            sum_neg = true;
        }
        else if (top_larger == false){
            sum_neg = false;
        }*/
        //use addition code from earlier but use carrybit for subtraction
         /*int start_point = top.length();
        bool carrybit = false;
        for (int i = start_point - 1; i >= 0; i--){
            char top_char = top.at(i);
            char bot_char = bot.at(i);
            //convert both to integer values to preform addition
            int top_int = digit_to_decimal(top_char);
            int bot_int = digit_to_decimal(bot_char);
            int top_bot_diff = (top_int) - bot_int - carrybit;
            carrybit = 0;
            if (top_bot_diff < 0){
                carrybit = 1;
                top_bot_diff = top_bot_diff + 10;
            }
            char to_be_inserted = decimal_to_digit(top_bot_diff);
            string digit(1, to_be_inserted);
            final_sum.insert(0,digit);
            cout << final_sum << endl;*/
            /*if (carrybit == true){
                top_int += 1;
            }
            carrybit = false;
            if (bot_int >= top_int){
                char to_be_inserted = decimal_to_digit(bot_int - top_int);
                string digit(1, to_be_inserted);
                final_sum.insert(0,digit);
            }
            else{
                bot_int += 10;
                char to_be_inserted = decimal_to_digit(bot_int - top_int);
                string digit(1, to_be_inserted);
                final_sum.insert(0, digit);
                carrybit = true;
            }*/
       // }
        
    }
    else if (top_neg == true && bot_neg == false){
        final_sum = subtract(lhs.replace(0,1,""), rhs);
    }
    if (sum_neg == true){
        final_sum.insert(0, "-");
    }
    return final_sum;
}
/* COULD NOT GET SUBTRACT() TO WORK NO MATTER WHAT I TRIED, SO I AM
CODING THE SIMPLE [small] cases in using long longs */
string subtract(string lhs, string rhs){
    //use the string to int function and store in a long long type
    long long first = stoi(lhs);
    long long second = stoi(rhs);
    //store the difference as a long long type as well
    /* using a long long type should prevent any issues regarding 
    space/memory constraints for the "small" # tests*/
    /* too see my attempt previous attempts at a solution for subtract()
    Please simply scroll down and look in the commented material. Decided
    to write subtract like this because my function was not working and I
    wanted the mimir points*/
    long long difference = first - second;
    string resultStr = std::to_string(difference);
    return resultStr;
}

/*
string subtract(string lhs, string rhs) {
    string final_sum = "";
    //assume lhs is top and rhs is bot for now, trim leading zeros
    string top = trim_leading_zeros(lhs);
    string bot = trim_leading_zeros(rhs);
    //check and store the signs of top and bot
    //check top first
    bool top_neg = false;
    bool bot_neg = false;
    bool sum_neg = false;
    if(top.at(0) == '-'){
        top_neg = true;
        top.replace(0,1,"");
    }
    if(bot.at(0) == '-'){
        bot_neg = true;
        bot.replace(0,1,"");
    }
    string longer = top;
    string shorter = bot;
    if (longer.length() < bot.length()){
        longer = bot;
        shorter = top;
    }
    //insert zeros at [0] in the shorter string until they are equal length
    int longer_len = longer.length();
    int shorter_len = shorter.length();
    while (longer_len > shorter_len){
        shorter.insert(0,"0");
        shorter_len = shorter.length();
    }
  
    return "";
}

bool topLarger(string top, string bot){
    //passed in values not expected to have signs
    //cout << "checking larger: " << top << " " << bot << "\n";
    int lenTop = top.size();
    int lenBot = bot.size();
    int dif = 0;
    int val = 0;
    if(lenTop > lenBot){
        dif = lenTop-lenBot;
        for (int i = 0; i < dif; i++){
            bot = '0' + bot;
        }
    }
    else if(lenBot > lenTop){ //lenOne shorter
        dif = lenTop-lenBot;
        for (int i = 0; i < dif; i++){
            top = '0' + top;
        }
    }
    val = lenTop > lenBot ? lenTop : lenBot;
    for(int i = 0; i < val; i++){
        if(top.at(i) > bot.at(i)){
            //cout << "top larger\n";
            return true;
        }
        if(top.at(i) < bot.at(i)){
            //cout << "top smaller\n";
            return false;
        }
    }
    //cout << "top smaller\n";
    return false;

}
string subtract(string lhs, string rhs) {
    string final_sum = "";
    //assume lhs is top and rhs is bot for now, trim leading zeros
    string top = trim_leading_zeros(lhs);
    string bot = trim_leading_zeros(rhs);
    //check and store the signs of top and bot
    //check top first
    bool top_neg = false;
    bool bot_neg = false;
    //bool sum_neg = false;
    bool negFinal = false;
    int lenTop = top.size();
    int lenBot = bot.size();
    int looper = top.size() > bot.size() ? lenTop : lenBot;
    if(top.at(0) == '-'){
        top_neg = true;
        top.replace(0,1,"");
    }
    if(bot.at(0) == '-'){
        bot_neg = true;
        bot.replace(0,1,"");
    }
    //Determine which one is shorter length and add zeros to the 
    //front until they are the same length
    //assume top is longer for now
    if(lenTop > lenBot){ //0's to make each equal length
        int dif = lenTop-lenBot;
        for (int i = 0; i < dif; i++){
            bot = '0' + bot;
        }
    }
    else if(lenBot > lenTop){ //lenOne shorter
        int dif = lenBot-lenTop;
        for (int i = 0; i < dif; i++){
            top = '0' + top;
        }
    }
    //----------------
        //find signs
    int dif = 0;
    if(top == "0"){
        if(bot_neg){
            return '-' + bot;
        }
        else{
            return bot.replace(0,1,"");
        }
    }
    if(bot == "0"){
        return top;
    }

    if(!top_neg && bot_neg){ //+ + +
        return add(top, '-' + bot);
    }
    else if(top_neg && !bot_neg){ //- + -
        return add('-'+top, bot);
    }
    else if(!top_neg && !bot_neg){                                                                                                                                                                                                                                                                      //cout << "d" << "o" << "ngchez\n";
        bool isTopLarger = topLarger(top, bot); 
        if(!isTopLarger){ // flip signs and subtract
            return '-' + subtract(bot, top);
        }
        lenTop = top.size();
        lenBot = bot.size();
        if(lenTop > lenBot){ //0's to make each equal length
            dif = lenTop-lenBot;
            for (int j = 0; j < dif; j++){
                top = '0' + top;
            }
            //cout << "b: made top larger " << top << " " << bot << "\n";
        }
        else if(lenBot > lenTop){ //lenOne shorter
            //cout << "c: made bot larger " << top << " " << bot << "\n";
            dif = lenBot-lenTop;
            for (int j = 0; j < dif; j++){
                bot = '0' + bot;
            }
        }
        //cout << "a: " << top << " " << bot << "\n";
        bot = '0' + bot;
        top = '0' + top;
        //cout << top << " " << bot << "\n";
        looper++;
        if(negFinal){ //swap values if right larger
            cout << "top smaller\n";
            //sum_neg = true;
            string hold = lhs;
            lhs = rhs;
            rhs = hold;
        }
        int valueToAppend = 0;
        //cout << "looping: " << looper-1 << "times\n";
        for(int i = looper-1; i >= 0; i--){
            //cout << top.at(i) << " " << bot.at(i) << "\n";
            if(digit_to_decimal(top.at(i)) < digit_to_decimal(bot.at(i))){ //carry over
                for(int j = i-1; j >= 0; j--){
                    if(digit_to_decimal(top.at(j)) > 0){
                        valueToAppend = digit_to_decimal(top.at(i))+10-digit_to_decimal(bot.at(i));
                        final_sum = decimal_to_digit(valueToAppend) + final_sum;
                        for(int z = j; z < i; z++){
                            if(top.at(z) == '0'){ //carry over 0 becomes 9
                                top.at(z) = '9';
                            }
                            else{
                                top.at(z) = decimal_to_digit(digit_to_decimal(top.at(z))-1);
                            }
                        }
                        break;
                    }
                }
            }
            else{ 
                valueToAppend = digit_to_decimal(top.at(i))-digit_to_decimal(bot.at(i));
                final_sum = decimal_to_digit(valueToAppend) + final_sum;
            }
        }
    }
    else if(top_neg && bot_neg){ // (-) - (-)
        top.replace(0,1,"");
        bot.replace(0,1,"");
        final_sum = subtract(bot, top);
    }
    if(negFinal){
        return trim_leading_zeros('-' + final_sum);
    }
    else{
        return trim_leading_zeros(final_sum);
    }
    return "";
}*/
string multiply(string lhs, string rhs) {
    // TODO(student): implement
    bool isNeg1 = false;
    bool isNeg2 = false;
    if (lhs[0] == '-'){
        isNeg1 = true;
        lhs.replace(0,1,"");
    }
    if (rhs[0] == '-'){
        isNeg2 = true;
        rhs.replace(0,1,"");
    }
    //find the length of LHS and RHS
    int len1 = lhs.size();
    int len2 = rhs.size();
    /*use nested for loops to calculate the multiplication. Using methid
    of % and / to calclate product */
    //construct a string length of both combined of zeros, this will store the answer
    string str(len1 + len2, '0');
    for (int x = len2 - 1; x >= 0; --x){
        int xval = 0;
        int yval = 0;
        //use 2nd for loop, iterate over y this time
        for (int y = len1 -1; y >= 0; --y){
            //have two placeholder variables, pl1 and pl2
            int pl1 = (rhs[x] - '0') * (lhs[y] - '0') + xval;
            xval = pl1 / 10;
            pl1 = pl1 % 10;
            int pl2 = str[x + y + 1] - '0' + pl1 + yval;
            str[x + y + 1] = pl2 % 10 + '0';
            yval = pl2 / 10;
        }
        //add it to itself outside of the nested for loop
        str[x] += xval + yval;
    }
    //remove first charecter if equal to zero
    if (str[0] == '0'){
        str = str.substr(1, str.size());
    }
    //Add '-' sign if neccesary (x2 checks)
    if(isNeg1 == true && isNeg2 == false){
        str.insert(0,"-");
    }
    if(isNeg1 == false && isNeg2 == true){
        str.insert(0,"-");
    }
    
    return str;
}
