// make an test array for the cube each element contains six elements which
// represent the colors of that cubicle in the order
// front, left, right, top, bottom, back
// g = green o = orange w = white y = yellow r = red and - = black

#include <AccelStepper.h>

#define motorInterfaceType 1

AccelStepper stepper_1 = AccelStepper(motorInterfaceType, 2,3);
AccelStepper stepper_2 = AccelStepper(motorInterfaceType, 4,5);
AccelStepper stepper_3 = AccelStepper(motorInterfaceType, 6,7);
AccelStepper stepper_4 = AccelStepper(motorInterfaceType, 8,9);
AccelStepper stepper_5 = AccelStepper(motorInterfaceType, 10,11);
AccelStepper stepper_6 = AccelStepper(motorInterfaceType, 12,13);

char cubeArray[20][6] = { {'g','o','-','-','y','-'},
  {'g','-','-','-','y','-'},
  {'g','-','r','-','y','-'},
  {'g','o','-','-','-','-'},
  {'g','-','r','-','-','-'},
  {'g','o','-','w','-','-'},
  {'g','-','-','w','-','-'},
  {'g','-','r','w','-','-'},
  {'-','o','-','-','y','-'},
  {'-','-','r','-','y','-'},
  {'-','o','-','w','-','-'},
  {'-','-','r','w','-','-'},
  {'-','o','-','-','y','b'},
  {'-','-','-','-','y','b'},
  {'-','-','r','-','y','b'},
  {'-','o','-','-','-','b'},
  {'-','-','r','-','-','b'},
  {'-','o','-','w','-','b'},
  {'-','-','-','w','-','b'},
  {'-','-','r','w','-','b'}};

  // input string to put in cubeArray
  char test_str[] = "ry--b-b---o-b-w-o-br----o-g---yo-g--g--w--y-rg---y--b---y-o--g-y----wo---y--bo----wr--w-og-r---g--b--w-g-r-w---r-y--br-w";

  // set up variables for conversion(rotation / position) of the cubicles
  char orgColour = '-';
  char orgArray[6]= {};
  char convArray[8][6]= {{}};



  // Set up variables for the solver
  byte solveArray[7] = {0,0,0,0,0,0,0};
  byte edgeArray[4] = {0,0,0,0};
  byte cornerArray[4] = {0,0,0,0};
  byte middleArray[4] = {0,0,0,0};
  byte upperArray[4] = {0,0,0,0};
  byte upperCorner[4] = {0,0,0,0};
  byte upperCorner2 [4] = {0,0,0,0};
  int cornerTwists[4] = {0,0,0,0};


void setup() {
  // put your setup code here, to run once:
  stepper_1.setMaxSpeed(200);
  stepper_2.setMaxSpeed(200);
  stepper_1.setAcceleration(2000);
  stepper_2.setAcceleration(2000);
  stepper_3.setMaxSpeed(200);
  stepper_4.setMaxSpeed(200);
  stepper_3.setAcceleration(2000);
  stepper_4.setAcceleration(2000);
  stepper_5.setMaxSpeed(200);
  stepper_6.setMaxSpeed(200);
  stepper_5.setAcceleration(2000);
  stepper_6.setAcceleration(2000);
  Serial.begin(115200);
  Serial.println("CUBEARRAY");
  Serial.println();
  // print cube array initial position per blok
  for (int i = 0; i < 20; i ++){
    Serial.print("Blok ");
    Serial.print(i);
    Serial.print(" ");
    for (int k = 0; k < 6; k++){
      Serial.print(cubeArray[i][k]);
    }
    Serial.println();
  }

  // do changes
  setupcubeArray(test_str);
  Serial.println("cube array before changes");
  Serial.println(cubeArray[0]);


  while (solveArray[6] != 1){
    if (solveArray[0] != 1){
      WhiteCross();
    }
    else if (solveArray[1] != 1){
      WhiteCorners();
    }
    else if (solveArray[2] != 1){
      MiddleLayer();
    }
    else if (solveArray[3] != 1){
      YellowCross();
    }
    else if (solveArray[4] != 1){
      UpperEdges();
    }
    else if (solveArray[5] != 1){
      UpperCorners();
    }
    else if (solveArray[6] != 1){
      UpperCorners2();
    }  
  }

  // print cubearray after changes to test with python code
  Serial.println("cube array after solve");
  Serial.println(cubeArray[0]);

}

void loop() {
  // put your main code here, to run repeatedly:


}

void setupcubeArray(char string[]){
  int k = 0;
  for (int l = 0; l < 20; l++){
    for (int j = 0; j < 6; j++){
      cubeArray[l][j] = string[k];
      k++;
    }
  }
}

void FrontRight(char Array[][6]) {
  // Turn the front of the cube right
  for (int i = 0; i < 6; i++){
    orgArray[i] = Array[5][i];
    Array[5][i] = Array[0][i];
    Array[0][i] = Array[2][i];
    Array[2][i] = Array[7][i];
    cubeArray[7][i] = orgArray[i];

    orgArray[i] = Array[1][i];
    Array[1][i] = Array[4][i];
    Array[4][i] = Array[6][i];
    Array[6][i] = Array[3][i];
    Array[3][i] = orgArray[i];
  }
  // Rotate the colors
  for (int i = 0; i < 8; i++){
    orgColour = Array[i][1];
    Array[i][1] = Array[i][4];
    Array[i][4] = Array[i][2];
    Array[i][2] = Array[i][3];
    Array[i][3] = orgColour;

  }
  // // Rotate motor
  // stepper_5.move(50);
  // stepper_5.runToPosition();
}

void FrontLeft(char Array[][6]){
  for (int i = 0; i < 6; i++){
    orgArray[i] = Array[5][i];
    Array[5][i] = Array[7][i];
    Array[7][i] = Array[2][i];
    Array[2][i] = Array[0][i];
    cubeArray[0][i] = orgArray[i];

    orgArray[i] = Array[1][i];
    Array[1][i] = Array[3][i];
    Array[3][i] = Array[6][i];
    Array[6][i] = Array[4][i];
    Array[4][i] = orgArray[i];
  }
  // Rotate the colors
  for (int i = 0; i < 8; i++){
    orgColour = Array[i][1];
    Array[i][1] = Array[i][3];
    Array[i][3] = Array[i][2];
    Array[i][2] = Array[i][4];
    Array[i][4] = orgColour;
  }
  // // Rotate motor
  // stepper_5.move(-50);
  // stepper_5.runToPosition();
}

void RightRight(char Array[][6]){
  // Make a conversion array
  // Set the rotating cubes in the conversion array
  for (int i = 0; i < 6; i++){
      convArray[0][i] = Array[2][i];
      convArray[1][i] = Array[7][i];
      convArray[2][i] = Array[19][i];
      convArray[3][i] = Array[14][i];
      convArray[4][i] = Array[4][i];
      convArray[5][i] = Array[11][i];
      convArray[6][i] = Array[16][i];
      convArray[7][i] = Array[9][i];
  }
  // Rotate the colors in the conversion array
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][4];
    convArray[i][4] = convArray[i][5];
    convArray[i][5] = convArray[i][3];
    convArray[i][3] = orgColour;
  }
  // Put rotated cubes back in cubeArray in the right position
  for (int i = 0; i < 6; i++){
    Array[7][i] = convArray[0][i];
    Array[19][i] = convArray[1][i];
    Array[14][i] = convArray[2][i];
    Array[2][i] = convArray[3][i];
    Array[11][i] = convArray[4][i];
    Array[16][i] = convArray[5][i];
    Array[9][i] = convArray[6][i];
    Array[4][i] = convArray[7][i];
  }
  // stepper_2.move(-50);
  // stepper_2.runToPosition();
}

void RightLeft(char Array[][6]){
  for (int i = 0; i < 6; i++){
      convArray[0][i] = Array[2][i];
      convArray[1][i] = Array[4][i];
      convArray[2][i] = Array[7][i];
      convArray[3][i] = Array[9][i];
      convArray[4][i] = Array[11][i];
      convArray[5][i] = Array[14][i];
      convArray[6][i] = Array[16][i];
      convArray[7][i] = Array[19][i];
  }
  // Rotate the colors in the conversion array
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][3];
    convArray[i][3] = convArray[i][5];
    convArray[i][5] = convArray[i][4];
    convArray[i][4] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[14][i] = convArray[0][i];
    Array[9][i] = convArray[1][i];
    Array[2][i] = convArray[2][i];
    Array[16][i] = convArray[3][i];
    Array[4][i] = convArray[4][i];
    Array[19][i] = convArray[5][i];
    Array[11][i] = convArray[6][i];
    Array[7][i] = convArray[7][i];
  }
  // stepper_2.move(50);
  // stepper_2.runToPosition();
}

void LeftRight(char Array[][6]){
  // Apply same strategy as rightright
  for (int i = 0; i < 6; i++){
      convArray[0][i] = Array[0][i];
      convArray[1][i] = Array[3][i];
      convArray[2][i] = Array[5][i];
      convArray[3][i] = Array[8][i];
      convArray[4][i] = Array[10][i];
      convArray[5][i] = Array[12][i];
      convArray[6][i] = Array[15][i];
      convArray[7][i] = Array[17][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][3];
    convArray[i][3] = convArray[i][5];
    convArray[i][5] = convArray[i][4];
    convArray[i][4] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[12][i] = convArray[0][i];
    Array[8][i] = convArray[1][i];
    Array[0][i] = convArray[2][i];
    Array[15][i] = convArray[3][i];
    Array[3][i] = convArray[4][i];
    Array[17][i] = convArray[5][i];
    Array[10][i] = convArray[6][i];
    Array[5][i] = convArray[7][i];
  }
  // stepper_1.move(50);
  // stepper_1.runToPosition();
}

void LeftLeft(char Array[][6]){
  for (int i = 0; i < 6; i++){
      convArray[0][i] = Array[0][i];
      convArray[1][i] = Array[3][i];
      convArray[2][i] = Array[5][i];
      convArray[3][i] = Array[8][i];
      convArray[4][i] = Array[10][i];
      convArray[5][i] = Array[12][i];
      convArray[6][i] = Array[15][i];
      convArray[7][i] = Array[17][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][0];
    convArray[i][0] = convArray[i][4];
    convArray[i][4] = convArray[i][5];
    convArray[i][5] = convArray[i][3];
    convArray[i][3] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[5][i] = convArray[0][i];
    Array[10][i] = convArray[1][i];
    Array[17][i] = convArray[2][i];
    Array[3][i] = convArray[3][i];
    Array[15][i] = convArray[4][i];
    Array[0][i] = convArray[5][i];
    Array[8][i] = convArray[6][i];
    Array[12][i] = convArray[7][i];
  }
  // stepper_1.move(-50);
  // stepper_1.runToPosition();
}

void BottomRight(char Array[][6]){
  for (int i = 0; i < 6; i++){
      convArray[0][i] = Array[0][i];
      convArray[1][i] = Array[1][i];
      convArray[2][i] = Array[2][i];
      convArray[3][i] = Array[8][i];
      convArray[4][i] = Array[9][i];
      convArray[5][i] = Array[12][i];
      convArray[6][i] = Array[13][i];
      convArray[7][i] = Array[14][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][5];
    convArray[i][5] = convArray[i][2];
    convArray[i][2] = convArray[i][0];
    convArray[i][0] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[2][i] = convArray[0][i];
    Array[9][i] = convArray[1][i];
    Array[14][i] = convArray[2][i];
    Array[1][i] = convArray[3][i];
    Array[13][i] = convArray[4][i];
    Array[0][i] = convArray[5][i];
    Array[8][i] = convArray[6][i];
    Array[12][i] = convArray[7][i];
  }
  // stepper_4.move(50);
  // stepper_4.runToPosition();
}

void BottomLeft(char Array[][6]){
  for (int i = 0; i < 6; i++){
      convArray[0][i] = Array[0][i];
      convArray[1][i] = Array[1][i];
      convArray[2][i] = Array[2][i];
      convArray[3][i] = Array[8][i];
      convArray[4][i] = Array[9][i];
      convArray[5][i] = Array[12][i];
      convArray[6][i] = Array[13][i];
      convArray[7][i] = Array[14][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][0];
    convArray[i][0] = convArray[i][2];
    convArray[i][2] = convArray[i][5];
    convArray[i][5] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[12][i] = convArray[0][i];
    Array[8][i] = convArray[1][i];
    Array[0][i] = convArray[2][i];
    Array[13][i] = convArray[3][i];
    Array[1][i] = convArray[4][i];
    Array[14][i] = convArray[5][i];
    Array[9][i] = convArray[6][i];
    Array[2][i] = convArray[7][i];
  }
  // stepper_4.move(-50);
  // stepper_4.runToPosition();
}

void TopRight(char Array[][6]){
  for (int i = 0; i < 6; i++){
    convArray[0][i] = Array[5][i];
    convArray[1][i] = Array[6][i];
    convArray[2][i] = Array[7][i];
    convArray[3][i] = Array[10][i];
    convArray[4][i] = Array[11][i];
    convArray[5][i] = Array[17][i];
    convArray[6][i] = Array[18][i];
    convArray[7][i] = Array[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][0];
    convArray[i][0] = convArray[i][2];
    convArray[i][2] = convArray[i][5];
    convArray[i][5] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[17][i] = convArray[0][i];
    Array[10][i] = convArray[1][i];
    Array[5][i] = convArray[2][i];
    Array[18][i] = convArray[3][i];
    Array[6][i] = convArray[4][i];
    Array[19][i] = convArray[5][i];
    Array[11][i] = convArray[6][i];
    Array[7][i] = convArray[7][i];
  }
  // stepper_3.move(50);
  // stepper_3.runToPosition();
}

void TopLeft(char Array[][6]){
  for (int i = 0; i < 6; i++){
    convArray[0][i] = Array[5][i];
    convArray[1][i] = Array[6][i];
    convArray[2][i] = Array[7][i];
    convArray[3][i] = Array[10][i];
    convArray[4][i] = Array[11][i];
    convArray[5][i] = Array[17][i];
    convArray[6][i] = Array[18][i];
    convArray[7][i] = Array[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][5];
    convArray[i][5] = convArray[i][2];
    convArray[i][2] = convArray[i][0];
    convArray[i][0] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[7][i] = convArray[0][i];
    Array[11][i] = convArray[1][i];
    Array[19][i] = convArray[2][i];
    Array[6][i] = convArray[3][i];
    Array[18][i] = convArray[4][i];
    Array[5][i] = convArray[5][i];
    Array[10][i] = convArray[6][i];
    Array[17][i] = convArray[7][i];
  }
  // stepper_3.move(-50);
  // stepper_3.runToPosition();
}

void BackRight(char Array[][6]){
  for (int i = 0; i < 6; i++){
    convArray[0][i] = Array[12][i];
    convArray[1][i] = Array[13][i];
    convArray[2][i] = Array[14][i];
    convArray[3][i] = Array[15][i];
    convArray[4][i] = Array[16][i];
    convArray[5][i] = Array[17][i];
    convArray[6][i] = Array[18][i];
    convArray[7][i] = Array[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][3];
    convArray[i][3] = convArray[i][2];
    convArray[i][2] = convArray[i][4];
    convArray[i][4] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[14][i] = convArray[0][i];
    Array[16][i] = convArray[1][i];
    Array[19][i] = convArray[2][i];
    Array[13][i] = convArray[3][i];
    Array[18][i] = convArray[4][i];
    Array[12][i] = convArray[5][i];
    Array[15][i] = convArray[6][i];
    Array[17][i] = convArray[7][i];
  }
  // stepper_6.move(50);
  // stepper_6.runToPosition();
}

void BackLeft(char Array[][6]){
  for (int i = 0; i < 6; i++){
    convArray[0][i] = Array[12][i];
    convArray[1][i] = Array[13][i];
    convArray[2][i] = Array[14][i];
    convArray[3][i] = Array[15][i];
    convArray[4][i] = Array[16][i];
    convArray[5][i] = Array[17][i];
    convArray[6][i] = Array[18][i];
    convArray[7][i] = Array[19][i];
  }
  for (int i = 0; i < 8; i++){
    orgColour = convArray[i][1];
    convArray[i][1] = convArray[i][4];
    convArray[i][4] = convArray[i][2];
    convArray[i][2] = convArray[i][3];
    convArray[i][3] = orgColour;
  }
  for (int i = 0; i < 6; i++){
    Array[17][i] = convArray[0][i];
    Array[15][i] = convArray[1][i];
    Array[12][i] = convArray[2][i];
    Array[18][i] = convArray[3][i];
    Array[13][i] = convArray[4][i];
    Array[19][i] = convArray[5][i];
    Array[16][i] = convArray[6][i];
    Array[14][i] = convArray[7][i];
  }
  // stepper_6.move(-50);
  // stepper_6.runToPosition();
}

void WhiteCross(){
  // Check al edges of the cube for white edges.
  // If they are in the top, but not in the right orientatien then place it directly.
  // It they are in the top but not in the right place put them in bottom.
  // If they are in the bottom place them directly
  // By first checking the top and then chechking the bottom, we put the pieces in the right place
  // that were in the wrong spot on the top-side because we moved them to the bottom side.

  // if all edges are on the right spot the cross is solved we return without doing anything
  if (edgeArray[1] == 1 && edgeArray[0] == 1 && edgeArray[3] == 1 && edgeArray[2] == 1){
    solveArray[0] = 1;
    Serial.println("edges solved");
    return;
  }
  // left top edge
  if (cubeArray[10][3] == 'w'){
    if (cubeArray[10][1] == 'o'){
      edgeArray[1] = 1;
    }
    else if (cubeArray[10][1] == 'r' || cubeArray[10][1] == 'b' || cubeArray[10][1] == 'g'){
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
    }
  }
  else if (cubeArray[10][1] == 'w'){
    if (cubeArray[10][3] == 'o'){
      LeftRight(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[10][3] == 'r' || cubeArray[10][3] == 'b' || cubeArray[10][3] == 'g'){
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
    }
  // left back edge
  }
  if (cubeArray[15][5] == 'w'){
    if (cubeArray[15][1] == 'o'){
      LeftRight(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[15][1] == 'r' || cubeArray[15][1] == 'g'){
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
    }
    else if (cubeArray[15][1] == 'b'){
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      edgeArray[2] = 1;
    }
  }
  else if (cubeArray[15][1] == 'w'){
    if (cubeArray[15][5] == 'o'){
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[15][5] == 'r' || cubeArray[15][5] == 'g'){
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
    }
    else if (cubeArray[15][5] == 'b'){
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
  }
  // Left front edge
  if (cubeArray[3][0] == 'w'){
    if (cubeArray[3][1] == 'o'){
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[3][1] == 'r' || cubeArray[3][1] == 'b'){
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
    }
    else if (cubeArray[3][1] == 'g'){
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
  }
  else if (cubeArray[3][1] == 'w'){
    if (cubeArray[3][0] == 'o'){
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[3][0] == 'r' || cubeArray[3][0] == 'b'){
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
    }
    else if (cubeArray[3][0] == 'g'){
      FrontRight(cubeArray);
      edgeArray[0] = 1;
    }
  }
  // front top edge
  if (cubeArray[6][3] == 'w'){
    if (cubeArray[6][0] == 'g'){
      edgeArray[0] = 1;
    }
    else if (cubeArray[6][0] == 'r' || cubeArray[6][0] == 'b' || cubeArray[6][0] == 'o'){
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
    }
  }
  else if (cubeArray[6][0] == 'w'){
    if (cubeArray[6][3] == 'g'){
      FrontRight(cubeArray);
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[6][3] == 'r' || cubeArray[6][3] == 'b' || cubeArray[6][3] == 'o'){
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
    }
  }
  // Front right edge
  if (cubeArray[4][2] == 'w'){
    if (cubeArray[4][0] == 'g'){
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[4][0] == 'o' || cubeArray[4][0] == 'b'){
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
    }
    else if (cubeArray[4][0] == 'r'){
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
  }
  else if (cubeArray[4][0] == 'w'){
    if (cubeArray[4][2] == 'g'){
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[4][2] == 'r'){
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[4][2] == 'b' || cubeArray[4][2] == 'o'){
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
    }
  }
  // Top right egde
  if (cubeArray[11][3] == 'w'){
    if (cubeArray[11][2] == 'r'){
      edgeArray[3] = 1;
    }
    else if (cubeArray[11][2] == 'g' || cubeArray[11][2] == 'o' || cubeArray[11][2] == 'b'){
      RightRight(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
    }
  }
  else if (cubeArray[11][2] == 'w'){
    if (cubeArray[11][3] == 'r'){
      RightLeft(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[11][3] == 'g' || cubeArray[11][3] == 'b' || cubeArray[11][3] == 'o'){
      RightLeft(cubeArray);
      RightLeft(cubeArray);
      BottomRight(cubeArray);
    }
  }
  // back right edge
  if (cubeArray[16][5] == 'w'){
    if (cubeArray[16][2] == 'r'){
      RightLeft(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[16][2] == 'g' || cubeArray[16][2] == 'o'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
    }
    else if (cubeArray[16][2] == 'b'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      edgeArray[2] = 1;
    }
  }
  else if (cubeArray[16][2] == 'w'){
    if (cubeArray[16][5] == 'r'){
      BackLeft(cubeArray);
      BottomLeft(cubeArray);
      BackRight(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[16][5] == 'g' || cubeArray[16][5] == 'o'){
      BackLeft(cubeArray);
      BottomRight(cubeArray);
      BackRight(cubeArray);
    }
    else if (cubeArray[16][5] == 'b'){
      BackRight(cubeArray);
      edgeArray[2] = 1;
    }
  }
  // Top back edge
  if (cubeArray[18][3] == 'w'){
    if (cubeArray[18][5] == 'b'){
      edgeArray[2] = 1;
    }
    else if (cubeArray[18][5] == 'g' || cubeArray[18][5] == 'r' || cubeArray[18][5] == 'o'){
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      BottomRight(cubeArray);
    }
  }
  else if (cubeArray[18][5] == 'w'){
    if (cubeArray[18][3] == 'b'){
      BackRight(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[18][3] == 'g' || cubeArray[18][3] == 'o' || cubeArray[18][3] == 'r'){
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      BottomRight(cubeArray);
    }
  }
  // Front bottom edge
  if (cubeArray[1][4] == 'w'){
    if (cubeArray[1][0] == 'g'){
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[1][0] == 'o'){
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[1][0] == 'b'){
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[1][0] == 'r'){
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      RightLeft(cubeArray);
      edgeArray[3] = 1;
    }
  }
  else if (cubeArray[1][0] == 'w'){
    if (cubeArray[1][4] == 'g'){
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[1][4] == 'o'){
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[1][4] == 'b'){
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[1][4] == 'r'){
      BottomRight(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
  }
  // Bottom right edge
  if (cubeArray[9][4] == 'w'){
    if (cubeArray[9][2] == 'r'){
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[9][2] == 'g'){
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[9][2] == 'b'){
      BottomRight(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[9][2] == 'o'){
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
  }
  else if (cubeArray[9][2] == 'w'){
    if (cubeArray[9][4] == 'r'){
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[9][4] == 'b'){
      BottomRight(cubeArray);
      BackRight(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[9][4] == 'o'){
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[9][4] == 'g'){
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
  }
  // bottom back edge
  else if (cubeArray[13][4] == 'w'){
    if (cubeArray[13][5] == 'b'){
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[13][5] == 'g'){
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[13][5] == 'r'){
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[13][5] == 'o'){
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
  }
  else if (cubeArray[13][5] == 'w'){
    if (cubeArray[13][4] == 'b'){
      BackLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[13][4] == 'o'){
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[13][4] == 'r'){
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[13][4] == 'g'){
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      edgeArray[0] = 1;
    }
  }
  // Bottom left edge
  if (cubeArray[8][4] == 'w'){
    if (cubeArray[8][1] == 'o'){
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[8][1] == 'b'){
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
    else if (cubeArray[8][1] == 'r'){
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[8][1] == 'g'){
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      edgeArray[0] = 1;
    }
  }
  else if (cubeArray[8][1] == 'w'){
    if (cubeArray[8][4] == 'o'){
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      edgeArray[1] = 1;
    }
    else if (cubeArray[8][4] == 'g'){
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      edgeArray[0] = 1;
    }
    else if (cubeArray[8][4] == 'r'){
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      RightLeft(cubeArray);
      edgeArray[3] = 1;
    }
    else if (cubeArray[8][4] == 'b'){
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      edgeArray[2] = 1;
    }
  }
}

void WhiteCorners(){
  // Solve the first layer by putting the white corners in the right place
  // We check al the corners if we cant place it direcly we put it in the top layer to solve it later
  if (cornerArray[0] == 1 && cornerArray[1] == 1 && cornerArray[2] == 1 && cornerArray[3] == 1){
    solveArray[1] = 1;
  }
  // Top left corner
  if (cubeArray[5][3] == 'w'){
    if (cubeArray[5][0] == 'g'){
      cornerArray[0] = 1;
    }
    else if (cubeArray[5][0] == 'o' || cubeArray[5][0] == 'b' || cubeArray[5][0] == 'r'){
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
    }
  }
  else if (cubeArray[5][1] == 'w'){
    if (cubeArray[5][0] == 'o'){
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      cornerArray[0] = 1;
    }
    else if (cubeArray[5][0] == 'r' || cubeArray[5][0] == 'b' || cubeArray[5][0] == 'g'){
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
    }
  }
  else if (cubeArray[5][0] == 'w'){
    if (cubeArray[5][3] == 'o'){
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      cornerArray[0] = 1;
    }
    else if (cubeArray[5][3] == 'b' || cubeArray[5][3] == 'g' || cubeArray[5][3] == 'r'){
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
    }
  }
  // Top right front color
  if (cubeArray[7][3] == 'w'){
    if (cubeArray[7][0] == 'g'){
      cornerArray[1] = 1;
    }
    else if (cubeArray[7][0] == 'r' || cubeArray[7][0] == 'b' || cubeArray[7][0] == 'o'){
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
    }
  }
  else if (cubeArray[7][0] == 'w'){
    if (cubeArray[7][3] == 'r'){
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      cornerArray[1] = 1;
    }
    else if (cubeArray[7][3] == 'g' || cubeArray[7][3] == 'o' || cubeArray[7][3] == 'b'){
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
    }
  }
  else if (cubeArray[7][2] == 'w'){
    if (cubeArray[7][3] == 'g'){
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      cornerArray[1] = 1;
    }
    else if (cubeArray[7][3] == 'r' || cubeArray[7][3] == 'b' || cubeArray[7][3] == 'o'){
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
    }
  }
  // Top back left corner
  if (cubeArray[17][3] == 'w'){
    if (cubeArray[17][1] == 'o'){
      cornerArray[2] = 1;
    }
    else if (cubeArray[17][1] == 'r' || cubeArray[17][1] == 'g' || cubeArray[17][1] == 'b'){
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
      LeftRight(cubeArray);
    }
  }
  else if (cubeArray[17][1] == 'w'){
    if (cubeArray[17][3] == 'b'){
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      cornerArray[2] = 1;
    }
    else if (cubeArray[17][3] == 'g' || cubeArray[17][3] == 'r' || cubeArray[17][3] == 'o'){
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
      LeftRight(cubeArray);
    }
  }
  else if (cubeArray[17][5] == 'w'){
    if (cubeArray[17][3] == 'o'){
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
      LeftRight(cubeArray);
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
      cornerArray[2] = 1;
    }
    else if (cubeArray[17][3] == 'r' || cubeArray[17][3] == 'b' || cubeArray[17][3] == 'g'){
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
      LeftRight(cubeArray);
    }
  }
  if (cubeArray[19][3] == 'w'){
    if (cubeArray[19][5] == 'b'){
      cornerArray[3] = 1;
    }
    else if (cubeArray[19][5] == 'g' || cubeArray[19][5] == 'r' || cubeArray[19][5] == 'o'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
    }
  }
  else if (cubeArray[19][2] == 'w'){
    if (cubeArray[19][3] == 'b'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      cornerArray[3] = 1;
    }
    else if (cubeArray[19][3] == 'r' || cubeArray[19][3] == 'g' || cubeArray[19][3] == 'o'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
    }
  }
  else if (cubeArray[19][5] == 'w'){
    if (cubeArray[19][3] == 'r'){
      RightRight(cubeArray);
      BottomLeft(cubeArray);
      RightLeft(cubeArray);
      BackLeft(cubeArray);
      BottomLeft(cubeArray);
      BackRight(cubeArray);
      cornerArray[3] = 1;
    }
    else if (cubeArray[19][3] == 'g' || cubeArray[19][3] == 'b' || cubeArray[19][3] == 'o'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
    }
  }
  // Bottom front left corner
  if (cubeArray[0][4] == 'w'){
    if (cubeArray[0][0] == 'o'){
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      cornerArray[0] = 1;
    }
  }
  else if (cubeArray[0][0] == 'w'){
    if (cubeArray[0][4] == 'g'){
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      cornerArray[0] = 1;
    }
  }
  else if (cubeArray[0][1] == 'w'){
    if (cubeArray[0][0] == 'g'){
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      cornerArray[0] = 1;
    }
  }
  // Bottom back left corner
  if (cubeArray[12][4] == 'w'){
    if (cubeArray[12][1] == 'b'){
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      cornerArray[2] = 1;
    }
  }
  else if (cubeArray[12][1] == 'w'){
    if (cubeArray[12][4] == 'o'){
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      cornerArray[2] = 1;
    }
  }
  else if (cubeArray[12][5] == 'w'){
    if (cubeArray[12][4] == 'w'){
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
      cornerArray[2] = 1;
    }
  }
  // Bottom back right corner
  if (cubeArray[14][4] == 'w'){
    if (cubeArray[14][2] == 'b'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      cornerArray[3] = 1;
    }
  }
  else if (cubeArray[14][2] == 'w'){
    if (cubeArray[14][4] == 'r'){
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      cornerArray[3] = 1;
    }
  }
  else if (cubeArray[14][5] == 'w'){
    if (cubeArray[14][4] == 'b'){
      BackLeft(cubeArray);
      BottomLeft(cubeArray);
      BackRight(cubeArray);
      cornerArray[3] = 1;
    }
  }
  // Bottom front right corner
  if (cubeArray[2][4] == 'w'){
    if (cubeArray[2][0] == 'r'){
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      cornerArray[1] = 1;
    }
  }
  else if (cubeArray[2][2] == 'w'){
    if (cubeArray[2][4] == 'r'){
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      cornerArray[1] = 1;
    }
  }
  else if (cubeArray[2][0] == 'w'){
    if (cubeArray[2][4] == 'g'){
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
    }
  }
  // Turn bottom right in case there is no corner on the bottom layer to be solver
  BottomRight(cubeArray);
}

void MiddleLayer(){
  if (middleArray[0] == 1 && middleArray[1] == 1 && middleArray[2] == 1 && middleArray[3] == 1){
    solveArray[2] = 1;
  }
  // Go through al the edges again to find the middle layer edges and place them accordingly
    // Front bottom edge
  if (cubeArray[1][0] == 'g'){
    if (cubeArray[1][4] == 'r'){
      BottomLeft(cubeArray);
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      middleArray[0] = 1;
    }
    else if (cubeArray[1][4] == 'o'){
      BottomRight(cubeArray);
      LeftRight(cubeArray);
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      middleArray[1] = 1;
    }
  }
    // Left bottom edge
  if (cubeArray[8][1] == 'o'){
    if (cubeArray[8][4] == 'g'){
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      LeftRight(cubeArray);
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      middleArray[1] = 1;
    }
    else if (cubeArray[8][4] == 'b'){
      BottomRight(cubeArray);
      BackRight(cubeArray);
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
      LeftRight(cubeArray);
      middleArray[3] = 1;
    }
  }
    // Bottom right edge
  if (cubeArray[9][2] == 'r'){
    if (cubeArray[9][4] == 'b'){
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      BottomRight(cubeArray);
      BackRight(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      BottomLeft(cubeArray);
      RightLeft(cubeArray);
      middleArray[2] = 1;
    }
    else if (cubeArray[9][4] == 'g'){
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      middleArray[0] = 1;
    }
  }
    // Bottom back edge
  if (cubeArray[13][5] == 'b'){
    if (cubeArray[13][4] == 'r'){
      BottomRight(cubeArray);
      RightRight(cubeArray);
      BottomLeft(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      BottomRight(cubeArray);
      BackRight(cubeArray);
      middleArray[2] = 1;
    }
    else if (cubeArray[13][4] == 'o'){
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      BackRight(cubeArray);
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      middleArray[3] = 1;
    }
  }
    // Front left edge
  if (cubeArray[3][0] == 'g' && cubeArray[3][1] == 'o'){
    middleArray[1] = 1;
  }
  else if (cubeArray[3][0] == 'o' && cubeArray[3][1] == 'g'){
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    middleArray[1] = 1;
  }
  else if (cubeArray[3][1] == 'r' || cubeArray[3][1] == 'b' || cubeArray[3][1] == 'g' || cubeArray[3][1] == 'o'){
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomRight(cubeArray);
  }
  // Front right edge
  if (cubeArray[4][0] == 'g' && cubeArray[4][2] == 'r'){
    middleArray[0] = 1;
  }
  else if (cubeArray[4][0] == 'r' && cubeArray[4][2] == 'g'){
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    BottomLeft(cubeArray);
    BottomLeft(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    middleArray[0] = 1;
  }
  else if (cubeArray[4][2] == 'r' || cubeArray[4][2] == 'g' || cubeArray[4][2] == 'b' || cubeArray[4][2] == 'o'){
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
  }
  // Back left edge
  if (cubeArray[15][5] == 'b' && cubeArray[15][1] == 'o'){
    middleArray[3] = 1;
  }
  else if (cubeArray[15][5] == 'o' && cubeArray[15][1] == 'b'){
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    BackRight(cubeArray);
    BottomLeft(cubeArray);
    BackLeft(cubeArray);
    BottomLeft(cubeArray);
    BottomLeft(cubeArray);
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    BackRight(cubeArray);
    BottomLeft(cubeArray);
    BackLeft(cubeArray);
    middleArray[3] = 1;
  }
  else if (cubeArray[15][5] == 'o' || cubeArray[15][5] == 'g' || cubeArray[15][5] == 'b' || cubeArray[15][5] == 'r'){
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    BackRight(cubeArray);
    BottomLeft(cubeArray);
    BackLeft(cubeArray);
    BottomRight(cubeArray);
  }
  // Back right edge
  if (cubeArray[16][5] == 'b' && cubeArray[16][2] == 'r'){
    middleArray[2] = 1;
  }
  else if (cubeArray[16][5] == 'r' && cubeArray[16][2] == 'b'){
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomLeft(cubeArray);
    BackLeft(cubeArray);
    BottomRight(cubeArray);
    BackRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomLeft(cubeArray);
    BackLeft(cubeArray);
    BottomRight(cubeArray);
    BackRight(cubeArray);
    middleArray[2] = 1;
  }
  else if (cubeArray[16][5] == 'b' || cubeArray[16][5] == 'g' || cubeArray[16][5] == 'r' || cubeArray[16][5] == 'o'){
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomLeft(cubeArray);
    BackLeft(cubeArray);
    BottomRight(cubeArray);
    BackRight(cubeArray);
  }
  // In case nothing is solveable from te bottom layer we turn the bottom right once
  BottomRight(cubeArray);
}

void YellowCross(){
  // Edges have two orientations. In this function we orientate the yellow edges so that the yellow faces up

   // After solving the middle layer there are four different configurations on the yellow layer.
  // The yellow edges form a cross then we leave the function.
  // The yellow edges form a L-shape
    // L-shapes can be on four different sides
  // The yellow edges form a line
  // Or the yellow edges form a dot ( only the middle piece is correct)
  if (cubeArray[1][4] == 'y' && cubeArray[8][4] == 'y' && cubeArray[9][4] == 'y' && cubeArray[13][4] == 'y'){
    solveArray[3] = 1;
    return;
  }

  // L shape and green is front
  else if (cubeArray[9][4] == 'y' && cubeArray[13][4] == 'y'){
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    FrontLeft(cubeArray);
    solveArray[3] = 1;
    return;
  }
  // L shape and red is front
  else if (cubeArray[13][4] == 'y' && cubeArray[8][4] == 'y'){
    RightRight(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    RightLeft(cubeArray);
    solveArray[3] = 1;
    return;
  }
  // L shape and blue is front
  else if (cubeArray[8][4] == 'y' && cubeArray[1][4] == 'y'){
    BackRight(cubeArray);
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BackLeft(cubeArray);
    solveArray[3] = 1;
    return;
  }
  //L shape and orange is front
  else if (cubeArray[1][4] == 'y' && cubeArray[9][4]){
    FrontRight(cubeArray);
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    FrontRight(cubeArray);
    solveArray[3] = 1;
    return;
  }
  // Line blue and green are in the spot
  else if (cubeArray[1][4] == 'y' && cubeArray[13][4] == 'y'){
    RightRight(cubeArray);
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    solveArray[3] = 1;
    return;
  }
  // Line orange and red are in the right spot
  else if (cubeArray[8][4] == 'y' && cubeArray[9][4] == 'y'){
    FrontRight(cubeArray);
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    solveArray[3] = 1;
    return;
  }
  // No shape, so dot, we apply the algorithm once and come back in the function (because it's nog solved)
  else {
    FrontRight(cubeArray);
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    return;
  }
}

void UpperEdges(){
  // Set the yellow edges in the right position

  // We first check which edges are already in the right position
  if (cubeArray[1][0] == 'g'){
    upperArray[0] = 1;
  }
  else {
    upperArray[0] = 0;
  }
  if (cubeArray[8][1] == 'o'){
    upperArray[1] = 1;
  }
  else {
    upperArray[1] = 0;
  }
  if (cubeArray[9][2] == 'r'){
    upperArray[2] = 1;
  }
  else {
    upperArray[2] = 0;
  }
  if (cubeArray[13][5] == 'b'){
    upperArray[3] = 1;
  }
  else {
    upperArray[3] = 0;
  }

  // If all edges are in the right position already we leave the function
  if (upperArray[0] == 1 && upperArray[1] == 1 && upperArray[2] == 1 && upperArray[3] == 1){
    solveArray[4] = 1;
    return;
  }

  // There are always 2 edges in the right relative position, but the layer itself can not be in the right orientation
  // This results in either 1 or 0 edges are in the absolute right position
  // We rotate the layer till we find a configuration with two edges in the right position
  else if (upperArray[0] == 0 && upperArray[1] == 0 && upperArray[2] == 0 && upperArray[3] == 0){
    BottomRight(cubeArray);
    return;
  }
  else if (upperArray[0] == 1 && upperArray[1] == 0 && upperArray[2] == 0 && upperArray[3] == 0){
    BottomRight(cubeArray);
    return;
  }
  else if (upperArray[0] == 0 && upperArray[1] == 1 && upperArray[2] == 0 && upperArray[3] == 0){
    BottomRight(cubeArray);
    return;
  }
  else if (upperArray[0] == 0 && upperArray[1] == 0 && upperArray[2] == 1 && upperArray[3] == 0){
    BottomRight(cubeArray);
    return;
  }
  else if (upperArray[0] == 0 && upperArray[1] == 0 && upperArray[2] == 0 && upperArray[3] == 1){
    BottomRight(cubeArray);
    return;
  }
  else if (upperArray[0] == 0 && upperArray[1] == 0 && upperArray[2] == 0 && upperArray[3] == 0){
    BottomRight(cubeArray);
    return;
  }
  // For every combination of the correct edges we write an algorithm
  // If the correct edges are on the opposite sides we apply the algorithm once and leave the function
  // By applying the algorithm once we assure that the next time we enter the function the correct edges will be
  // on adjacent sides of the cube. From this position we can solve the upper edges with one algorithm
  else if (upperArray[0] == 1 && upperArray[1] == 1 && upperArray[2] == 0 && upperArray[3] == 0){
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    solveArray[4] = 1;
    return;
  }
  else if (upperArray[0] == 1 && upperArray[1] == 0 && upperArray[2] == 0 && upperArray[3] == 1){
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    return;
  }
  else if (upperArray[0] == 1 && upperArray[1] == 0 && upperArray[2] == 1 && upperArray[3] == 0){
    RightRight(cubeArray);
    BottomRight(cubeArray);
    RightLeft(cubeArray);
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    RightLeft(cubeArray);
    BottomRight(cubeArray);
    solveArray[4] = 1;
    return;
  }
  else if (upperArray[0] == 0 && upperArray[1] == 1 && upperArray[2] == 1 && upperArray[3] == 0){
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    return;
  }
  else if (upperArray[0] == 0 && upperArray[1] == 1 && upperArray[2] == 0 && upperArray[3] == 1){
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    LeftLeft(cubeArray);
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    LeftLeft(cubeArray);
    BottomRight(cubeArray);
    solveArray[4] = 1;
    return;
  }
  else if (upperArray[0] == 0 && upperArray[1] == 0 && upperArray[2] == 1 && upperArray[3] == 1){
    BackRight(cubeArray);
    BottomRight(cubeArray);
    BackLeft(cubeArray);
    BottomRight(cubeArray);
    BackRight(cubeArray);
    BottomRight(cubeArray);
    BottomRight(cubeArray);
    BackLeft(cubeArray);
    BottomRight(cubeArray);
    solveArray[4] = 1;
    return;
  }
}

void UpperCorners(){
  // Set the upper corners in the right positions

  // First check if the corners are accidentally already in the right spot
  // A corner can have 3 orientations so we check all three for every corner
  if (cubeArray[0][4] == 'y' && cubeArray[0][1] == 'o' && cubeArray[0][0] == 'g'
  || cubeArray[0][4] =='g' && cubeArray[0][1] == 'y' && cubeArray[0][0] == 'o'
  || cubeArray[0][4] == 'o' && cubeArray[0][1] == 'g' && cubeArray[0][0] == 'y'){
    upperCorner[0] = 1;
  }
  else {
    upperCorner[0] = 0;
  }
  if (cubeArray[2][4] == 'g' && cubeArray[2][0] == 'r' && cubeArray[2][2] == 'y'
  || cubeArray[2][4] == 'r' && cubeArray[2][0] == 'y' && cubeArray[2][2] == 'g'
  || cubeArray[2][4] == 'y'  && cubeArray[2][0] == 'g' && cubeArray[2][2] == 'r'){
    upperCorner[1] = 1;
  }
  else {
    upperCorner[1] = 0;
  }
  if (cubeArray[12][4] == 'y' && cubeArray[12][1] == 'o' && cubeArray[12][5] == 'b'
  || cubeArray[12][4] ==  'b' && cubeArray[12][1] == 'y' && cubeArray[12][5] == 'o'
  || cubeArray[12][4] == 'o' && cubeArray[12][1] == 'b' && cubeArray[12][5] == 'y'){
    upperCorner[2] = 1;
  }
  else {
    upperCorner[2] = 0;
  }
  if (cubeArray[14][4] == 'r' && cubeArray[14][5] == 'y' && cubeArray[14][2] == 'b'
  || cubeArray[14][4] == 'b' && cubeArray[14][5] == 'r' && cubeArray[14][2] == 'y'
  || cubeArray[14][4] == 'y' && cubeArray[14][5] == 'b' && cubeArray[14][2] == 'r'){
    upperCorner[3] = 1;
  }
  else {
    upperCorner[3] = 0;
  }

  if (upperCorner[0] == 1 && upperCorner[1] == 1 && upperCorner[2] == 1 && upperCorner[3] == 1){
    solveArray[5] = 1;
    return;
  }
  else if (upperCorner[0] == 0 && upperCorner[1] == 0 && upperCorner[2] == 0 && upperCorner[3] == 0){
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomRight(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    RightRight(cubeArray);
    return;
  }
  else if (upperCorner[0] == 1){
    BottomRight(cubeArray);
    LeftRight(cubeArray);
    BottomLeft(cubeArray);
    RightLeft(cubeArray);
    BottomRight(cubeArray);
    LeftLeft(cubeArray);
    BottomLeft(cubeArray);
    RightRight(cubeArray);
    return;
  }
  else if (upperCorner[1] == 1){
    BottomRight(cubeArray);
    FrontRight(cubeArray);
    BottomLeft(cubeArray);
    BackLeft(cubeArray);
    BottomRight(cubeArray);
    FrontLeft(cubeArray);
    BottomLeft(cubeArray);
    BackRight(cubeArray);
    return;
  }
  else if (upperCorner[2] == 1){
    BottomRight(cubeArray);
    BackRight(cubeArray);
    BottomLeft(cubeArray);
    FrontLeft(cubeArray);
    BottomRight(cubeArray);
    BackLeft(cubeArray);
    BottomLeft(cubeArray);
    FrontRight(cubeArray);
    return;
  }
  else if (upperCorner[3] == 1){
    BottomRight(cubeArray);
    RightRight(cubeArray);
    BottomLeft(cubeArray);
    LeftLeft(cubeArray);
    BottomRight(cubeArray);
    RightLeft(cubeArray);
    BottomLeft(cubeArray);
    LeftRight(cubeArray);
    return;
  }
}

void UpperCorners2(){
  // After the yellow corners are in the correct position they can in either of three
  // orientations. In this function we put them in the right orientation en thereby 
  // solving the cube.
  
  // Depending on which side the yellow side is facing the algorithm is applied 0, 2 or 4 times.
  // We first determine which side the yellow side is facing and put in an array how many times we
  // should do the algorithm.
  
  if (cubeArray[0][4] == 'y'){
    upperCorner2[0] = 1;
    cornerTwists[0] = 0;
  }
  else if (cubeArray[0][1] == 'y'){
    upperCorner2[0] = 0;
    cornerTwists[0] = 2;
  }
  else if (cubeArray[0][0] == 'y'){
    upperCorner2[0] = 0;
    cornerTwists[0] = 4;
  }
  if (cubeArray[2][4] == 'y'){
    upperCorner2[1] = 1;
    cornerTwists[1] = 0;
  }
  else if (cubeArray[2][0] == 'y'){
    upperCorner2[1] = 0;
    cornerTwists[1] = 2;
  }
  else if (cubeArray[2][2] == 'y'){
    upperCorner2[1] = 0;
    cornerTwists[1] = 4;
  }
  if (cubeArray[12][4] == 'y'){
    upperCorner2[2] = 1;
    cornerTwists[2] = 0;
  }
  else if (cubeArray[12][5] == 'y'){
    upperCorner2[2] = 0;
    cornerTwists[2] = 2;
  }
  else if (cubeArray[12][1] == 'y'){
    upperCorner2[2] = 0;
    cornerTwists[2] = 4;
  }
  if (cubeArray[14][4] == 'y'){
   upperCorner2[3] = 1;
   cornerTwists[3] = 0;
  }
  else if (cubeArray[14][1] == 'y'){
    upperCorner2[3] = 0;
    cornerTwists[3] = 2;
  }
  else if (cubeArray[14][5] == 'y'){
    upperCorner2[3] = 0;
    cornerTwists[3] = 4;
  }
  
  if (upperCorner2[0] == 1 && upperCorner2[1] == 1 && upperCorner2[2] == 1 && upperCorner2[3] == 1){
    solveArray[6] = 1;
    return;
  }
  else {
    if (upperCorner2[0] == 1){
      BottomRight(cubeArray);
    }
    else {
      for (int i = 0; i < cornerTwists[0]; i++){
        LeftLeft(cubeArray);
        TopLeft(cubeArray);
        LeftRight(cubeArray);
        TopRight(cubeArray);
      }
      BottomRight(cubeArray);
    }
    if (upperCorner2[3] == 1){
      BottomRight(cubeArray);
    }
    else {
      for (int i = 0; i < cornerTwists[3]; i++){
        LeftLeft(cubeArray);
        TopLeft(cubeArray);
        LeftRight(cubeArray);
        TopRight(cubeArray);
      }
      BottomRight(cubeArray);
    }
    if (upperCorner2[2] == 1){
      BottomRight(cubeArray);
    }
    else {
      for (int i = 0; i < cornerTwists[2]; i++){
        LeftLeft(cubeArray);
        TopLeft(cubeArray);
        LeftRight(cubeArray);
        TopRight(cubeArray);
      }
      BottomRight(cubeArray);
    }
    if (upperCorner2[1] == 1){
      BottomRight(cubeArray);
      solveArray[6] = 1;
      return;
    }
    else {
      for (int i = 0; i < cornerTwists[1]; i++){
        LeftLeft(cubeArray);
        TopLeft(cubeArray);
        LeftRight(cubeArray);
        TopRight(cubeArray);
      }
      BottomRight(cubeArray);
      solveArray[6] = 1;
      return;
    }
  }
}
