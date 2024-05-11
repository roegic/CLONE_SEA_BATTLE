#pragma once

#include "../headers/game_update.h"

#include <cctype>
#include <vector>

string invalid_input = "Invalid input! Please try again";
vector<pair<string, string>> client_field;

void GetCoordinatesFire(Player &player1, Player &player2) {
  int turn = 1;
  while (true) {
    Player *selectedPlayer;
    Player *otherPlayer;
    if (turn % 2 == 0) {
      selectedPlayer = &player1;
      otherPlayer = &player2;
    } else {
      selectedPlayer = &player2;
      otherPlayer = &player1;
    }
    if (player2.IsWin()) {
      cout << "\nPlayer " << player2.GetPlayerName() << " you won!" << endl;
      break;
    }
    if (player1.IsWin()) {
      cout << "\nPlayer " << player1.GetPlayerName() << " you won!" << endl;
      break;
    }
    cout << "\nTurn: " << turn << "\nPlayer " << selectedPlayer->GetPlayerName()
         << " enter coordinates to Fire \n \n";
    otherPlayer->DrawHitFlield();

    char xc;
    char yc;
    while (true) {
      GetCoordinates(xc, yc, 1); // TODO ЭТО ПРОСТО СЕЙЧАС ЗАГЛУШКАА NEEDS FIXXX
      int x = toupper(xc) - 'A';
      int y = (yc - '0') - 1;
      if (!otherPlayer->IsHitTwice(x, y)) {
        if (otherPlayer->FireEnemy(x, y)) {
          cout << "It's a Hit!" << endl;
          turn--;
          selectedPlayer->DecHits();
        } else {
          cout << "It's a miss!" << endl;
        }
        break;
      } else {
        cout << "You are trying shoot the same square twice, try again!"
             << endl;
      }
    }
    cout << "\n";
    EnterToContinue();
    turn++;
  }
  cout << "\n";
}

void GetDirection(int &direction) {
  char charDir;
  std::vector<char> base = {'U', 'R', 'D', 'L'};
  string tempDirection;
  while (true) {
    cout << "Enter the direction (U/R/D/L): ";
    getline(cin, tempDirection);
    if (!isalpha(tempDirection[0]) || tempDirection.size() != 1) {
      cout << invalid_input << endl;
      continue;
    }
    charDir = toupper(tempDirection[0]);
    bool isValid = false;
    for (int i = 0; i < base.size(); ++i) {
      if (base[i] == charDir) {
        direction = i + 1;
        isValid = true;
        break;
      }
    }
    if (!isValid) {
      cout << invalid_input << endl;
    } else {
      break;
    }
  }
}

string recieve_player_coords(int type) {
  std::string message = "-1";
  if (type == 1) { // 1 локалка
    getline(cin, message);
  } else if (type == 2) { // хост
    message = recieve_client_coords();
  } else if (type == 3) { // клиент
    send_client_coords();
  }
  return message;
}

void GetCoordinates(char &xc, char &yc, int type) {
  cout << "Enter the coordinate [letter(A-H)][number(1-8)] (example: A1): ";
  while (true) {
    std::string xcord = recieve_player_coords(type);
    if (xcord == "-1") {
      continue;
    }
    cout << "Enter the coordinate [letter(A-H)][number(1-8)] (example: A1): ";
    string x_enter;
    for (int i = 0; i < xcord.size(); ++i) {
      if (!isspace(xcord[i])) {
        x_enter += xcord[i];
      }
    }
    if (x_enter.length() == 2) {
      if (!isalpha(x_enter[0])) {
        cout << invalid_input << endl;
      } else if (!(toupper(x_enter[0]) - 'A' < 9 &&
                   toupper(x_enter[0]) - 'A' >= 0)) {
        cout << invalid_input << endl;
      } else if (!isdigit(x_enter[1])) {
        cout << invalid_input << endl;
      } else if (x_enter[1] - '0' < 1 || x_enter[1] - '0' >= 9) {
        cout << invalid_input << endl;
      } else {
        xc = toupper(x_enter[0]);
        yc = x_enter[1];
        break;
      }
    } else {
      cout << invalid_input << endl;
    }
  }
}

void AddShips(Player &player, int type) {
  // addship for the given player object
  std::string table =
      "--------------------------------------------- \n               Add "
      "Ship\n--------------------------------------------- \n           No  "
      "Name        size\n--------------------------------------------- \n      "
      "     1   Battleship   4 \n           2   Cruiser      3 \n           3  "
      " Destroyer    2 \n           4   Submarine    1 "
      "\n--------------------------------------------- \n";
  cout << table;

  std::vector<std::string> shipName = {"Battleship", "Cruiser", "Destroyer",
                                       "Submarine"};
  std::vector<int> sizeShip = {4, 3, 2, 1};
  char x_enter;
  char y_enter;
  int direction;

  for (int i = 0; i < shipName.size(); ++i) {
    for (int j = 0; j < 5 - sizeShip[i]; ++j) {
      while (true) {
        cout << player.GetPlayerName() << " add a " << shipName[i]
             << " size: " << sizeShip[i] << endl;
        GetCoordinates(x_enter, y_enter, type);
        if (sizeShip[i] == 1) {
          direction = 2;
        } else {
          GetDirection(direction);
        }
        int x = toupper(x_enter) - 'A';
        int y = y_enter - '0' - 1;
        if (player.PlaceShip(x, y, direction, i)) {
          break;
        } else {
          cout << "The location of the ships is incorrect! \nShips should not "
                  "overlap, go beyond borders!\nPlease try again."
               << endl;
        }
      }
      cout << "\x1B[2J\x1B[H" << endl;
      player.DrawField();
      cout << "\n";
    }
  }
  cout << "All ships are added!" << endl;
  EnterToContinue();
}

void EnterToContinue() {
  cout << "Press enter to continue!";
  cin.ignore();
  cout << "\x1B[2J\x1B[H" << endl;
}
