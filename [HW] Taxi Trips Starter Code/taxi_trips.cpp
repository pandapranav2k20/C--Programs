#include <stdexcept>
#include <string>
using std::string;
#include "taxi_trips.h"


bool is_payment_valid(string type, string valid_types[], unsigned int size) {
  // TODO(student): implement 
  /*use a for loop to iterate through and compare the items in
  valid_types to the string type*/
  for (unsigned int i = 0; i < size; i++){
    if (type == valid_types[i]){
      return true;
    }
  }
  if (type == "x" && size == 0){
    throw std::invalid_argument("");
  }
  return false;
}

double max(double values[], unsigned int size) {
  // TODO(student): implement
  /* assume the maximum is the first value and then iterate through
  values comparin every value at every index. Throw an error if size  = 0*/
  
  double maximum;
  if (size == 0){
    throw std::invalid_argument("");
  }
  else{
    maximum = values[0];
    for (unsigned int k = 1; k < size; k++){
      if(maximum < values[k]){
        maximum = values[k];
      }
    }
  }
  return maximum;
}

double min(double values[], unsigned int size) {
  // TODO(student): implement
  /*Pretty much the same logic as max, but checking for smallest*/
  double minimum;
  if (size == 0){
    throw std::invalid_argument("");
  }
  else{
    minimum = values[0];
    for (unsigned int l = 1; l < size; l++){
      if (minimum > values[l]){
        minimum = values[l];
      }
    }
  }
  return minimum;
}

double average(double values[], unsigned int size) {
  // TODO(student): implement
  /* calculate the average by summing all elements of values, 
  then divide by size (number of elements) */
  double sum = 0;
  if(size == 0){
    throw std::invalid_argument("");
  }
  //use a for loop to sum all elements
  for (unsigned int x = 0; x < size; x++){
    sum += values[x];
  }
  //calculate the average
  double avgCalc = sum / size;
  return avgCalc;
}

double mode(double values[], unsigned int size) {
  // TODO(student): implement
  if (size == 0){
    throw std::invalid_argument("");
  }/*
  double start_pt = values[0];
  double mode = start_pt;
  double count = 1;
  double countMode = 1;
  //use a for loop to determine the mode for values[]
  for (unsigned int i = 1; i < size; i++){
    if (values[i] == start_pt){
      ++count;
    }
    else{
      //now we move onto the next number
      count = 1;
      start_pt = values[i];
    }
    if(count > countMode){
      countMode = count;
      mode= start_pt;
    }
  }*/
  double counter = 0;
  double newElement = 0;
  double mode = 0;
  for (unsigned int i = 0; i < size; ++i){
    for (unsigned int j = 0; j < size; ++j){
      if (values[i] == values[j]){
        counter += 1;
      }
    }
    if (counter > newElement){
      newElement = counter;
      mode = values[i];
    }
    //reset the counter 
    counter = 0;
  }


  //Sort the array from least to greatest
  /*for (unsigned int i = 0; i < size - 1; i++){
    for (unsigned int j = 0; j < size - i - 1; j++ ){
      if(values[j] > values[j+1]){
        double tempHolder = values[j];
        values[j] = values [j+1];
        values[j+1] = tempHolder;
      }
    }
  }*/
  //Find the mode of the values
  /*int count = 1;
  int highest = 0;
  double mode = values[0];
  for (unsigned int key = 0; key < size - 1; key++){
    if (values[key] == values[key + 1]){
      count++;
      if (count > highest){
        highest = count;
        mode = values[key];
      }
    }else{
      count = 1;
    }
  }*/
  return mode;
}

int length_longest_seq_zeros(double values[], unsigned int size) {
  // TODO(student): implement
  if (size == 0){
    throw std::invalid_argument("");
  }
  int counter = 0;
  int prevCounter = 0;
  bool go = true;
  for (unsigned int x = 0; x < size; x++){
    if (values[x] == 0){
      //use a while loop here actually to check how many are in a row
      counter = 1;
      unsigned int index2 = x + 1;
      go = true;
      while (go){
        if (values[index2] == 0 && (index2 != size)){
          ++counter;
          ++index2;
        }
        else{
          if (counter > prevCounter){
            prevCounter = counter;
          }
        go = false;
          
        }
      }
    }
  }
  //Return what the largest number of counter seq. zeros is
  /*If the last element of the array is zero, the largest value
  may be stored in counter rather than prevCounter, so check to 
  see which is larger and return that one*/
  if (prevCounter > counter){
    return prevCounter;
  }
  else{
    return prevCounter;
  }
}