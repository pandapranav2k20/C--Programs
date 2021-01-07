// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin" 
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades 
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO
    
    // TODO(student): declare and initialize variables that you want
    double hwTotalPercent = 0.0;
    int hwCounter = 0;
    double lwTotalPercent = 0.0;
    int lwCounter = 0;
    double examTotalPercent = 0.0;
    int examCounter = 0;
    double finalExamScore = 0.0;
    double enTotalPercent = 0.0;
    int enCounter = 0;
    //In the case there are multiple final exam scores for some reason
    int finalCounter = 0;
    char final_letter_grade_calc = 'X';
    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            // TODO(student): process exam score
            examTotalPercent += score;
            examCounter += 1;
        } else if (category == "final-exam") {
            // TODO(student): process final score
            finalExamScore += score;
            finalCounter += 1;
        } else if (category == "hw") {
            // TODO(student): process hw score
            hwTotalPercent += score;
            hwCounter += 1;
        } else if (category == "lw") {
            // TODO(student): process lw score
            if (score >= 1){
                lwTotalPercent += 100;
                lwCounter += 1;
            }
            else{
                lwTotalPercent += 0;
                lwCounter += 1;
            }
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            if (score >= 100){
                enTotalPercent += 100;
                enCounter += 1;
            }
            else {
                enTotalPercent += score;
                enCounter += 1;
            }
        } else{cout << "ignored invalid input" << endl;}

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    if ((examTotalPercent /(examCounter) < 60) && finalExamScore == 0){  
        finalCounter += 1;
    }
    //double ThreeExamAvg = enTotalPercent / double(enCounter); 
    double exam_average;
    if((examTotalPercent + finalExamScore) == 0 || (examCounter + finalCounter) == 0){
        exam_average = 0;
    } 
    else{
        
        exam_average = (examTotalPercent + finalExamScore) / (examCounter + finalCounter);
    }
    if(finalExamScore > exam_average){
        exam_average = finalExamScore;
    }
    else{}
    double hw_average;
    if(hwTotalPercent == 0 && hwCounter == 0){
        hw_average = 0;
    }
    else{
        hw_average = hwTotalPercent / (hwCounter);
    }
    double lw_average;
    if(lwTotalPercent == 0 && lwCounter == 0){
        lw_average = 0;
    }
    else{
        lw_average = (lwTotalPercent) / (lwCounter);
    }
    double engagement;
    if(enTotalPercent >= 100){

        enTotalPercent = 100;
        engagement = enTotalPercent;
    }
    else{
        engagement = enTotalPercent; // enCounter;
    }
    
    // TODO(student): compute weighted total of components
    double weighted_total = 0.4 * exam_average + 0.1 * engagement + 0.4 * hw_average + 0.1 * lw_average;

    // TODO(student): compute final letter grade
    if (weighted_total >= 90.0){
        final_letter_grade_calc = 'A';
    }
    else if (90.0 > weighted_total && weighted_total >= 80.0){
        final_letter_grade_calc = 'B';
    }
    else if (80.0 > weighted_total && weighted_total >= 70.0){
        final_letter_grade_calc = 'C';
    }
    else if (70.0 > weighted_total && weighted_total >= 60.0){
        final_letter_grade_calc = 'D';
    }
    else{
        final_letter_grade_calc = 'F';
    }
    char final_letter_grade = final_letter_grade_calc;

    print_results(
        exam_average, hw_average, lw_average, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
