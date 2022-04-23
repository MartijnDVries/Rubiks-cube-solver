// make an test array for the cube each element contains six elements which 
// represent the colors of that cubicle in the order
// front, left, right, top, bottom, back
// g = green o = orange w = white y = yellow r = red and - = black
#include <string.h>

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("CUBEARRAY");
  Serial.println();
  for (int i = 0; i < 20; i ++){
    Serial.print("Blok ");
    Serial.print(i);
    Serial.print(" ");
    for (int k = 0; k < 6; k++){
      Serial.print(cubeArray[i][k]);
    }
    Serial.println();
  }
  RightRight(cubeArray);
  Serial.println(cubeArray[0]);
}

void loop() {
  // put your main code here, to run repeatedly:


}

void FrontRight(char Array[][6]) {
  // Turn the front of the cube right
  char orgColour = '-';
  char orgArray[6]= {};
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

void RightRight(char Array[][6]){
  // Make a conversion array 
  char orgColour = '-';
  char orgArray[6]= {};
  char convArray[8][6]= {{'-','-','-','-','-','-'}, 
  {'-','-','-','-','-','-'},
  {'-','-','-','-','-','-'},
  {'-','-','-','-','-','-'},
  {'-','-','-','-','-','-'},
  {'-','-','-','-','-','-'},
  {'-','-','-','-','-','-'}};
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
