#include <iostream>
#include <limits>
#include "functions.h"

using std::cout, std::cin, std::endl;
int main() {
    // TODO(student): print prompt for input
    int num1;
    int num2;
    cout << "Enter numbers 0 < a <= b <= 10000: ";
    cin >> num1; 
    //cout << ", ";
    cin >> num2;
    //cout << endl;
    // TODO(student): read the numbers from standard input
    //cout << num1 << ", " << num2 << endl;
    // TODO(student): validate input (and reprompt on invalid input)
    bool valInput = false;
    if (is_valid_range(num1, num2)){
        valInput = true;
    }
    else{
        cout << "Invalid input" << endl;
        cout << "Enter numbers 0 < a <= b <= 10000: ";
        cin >> num1; 
        cin >> num2;
        int resultNums = count_valid_numbers(num1,num2);
        cout << "There are " << resultNums << " valid numbers between " << num1 << " and " << num2 << endl;
    }
    // TODO(student): compute and display solution
    /*int digitOccurr = count_digit_occurrences(num1, 2);
    cout << digitOccurr << endl;
    bool chceck = has_repeated_digits(num1);
    cout << chceck << endl;*/
    if (valInput == true){
        int resultNums = count_valid_numbers(num1,num2);
        cout << "There are " << resultNums << " valid numbers between " << num1 << " and " << num2 << endl;
        return 0;
    }
}
