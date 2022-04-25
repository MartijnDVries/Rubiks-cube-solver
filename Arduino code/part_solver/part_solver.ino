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
  char test_str[] = "gr--w-g---w-y-g-r-yo----b-r---bw-o--o--g--b-ry---g--y---b-y--r-w----ry---y--bo----bo--w-rb-b---w--o--w-w-o-g---g-r--yo-g";

  // set up variables for conversion(rotation / position) of the cubicles
  char orgColour = '-';
  char orgArray[6]= {};
  char convArray[8][6]= {{}};
 
  

  // Set up variables for the solver
    // White Cross
  bool WhiteCrossSolved = false;
  bool whitefrontedge = false;
  bool whiteleftedge = false;
  bool whiterightedge = false;
  bool whitebackedge = false;

  // Set up an directions array
  String dirStr = String();

void setup() {
  stepper_1.setMaxSpeed(200);
  stepper_2.setMaxSpeed(200);
  stepper_1.setAcceleration(200);
  stepper_2.setAcceleration(200);
  stepper_3.setMaxSpeed(200);
  stepper_4.setMaxSpeed(200);
  stepper_3.setAcceleration(200);
  stepper_4.setAcceleration(200);
  stepper_5.setMaxSpeed(200);
  stepper_6.setMaxSpeed(200);
  stepper_5.setAcceleration(200);
  stepper_6.setAcceleration(200);
  // put your setup code here, to run once:
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
  Serial.println("cube array before changes");
  Serial.println(cubeArray[0]);
  // do changes
  setupcubeArray(test_str);
  while (WhiteCrossSolved != true){
    Serial.println("solving white cross");
    WhiteCross(cubeArray);
  }
  Serial.println(dirStr);
  // print cubearray after changes to test with python code
  Serial.println("cube array after solve");
  Serial.println(cubeArray[0]);

  for (int i = 0; i <= dirStr.length(); i++){
    if (i % 2 == 0){
      if (dirStr[i] == 'l'){
        if (dirStr[i+1] == 'l'){
          stepper_1.move(-50);
          stepper_1.runToPosition();
        }
        else if (dirStr[i+1] == 'r'){
          stepper_1.move(50);
          stepper_1.runToPosition();
        }
      }
      else if (dirStr[i] == 'r'){
        if (dirStr[i+1] == 'l'){
          stepper_2.move(-50);
          stepper_2.runToPosition();
        }
        else if (dirStr[i+1] == 'r'){
          stepper_2.move(50);
          stepper_2.runToPosition();
        }
      }
      else if (dirStr[i] == 't'){
        if (dirStr[i+1] == 'l'){
          stepper_3.move(-50);
          stepper_3.runToPosition();
        }
        else if (dirStr[i+1] == 'r'){
          stepper_3.move(50);
          stepper_3.runToPosition();
        }
      }
      else if (dirStr[i] == 'b'){
        if (dirStr[i+1] == 'l'){
          stepper_4.move(-50);
          stepper_4.runToPosition();
        }
        else if (dirStr[i+1] == 'r'){
          stepper_4.move(50);
          stepper_4.runToPosition();
        }
      }
      else if (dirStr[i] == 'f'){
        if (dirStr[i+1] == 'l'){
          stepper_5.move(-50);
          stepper_5.runToPosition();
        }
        else if (dirStr[i+1] == 'r'){
          stepper_5.move(50);
          stepper_5.runToPosition();
        }
      }
      else if (dirStr[i] == 'a'){
        if (dirStr[i+1] == 'l'){
          stepper_6.move(-50);
          stepper_6.runToPosition();
        }
        else if (dirStr[i+1] == 'r'){
          stepper_6.move(50);
          stepper_6.runToPosition();
        }
      }
      
    }
  } 
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
}

void WhiteCross(char Array[][6]){
  // Check al edges of the cube for white edges.
  // If they are in the top, but not in the right orientatien then place it directly.
  // It they are in the top but not in the right place put them in bottom.
  // If they are in the bottom place them directly
  // By first checking the top and then chechking the bottom, we put the pieces in the right place
  // that were in the wrong spot on the top-side because we moved them to the bottom side.

  // if all edges are on the right spot the cross is solved we return without doing anything
  if (whiteleftedge == true && whitefrontedge == true && whiterightedge == true && whitebackedge == true){
    WhiteCrossSolved = true;
    return;
  }
  // left top edge
  if (cubeArray[10][3] == 'w'){
    if (cubeArray[10][1] == 'o'){
      whiteleftedge = true;
    }
    else if (cubeArray[10][1] == 'r' || cubeArray[10][1] == 'b' || cubeArray[10][1] == 'g'){
      dirStr += "llllbr";
      LeftLeft(Array);
      LeftLeft(Array);
      BottomRight(Array);
      WhiteCrossSolved = true;
      return;
    }
  }
  else if (cubeArray[10][1] == 'w'){
    if (cubeArray[10][3] == 'o'){
      dirStr += "lrflblfrlrlr";
      LeftRight(Array);
      FrontLeft(Array);
      BottomLeft(Array);
      FrontRight(Array);
      LeftRight(Array);
      LeftRight(Array);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[10][3] == 'r' || cubeArray[10][3] == 'b' || cubeArray[10][3] == 'g'){
      dirStr += "lrlrbr";
      LeftRight(Array);
      LeftRight(Array);
      BottomRight(Array);
      return;
    }
  // left back edge
  }
  if (cubeArray[15][5] == 'w'){
    if (cubeArray[15][1] == 'o'){
      dirStr += "lr";
      LeftRight(Array);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[15][1] == 'r' || cubeArray[15][1] == 'g'){
      dirStr += "arbral";
      BackRight(Array);
      BottomRight(Array);
      BackLeft(Array);
      return;
    }
    else if (cubeArray[15][1] == 'b'){
      dirStr += "llbllrarar";
      LeftLeft(Array);
      BottomLeft(Array);
      LeftRight(Array);
      BackRight(Array);
      BackRight(Array);
      whitebackedge = true;
      return;
    }
  }
  else if (cubeArray[15][1] == 'w'){
    if (cubeArray[15][5] == 'o'){
      dirStr += "arbrallrlr";
      BackRight(Array);
      BottomRight(Array);
      BackLeft(Array);
      LeftRight(Array);
      LeftRight(Array);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[15][5] == 'r' || cubeArray[15][5] == 'g'){
      dirStr += "arbral";
      BackRight(Array);
      BottomRight(Array);
      BackLeft(Array);
      return;
    }
    else if (cubeArray[15][5] == 'b'){
      dirStr += "al";
      BackLeft(Array);
      whitebackedge = true;
      return;
    }
  }
  // Left front edge
  if (cubeArray[3][0] == 'w'){
    if (cubeArray[3][1] == 'o'){
      dirStr += "ll";
      LeftLeft(Array);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[3][1] == 'r' || cubeArray[3][1] == 'b'){
      dirStr += "flbrfr";
      FrontLeft(Array);
      BottomRight(Array);
      FrontRight(Array);
      return;
    }
    else if (cubeArray[3][1] == 'g'){
      dirStr += "lrbrllflfl";
      LeftRight(Array);
      BottomRight(Array);
      LeftLeft(Array);
      FrontLeft(Array);
      FrontLeft(Array);
      whitefrontedge = true;
      return;
    }
  }
  else if (cubeArray[3][1] == 'w'){
    if (cubeArray[3][0] == 'o'){
      dirStr += "flblfrlrlr";
      FrontLeft(Array);
      BottomLeft(Array);
      FrontRight(Array);
      LeftRight(Array);
      LeftRight(Array);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[3][0] == 'r' || cubeArray[3][0] == 'b'){
      dirStr += "flbrfr";
      FrontLeft(Array);
      BottomRight(Array);
      FrontRight(Array);
      return;
    }
    else if (cubeArray[3][0] == 'g'){
      dirStr += "fr";
      FrontRight(Array);
      whitefrontedge = true;
      return;
    }
  }
  // front top edge
  if (cubeArray[6][3] == 'w'){
    if (cubeArray[6][0] == 'g'){
      whitefrontedge = true;
    }
    else if (cubeArray[6][0] == 'r' || cubeArray[6][0] == 'b' || cubeArray[6][0] == 'o'){
      dirStr += "frfrbr";
      FrontRight(Array);
      FrontRight(Array);
      BottomRight(Array);
      return;
    }
  }
  else if (cubeArray[6][0] = 'w'){
    if (cubeArray[6][3] == 'g'){
      dirStr += "frrlbrrrfrfr";
      FrontRight(Array);
      RightLeft(Array);
      BottomRight(Array);
      RightRight(Array);
      FrontRight(Array);
      FrontRight(Array);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[6][3] == 'r' || cubeArray[6][3] == 'b' || cubeArray[6][3] == 'o'){
      dirStr += "frfrbr";
      FrontRight(Array);
      FrontRight(Array);
      BottomRight(Array);
      return;
    }
  }
  // Front right edge
  if (cubeArray[4][2] == 'w'){
    if (cubeArray[4][0] == 'g'){
      dirStr += "fl";
      FrontLeft(Array);
      whitefrontedge = true;
    }
    else if (cubeArray[4][0] == 'o' || cubeArray[4][0] == 'b'){
      dirStr += "frbrfl";
      FrontRight(Array);
      BottomRight(Array);
      FrontLeft(Array);
      return;
    }
    else if (cubeArray[4][0] == 'r'){
      dirStr += "frbrflrrrr";
      FrontRight(Array);
      BottomRight(Array);
      FrontLeft(Array);
      RightRight(Array);
      RightRight(Array);
      whiterightedge = true;
      return;
    }
  }
  else if (cubeArray[4][0] == 'w'){
    if (cubeArray[4][2] == 'g'){
      dirStr += "rlblrrflfl";
      RightLeft(Array);
      BottomLeft(Array);
      RightRight(Array);
      FrontLeft(Array);
      FrontLeft(Array);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[4][2] == 'r'){
      dirStr += "rr";
      RightRight(Array);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[4][2] == 'b' || cubeArray[4][2] == 'o'){
      dirStr += "rlbrrr";
      RightLeft(Array);
      BottomRight(Array);
      RightRight(Array);
      return;
    }
  }
  // Top right egde
  if (cubeArray[11][3] == 'w'){
    if (cubeArray[11][2] == 'r'){
      whiterightedge = true;
    }
    else if (cubeArray[11][2] == 'g' || cubeArray[11][2] == 'o' || cubeArray[11][2] == 'b'){
      dirStr += "rrrrbr";
      RightRight(Array);
      RightRight(Array);
      BottomRight(Array);
      return;
    }
  }
  else if (cubeArray[11][2] == 'w'){
    if (cubeArray[11][3] == 'r'){
      dirStr += "rlfrbrflrrrr";
      RightLeft(Array);
      FrontRight(Array);
      BottomRight(Array);
      FrontLeft(Array);
      RightRight(Array);
      RightRight(Array);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[11][3] == 'g' || cubeArray[11][3] == 'b' || cubeArray[11][3] == 'o'){
      dirStr += "rlrlbr";
      RightLeft(Array);
      RightLeft(Array);
      BottomRight(Array);
      return;
    }
  }
}
