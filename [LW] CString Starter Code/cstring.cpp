#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)
  bool go = true;
  unsigned int strLen = 0;
  if (str[strLen] == '\0'){
    return 0;
  }
  while(go == true){
    strLen++;
    if (str[strLen]== '\0'){
      go = false;
    }
  }
  return strLen;
}

unsigned int find(char str[], char character) {
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
  unsigned int len = length(str);
  unsigned int index2 = 0;
  for (unsigned int i = 0; i < len; ++i){
    if(str[i] == character){
      return i;
    }
  }
  return len;
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not
  unsigned int size1 = length(str1);
  unsigned int size2 = length(str2);
  if (size2 != size1){
    return false;
  }
  else{
    for (unsigned int k = 0; k < size1; k++){
      if (str1[k] != str2[k]){
        return false;
      }
    }
  }
  
  return true;
}