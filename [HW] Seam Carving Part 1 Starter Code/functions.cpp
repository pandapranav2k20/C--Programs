#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  int* map = new int[length]();
  return map;
}

void deleteSeam(int* seam) {
  delete [] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  cout << "Loading image..." << endl;
  // declare/define and open input file stream
  ifstream ifs (filename);
  
  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
  
  // get type from preamble
  char type[3];
  ifs >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }
  
  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  ifs >> w >> h;
  if (ifs.fail()){
          cout << "Error: read non-integer value" <<endl;
          return false;
        }
  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    /*cout << " - input width: " << width << endl;
    cout << " -  file width: " << w << endl;*/
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;    
    /*cout << " - input height: " << height << endl;
    cout << " -  file height: " << h << endl;*/
    return false;
  }
  
  // get maximum value from preamble
  int colorMax = 0;
  ifs >> colorMax;
  

  // get RGB pixel values
  while (!ifs.eof()) {
    for (int row = 0; row < height; ++row) {
      for (int col = 0; col < width; ++col) {
        //error check r
        ifs >> image[col][row].r;
        if (ifs.fail() && !ifs.eof()){
          cout << "Error: read non-integer value" <<endl;
          return false;
        }
        if (image[col][row].r > 255) {
          cout << "Error: invalid color value " << image[col][row].r <<endl;
          return false;
        }
        else if (image[col][row].r < 0) {
          cout << "Error: invalid color value " << image[col][row].r <<endl;
          return false;
        }
        if (ifs.fail() && ifs.eof()){
          cout << "Error: not enough color values" << endl;
          return false;
        }
    
        //error check g
        ifs >> image[col][row].g;
        if (ifs.fail() && !ifs.eof()){
          cout << "Error: read non-integer value" <<endl;
          return false;
        }
        if (image[col][row].g > 255) {
          cout << "Error: invalid color value " << image[col][row].g <<endl;
          return false;
        }
        else if (image[col][row].g < 0) {
          cout << "Error: invalid color value " << image[col][row].g <<endl;
          return false;
        }
        if (ifs.fail() && ifs.eof()){
          cout << "Error: not enough color values" << endl;
          return false;
        }
        
        //error check b
        ifs >> image[col][row].b;
        if (ifs.fail() && !ifs.eof()){
          cout << "Error: read non-integer value" <<endl;
          return false;
        }
        if (image[col][row].b > 255) {
          cout << "Error: invalid color value " << image[col][row].b <<endl;
          return false;
        }
        else if (image[col][row].b < 0) {
          cout << "Error: invalid color value " << image[col][row].b <<endl;
          return false;
        }
        if (ifs.fail() && ifs.eof()){
          cout << "Error: not enough color values" << endl;
          return false;
        }
        
        //check if there are too little or too many colors
      }
    }
   /* string extraCheck = to_string(ifs.peek());
    if (extraCheck != "" && extraCheck != " "){
      cout << "Error: too many color values" << endl;
      return false;
    }*/
    int nextVal = 0;
    ifs >> nextVal;
    if (ifs.good()){
      cout << "Error: too many color values" << endl;
      return false;
    }
  }
  
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
  
  cout << "Outputting image..." << endl;
  // declare/define and open output file stream
  ofstream ofs (filename);
  
  // check if output stream opened successfully
  if (!ofs.is_open()) {
    cout << "Error: failed to open output file " << filename << endl;
    return false;
  }
  
  // output preamble
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  
  // output pixels
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
  int xGrad = 0;
  int yGrad = 0;
  int deltaRx = 0;
  int deltaGx = 0;
  int deltaBx = 0;
  int deltaRy = 0;
  int deltaGy = 0;
  int deltaBy = 0;
  //Determine whether or not we are dealing with a border pixel
  //check the corners first
  //Top-left corner
  if(x == 0 && y == 0){
    deltaRx = image[x+1][y].r - image[width-1][y].r;
    deltaGx = image[x+1][y].g - image[width-1][y].g;
    deltaBx = image[x+1][y].b - image[width-1][y].b;

    deltaRy = image[x][y+1].r - image[x][height-1].r;
    deltaGy = image[x][y+1].g - image[x][height-1].g;
    deltaBy = image[x][y+1].b - image[x][height-1].b;

    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //Top-right corner
  else if(x == width-1 && y == 0){
    deltaRx = image[x-1][y].r - image[0][y].r;
    deltaGx = image[x-1][y].g - image[0][y].g;
    deltaBx = image[x-1][y].b - image[0][y].b;

    deltaRy = image[x][y+1].r - image[x][height-1].r;
    deltaGy = image[x][y+1].g - image[x][height-1].g;
    deltaBy = image[x][y+1].b - image[x][height-1].b;

    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //Bottom-left corner
  else if(x == 0 && y == height-1){
    deltaRx = image[x+1][y].r - image[width-1][y].r;
    deltaGx = image[x+1][y].g - image[width-1][y].g;
    deltaBx = image[x+1][y].b - image[width-1][y].b;

    deltaRy = image[x][y-1].r - image[x][0].r;
    deltaGy = image[x][y-1].g - image[x][0].g;
    deltaBy = image[x][y-1].b - image[x][0].b;

    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //Bottom-right corner
  else if(x == width-1 && y == height-1){
    deltaRx = image[x-1][y].r - image[0][y].r;
    deltaGx = image[x-1][y].g - image[0][y].g;
    deltaBx = image[x-1][y].b - image[0][y].b;

    deltaRy = image[x][y-1].r - image[x][0].r;
    deltaGy = image[x][y-1].g - image[x][0].g;
    deltaBy = image[x][y-1].b - image[x][0].b;

    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //check top row
  else if(y == 0){
    deltaRx = image[x+1][y].r - image[x-1][y].r;
    deltaGx = image[x+1][y].g - image[x-1][y].g;
    deltaBx = image[x+1][y].b - image[x-1][y].b;

    deltaRy = image[x][y+1].r - image[x][height-1].r;
    deltaGy = image[x][y+1].g - image[x][height-1].g;
    deltaBy = image[x][y+1].b - image[x][height-1].b;

    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //check bottom row
  else if(y == height-1){
    deltaRx = image[x+1][y].r - image[x-1][y].r;
    deltaGx = image[x+1][y].g - image[x-1][y].g;
    deltaBx = image[x+1][y].b - image[x-1][y].b;

    deltaRy = image[x][y-1].r - image[x][0].r;
    deltaGy = image[x][y-1].g - image[x][0].g;
    deltaBy = image[x][y-1].b - image[x][0].b;

    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //check leftmost column
  else if(x == 0){
    deltaRx = image[x+1][y].r - image[width-1][y].r;
    deltaGx = image[x+1][y].g - image[width-1][y].g;
    deltaBx = image[x+1][y].b - image[width-1][y].b;

    deltaRy = image[x][y+1].r - image[x][y-1].r;
    deltaGy = image[x][y+1].g - image[x][y-1].g;
    deltaBy = image[x][y+1].b - image[x][y-1].b;
    
    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //check the rightmost column
  else if(x == width-1){
    deltaRx = image[x-1][y].r - image[0][y].r;
    deltaGx = image[x-1][y].g - image[0][y].g;
    deltaBx = image[x-1][y].b - image[0][y].b;

    deltaRy = image[x][y+1].r - image[x][y-1].r;
    deltaGy = image[x][y+1].g - image[x][y-1].g;
    deltaBy = image[x][y+1].b - image[x][y-1].b;
    
    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  //At this point, we are dealing with a non-border pixel
  else{
    deltaRx = image[x+1][y].r - image[x-1][y].r;
    deltaGx = image[x+1][y].g - image[x-1][y].g;
    deltaBx = image[x+1][y].b - image[x-1][y].b;

    deltaRy = image[x][y+1].r - image[x][y-1].r;
    deltaGy = image[x][y+1].g - image[x][y-1].g;
    deltaBy = image[x][y+1].b - image[x][y-1].b;

    xGrad = deltaRx*deltaRx + deltaGx*deltaGx + deltaBx*deltaBx;
    yGrad = deltaRy*deltaRy + deltaGy*deltaGy + deltaBy*deltaBy;
    return xGrad + yGrad;
  }
  return 0;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  //set the starting value of seam equal to the index start_col, the value of start_col will be changed during looping
  seam[0] = start_col;
  //set the total energy equal to that of the first pixel (start_col, 0)
  int totalEnergy = energy(image, start_col, 0, width, height);
  //initialize minimal energy to zero
  int minimalEnergy = 0;
  int forwardEnergy = 0;
  int leftEnergy = 0;
  int rightEnergy = 0;
  for (int row = 1; row < height; ++row){
      if ((row < height && start_col + 1 < width) && start_col != 0){
        forwardEnergy = energy(image, start_col, row, width, height);
        leftEnergy = energy(image, start_col+1, row, width, height);
        rightEnergy = energy(image, start_col-1, row, width, height);
      }
      else if (start_col == 0){
        //set the right energy to something arbitrarily high
        //actually set equal to forward energy
        rightEnergy = 100000000;
        forwardEnergy = energy(image, start_col, row, width, height);
        leftEnergy = energy(image, start_col+1, row, width, height);
      }
      else if (start_col + 1 == width){
        //set the left energy to something arbitrarily high
        leftEnergy = 100000000;
        forwardEnergy = energy(image, start_col, row, width, height);
        rightEnergy = energy(image, start_col-1, row, width, height);
      }
    //use if statements to determine which is the minimal energy
    //check the non-equal cases first
    if (forwardEnergy < leftEnergy && forwardEnergy < rightEnergy){
      minimalEnergy = forwardEnergy;
      seam[row] = start_col;
      totalEnergy += minimalEnergy; 
    }
    else if (leftEnergy < forwardEnergy && leftEnergy < rightEnergy){
      minimalEnergy = leftEnergy;
      start_col += 1;
      seam[row] = start_col;
      totalEnergy += minimalEnergy; 
    }
    else if (rightEnergy < forwardEnergy && rightEnergy < leftEnergy){
      minimalEnergy = rightEnergy;
      start_col -= 1;
      seam[row] = start_col;
      totalEnergy += minimalEnergy; 
    }
    //check the equal cases
    else if ((forwardEnergy == leftEnergy || forwardEnergy == rightEnergy) && (forwardEnergy < leftEnergy || forwardEnergy < rightEnergy)){
      minimalEnergy = forwardEnergy;
      seam[row] = start_col;
      totalEnergy += minimalEnergy; 
    }
    else if ((leftEnergy == forwardEnergy || leftEnergy == rightEnergy) && (leftEnergy < forwardEnergy || leftEnergy < rightEnergy)){
      minimalEnergy = leftEnergy;
      start_col += 1;
      seam[row] = start_col;
      totalEnergy += minimalEnergy; 
    }
    else if ((rightEnergy == leftEnergy || rightEnergy == forwardEnergy) && (rightEnergy < forwardEnergy || rightEnergy < leftEnergy)){
      minimalEnergy = rightEnergy;
      start_col -= 1;
      seam[row] = start_col;
      totalEnergy += minimalEnergy; 
    }
    //check if all three are equal, use forward
    else if ((leftEnergy == forwardEnergy && forwardEnergy == rightEnergy) && leftEnergy == rightEnergy){
      minimalEnergy = forwardEnergy;
      seam[row] = start_col;
      totalEnergy += minimalEnergy; 
    }
  }
  return totalEnergy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  seam[0] = start_row;
  //set the total energy equal to that of the first pixel (0, start_row)
  int totalEnergy = energy(image, 0, start_row, width, height);
  //initialize minimal energy to zero
  int minimalEnergy = 0;
  int forwardEnergy = 0;
  int leftEnergy = 0;
  int rightEnergy = 0;
  for (int col = 1; col < width; ++col){
      if ((col < width && start_row + 1 < height) && start_row != 0){
        forwardEnergy = energy(image, col, start_row, width, height);
        leftEnergy = energy(image, col, start_row-1, width, height);
        rightEnergy = energy(image, col, start_row+1, width, height);
      }
      else if (start_row == 0){
        //set the left energy to something arbitrarily high
        leftEnergy = 100000000;
        forwardEnergy = energy(image, col, start_row, width, height);
        rightEnergy = energy(image, col, start_row+1, width, height);
      }
      else if (start_row + 1 == width){
        //set the right energy to something arbitrarily high
        rightEnergy = 100000000;
        forwardEnergy = energy(image, col, start_row, width, height);
        leftEnergy = energy(image, col, start_row-1, width, height);
      }
    //use if statements to determine which is the minimal energy
    //check the non-equal cases first
    if (forwardEnergy < leftEnergy && forwardEnergy < rightEnergy){
      minimalEnergy = forwardEnergy;
      seam[col] = start_row;
      totalEnergy += minimalEnergy; 
    }
    else if (leftEnergy < forwardEnergy && leftEnergy < rightEnergy){
      minimalEnergy = leftEnergy;
      start_row -= 1;
      seam[col] = start_row;
      totalEnergy += minimalEnergy; 
    }
    else if (rightEnergy < forwardEnergy && rightEnergy < leftEnergy){
      minimalEnergy = rightEnergy;
      start_row += 1;
      seam[col] = start_row;
      totalEnergy += minimalEnergy; 
    }
    //check the equal cases
    else if ((forwardEnergy == leftEnergy || forwardEnergy == rightEnergy) && (forwardEnergy < leftEnergy || forwardEnergy < rightEnergy)){
      minimalEnergy = forwardEnergy;
      seam[col] = start_row;
      totalEnergy += minimalEnergy; 
    }
    else if ((leftEnergy == forwardEnergy || leftEnergy == rightEnergy) && (leftEnergy < forwardEnergy || leftEnergy < rightEnergy)){
      minimalEnergy = leftEnergy;
      start_row -= 1;
      seam[col] = start_row;
      totalEnergy += minimalEnergy; 
    }
    else if ((rightEnergy == leftEnergy || rightEnergy == forwardEnergy) && (rightEnergy < forwardEnergy || rightEnergy < leftEnergy)){
      minimalEnergy = rightEnergy;
      start_row += 1;
      seam[col] = start_row;
      totalEnergy += minimalEnergy; 
    }
    //check if all three are equal, use forward
    else if ((leftEnergy == forwardEnergy && forwardEnergy == rightEnergy) && leftEnergy == rightEnergy){
      minimalEnergy = forwardEnergy;
      seam[col] = start_row;
      totalEnergy += minimalEnergy; 
    }
  }
  return totalEnergy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int* currentSeam = createSeam(height);
  
  int minimalEnergy = loadVerticalSeam(image, 0, width, height, currentSeam);
  //use a for loop to examine the other rows
  for (int col = 0; col < width; ++col){
    int* nextSeam = createSeam(height);
    int nextEnergy = loadVerticalSeam(image, col, width, height, nextSeam);
    //check if the energy is less than minimal energy
    if (nextEnergy < minimalEnergy){
      minimalEnergy = nextEnergy;
      //set lowestSeam equal to nextSeam
      /*deleteSeam(currentSeam);
      currentSeam = createSeam(height);*/
      for (int i = 0; i < height; ++i){
        currentSeam[i] = nextSeam[i];
      }
    }
    deleteSeam(nextSeam);
  }
  return currentSeam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  int* currentSeam = createSeam(width);
  
  int minimalEnergy = loadHorizontalSeam(image, 0, width, height, currentSeam);
  //use a for loop to examine the other columns
  for (int row = 0; row < height; ++row){
    int* nextSeam = createSeam(width);
    int nextEnergy = loadHorizontalSeam(image, row, width, height, nextSeam);
    //check if the energy is less than minimal energy
    if (nextEnergy < minimalEnergy){
      minimalEnergy = nextEnergy;
      //set lowestSeam equal to nextSeam
      /*deleteSeam(currentSeam);
      currentSeam = createSeam(height);*/
      for (int i = 0; i < width; ++i){
        currentSeam[i] = nextSeam[i];
      }
    }
    deleteSeam(nextSeam);
  }
  return currentSeam;

}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for (int row = 0; row < height; ++row){
    for (int startingShift = verticalSeam[row]; startingShift < width - 1; ++startingShift){
      image[startingShift][row].r = image[startingShift + 1][row].r;
      image[startingShift][row].g = image[startingShift + 1][row].g;
      image[startingShift][row].b = image[startingShift + 1][row].b;
    }
  }
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  for (int col = 0; col < width; ++col){
    for (int startingShift = horizontalSeam[col]; startingShift < height - 1; ++startingShift){
      image[col][startingShift].r = image[col][startingShift + 1].r;
      image[col][startingShift].g = image[col][startingShift + 1].g;
      image[col][startingShift].b = image[col][startingShift + 1].b;
    }
  }
}
