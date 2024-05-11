#include <SFML/Network.hpp>
#include <iostream>
#include <string>

void start_multiplayer_game();
char create_connection();
void get_players_message();
std::pair<int,int> recieve_client_coords();
void send_client_coords(int x, int y);