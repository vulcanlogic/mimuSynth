#ifndef _mocker_user_interface_h_
#define _mocker_user_interface_h_

// KEYBOARD

unsigned char getPeriodIndex(unsigned char key){
  unsigned char index = 0;

  switch (key){ // just a several keys, loop unrolling

    case 90:
      index = 0;
    break;

    case 83:
      index = 1;
    break;

    case 88:
      index = 2;
    break;

    case 68:
      index = 3;
    break;

    case 67:
      index = 4;
    break;

    case 86:
      index = 5;
    break;

    case 71:
      index = 6;
    break;

    case 66:
      index = 7;
    break;

    case 72:
      index = 8;
    break;

    case 78:
      index = 9;
    break;

    case 74:
      index = 10;
    break;

    case 77:
      index = 11;
    break;

    default:
      index = 12;
    break;
  }

  return index;
}

// VISUAL

// envelope shapes
static const char envelopeForm[10][14] = {
  "\\__________...",
  "/__________...",
  "\\|\\|\\|\\|\\|\\...",
  "\\__________...",
  "\\/\\/\\/\\/\\/\\...",
  "\\|         ...",
  "/|/|/|/|/|/...",
  "/----------...",
  "/\\/\\/\\/\\/\\/...",
  "/|_________..."
};

#endif
