
#include <Stepper.h>

#define stepsPerRotation 1600

Stepper stepperTop = Stepper(stepsPerRotation, 3,4);
Stepper stepperBottom = Stepper(stepsPerRotation, 5,6);
Stepper stepperLeft = Stepper(stepsPerRotation, 7,8);
Stepper stepperRight = Stepper(stepsPerRotation, 9,10);
Stepper stepperBack = Stepper(stepsPerRotation, 12,13);

// Solved state of cube, each element is single block of the cube
// front, left, right, top, bottom, back
// g = green o = orange w = white y = yellow r = red and - = black
char cubeArray[20][6] = { {'g','r','-','-','w','-'},
  {'g','-','-','-','w','-'},
  {'g','-','o','-','w','-'},
  {'g','r','-','-','-','-'},
  {'g','-','o','-','-','-'},
  {'g','r','-','y','-','-'},
  {'g','-','-','y','-','-'},
  {'g','-','o','y','-','-'},
  {'-','r','-','-','w','-'},
  {'-','-','o','-','w','-'},
  {'-','r','-','y','-','-'},
  {'-','-','o','y','-','-'},
  {'-','r','-','-','w','b'},
  {'-','-','-','-','w','b'},
  {'-','-','o','-','w','b'},
  {'-','r','-','-','-','b'},
  {'-','-','o','-','-','b'},
  {'-','r','-','y','-','b'},
  {'-','-','-','y','-','b'},
  {'-','-','o','y','-','b'}};

  // const int for the colors representing the index of the element in Array.
  // With this we can acces the element of the Array with the name of the face
  const int front = 0;
  const int left = 1;
  const int right = 2;
  const int top = 3;
  const int bottom = 4;
  const int back = 5;

  // Set conts int for steps for left- right and halve turn
  const int turnRight = 1600;
  const int turnLeft = 4800;
  const int turnHalve = 3200;

  // Setup list for solving. Every solved piece is set to 1 in te corresponding array. That way
  // we can keep track of the solved pieces.
  int solveArray[7] = {0,0,0,0,0,0,0};
  int whiteEdges[4] = {0,0,0,0};
  byte whiteCorners[4] = {0,0,0,0};
  byte middleEdges[4] = {0,0,0,0};
  byte yellowEdges[4] = {0,0,0,0};
  byte yellowCornerPos[4] = {0,0,0,0};
  byte yellowCornerOr[4] = {0,0,0,0};
  int cornerTwists[4] = {0,0,0,0};

  // Set flag for start solving
  bool solving = false;
  bool stop = false;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("CUBEARRAY");
    Serial.println();
    Serial.println(cubeArray[0]);


    /////////// TEST ////////////////////
    /////////// TEST ////////////////////

}

void loop() {
  // put your main code here, to run repeatedly:


  
  
  if (!stop){
    scrambleCube();
    Serial.println("SCRAMBLED CUBE");
    Serial.println(cubeArray[0]);
    solving = true;
  }

  while (solving){
    if (solveArray[0] == 0){
      Serial.println(cubeArray[0]);
      whiteCross();
    }
    if (solveArray[0] == 1){
      Serial.println("SOLVED CUBE");
      Serial.println(cubeArray[0]);
      if (!testWhiteCross()){
        stop = true;
        Serial.println("ERROR");
      }
      else{
        Serial.println("SOLVE SUCCESFULL");
        reset();
      }
      solving = false;
      
    }
  }
}


void whiteCross(){
  // In this function we make the white cross. We do so by checking every edge if it has white.
  // If we find a piece and solve it we return and run the function again. Because by applying an algorithm
  // The other edges kan change position and orientation.

  // We first check if the edges are already solved. 
  if (whiteEdges[0] == 1 && whiteEdges[1] == 1 && whiteEdges[2] == 1 && whiteEdges[3] == 1){
    solveArray[0] = 1;
    return;
  }

  // Indices in cubearray are 1(green), 8(red), 9(orange), 13(blue). White on bottom offcourse.
  // Corrensponding indices in whiteEdges 0 = green, 1 = red, 2 = orange ,  3 = blue.

  // Front bottom edge index = 1
  // First check bottom white , then front white
  if (whiteEdges[0] != 1){
    if (cubeArray[1][bottom] == 'w'){
      if (cubeArray[1][front] == 'g'){
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[1][front] == 'r'){
        FrontRight();
        BottomRight();
        FrontLeft();
        BottomLeft();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[1][front] == 'o'){
        FrontRight();
        BottomLeft();
        FrontLeft();
        BottomRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[1][front] == 'b'){
        FrontRight();
        BottomRight();
        BottomRight();
        FrontLeft();
        BottomRight();
        BottomRight();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[1][front] == 'w'){
      if (cubeArray[1][bottom] == 'g'){
        FrontRight();
        BottomLeft();
        LeftRight();
        BottomRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[1][bottom] == 'r'){
        FrontRight();
        LeftRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[1][bottom] == 'o'){
        FrontLeft();
        RightLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[1][bottom] == 'b'){
        FrontRight();
        BottomRight();
        LeftRight();
        BottomLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Left Bottom edge (red) index = 8
  // First check bottom white, then left white
  if (whiteEdges[1] != 1){
    if (cubeArray[8][bottom] == 'w'){
      if (cubeArray[8][left] == 'r'){
        Serial.println("red edge solved");
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[8][left] == 'g'){
        LeftLeft();
        BottomLeft();
        LeftRight();
        BottomRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[8][left] == 'o'){
        LeftRight();
        LeftRight();
        TopRight();
        TopRight();
        RightRight();
        RightRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[8][left] == 'b'){
        LeftRight();
        BottomRight();
        LeftLeft();
        BottomLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[8][left] == 'w'){
      if (cubeArray[8][bottom] == 'g'){
        LeftLeft();
        FrontLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[8][bottom] == 'r'){
        LeftRight();
        BottomLeft();
        BackRight();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[8][bottom] == 'o'){
        LeftRight();
        BottomRight();
        BackRight();
        BottomLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[8][bottom] == 'b'){
        LeftRight();
        BackRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Right bottom edge (orange) index = 9
  // First bottom , then right white
  if (whiteEdges[2] != 1){
    if (cubeArray[9][bottom] == 'w'){
      if (cubeArray[9][right] == 'g'){
        RightRight();
        BottomRight();
        RightLeft();
        BottomLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[9][right] == 'r'){
        RightRight();
        RightRight();
        TopRight();
        TopRight();
        LeftRight();
        LeftRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[9][right] == 'o'){
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[9][right] == 'b'){
        RightLeft();
        BottomLeft();
        RightRight();
        BottomRight();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[9][right] == 'w'){
      if (cubeArray[9][bottom] == 'g'){
        RightRight();
        FrontRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[9][bottom] == 'r'){
        RightLeft();
        BottomLeft();
        BackLeft();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[9][bottom] == 'o'){
        RightLeft();
        BottomRight();
        BackLeft();
        BottomLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[9][bottom] == 'b'){
        RightLeft();
        BackLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Back bottom edge (orange) index = 13
  // First bottom , then back white
  if (whiteEdges[3] != 1){
    if (cubeArray[13][bottom] == 'w'){
      if (cubeArray[13][back] == 'g'){
        BackRight();
        BottomRight();
        BottomRight();
        BackLeft();
        BottomRight();
        BottomRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[13][back] == 'r'){
        BackLeft();
        BottomLeft();
        BackRight();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[13][back] == 'o'){
        BackRight();
        BottomRight();
        BackLeft();
        BottomLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[13][back] == 'b'){
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[13][back] == 'w'){
      if (cubeArray[13][bottom] == 'g'){
        BackRight();
        BottomRight();
        RightRight();
        BottomLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[13][bottom] == 'r'){
        BackLeft();
        LeftLeft();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[13][bottom] == 'o'){
        BackRight();
        RightRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[13][bottom] == 'b'){
        BackRight();
        BottomLeft();
        RightRight();
        BottomRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Now we check all edges on the middle layer Indices are 3, 4, 15, 16

  // if (true) is just for easy folding purposes. Can be removed later.

  // Front left edge index = 3
  // First white front then left
  if (true){
    if (cubeArray[3][front] == 'w'){
      if (cubeArray[3][left] == 'g'){
        BottomLeft();
        LeftRight();
        BottomRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[3][left] == 'r'){
        whiteEdges[1] = 1;
        LeftRight();
        return;
      }
      else if (cubeArray[3][left] == 'o'){
        BottomRight();
        BottomRight();
        LeftRight();
        BottomRight();
        BottomRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[3][left] == 'b'){
        BottomRight();
        LeftRight();
        BottomLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[3][left] == 'w'){
      if (cubeArray[3][front] == 'g'){
        FrontLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[3][front] == 'r'){
        BottomRight();
        FrontLeft();
        BottomLeft();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[3][front] == 'o'){
        BottomLeft();
        FrontLeft();
        BottomRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[3][front] == 'b'){
        BottomRight();
        BottomRight();
        FrontLeft();
        BottomRight();
        BottomRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Front right edge index = 4
  // First white front, then right
  if (true){
    if (cubeArray[4][front] == 'w'){
      if (cubeArray[4][right] == 'g'){
        BottomRight();
        RightLeft();
        BottomLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[4][right] == 'r'){
        BottomRight();
        BottomRight();
        RightLeft();
        BottomRight();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[4][right] == 'o'){
        RightLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[4][right] == 'b'){
        BottomLeft();
        RightLeft();
        BottomRight();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[4][right] == 'w'){
      if (cubeArray[4][front] == 'g'){
        FrontRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[4][front] == 'r'){
        BottomRight();
        FrontRight();
        BottomLeft();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[4][front] == 'o'){
        BottomLeft();
        FrontRight();
        BottomRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[4][front] == 'b'){
        BottomRight();
        BottomRight();
        FrontRight();
        BottomRight();
        BottomRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Back Left edge index = 15
  // First white left, then back
  if (true){
    if (cubeArray[15][left] == 'w'){
      if (cubeArray[15][back] == 'g'){
        BottomRight();
        BottomRight();
        BackRight();
        BottomRight();
        BottomRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[15][back] == 'r'){
        BottomLeft();
        BackRight();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[15][back] == 'o'){
        BottomRight();
        BackRight();
        BottomLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[15][back] == 'b'){
        BackRight();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[15][back] == 'w'){
      if (cubeArray[15][left] == 'g'){
        BottomLeft();
        LeftLeft();
        BottomRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[15][left] == 'r'){
        LeftLeft();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[15][left] == 'o'){
        BottomRight();
        BottomRight();
        LeftLeft();
        BottomRight();
        BottomRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[15][left] == 'b'){
        BottomRight();
        LeftLeft();
        BottomLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  //Back Right edge index = 16
  //First white right then back white
  if (true){
    if (cubeArray[16][right] == 'w'){
      if (cubeArray[16][back] == 'g'){
        BottomRight();
        BottomRight();
        BackLeft();
        BottomRight();
        BottomRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[16][back] == 'r'){
        BottomLeft();
        BackLeft();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[16][back] == 'o'){
        BottomRight();
        BackLeft();
        BottomLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[16][back] == 'b'){
        BackLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[16][back] == 'w'){
      if (cubeArray[16][right] == 'g'){
        BottomRight();
        RightRight();
        BottomLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[16][right] == 'r'){
        BottomRight();
        BottomRight();
        RightRight();
        BottomRight();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[16][right] == 'o'){
        whiteEdges[2] = 1;
        RightRight();
        return;
      }
      else if (cubeArray[16][right] == 'b'){
        BottomLeft();
        RightRight();
        BottomRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Now the last 4 edges on the top layer indices are 6, 10, 11 , 18
  
  // Front top edge index = 6
  // First white front, then top
  if (true){
    if (cubeArray[6][front] == 'w'){
      if (cubeArray[6][top] == 'g'){
        FrontRight();
        BottomRight();
        RightLeft();
        BottomLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[6][top] == 'r'){
        FrontLeft();
        LeftRight();
        FrontRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[6][top] == 'o'){
        FrontRight();
        RightLeft();
        FrontLeft();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[6][top] == 'b'){
        RightLeft();
        TopLeft();
        RightRight();
        BackLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[6][top] == 'w'){
      if (cubeArray[6][front] == 'g'){
        FrontLeft();
        FrontLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[6][front] == 'r'){
        TopRight();
        LeftRight();
        LeftRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[6][front] == 'o'){
        TopLeft();
        RightRight();
        RightRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[6][front] == 'b'){
        TopRight();
        TopRight();
        BackRight();
        BackRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Left top edge index = 10
  // First white left, then top
  if (true){
    if (cubeArray[10][left] == 'w'){
      if (cubeArray[10][top] == 'g'){
        LeftRight();
        FrontLeft();
        LeftLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[10][top] == 'r'){
        LeftLeft();
        BottomLeft();
        BackRight();
        BottomRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[10][top] == 'o'){
        TopRight();
        BackLeft();
        RightRight();
        BackRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[10][top] == 'b'){
        whiteEdges[3] = 1;
        LeftLeft();
        BackRight();
        LeftRight();
        return;
      }
    }
    if (cubeArray[10][top] == 'w'){
      if (cubeArray[10][left] == 'g'){
        TopLeft();
        FrontLeft();
        FrontLeft();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[10][left] == 'r'){
        LeftRight();
        LeftRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[10][left] == 'o'){
        TopRight();
        TopRight();
        RightRight();
        RightRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[10][left] == 'b'){
        TopRight();
        BackRight();
        BackRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Right top edge index = 11
  // First white right, then top
  if (true){
    if (cubeArray[11][right] == 'w'){
      if (cubeArray[11][top] == 'g'){
        RightLeft();
        FrontRight();
        RightRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[11][top] == 'r'){
        TopLeft();
        BackRight();
        LeftLeft();
        BackLeft();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[11][top] == 'o'){
        TopLeft();
        BackLeft();
        RightRight();
        BackRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[11][top] == 'b'){
        RightRight();
        BackLeft();
        RightLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[11][top] == 'w'){
      if (cubeArray[11][right] == 'g'){
        TopRight();
        FrontRight();
        FrontRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[11][right] == 'r'){
        TopRight();
        TopRight();
        LeftRight();
        LeftRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[11][right] == 'o'){
        RightRight();
        RightRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[11][right] == 'b'){
        TopLeft();
        BackRight();
        BackRight();
        whiteEdges[3] = 1;
        return;
      }
    }
  }

  // Back top edge index = 18
  // First white top,then back
  if (true){
    if (cubeArray[18][top] == 'w'){
      if (cubeArray[18][back] == 'g'){
        TopRight();
        TopRight();
        FrontRight();
        FrontRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[18][back] == 'r'){
        TopLeft();
        LeftRight();
        LeftRight();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[18][back] == 'o'){
        TopRight();
        RightRight();
        RightRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[18][back] == 'b'){
        BackRight();
        BackRight();
        whiteEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[18][back] == 'w'){
      if (cubeArray[18][top] == 'g'){
        TopRight();
        RightLeft();
        FrontRight();
        RightRight();
        whiteEdges[0] = 1;
        return;
      }
      else if (cubeArray[18][top] == 'r'){
        BackRight();
        LeftLeft();
        BackLeft();
        whiteEdges[1] = 1;
        return;
      }
      else if (cubeArray[18][top] == 'o'){
        BackLeft();
        RightRight();
        BackRight();
        whiteEdges[2] = 1;
        return;
      }
      else if (cubeArray[18][top] == 'b'){
        TopRight();
        RightRight();
        BackLeft();
        RightLeft();
        whiteEdges[3] = 1;
        return;
      }
    }
  }
  
}

void reset(){
  solveArray[0] = 0;
  for (int i =0; i < 4; ++i){
    whiteEdges[i] = 0;
  }

}
bool testWhiteCross(){
  if (cubeArray[1][front] != 'g'){
    return false;
  }
  else if (cubeArray[1][bottom] != 'w'){
    return false;
  }
  else if (cubeArray[8][left] != 'r'){
    return false;
  }
  else if (cubeArray[8][bottom] != 'w'){
    return false;
  }
  else if (cubeArray[9][right] != 'o'){
    return false;
  }
  else if (cubeArray[9][bottom] != 'w'){
    return false;
  }
  else if (cubeArray[13][back] != 'b'){
    return false;
  }
  else if (cubeArray[13][bottom] != 'w'){
    return false;
  }
  else {
    return true;
  }
}



void RightRight(){
  char convArray[8][6];
  char orgColour;
  // Store the rotating cubes in the conversion cubeArray
  for (int i = 0; i < 6; i++){
      convArray[0][i] = cubeArray[2][i];
      convArray[1][i] = cubeArray[7][i];
      convArray[2][i] = cubeArray[19][i];
      convArray[3][i] = cubeArray[14][i];
      convArray[4][i] = cubeArray[4][i];
      convArray[5][i] = cubeArray[11][i];
      convArray[6][i] = cubeArray[16][i];
      convArray[7][i] = cubeArray[9][i];
  }
  // Rotate the colors in the conversion cubeArray
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][4];
    convArray[i][4] = convArray[i][5];
    convArray[i][5] = convArray[i][3];
    convArray[i][3] = orgColour;
  }
  // Put rotated cubes back in cubeArray in the right position
  for (int i = 0; i < 6; i++){
    cubeArray[7][i] = convArray[0][i];
    cubeArray[19][i] = convArray[1][i];
    cubeArray[14][i] = convArray[2][i];
    cubeArray[2][i] = convArray[3][i];
    cubeArray[11][i] = convArray[4][i];
    cubeArray[16][i] = convArray[5][i];
    cubeArray[9][i] = convArray[6][i];
    cubeArray[4][i] = convArray[7][i];
  }
  stepperRight.step(turnRight);
}

void RightLeft(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
      convArray[0][i] = cubeArray[2][i];
      convArray[1][i] = cubeArray[4][i];
      convArray[2][i] = cubeArray[7][i];
      convArray[3][i] = cubeArray[9][i];
      convArray[4][i] = cubeArray[11][i];
      convArray[5][i] = cubeArray[14][i];
      convArray[6][i] = cubeArray[16][i];
      convArray[7][i] = cubeArray[19][i];
  }
  // Rotate the colors in the conversion cubeArray
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][3];
    convArray[i][3] = convArray[i][5];
    convArray[i][5] = convArray[i][4];
    convArray[i][4] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[14][i] = convArray[0][i];
    cubeArray[9][i] = convArray[1][i];
    cubeArray[2][i] = convArray[2][i];
    cubeArray[16][i] = convArray[3][i];
    cubeArray[4][i] = convArray[4][i];
    cubeArray[19][i] = convArray[5][i];
    cubeArray[11][i] = convArray[6][i];
    cubeArray[7][i] = convArray[7][i];
  }
  stepperRight.step(turnLeft);
}

void LeftRight(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
      convArray[0][i] = cubeArray[0][i];
      convArray[1][i] = cubeArray[3][i];
      convArray[2][i] = cubeArray[5][i];
      convArray[3][i] = cubeArray[8][i];
      convArray[4][i] = cubeArray[10][i];
      convArray[5][i] = cubeArray[12][i];
      convArray[6][i] = cubeArray[15][i];
      convArray[7][i] = cubeArray[17][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][3];
    convArray[i][3] = convArray[i][5];
    convArray[i][5] = convArray[i][4];
    convArray[i][4] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[12][i] = convArray[0][i];
    cubeArray[8][i] = convArray[1][i];
    cubeArray[0][i] = convArray[2][i];
    cubeArray[15][i] = convArray[3][i];
    cubeArray[3][i] = convArray[4][i];
    cubeArray[17][i] = convArray[5][i];
    cubeArray[10][i] = convArray[6][i];
    cubeArray[5][i] = convArray[7][i];
  }
  stepperLeft.step(turnRight);
}

void LeftLeft(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
      convArray[0][i] = cubeArray[0][i];
      convArray[1][i] = cubeArray[3][i];
      convArray[2][i] = cubeArray[5][i];
      convArray[3][i] = cubeArray[8][i];
      convArray[4][i] = cubeArray[10][i];
      convArray[5][i] = cubeArray[12][i];
      convArray[6][i] = cubeArray[15][i];
      convArray[7][i] = cubeArray[17][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][4];
    convArray[i][4] = convArray[i][5];
    convArray[i][5] = convArray[i][3];
    convArray[i][3] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[5][i] = convArray[0][i];
    cubeArray[10][i] = convArray[1][i];
    cubeArray[17][i] = convArray[2][i];
    cubeArray[3][i] = convArray[3][i];
    cubeArray[15][i] = convArray[4][i];
    cubeArray[0][i] = convArray[5][i];
    cubeArray[8][i] = convArray[6][i];
    cubeArray[12][i] = convArray[7][i];
  }
  stepperLeft.step(turnLeft);
}

void BottomRight(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
      convArray[0][i] = cubeArray[0][i];
      convArray[1][i] = cubeArray[1][i];
      convArray[2][i] = cubeArray[2][i];
      convArray[3][i] = cubeArray[8][i];
      convArray[4][i] = cubeArray[9][i];
      convArray[5][i] = cubeArray[12][i];
      convArray[6][i] = cubeArray[13][i];
      convArray[7][i] = cubeArray[14][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][5];
    convArray[i][5] = convArray[i][2];
    convArray[i][2] = convArray[i][0];
    convArray[i][0] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[2][i] = convArray[0][i];
    cubeArray[9][i] = convArray[1][i];
    cubeArray[14][i] = convArray[2][i];
    cubeArray[1][i] = convArray[3][i];
    cubeArray[13][i] = convArray[4][i];
    cubeArray[0][i] = convArray[5][i];
    cubeArray[8][i] = convArray[6][i];
    cubeArray[12][i] = convArray[7][i];
  }
  stepperBottom.step(turnRight);
}

void BottomLeft(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
      convArray[0][i] = cubeArray[0][i];
      convArray[1][i] = cubeArray[1][i];
      convArray[2][i] = cubeArray[2][i];
      convArray[3][i] = cubeArray[8][i];
      convArray[4][i] = cubeArray[9][i];
      convArray[5][i] = cubeArray[12][i];
      convArray[6][i] = cubeArray[13][i];
      convArray[7][i] = cubeArray[14][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][0];
    convArray[i][0] = convArray[i][2];
    convArray[i][2] = convArray[i][5];
    convArray[i][5] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[12][i] = convArray[0][i];
    cubeArray[8][i] = convArray[1][i];
    cubeArray[0][i] = convArray[2][i];
    cubeArray[13][i] = convArray[3][i];
    cubeArray[1][i] = convArray[4][i];
    cubeArray[14][i] = convArray[5][i];
    cubeArray[9][i] = convArray[6][i];
    cubeArray[2][i] = convArray[7][i];
  }
  stepperBottom.step(turnLeft);
}

void TopRight(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
    convArray[0][i] = cubeArray[5][i];
    convArray[1][i] = cubeArray[6][i];
    convArray[2][i] = cubeArray[7][i];
    convArray[3][i] = cubeArray[10][i];
    convArray[4][i] = cubeArray[11][i];
    convArray[5][i] = cubeArray[17][i];
    convArray[6][i] = cubeArray[18][i];
    convArray[7][i] = cubeArray[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][0];
    convArray[i][0] = convArray[i][2];
    convArray[i][2] = convArray[i][5];
    convArray[i][5] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[17][i] = convArray[0][i];
    cubeArray[10][i] = convArray[1][i];
    cubeArray[5][i] = convArray[2][i];
    cubeArray[18][i] = convArray[3][i];
    cubeArray[6][i] = convArray[4][i];
    cubeArray[19][i] = convArray[5][i];
    cubeArray[11][i] = convArray[6][i];
    cubeArray[7][i] = convArray[7][i];
  }
  stepperTop.step(turnRight);
}

void TopLeft(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
    convArray[0][i] = cubeArray[5][i];
    convArray[1][i] = cubeArray[6][i];
    convArray[2][i] = cubeArray[7][i];
    convArray[3][i] = cubeArray[10][i];
    convArray[4][i] = cubeArray[11][i];
    convArray[5][i] = cubeArray[17][i];
    convArray[6][i] = cubeArray[18][i];
    convArray[7][i] = cubeArray[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][5];
    convArray[i][5] = convArray[i][2];
    convArray[i][2] = convArray[i][0];
    convArray[i][0] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[7][i] = convArray[0][i];
    cubeArray[11][i] = convArray[1][i];
    cubeArray[19][i] = convArray[2][i];
    cubeArray[6][i] = convArray[3][i];
    cubeArray[18][i] = convArray[4][i];
    cubeArray[5][i] = convArray[5][i];
    cubeArray[10][i] = convArray[6][i];
    cubeArray[17][i] = convArray[7][i];
  }
  stepperTop.step(turnLeft);
}

void BackRight(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
    convArray[0][i] = cubeArray[12][i];
    convArray[1][i] = cubeArray[13][i];
    convArray[2][i] = cubeArray[14][i];
    convArray[3][i] = cubeArray[15][i];
    convArray[4][i] = cubeArray[16][i];
    convArray[5][i] = cubeArray[17][i];
    convArray[6][i] = cubeArray[18][i];
    convArray[7][i] = cubeArray[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][3];
    convArray[i][3] = convArray[i][2];
    convArray[i][2] = convArray[i][4];
    convArray[i][4] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[14][i] = convArray[0][i];
    cubeArray[16][i] = convArray[1][i];
    cubeArray[19][i] = convArray[2][i];
    cubeArray[13][i] = convArray[3][i];
    cubeArray[18][i] = convArray[4][i];
    cubeArray[12][i] = convArray[5][i];
    cubeArray[15][i] = convArray[6][i];
    cubeArray[17][i] = convArray[7][i];
  }
  stepperBack.step(turnRight);
}

void BackLeft(){
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
    convArray[0][i] = cubeArray[12][i];
    convArray[1][i] = cubeArray[13][i];
    convArray[2][i] = cubeArray[14][i];
    convArray[3][i] = cubeArray[15][i];
    convArray[4][i] = cubeArray[16][i];
    convArray[5][i] = cubeArray[17][i];
    convArray[6][i] = cubeArray[18][i];
    convArray[7][i] = cubeArray[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][4];
    convArray[i][4] = convArray[i][2];
    convArray[i][2] = convArray[i][3];
    convArray[i][3] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[17][i] = convArray[0][i];
    cubeArray[15][i] = convArray[1][i];
    cubeArray[12][i] = convArray[2][i];
    cubeArray[18][i] = convArray[3][i];
    cubeArray[13][i] = convArray[4][i];
    cubeArray[19][i] = convArray[5][i];
    cubeArray[16][i] = convArray[6][i];
    cubeArray[14][i] = convArray[7][i];
  }
  stepperBack.step(turnLeft);
}

void FrontRight() {
  // Turn the front of the cube right
  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
    convArray[0][i] = cubeArray[0][i];
    convArray[1][i] = cubeArray[1][i];
    convArray[2][i] = cubeArray[2][i];
    convArray[3][i] = cubeArray[3][i];
    convArray[4][i] = cubeArray[4][i];
    convArray[5][i] = cubeArray[5][i];
    convArray[6][i] = cubeArray[6][i];
    convArray[7][i] = cubeArray[7][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][4];
    convArray[i][4] = convArray[i][2];
    convArray[i][2] = convArray[i][3];
    convArray[i][3] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[0][i] = convArray[2][i];
    cubeArray[1][i] = convArray[4][i];
    cubeArray[2][i] = convArray[7][i];
    cubeArray[3][i] = convArray[1][i];
    cubeArray[4][i] = convArray[6][i];
    cubeArray[5][i] = convArray[0][i];
    cubeArray[6][i] = convArray[3][i];
    cubeArray[7][i] = convArray[5][i];
  }

  stepperRight.step(turnRight);
  stepperLeft.step(turnRight);
  stepperBottom.step(turnHalve);
  stepperTop.step(turnHalve);
  stepperRight.step(turnLeft);
  stepperLeft.step(turnLeft);
  stepperBack.step(turnRight);
  stepperRight.step(turnRight);
  stepperLeft.step(turnRight);
  stepperBottom.step(turnHalve);
  stepperTop.step(turnHalve);
  stepperRight.step(turnLeft);
  stepperLeft.step(turnLeft);
}

void FrontLeft(){

  char convArray[8][6];
  char orgColour;
  for (int i = 0; i < 6; i++){
    convArray[0][i] = cubeArray[0][i];
    convArray[1][i] = cubeArray[1][i];
    convArray[2][i] = cubeArray[2][i];
    convArray[3][i] = cubeArray[3][i];
    convArray[4][i] = cubeArray[4][i];
    convArray[5][i] = cubeArray[5][i];
    convArray[6][i] = cubeArray[6][i];
    convArray[7][i] = cubeArray[7][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][3];
    convArray[i][3] = convArray[i][2];
    convArray[i][2] = convArray[i][4];
    convArray[i][4] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    cubeArray[0][i] = convArray[5][i];
    cubeArray[1][i] = convArray[3][i];
    cubeArray[2][i] = convArray[0][i];
    cubeArray[3][i] = convArray[6][i];
    cubeArray[4][i] = convArray[1][i];
    cubeArray[5][i] = convArray[7][i];
    cubeArray[6][i] = convArray[4][i];
    cubeArray[7][i] = convArray[2][i];
  }

  stepperRight.step(turnRight);
  stepperLeft.step(turnRight);
  stepperBottom.step(turnHalve);
  stepperTop.step(turnHalve);
  stepperRight.step(turnLeft);
  stepperLeft.step(turnLeft);
  stepperBack.step(turnLeft);
  stepperRight.step(turnRight);
  stepperLeft.step(turnRight);
  stepperBottom.step(turnHalve);
  stepperTop.step(turnHalve);
  stepperRight.step(turnLeft);
  stepperLeft.step(turnLeft);
}

void scrambleCube(){
  for (int i = 0; i <25; ++i){
    int r = analogRead(A0) % 12;
    switch(r){
      case 0:
        FrontRight();
      case 1:
        FrontLeft();
      case 2:
        RightRight();
      case 3: 
        RightLeft();
      case 4:
        LeftRight();
      case 5:
        LeftLeft();
      case 6:
        BackRight();
      case 7:
        BackLeft();
      case 8:
        TopRight();
      case 9:
        TopLeft();
      case 10:
        BottomRight();
      case 11:
        BottomLeft();  
    }
  }
  delay(100);
}
