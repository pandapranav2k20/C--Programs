#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "taxi_trips.h"
using std::string, std::ifstream, std::cin, std::cout, std::endl;

int main() {
  const unsigned int MAX_TRIPS = 10000;

  /*Promt the user to enter the name of the file and 
  create the input file stream object*/
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  ifstream ifs(filename);
  
  /*Determine whether or not the file can be opened*/
  if (!ifs.is_open()) {
    cout << "Can't open " << filename << endl;
    return 1;
  }
  
  /*Count the number of lines in the txt file, we will
  need to use this in order to determine the size of 
  the arrays we will use to store data*/
  /*string lineCounterHolder;
  unsigned int number_of_lines = 0;
  while (getline(ifs, lineCounterHolder)){
        ++number_of_lines;
  }*/

  /*Declare the arrays used to store the values which we will
  be parsing from the txt file*/
  /*ACTUALLY SET SIZE EQUAL TO THE GIVEN CONSTANT MAX TRIPS*/
  double durations [MAX_TRIPS];
  double distances [MAX_TRIPS];
  double fares [MAX_TRIPS];
  double tips [MAX_TRIPS];
  string payments [MAX_TRIPS];
  
  /*Declare the variables that will hold the values which we 
  will ultimately output to the console*/
  unsigned int number_of_lines = 0;
  string line = "";
  unsigned int numTrips = 0;
  //int numInvalid = 0;
  double avgDur = 0.0;
  double avgDist = 0.0;
  double avgFare = 0.0;
  double avgTip = 0.0;
  double maxDur = 0.0;
  double maxDist = 0.0;
  double maxFare = 0.0;
  double maxTip = 0.0;
  double minDur = 0.0;
  double minDist = 0.0;
  double minFare = 0.0;
  double minTip = 0.0;
  double modeDur = 0.0;
  double modeDist = 0.0;
  double modeFare = 0.0;
  double modeTip = 0.0;
  
  /*Sort through and parse the data, log into the
  arrays created above*/
  /*if(number_of_lines < MAX_TRIPS){
    numTrips = number_of_lines;
  }*/
  //copy the string and find the locations in the line where whitespaces exist
  int n = 0;
  const unsigned int numSpaces = 6;
  int spaceIndexes[numSpaces];
  while (!ifs.eof()){
    std::getline(ifs, line);
    string copyLine = line + " ";
    line = line + " ";
    //cout << line << endl;
    //cout << copyLine << endl;
    ++number_of_lines;
    //there are 5 whitespaces seperating out the data, find the index of each
    //int spInd1, spInd2, spInd3, spInd4, spInd5;
    //int spaceIndexes[50];
    int i = 0;
    while (copyLine != "" && i <= 5){
      int spaceLoc = copyLine.find(" ");
      spaceIndexes[i] = spaceLoc;
      copyLine = copyLine.erase(0, spaceLoc + 1);
      //cout << spaceLoc << endl;
      //cout << copyLine << endl;
      ++i;
    }
    /*add the data to the array as doubles*/
    //cout << spaceIndexes << endl;
    /*find the location of each space seperating the data using the indices of
    spaces found above*/
    int spLoc1 = spaceIndexes[0];
    int spLoc2 = spaceIndexes[1] + spLoc1;
    int spLoc3 = spaceIndexes[2] + spLoc2;
    int spLoc4 = spaceIndexes[3] + spLoc3;
    int spLoc5 = spaceIndexes[4] + spLoc4;
    int spLoc6 = spaceIndexes[5] + spLoc5;
    
    /*durations[n] = std::stod(line.substr(spaceIndexes[1-1],spaceIndexes[2-1] - spaceIndexes[1-1]));
    distances[n] = std::stod(line.substr(spaceIndexes[2-1],spaceIndexes[3-1] - spaceIndexes[2-1]));
    fares[n] = std::stod(line.substr(spaceIndexes[3-1],spaceIndexes[4-1] - spaceIndexes[3-1]));
    tips[n] = std::stod(line.substr(spaceIndexes[4-1],spaceIndexes[5-1] - spaceIndexes[4-1]));*/

    /*durations[n] = std::stod(line.substr(spLoc1, spLoc2 - spLoc1));
    distances[n] = std::stod(line.substr(spLoc2, spLoc3 - spLoc2));
    fares[n] = std::stod(line.substr(spLoc3, spLoc4 - spLoc3));
    tips[n] = std::stod(line.substr(spLoc4, spLoc5 - spLoc4));*/

    /*make a bunch of copes of line to substring*/
    string copy1 = line;
    string copy2 = line;
    string copy3 = line;
    string copy4 = line;
    string copy5 = line;
    /*
    cout << copy1.substr(spLoc1 + 1, spLoc2 - spLoc1 + 1) << endl;
    cout << copy2.substr(spLoc2 + 2, spLoc3 - spLoc2 + 1) << endl;
    cout << copy3.substr(spLoc3 + 3, spLoc4 - spLoc3 + 1) << endl;
    cout << copy4.substr(spLoc4 + 4, spLoc5 - spLoc4 + 1) << endl;
    */
    string curDur = copy1.substr(spLoc1 + 1, spLoc2 - spLoc1 + 1);
    //cout << curDur << endl;
    double decForm1 = std::stod(curDur);
    //cout << decForm << endl;
    string curDis = copy2.substr(spLoc2 + 2, spLoc3 - spLoc2 + 1);
    double decForm2 = std::stod(curDis);
    string curFar = copy3.substr(spLoc3 + 3, spLoc4 - spLoc3 + 1);
    double decForm3 = std::stod(curFar);
    string curTip = copy4.substr(spLoc4 + 4, spLoc5 - spLoc3 + 1);
    double decForm4 = std::stod(curTip);
    string curPay = copy5.substr(spLoc5 + 5, spLoc6 - spLoc3 + 1);
    //cout << curPay << endl;
    
    /*durations[n] = std::stod(copy1.substr(spLoc1 + 1, spLoc2 - spLoc1 + 1));
    distances[n] = std::stod(copy2.substr(spLoc2 + 2, spLoc3 - spLoc2 + 1));
    fares[n] = std::stod(copy3.substr(spLoc3 + 3, spLoc4 - spLoc3 + 1));
    tips[n] = std::stod(copy4.substr(spLoc4 + 4, spLoc5 - spLoc4 + 1));*/
    
    durations[n] = decForm1;
    distances[n] = decForm2;
    fares[n] = decForm3;
    tips[n] = decForm4;
    payments[n] = curPay;
    //cout << line.substr(spLoc2, spLoc3 - spLoc2) << endl;
    ++n;
  }
  /*Exit the loop, now validate and check data. Make copies of the arrays
  in the case where the original values are neccesary*/
  string paymentsLegal[4] = {"Credit Card", "Cash", "Nocharge", "Unknown"};
  unsigned int paymentsSize = 4;
  paymentsSize = paymentsSize + 0;
  double copDurations[MAX_TRIPS];
  double copDistances[MAX_TRIPS];
  double copFares[MAX_TRIPS];
  double copTips[MAX_TRIPS];
  string copPayments[MAX_TRIPS];
  std::copy(std::begin(durations), std::end(durations), std::begin(copDurations));
  std::copy(std::begin(distances), std::end(distances), std::begin(copDistances));
  std::copy(std::begin(fares), std::end(fares), std::begin(copFares));
  std::copy(std::begin(tips), std::end(tips), std::begin(copTips));
  std::copy(std::begin(payments), std::end(payments), std::begin(copPayments));
  
  //unsigned int i2 = 0;
  int numInvalid = 0;
  //bool isValid;
  for (unsigned int i2 = 0; i2 < number_of_lines; ++i2){
    /*check all conditions that may cause data to be invalid, if invalid
    remove all data for that trip (if-elif tree)*/
    i2 = i2 + 0;
    //bool isValid = true;
    //cout << copPayments[i2] << endl;
    /*if (copPayments[i2] != ""){
      isValid = is_payment_valid(copPayments[i2], paymentsLegal, paymentsSize);
    }
    else{
      isValid = true;
    }*/
    if ((copDurations[i2] == 0 && copDistances[i2] == 0)){
      //remove all data stored at i2
      if(copFares[i2] != 0){
        for (unsigned int i = i2; i < number_of_lines; i++){
        copDurations[i] = copDurations[i+1];
        copDistances[i] = copDistances[i+1];
        copFares[i] = copFares[i+1];
        copTips[i] = copTips[i+1];
        //copPayments[i] = copPayments[i+1];
      }
      copDurations[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copDistances[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copFares[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copTips[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      //copPayments[number_of_lines-1] = "";
      numInvalid++;
      }
    else if (copDurations[i2] > 86400){
      //remove all data stored at i2
      for (unsigned int i = i2; i < number_of_lines; i++){
        copDurations[i] = copDurations[i+1];
        copDistances[i] = copDistances[i+1];
        copFares[i] = copFares[i+1];
        copTips[i] = copTips[i+1];
        //copPayments[i] = copPayments[i+1];
      }
      copDurations[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copDistances[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copFares[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copTips[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      //copPayments[number_of_lines-1] = "";
      numInvalid++;
    }
    else if (copDistances[i2] > 1500){
      //remove all data stored at i2
      for (unsigned int i = i2; i < number_of_lines; i++){
        copDurations[i] = copDurations[i+1];
        copDistances[i] = copDistances[i+1];
        copFares[i] = copFares[i+1];
        copTips[i] = copTips[i+1];
        //copPayments[i] = copPayments[i+1];
      }
      copDurations[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copDistances[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copFares[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copTips[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      //copPayments[number_of_lines-1] = "";
      numInvalid++;
    }
    else if ((copFares[i2] + copTips[i2]) > 5000){
      //remove all data stored at i2
      for (unsigned int i = i2; i < number_of_lines; i++){
        copDurations[i] = copDurations[i+1];
        copDistances[i] = copDistances[i+1];
        copFares[i] = copFares[i+1];
        copTips[i] = copTips[i+1];
        //copPayments[i] = copPayments[i+1];
      }
      copDurations[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copDistances[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copFares[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copTips[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      //copPayments[number_of_lines-1] = "";
      numInvalid++;
    }
    
      
    }
    /*else if (!(is_payment_valid(copPayments[i2], paymentsLegal, paymentsSize))){
      for (unsigned int i = i2; i < number_of_lines; i++){
        copDurations[i] = copDurations[i+1];
        copDistances[i] = copDistances[i+1];
        copFares[i] = copFares[i+1];
        copTips[i] = copTips[i+1];
        //copPayments[i] = copPayments[i+1];
      }
      copDurations[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copDistances[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copFares[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copTips[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      //copPayments[number_of_lines-1] = "";
      numInvalid++;
    }*/
    /*else if (isValid == false && copPayments[i2] != ""){
      for (unsigned int i = i2; i < number_of_lines; i++){
        copDurations[i] = copDurations[i+1];
        copDistances[i] = copDistances[i+1];
        copFares[i] = copFares[i+1];
        copTips[i] = copTips[i+1];
        //copPayments[i] = copPayments[i+1];
      }
      copDurations[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copDistances[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copFares[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      copTips[number_of_lines-1] = __DBL_HAS_QUIET_NAN__;
      //copPayments[number_of_lines-1] = "";
      numInvalid++;
    }*/
  }
  /*Exit the loop, now call and store the values using the arrays created
  earlier as parameters. save the values in the placeholder variables
  declared above*/
  numTrips = number_of_lines - numInvalid;
  avgDur = average(copDurations, number_of_lines - numInvalid);
  avgDist = average(copDistances, number_of_lines - numInvalid);
  avgFare = average(copFares, number_of_lines - numInvalid);
  avgTip = average(copTips, number_of_lines - numInvalid);
  maxDur = max(copDurations, number_of_lines - numInvalid);
  maxDist = max(copDistances, number_of_lines - numInvalid);
  maxFare = max(copFares, number_of_lines - numInvalid);
  maxTip = max(copTips, number_of_lines - numInvalid);
  minDur = min(copDurations, number_of_lines - numInvalid);
  minDist = min(copDistances, number_of_lines - numInvalid);
  minFare = min(copFares, number_of_lines - numInvalid);
  minTip = min(copTips, number_of_lines - numInvalid);
  modeDur = mode(copDurations, number_of_lines - numInvalid);
  modeDist = mode(copDistances, number_of_lines - numInvalid);
  modeFare = mode(copFares, number_of_lines - numInvalid);
  modeTip = mode(copTips, number_of_lines - numInvalid);
  int lenMostZeroTips = length_longest_seq_zeros(copTips, number_of_lines - numInvalid);
  
  /*Print everything just to make sure its working*/
  //cout << durations << endl;
  //cout << distances << endl;
  /*We are now ready to output the gathered information to the console*/
  
  cout << "Number of trips: " << numTrips << endl;
  cout << "Number of trips with invalid data: " << numInvalid << endl;
  cout << "Duration: " << "max " << maxDur << " min " << minDur << " avg " << avgDur << " mode " << modeDur << endl;
  cout << "Distance: " << "max " << maxDist << " min " << minDist << " avg " << avgDist << " mode " << modeDist << endl;
  cout << "Fare: " << "max " << maxFare << " min " << minFare << " avg " << avgFare << " mode " << modeFare << endl;
  cout << "Tip: " << "max " << maxTip << " min " << minTip << " avg " << avgTip << " mode " << modeTip << endl;
  cout << "Length of longest sequence without tips: " << lenMostZeroTips << endl;

  //return zero because function is an 'int' type
  return 0;
}