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
    Serial.println("Upper edges solved");
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