  // left top edge
  if (cubeArray[10][3] == 'w'){
    if (cubeArray[10][1] == 'o'){
      whiteleftedge = true;
    }
    else if (cubeArray[10][1] == 'r' || cubeArray[10][1] == 'b' || cubeArray[10][1] == 'g'){
      dirStr += "llllbr";
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  }
  else if (cubeArray[10][1] == 'w'){
    if (cubeArray[10][3] == 'o'){
      dirStr += "lrflblfrlrlr";
      LeftRight(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[10][3] == 'r' || cubeArray[10][3] == 'b' || cubeArray[10][3] == 'g'){
      dirStr += "lrlrbr";
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  // left back edge
  }
  if (cubeArray[15][5] == 'w'){
    if (cubeArray[15][1] == 'o'){
      dirStr += "lr";
      LeftRight(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[15][1] == 'r' || cubeArray[15][1] == 'g'){
      dirStr += "arbral";
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
      return;
    }
    else if (cubeArray[15][1] == 'b'){
      dirStr += "llbllrarar";
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      whitebackedge = true;
      return;
    }
  }
  else if (cubeArray[15][1] == 'w'){
    if (cubeArray[15][5] == 'o'){
      dirStr += "arbrallrlr";
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[15][5] == 'r' || cubeArray[15][5] == 'g'){
      dirStr += "arbral";
      BackRight(cubeArray);
      BottomRight(cubeArray);
      BackLeft(cubeArray);
      return;
    }
    else if (cubeArray[15][5] == 'b'){
      dirStr += "al";
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
  }
  // Left front edge
  if (cubeArray[3][0] == 'w'){
    if (cubeArray[3][1] == 'o'){
      dirStr += "ll";
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[3][1] == 'r' || cubeArray[3][1] == 'b'){
      dirStr += "flbrfr";
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      return;
    }
    else if (cubeArray[3][1] == 'g'){
      dirStr += "lrbrllflfl";
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      whitefrontedge = true;
      return;
    }
  }
  else if (cubeArray[3][1] == 'w'){
    if (cubeArray[3][0] == 'o'){
      dirStr += "flblfrlrlr";
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftRight(cubeArray);
      LeftRight(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[3][0] == 'r' || cubeArray[3][0] == 'b'){
      dirStr += "flbrfr";
      FrontLeft(cubeArray);
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      return;
    }
    else if (cubeArray[3][0] == 'g'){
      dirStr += "fr";
      FrontRight(cubeArray);
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
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  }
  else if (cubeArray[6][0] = 'w'){
    if (cubeArray[6][3] == 'g'){
      dirStr += "frrlbrrrfrfr";
      FrontRight(cubeArray);
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[6][3] == 'r' || cubeArray[6][3] == 'b' || cubeArray[6][3] == 'o'){
      dirStr += "frfrbr";
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  }
  // Front right edge
  if (cubeArray[4][2] == 'w'){
    if (cubeArray[4][0] == 'g'){
      dirStr += "fl";
      FrontLeft(cubeArray);
      whitefrontedge = true;
    }
    else if (cubeArray[4][0] == 'o' || cubeArray[4][0] == 'b'){
      dirStr += "frbrfl";
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      return;
    }
    else if (cubeArray[4][0] == 'r'){
      dirStr += "frbrflrrrr";
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
  }
  else if (cubeArray[4][0] == 'w'){
    if (cubeArray[4][2] == 'g'){
      dirStr += "rlblrrflfl";
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[4][2] == 'r'){
      dirStr += "rr";
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[4][2] == 'b' || cubeArray[4][2] == 'o'){
      dirStr += "rlbrrr";
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
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
      RightRight(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  }
  else if (cubeArray[11][2] == 'w'){
    if (cubeArray[11][3] == 'r'){
      dirStr += "rlfrbrflrrrr";
      RightLeft(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[11][3] == 'g' || cubeArray[11][3] == 'b' || cubeArray[11][3] == 'o'){
      dirStr += "rlrlbr";
      RightLeft(cubeArray);
      RightLeft(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  }
  // back right edge
  if (cubeArray[16][5] == 'w'){
    if (cubeArray[16][2] == 'r'){
      dirStr += "rl";
      RightLeft(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[16][2] == 'g' || cubeArray[16][2] == 'o'){
      dirStr += "rrarrl";
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      return;
    }
    else if (cubeArray[16][2] == 'b'){
      dirStr += "rrbrrlarar";
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      whitebackedge = true;
      return;
    }
  }
  else if (cubeArray[16][2] == 'w'){
    if (cubeArray[16][5] == 'r'){
      dirStr += "alblbrrrrr";
      BackLeft(cubeArray);
      BottomLeft(cubeArray);
      BackRight(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[16][5] == 'g' || cubeArray[16][5] == 'o'){
      dirStr += "albrar";
      BackLeft(cubeArray);
      BottomRight(cubeArray);
      BackRight(cubeArray);
      return;
    }
    else if (cubeArray[16][5] == 'b'){
      dirStr += "ar";
      BackRight(cubeArray);
      whitebackedge = true;
      return;
    }
  }
  // Top back edge
  if (cubeArray[18][3] == 'w'){
    if (cubeArray[18][5] == 'b'){
      whitebackedge = true;
    }
    else if (cubeArray[18][5] == 'g' || cubeArray[18][5] == 'r' || cubeArray[18][5] == 'o'){
      dirStr += "alalbr";
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  }
  else if (cubeArray[18][5] = 'w'){
    if (cubeArray[18][3] == 'b'){
      dirStr += "arllbllralal";
      BackRight(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[18][3] == 'g' || cubeArray[18][3] == 'o' || cubeArray[18][3] == 'r'){
      dirStr += "alalbr";
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      BottomRight(cubeArray);
      return;
    }
  }
  // Front bottom edge
  if (cubeArray[1][4] == 'w'){
    if (cubeArray[1][0] == 'g'){
      dirStr += "frfr";
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[1][0] == 'o'){
      dirStr += "blllll";
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[1][0] == 'b'){
      dirStr += "blblalal";
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[1][0] == 'r'){
      dirStr += "brrlrl";
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      RightLeft(cubeArray);
      whiterightedge = true;
      return;
    }
  }
  else if (cubeArray[1][0] == 'w'){
    if (cubeArray[1][4] == 'g'){
      dirStr += "flrlblrrflfl";
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[1][4] == 'o'){
      dirStr += "blllflblfrllll";
      BottomLeft(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[1][4] == 'b'){
      dirStr += "blblalllbllralal";
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[1][4] == 'r'){
      dirStr += "brrrfrbrflrrrr";
      BottomRight(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
  }
  // Bottom right edge
  if (cubeArray[9][4] == 'w'){
    if (cubeArray[9][2] == 'r'){
      dirStr += "rrrr";
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[9][2] == 'g'){
      dirStr += "blflfl";
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[9][2] == 'b'){
      dirStr += "brarar";
      BottomRight(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[9][2] == 'o'){
      dirStr += "brbrllll";
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
  }
  else if (cubeArray[9][2] == 'w'){
    if (cubeArray[9][4] == 'r'){
      dirStr += "rrfrbrflrrrr";
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[9][4] == 'b'){
      dirStr += "brarrrbrrlarar";
      BottomRight(cubeArray);
      BackRight(cubeArray);
      RightRight(cubeArray);
      BottomRight(cubeArray);
      RightLeft(cubeArray);
      BackRight(cubeArray);
      BackRight(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[9][4] == 'o'){
      dirStr += "brbrllflblfrllll";
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[9][4] == 'g'){
      dirStr += "blflrlblrrflfl";
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      whitefrontedge = true;
      return;
    }
  }
  // bottom back edge
  else if (cubeArray[13][4] == 'w'){
    if (cubeArray[13][5] == 'b'){
      dirStr += "alal";
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[13][5] == 'g'){
      dirStr += "blblflfl";
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[13][5] == 'r'){
      dirStr += "blrrrr";
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[13][5] == 'o'){
      dirStr += "brllll";
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
  }
  else if (cubeArray[13][5] == 'w'){
    if (cubeArray[13][4] == 'b'){
      dirStr += "alllbllralal";
      BackLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[13][4] == 'o'){
      dirStr += "brllflblfrllll";
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[13][4] == 'r'){
      dirStr += "blrrfrbrflrrrr";
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[13][4] == 'g'){
      dirStr += "blblflrlblrrfrfr";
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      whitefrontedge = true;
      return;
    }
  }
  // Bottom left edge
  if (cubeArray[8][4] == 'w'){
    if (cubeArray[8][1] == 'o'){
      dirStr += "llll";
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[8][1] == 'b'){
      dirStr += "blalal";
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
    else if (cubeArray[8][1] == 'r'){
      dirStr += "blblrrrr";
      BottomLeft(cubeArray);
      BottomLeft(cubeArray);
      RightRight(cubeArray);
      RightRight(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[8][1] == 'g'){
      dirStr += "brfrfr";
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      FrontRight(cubeArray);
      whitefrontedge = true;
      return;
    }
  }
  else if (cubeArray[8][1] == 'w'){
    if (cubeArray[8][4] == 'o'){
      dirStr += "llflblfrllll";
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      BottomLeft(cubeArray);
      FrontRight(cubeArray);
      LeftLeft(cubeArray);
      LeftLeft(cubeArray);
      whiteleftedge = true;
      return;
    }
    else if (cubeArray[8][4] == 'g'){
      dirStr += "brfrlrbrllflfl";
      BottomRight(cubeArray);
      FrontRight(cubeArray);
      LeftRight(cubeArray);
      BottomRight(cubeArray);
      LeftLeft(cubeArray);
      FrontLeft(cubeArray);
      FrontLeft(cubeArray);
      whitefrontedge = true;
      return;
    }
    else if (cubeArray[8][4] == 'r'){
      dirStr += "brbrrrfrbrflrlrl";
      BottomRight(cubeArray);
      BottomRight(cubeArray);
      RightRight(cubeArray);
      FrontRight(cubeArray);
      BottomRight(cubeArray);
      FrontLeft(cubeArray);
      RightLeft(cubeArray);
      RightLeft(cubeArray);
      whiterightedge = true;
      return;
    }
    else if (cubeArray[8][4] == 'b'){
      dirStr += "blalllbllralal";
      BottomLeft(cubeArray);
      BackLeft(cubeArray);
      LeftLeft(cubeArray);
      BottomLeft(cubeArray);
      LeftRight(cubeArray);
      BackLeft(cubeArray);
      BackLeft(cubeArray);
      whitebackedge = true;
      return;
    }
  }