
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
  int whiteCorners[4] = {0,0,0,0};
  int middleEdges[4] = {0,0,0,0};
  int yellowEdges[4] = {0,0,0,0};
  int yellowCornerPos[4] = {0,0,0,0};
  int yellowCornerOr[4] = {0,0,0,0};
  int cornerTwists[4] = {0,0,0,0};

  // Set flag for start solving
  bool solving = false;
  bool stop = false;

  int succescount = 0;


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
      whiteCross();
    }
    else if (solveArray[1] == 0){
      solveWhiteCorners();
    }
    else if (solveArray[2] == 0){
      solveMiddleEdges();
    }
    else if (solveArray[3] == 0){
      YellowCross();
    }
    else if (solveArray[4] == 0){
      Serial.println(cubeArray[0]);
      solveYellowEdges();
    }
    if (solveArray[4] == 1){
      Serial.println("SOLVED CUBE");
      Serial.println(cubeArray[0]);
      if (!testCube()){
        stop = true;
        Serial.println("ERROR");
      }
      else{
        succescount++;
        Serial.print("SUCCESFULL SOLVE #");
        Serial.println(succescount);
        if (succescount == 100){
          stop = true;
        }
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

void solveWhiteCorners(){
  // We are going to look at all the corners on the cube and find the white corners. If a corner has 
  // a white face we are going to solve this with according algorithms. Each corner can be in 3 different 
  // orientations so we have 8 X 3 = 24 situations we have to look at.

  // First we check if corners are solved and their respective flags are set
  if (whiteCorners[0] == 1 && whiteCorners[1] == 1 && whiteCorners[2] == 1 && whiteCorners[3] == 1){
    solveArray[1] = 1;
    return;
  }

  //Indices for the four corners we are solving are 0(green/red), 2(green/orange), 12(blue/red), 14(blue/orange)

  // We make things a little easier by making four functions (See under this function) for each of the corners. 
  // After we find a corner  we set it above the correct corner in the top layer and solve it from there with 
  // these four functions
  
  // Bottom left corner index = 0
  if (whiteCorners[0] != 1){
    if (cubeArray[0][bottom] == 'w'){
      if (cubeArray[0][front] == 'g'){
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[0][front] == 'o'){
        LeftLeft();
        TopLeft();
        LeftRight();
        GreenOrangeCorner(right);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[0][front] == 'r'){
        LeftLeft();
        TopRight();
        TopRight();
        LeftRight();
        TopLeft();
        BlueRedCorner(left);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[0][front] == 'b'){
        LeftLeft();
        TopRight();
        TopRight();
        LeftRight();
        BlueOrangeCorner(back);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[0][front] == 'w'){
      if (cubeArray[0][left] == 'g'){
        LeftLeft();
        TopRight();
        LeftRight();
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[0][left] == 'o'){
        LeftLeft();
        TopLeft();
        LeftRight();
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[0][left] == 'r'){
        LeftLeft();
        TopRight();
        TopRight();
        LeftRight();
        TopLeft();
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[0][left] == 'b'){
        LeftLeft();
        TopRight();
        TopRight();
        LeftRight();
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[0][left] == 'w'){
      if (cubeArray[0][bottom] == 'g'){
        LeftLeft();
        TopRight();
        LeftRight();
        GreenRedCorner(top);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[0][bottom] == 'o'){
        LeftLeft();
        TopLeft();
        LeftRight();
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[0][bottom] == 'r'){
        LeftLeft();
        TopRight();
        TopRight();
        LeftRight();
        TopLeft();
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[0][bottom] == 'b'){
        LeftLeft();
        TopRight();
        TopRight();
        LeftRight();
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
  }

  // Bottom right corner index = 2
  if (whiteCorners[1] != 1){
    if (cubeArray[2][bottom] == 'w'){
      if (cubeArray[2][right] == 'g'){
        RightRight();
        TopRight();
        RightLeft();
        GreenRedCorner(left);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[2][right] == 'o'){
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[2][right] == 'r'){
        RightRight();
        TopRight();
        TopRight();
        RightLeft();
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[2][right] == 'b'){
        RightRight();
        TopRight();
        TopRight();
        RightLeft();
        TopRight();
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[2][right] == 'w'){
      if (cubeArray[2][front] == 'g'){
        RightRight();
        TopRight();
        RightLeft();
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[2][front] == 'o'){
        RightRight();
        TopLeft();
        RightLeft();
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[2][front] == 'r'){
        RightRight();
        TopRight();
        TopRight();
        RightLeft();
        BlueRedCorner(left);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[2][front] == 'b'){
        RightRight();
        TopRight();
        TopRight();
        RightLeft();
        TopRight();
        BlueOrangeCorner(back);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[2][front] == 'w'){
      if (cubeArray[2][bottom] == 'g'){
        whiteCorners[0] = 1;
        RightRight();
        TopRight();
        RightLeft();
        GreenRedCorner(top);
        return;
      }
      else if (cubeArray[2][bottom] == 'o'){
        RightRight();
        TopLeft();
        RightLeft();
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[2][bottom] == 'r'){
        RightRight();
        TopRight();
        TopRight();
        RightLeft();
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[2][bottom] == 'b'){
        RightRight();
        TopRight();
        TopRight();
        RightLeft();
        TopRight();
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
  }
  
  //Back Left corner index = 12
  if (whiteCorners[2] != 1){
    if (cubeArray[12][bottom] == 'w'){
      if (cubeArray[12][left] == 'g'){
        LeftRight();
        TopRight();
        TopRight();
        LeftLeft();
        TopRight();
        GreenRedCorner(left);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[12][left] == 'o'){
        LeftRight();
        TopRight();
        TopRight();
        LeftLeft();
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[12][left] == 'r'){
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[12][left] == 'b'){
        LeftRight();
        TopRight();
        LeftLeft();
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[12][left] == 'w'){
      if (cubeArray[12][back] == 'g'){
        LeftRight();
        TopRight();
        TopRight();
        LeftLeft();
        TopRight();
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[12][back] == 'o'){
        LeftRight();
        TopRight();
        TopRight();
        LeftLeft();
        GreenOrangeCorner(right);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[12][back] == 'r'){
        LeftRight();
        TopLeft();
        LeftLeft();
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[12][back] == 'b'){
        LeftRight();
        TopRight();
        LeftLeft();
        BlueOrangeCorner(back);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[12][back] == 'w'){
      if (cubeArray[12][bottom] == 'g'){
        LeftRight();
        TopRight();
        TopRight();
        LeftLeft();
        TopRight();
        GreenRedCorner(top);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[12][bottom] == 'o'){
        LeftRight();
        TopRight();
        TopRight();
        LeftLeft();
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[12][bottom] == 'r'){
        LeftRight();
        TopLeft();
        LeftLeft();
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[12][bottom] == 'b'){
        LeftRight();
        TopRight();
        LeftLeft();
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
  }

  //Back right corner index = 14
  if (whiteCorners[3] != 1){
    if (cubeArray[14][bottom] == 'w'){
      if (cubeArray[14][back] == 'g'){
        BackRight();
        TopRight();
        TopRight();
        BackLeft();
        GreenRedCorner(left);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[14][back] == 'o'){
        BackRight();
        TopRight();
        BackLeft();
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[14][back] == 'r'){
        BackRight();
        TopRight();
        TopRight();
        BackLeft();
        TopRight();
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[14][back] == 'b'){
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[14][back] == 'w'){
      if (cubeArray[14][right] == 'g'){
        BackRight();
        TopRight();
        TopRight();
        BackLeft();
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[14][right] == 'o'){
        BackRight();
        TopRight();
        BackLeft();
        GreenOrangeCorner(right);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[14][right] == 'r'){
        BackRight();
        TopRight();
        TopRight();
        BackLeft();
        TopRight();
        BlueRedCorner(left);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[14][right] == 'b'){
        BackRight();
        TopLeft();
        BackLeft();
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[14][right] == 'w'){
      if (cubeArray[14][bottom] == 'g'){
        BackRight();
        TopRight();
        TopRight();
        BackLeft();
        GreenRedCorner(top);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[14][bottom] == 'o'){
        BackRight();
        TopRight();
        BackLeft();
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[14][bottom] == 'r'){
        BackRight();
        TopRight();
        TopRight();
        BackLeft();
        TopRight();
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[14][bottom] == 'b'){
        BackRight();
        TopLeft();
        BackLeft();
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
  }

  // Now we look at the corners in the top layer.  Indices for the top corners are 5, 7, 17, 19

  // Top left corner index = 5
  if (true){
    if (cubeArray[5][top] == 'w'){
      if (cubeArray[5][left] == 'g'){
        GreenRedCorner(top);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[5][left] == 'o'){
        TopLeft();
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[5][left] == 'r'){
        TopRight();
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[5][left] == 'b'){
        TopRight();
        TopRight();
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[5][left] == 'w'){
      if (cubeArray[5][front] == 'g'){
        GreenRedCorner(left);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[5][front] == 'o'){
        TopLeft();
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[5][front] == 'r'){
        TopRight();
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[5][front] == 'b'){
        TopRight();
        TopRight();
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[5][front] == 'w'){
      if (cubeArray[5][top] == 'g'){
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[5][top] == 'o'){
        TopLeft();
        GreenOrangeCorner(right);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[5][top] == 'r'){
        TopRight();
        BlueRedCorner(left);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[5][top] == 'b'){
        TopRight();
        TopRight();
        BlueOrangeCorner(back);
        whiteCorners[3] = 1;
        return;
      }
    }
  }

  // Top right corner index = 7
  if (true){
    if (cubeArray[7][top] == 'w'){
      if (cubeArray[7][front] == 'g'){
        TopRight();
        GreenRedCorner(top);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[7][front] == 'o'){
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[7][front] == 'r'){
        TopRight();
        TopRight();
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[7][front] == 'b'){
        TopLeft();
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[7][front] == 'w'){
      if (cubeArray[7][right] == 'g'){
        whiteCorners[0] = 1;
        TopRight();
        GreenRedCorner(left);
        return;
      }
      else if (cubeArray[7][right] == 'o'){
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[7][right] == 'r'){
        TopRight();
        TopRight();
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[7][right] == 'b'){
        TopLeft();
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[7][right] == 'w'){
      if (cubeArray[7][top] == 'g'){
        TopRight();
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[7][top] == 'o'){
        GreenOrangeCorner(right);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[7][top] == 'r'){
        TopRight();
        TopRight();
        BlueRedCorner(left);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[7][top] == 'b'){
        TopLeft();
        BlueOrangeCorner(back);
        whiteCorners[3] = 1;
        return;
      }
    }
  }

  // Back left corner index = 17
  if (true){
    if (cubeArray[17][top] == 'w'){
      if (cubeArray[17][back] == 'g'){
        TopLeft();
        GreenRedCorner(top);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[17][back] == 'o'){
        TopRight();
        TopRight();
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[17][back] == 'r'){
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[17][back] == 'b'){
        TopRight();
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[17][back] == 'w'){
      if (cubeArray[17][left] == 'g'){
        whiteCorners[0] = 1;
        TopLeft();
        GreenRedCorner(left);
        return;
      }
      else if (cubeArray[17][left] == 'o'){
        TopRight();
        TopRight();
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[17][left] == 'r'){
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[17][left] == 'b'){
        TopRight();
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[17][left] == 'w'){
      if (cubeArray[17][top] == 'g'){
        TopLeft();
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[17][top] == 'o'){
        TopRight();
        TopRight();
        GreenOrangeCorner(right);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[17][top] == 'r'){
        BlueRedCorner(left);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[17][top] == 'b'){
        TopRight();
        BlueOrangeCorner(back);
        whiteCorners[3] = 1;
        return;
      }
    }
  }
  
  //Back right corner index = 19
  if (true){
    if (cubeArray[19][top] == 'w'){
      if (cubeArray[19][right] == 'g'){
        TopRight();
        TopRight();
        GreenRedCorner(top);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[19][right] == 'o'){
        TopRight();
        GreenOrangeCorner(top);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[19][right] == 'r'){
        TopLeft();
        BlueRedCorner(top);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[19][right] == 'b'){
        BlueOrangeCorner(top);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[19][right] == 'w'){
      if (cubeArray[19][back] == 'g'){
        TopRight();
        TopRight();
        GreenRedCorner(left);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[19][back] == 'o'){
        TopRight();
        GreenOrangeCorner(front);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[19][back] == 'r'){
        TopLeft();
        BlueRedCorner(back);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[19][back] == 'b'){
        BlueOrangeCorner(right);
        whiteCorners[3] = 1;
        return;
      }
    }
    if (cubeArray[19][back] == 'w'){
      if (cubeArray[19][top] == 'g'){
        TopRight();
        TopRight();
        GreenRedCorner(front);
        whiteCorners[0] = 1;
        return;
      }
      else if (cubeArray[19][top] == 'o'){
        TopRight();
        GreenOrangeCorner(right);
        whiteCorners[1] = 1;
        return;
      }
      else if (cubeArray[19][top] == 'r'){
        TopLeft();
        BlueRedCorner(left);
        whiteCorners[2] = 1;
        return;
      }
      else if (cubeArray[19][top] == 'b'){
        BlueOrangeCorner(back);
        whiteCorners[3] = 1;
        return;
      }
    }
  }
}
void GreenRedCorner(int whitePos){
  if (whitePos == top){
    LeftLeft();
    TopRight();
    LeftRight();
    TopRight();
    TopRight();
    LeftLeft();
    TopLeft();
    LeftRight();
  }
  else if (whitePos == left){
    LeftLeft();
    TopLeft();
    LeftRight();
  }
  else if (whitePos == front){
    TopLeft();
    LeftLeft();
    TopRight();
    LeftRight();
  }
}
void GreenOrangeCorner(int whitePos){
  if (whitePos == front){
    TopRight();
    RightRight();
    TopLeft();
    RightLeft();
  }
  else if (whitePos == right){
    RightRight();
    TopRight();
    RightLeft();
  }
  else if (whitePos == top){
    RightRight();
    TopRight();
    TopRight();
    RightLeft();
    TopLeft();
    RightRight();
    TopRight();
    RightLeft();
  }
}
void BlueRedCorner(int whitePos){
  if (whitePos == top){
    LeftRight();
    TopRight();
    TopRight();
    LeftLeft();
    TopLeft();
    LeftRight();
    TopRight();
    LeftLeft();
  }
  else if (whitePos == back){
    BackLeft();
    TopLeft();
    BackRight();
  }
  else if(whitePos == left){
    LeftRight();
    TopRight();
    LeftLeft();
  }
}
void BlueOrangeCorner(int whitePos){
  if (whitePos == top){
    BackRight();
    TopRight();
    TopRight();
    BackLeft();
    TopLeft();
    BackRight();
    TopRight();
    BackLeft();
  }
  else if (whitePos == right){
    RightLeft();
    TopLeft();
    RightRight();
  }
  else if (whitePos == back){
    BackRight();
    TopRight();
    BackLeft();
  }
}

void solveMiddleEdges(){
  // We now search the 8 unsolved edges for the middle pieces and solve these.
  // The edges don't all have a color in common like the white in the white layer, so the structure of 
  // the code will be slightly different, but the strategy remains the same

  if (middleEdges[0] == 1 && middleEdges[1] == 1 && middleEdges[2] == 1 && middleEdges[3] == 1){
    solveArray[2] = 1;
    return;
  }

  // The middle edges we are going to solve have the indices: 3, 4, 15, 16. We start by searching in the middle layer first
  // Again we maken four helper functions with static algorithms to make coding this section a little easier.

  // We start by looking in the toplayer because if we can solve piece from the top in the middle-layer it requires les steps
  // therefore our solve will be faster and thus more spectacular.

  // Indices of the toplayer are 6, 10, 11, 18

  // Front top edge index = 6
  if (true){
    if (cubeArray[6][front] == 'g'){
      if (cubeArray[6][top] == 'r'){
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[6][top] == 'o'){
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[6][front] == 'o'){
      if (cubeArray[6][top] == 'g'){
        TopLeft();
        GreenOrangeEdge('o');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[6][top] == 'b'){
        TopLeft();
        BlueOrangeEdge('o');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[6][front] == 'r'){
      if (cubeArray[6][top] == 'g'){
        TopRight();
        GreenRedEdge('r');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[6][top] == 'b'){
        TopRight();
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[6][front] == 'b'){
      if (cubeArray[6][top] == 'r'){
        TopRight();
        TopRight();
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[6][top] == 'o'){
        TopRight();
        TopRight();
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
  }

  // Top left edge index = 10
  if (true){
    if (cubeArray[10][left] == 'g'){
      if (cubeArray[10][top] == 'r'){
        TopLeft();
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[10][top] == 'o'){
        TopLeft();
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[10][left] == 'o'){
      if (cubeArray[10][top] == 'g'){
        TopRight();
        TopRight();
        GreenOrangeEdge('o');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[10][top] == 'b'){
        TopRight();
        TopRight();
        BlueOrangeEdge('o');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[10][left] == 'r'){
      if (cubeArray[10][top] == 'g'){
        GreenRedEdge('r');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[10][top] == 'b'){
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[10][left] == 'b'){
      if (cubeArray[10][top] == 'r'){
        TopRight();
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[10][top] == 'o'){
        TopRight();
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
  }

  // Top right edge index = 11
  if (true){
    if (cubeArray[11][right] == 'g'){
      if (cubeArray[11][top] == 'r'){
        TopRight();
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[11][top] == 'o'){
        TopRight();
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[11][right] == 'o'){
      if (cubeArray[11][top] == 'g'){
        GreenOrangeEdge('o');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[11][top] == 'b'){
        BlueOrangeEdge('o');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[11][right] == 'r'){
      if (cubeArray[11][top] == 'g'){
        TopRight();
        TopRight();
        GreenRedEdge('r');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[11][top] == 'b'){
        TopRight();
        TopRight();
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[11][right] == 'b'){
      if (cubeArray[11][top] == 'r'){
        TopLeft();
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[11][top] == 'o'){
        TopLeft();
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
  }

  // Back top edge index = 18
  if (true){
    if (cubeArray[18][back] == 'g'){
      if (cubeArray[18][top] == 'r'){
        TopRight();
        TopRight();
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[18][top] == 'o'){
        TopRight();
        TopRight();
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[18][back] == 'o'){
      if (cubeArray[18][top] == 'g'){
        TopRight();
        GreenOrangeEdge('o');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[18][top] == 'b'){
        TopRight();
        BlueOrangeEdge('o');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[18][back] == 'r'){
      if (cubeArray[18][top] == 'g'){
        TopLeft();
        GreenRedEdge('r');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[18][top] == 'b'){
        TopLeft();
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[18][back] == 'b'){
      if (cubeArray[18][top] == 'r'){
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[18][top] == 'o'){
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
  }

  // Now we look at the edges in the middle layer

  // Front left edge index = 3
  if (middleEdges[0] != 1){
    if (cubeArray[3][front] == 'g'){
      if (cubeArray[3][left] == 'r'){
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[3][left] == 'o'){
        TakeOutEdge(1);
        TopRight();
        GreenOrangeEdge('o');
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[3][front] == 'o'){
      if (cubeArray[3][left] == 'g'){
        TakeOutEdge(1);
        TopRight();
        TopRight();
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[3][left] == 'b'){
        TakeOutEdge(1);
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[3][front] == 'r'){
      if (cubeArray[3][left] == 'g'){
        TakeOutEdge(1);
        TopRight();
        TopRight();
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[3][left] == 'b'){
        TakeOutEdge(1);
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[3][front] == 'b'){
      if (cubeArray[3][left] == 'r'){
        TakeOutEdge(1);
        TopLeft();
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[3][left] == 'o'){
        TakeOutEdge(1);
        TopRight();
        BlueOrangeEdge('o');
        middleEdges[3] = 1;
        return;
      }
    }
  }

  // Front right edge index = 4
  if (middleEdges[1] != 1){
    if (cubeArray[4][front] == 'g'){
      if (cubeArray[4][right] == 'r'){
        TakeOutEdge(2);
        TopLeft();
        GreenRedEdge('r');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[4][right] == 'o'){
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[4][front] == 'o'){
      if (cubeArray[4][right] == 'g'){
        TakeOutEdge(2);
        TopRight();
        TopRight();
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[4][right] == 'b'){
        TakeOutEdge(2);
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[4][front] == 'r'){
      if (cubeArray[4][right] == 'g'){
        TakeOutEdge(2);
        TopRight();
        TopRight();
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[4][right] == 'b'){
        TakeOutEdge(2);
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[4][front] == 'b'){
      if (cubeArray[4][right] == 'r'){
        TakeOutEdge(2);
        TopLeft();
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[4][right] == 'o'){
        TakeOutEdge(2);
        TopRight();
        BlueOrangeEdge('o');
        middleEdges[3] = 1;
        return;
      }
    }
  }

  // Back left edge index = 15
  if (middleEdges[2] != 1){
    if (cubeArray[15][back] == 'g'){
      if (cubeArray[15][left] == 'r'){
        TakeOutEdge(3);
        TopRight();
        GreenRedEdge('r');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[15][left] == 'o'){
        TakeOutEdge(3);
        TopLeft();
        GreenOrangeEdge('o');
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[15][back] == 'o'){
      if (cubeArray[15][left] == 'g'){
        TakeOutEdge(3);
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[15][left] == 'b'){
        TakeOutEdge(3);
        TopRight();
        TopRight();
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[15][back] == 'r'){
      if (cubeArray[15][left] == 'g'){
        TakeOutEdge(3);
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[15][left] == 'b'){
        TakeOutEdge(3);
        TopRight();
        TopRight();
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[15][back] == 'b'){
      if (cubeArray[15][left] == 'r'){
        TakeOutEdge(3);
        TopRight();
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[15][left] == 'o'){
        TakeOutEdge(3);
        TopLeft();
        BlueOrangeEdge('o');
        middleEdges[3] = 1;
        return;
      }
    }
  }

  //Back right edge index = 16
  if (middleEdges[3] != 1){
    if (cubeArray[16][back] == 'g'){
      if (cubeArray[16][right] == 'r'){
        TakeOutEdge(4);
        TopRight();
        GreenRedEdge('r');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[16][right] == 'o'){
        TakeOutEdge(4);
        TopLeft();
        GreenOrangeEdge('o');
        middleEdges[1] = 1;
        return;
      }
    }
    if (cubeArray[16][back] == 'o'){
      if (cubeArray[16][right] == 'g'){
        TakeOutEdge(4);
        GreenOrangeEdge('g');
        middleEdges[1] = 1;
        return;
      }
      else if (cubeArray[16][right] == 'b'){
        TakeOutEdge(4);
        TopRight();
        TopRight();
        BlueOrangeEdge('b');
        middleEdges[3] = 1;
        return;
      }
    }
    if (cubeArray[16][back] == 'r'){
      if (cubeArray[16][right] == 'g'){
        TakeOutEdge(4);
        GreenRedEdge('g');
        middleEdges[0] = 1;
        return;
      }
      else if (cubeArray[16][right] == 'b'){
        TakeOutEdge(4);
        TopRight();
        TopRight();
        BlueRedEdge('b');
        middleEdges[2] = 1;
        return;
      }
    }
    if (cubeArray[16][back] == 'b'){
      if (cubeArray[16][right] == 'r'){
        TakeOutEdge(4);
        TopRight();
        BlueRedEdge('r');
        middleEdges[2] = 1;
        return;
      }
      else if (cubeArray[16][right] == 'o'){
        middleEdges[3] = 1;
        return;
      }
    }
  }
}
void GreenRedEdge(char frontfacing){
  if (frontfacing == 'g'){
    TopLeft();
    LeftLeft();
    TopRight();
    LeftRight();
    TopRight();
    FrontRight();
    TopLeft();
    FrontLeft();
  }
  else if (frontfacing == 'r'){
    TopRight();
    FrontRight();
    TopLeft();
    FrontLeft();
    TopLeft();
    LeftLeft();
    TopRight();
    LeftRight();
  }
}
void GreenOrangeEdge(char frontfacing){
  if (frontfacing == 'g'){
    TopRight();
    RightRight();
    TopLeft();
    RightLeft();
    TopLeft();
    FrontLeft();
    TopRight();
    FrontRight();
  }
  else if (frontfacing == 'o'){
    TopLeft();
    FrontLeft();
    TopRight();
    FrontRight();
    TopRight();
    RightRight();
    TopLeft();
    RightLeft();
  }
}
void BlueOrangeEdge(char frontfacing){
  if (frontfacing == 'b'){
    TopLeft();
    RightLeft();
    TopRight();
    RightRight();
    TopRight();
    BackRight();
    TopLeft();
    BackLeft();
  }
  else if (frontfacing == 'o'){
    TopRight();
    BackRight();
    TopLeft();
    BackLeft();
    TopLeft();
    RightLeft();
    TopRight();
    RightRight();
  }
}
void BlueRedEdge(char frontfacing){
  if (frontfacing == 'b'){
    TopRight();
    LeftRight();
    TopLeft();
    LeftLeft();
    TopLeft();
    BackLeft();
    TopRight();
    BackRight();
  }
  else if (frontfacing == 'r'){
    TopLeft();
    BackLeft();
    TopRight();
    BackRight();
    TopRight();
    LeftRight();
    TopLeft();
    LeftLeft();
  }
}
void TakeOutEdge(int corner){
  // corner 1 = front left
  // corner 2 = front right
  // corner 3 = back left
  // corner 4 = back right
  if (corner == 1){
    LeftLeft();
    TopRight();
    LeftRight();
    TopRight();
    FrontRight();
    TopLeft();
    FrontLeft();
  }
  else if (corner == 2){
    RightRight();
    TopLeft();
    RightLeft();
    TopLeft();
    FrontLeft();
    TopRight();
    FrontRight();
  }
  else if (corner == 3){
    LeftRight();
    TopLeft();
    LeftLeft();
    TopLeft();
    BackLeft();
    TopRight();
    BackRight();
  }
  else if (corner == 4){
    RightLeft();
    TopRight();
    RightRight();
    TopRight();
    BackRight();
    TopLeft();
    BackLeft();
  }
}

void YellowCross(){
  // In this function we solve the yellow cross. There are three different patterns that always apear on the top
  // layer. These are a small mirrored L-shape, a line or a dot. Other faces can be yellow but one of these three 
  // always appears. There are two differnt algorithms. One solves the line and the other solves the L-shape. To
  // go from a dot to solve we apply the L-shape algorithm. Then a L-shape appears on the top layer.


  // indices of the top layer are 5, 6, 7, 10, 11, 17, 18, 19

  // First we check if the cross is already there. Indices with yellow top: 6, 10, 11, 18
  if (cubeArray[6][top] == 'y' && cubeArray[10][top] == 'y' && cubeArray[11][top] == 'y' && cubeArray[18][top] == 'y'){
    solveArray[3] = 1;
    return;
  }

  // We look for the line-shape. The line can be horizontal and vertical
  //First vertical
  if (cubeArray[6][top] == 'y' && cubeArray[18][top] == 'y'){
    RightRight();
    BackRight();
    TopRight();
    BackLeft();
    TopLeft();
    RightLeft();
    solveArray[3] = 1;
    return;
  }

  // Horizontal line
  if (cubeArray[10][top] == 'y' && cubeArray[11][top] == 'y'){
    TopRight();
    RightRight();
    BackRight();
    TopRight();
    BackLeft();
    TopLeft();
    RightLeft();
    solveArray[3] = 1;
    return;
  }

  // We look for the l-shape. this shape can be in four directions

  // L-shape green front. Indices are: 10, 18
  if (cubeArray[10][top] == 'y' && cubeArray[18][top] == 'y'){
    TopLeft();
    solveLshape();
    solveArray[3] = 1;
    return;
  }
  // L-shape Orange front. Indices are; 6, 10
  if (cubeArray[6][top] == 'y' && cubeArray[10][top] == 'y'){
    solveLshape();
    solveArray[3] = 1;
    return;
  }

  //L-shape blue front, indices are 6, 11
  if (cubeArray[6][top] == 'y' && cubeArray[11][top] == 'y'){
    TopRight();
    solveLshape();
    solveArray[3] = 1;
    return;
  }

  //L-shape red front, indices are 11, 18
  if (cubeArray[11][top] == 'y' && cubeArray[18][top] == 'y'){
    TopRight();
    TopRight();
    solveLshape();
    solveArray[3] = 1;
    return;
  }
  

  // If there is not an algorithm applied it automatically is an dot shape we apply the solveLshape algorithm once 
  // and run the function again
  solveLshape();
  return;
}
void solveLshape(){
  RightRight();
  TopRight();
  BackRight();
  TopLeft();
  BackLeft();
  RightLeft();
}

void solveYellowEdges(){
  // The yellow edges are in the right orientation but the position is not considered in the last function
  // in this function we solve the position of the yellow edges while keeping the orientation intact.
  // There are always two edges which are (by grouptheory, dont ask me im not an mathematical genius) already
  // in the right position. We find these two edges and solve the other two if necessary.

  // First check if they are already solved. Indices are again 6, 10, 11, 18.



  // if (yellowEdges[0] == 1 && yellowEdges[1] == 1 && yellowEdges[2] == 1 && yellowEdges[3] == 1){
  //   solveArray[4] == 1;
  //   return;
  // }

  // We know that two edges are already solved, but the position may be off. We count the correct positions
  // from the array. If the count is less than two we rotate the top layer once and count again.
  
  int correctEdges = 0;
  while (true){
    if (cubeArray[6][front] == 'g'){
      yellowEdges[0] = 1;
      correctEdges++;
    }
    else{
      yellowEdges[0] = 0;
    }
    if (cubeArray[10][left] == 'r'){
      yellowEdges[1] = 1;
      correctEdges++;
    }
    else{
      yellowEdges[1] = 0;
    }
    if (cubeArray[11][right] == 'o'){
      yellowEdges[2] = 1;
      correctEdges++;
    }
    else{
      yellowEdges[3] = 0;
    }
    if (cubeArray[18][back] == 'b'){
      yellowEdges[3] = 1;
      correctEdges++;
    }
    else{
      yellowEdges[3] = 0;
    }
    if (correctEdges == 4){
      solveArray[4] = 1;
      return;
    }
    else if (correctEdges < 2){
      correctEdges = 0;
      TopRight();
    }
    else{
      break;
    } 
  }
  
  // Now we have six different possible scenarios where 2 edges are solved. For each of te six we write an 
  // algorithm to solve all the edges

  // Yellow Edges array 0 = green, 1 = red, 2 = orange, 3 = blue


  // Green/Red correct, swap Orange/Blue
  if (yellowEdges[0] == 1 && yellowEdges[1] == 1){
    swapEdge();
    solveArray[4] = 1; 
    return;
  }

  // Green/Orange correct, swap Red/Blue
  else if (yellowEdges[0] == 1 && yellowEdges[2] == 1){
    TopRight();
    swapEdge();
    TopLeft();
    solveArray[4] = 1; 
    return;
  }

  // Blue/Red correct, swap Green/Orange
  else if (yellowEdges[1] == 1 && yellowEdges[3] == 1){
    TopLeft();
    swapEdge();
    TopRight();
    solveArray[4] = 1; 
    return;
  }

  //Blue/Orange correct, swap Green/Red 
  else if (yellowEdges[2] == 1 && yellowEdges[3] == 1){
    TopRight();
    TopRight();
    swapEdge();
    TopRight();
    TopRight();
    solveArray[4] = 1; 
    return;
  }

  // Blue/Green correct, swap Orange/Red
  else if (yellowEdges[0] == 1 && yellowEdges[3] == 1){
    swapEdge();
    TopRight();
    TopRight();
    swapEdge();
    TopRight();
    solveArray[4] = 1; 
    return;
  }

  // Orange/Red correct, swap Green/Blue
  else if (yellowEdges[1] == 1 && yellowEdges[2] == 1){
    swapEdge();
    TopRight();
    TopRight();
    swapEdge();
    TopLeft();
    solveArray[4] = 1; 
    return;
  }
}
void swapEdge(){
  LeftRight();
  TopRight();
  LeftLeft();
  TopRight();
  LeftRight();
  TopRight();
  TopRight();
  LeftLeft();
  TopRight();
}



void reset(){
  for (int i = 0; i < 7; ++i){
    solveArray[i] = 0;
  }
  for (int i =0; i < 4; ++i){
    whiteEdges[i] = 0;
    whiteCorners[i] = 0;
    middleEdges[i] = 0;
    yellowEdges[i] = 0;
    yellowCornerPos[i] = 0;
    yellowCornerOr[i] = 0;
    cornerTwists[i] = 0;
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
bool testWhiteCorners(){
  if (!(cubeArray[0][front] == 'g' && cubeArray[0][bottom] == 'w')){
    return false;
  }
  else if (!(cubeArray[2][front] == 'g' && cubeArray[1][bottom] == 'w')){
    return false;
  }
  else if (!(cubeArray[12][back] == 'b' && cubeArray[12][bottom] == 'w')){
    return false;
  }
  else if (!(cubeArray[14][back] == 'b' && cubeArray[14][bottom] == 'w')){
    return false;
  }
  else{
    return true;
  } 
}
bool testMiddleEdges(){
  // indices are 3, 4, 15, 16
  if (!(cubeArray[3][front] == 'g') && cubeArray[3][left] == 'r'){
    return false;
  }
  else if (!(cubeArray[4][front] == 'g') && cubeArray[4][right] == 'o'){
    return false;
  }
  else if (!(cubeArray[16][back] == 'b') && cubeArray[16][right] == 'o'){
    return false;
  }
  else if (!(cubeArray[15][back] == 'b') && cubeArray[15][left] == 'r'){
    return false;
  }
  else{
    return true;
  }
}
bool testYellowCross(){
  if (!(cubeArray[6][top] == 'y' && cubeArray[10][top] == 'y' && cubeArray[11][top] == 'y' && cubeArray[18][top] == 'y')){
    return false;
  }
  else{
    return true;
  }
}
bool testYellowEdges(){
  if (!cubeArray[6][front] == 'g'){
    return false;
  }
  else if (!cubeArray[10][left] == 'r'){
    return false;
  }
  else if (!cubeArray[11][right] == 'o'){
    return false;
  }
  else if (!cubeArray[18][back] == 'b'){
    return false;
  }
  else{
    return true;
  }
}
bool testCube(){
  if (!testWhiteCross()){
    return false;
  }
  else if (!testWhiteCorners()){
    return false;
  }
  else if (!testMiddleEdges()){
    return false;
  }
  else if (!testYellowCross()){
    return false;
  }
  else if (!testYellowEdges()){
    return false;
  }
  else{
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
  // stepperRight.step(turnRight);
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
  // stepperRight.step(turnLeft);
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
  // stepperLeft.step(turnRight);
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
  // stepperLeft.step(turnLeft);
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
  // stepperBottom.step(turnRight);
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
  // stepperBottom.step(turnLeft);
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
  // stepperTop.step(turnRight);
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
  // stepperTop.step(turnLeft);
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
  // stepperBack.step(turnRight);
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
  // stepperBack.step(turnLeft);
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

  // stepperRight.step(turnRight);
  // stepperLeft.step(turnRight);
  // stepperBottom.step(turnHalve);
  // stepperTop.step(turnHalve);
  // stepperRight.step(turnLeft);
  // stepperLeft.step(turnLeft);
  // stepperBack.step(turnRight);
  // stepperRight.step(turnRight);
  // stepperLeft.step(turnRight);
  // stepperBottom.step(turnHalve);
  // stepperTop.step(turnHalve);
  // stepperRight.step(turnLeft);
  // stepperLeft.step(turnLeft);
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

  // stepperRight.step(turnRight);
  // stepperLeft.step(turnRight);
  // stepperBottom.step(turnHalve);
  // stepperTop.step(turnHalve);
  // stepperRight.step(turnLeft);
  // stepperLeft.step(turnLeft);
  // stepperBack.step(turnLeft);
  // stepperRight.step(turnRight);
  // stepperLeft.step(turnRight);
  // stepperBottom.step(turnHalve);
  // stepperTop.step(turnHalve);
  // stepperRight.step(turnLeft);
  // stepperLeft.step(turnLeft);
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
