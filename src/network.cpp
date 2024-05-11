#include "../headers/network.h"
using namespace std;
sf::TcpSocket socket;
sf::Packet  packet;
#include "../headers/player.h"
char create_connection() {
  sf::IpAddress ip = sf::IpAddress::getLocalAddress();
  char type;
  std::cout << "Enter type connecting: [j] - join, [h] - host\n";
  std::cin  >> type;
  if(type == 'h')
  {
    sf::TcpListener listener;
    listener.listen(2000);

    if(listener.accept(socket) != sf::Socket::Done)
    {
      std::cout << "Error!\n";
    }
  }
  else if(type == 'j')
  {
    if(socket.connect(ip, 2000) != sf::Socket::Done)
    {
      std::cout << "Error!\n";
    }
  }
  //socket.setBlocking(false);
  return type;
}

void start_multiplayer_game()
{
  std::string name;
  std::cout << "Введите свое имя:\n";
  std::cin >> name;

  socket.setBlocking(false);

  std::string message = "";
  sf::Packet  packet;

  while(true)
  {
    std::string message;
    std::getline(std::cin, message);


    if(message != "" || message.length() >= 1)
    {
      packet.clear();
      packet << name << message;

      socket.send(packet);

      message = "";
    }

    if(socket.receive(packet) == sf::Socket::Done)
    {
      std::string nameRec;
      std::string messageRec;

      packet    >> nameRec >> messageRec;
      std::cout << nameRec << ": " << messageRec << '\n';
    }
  }
}
pair<int,int> recieve_client_coords() {
  socket.setBlocking(false);

  std::string message = "";
  int x = -100;
  int y = -100;

    if(socket.receive(packet) == sf::Socket::Done)
    {
      std::string nameRec;


      packet >> nameRec >> x >> y;

    }
    return {x,y};
}

void send_client_coords(int x, int y) {
  socket.setBlocking(false);


    packet.clear();
    packet << "Player" << x << y;

    socket.send(packet);

    x = 0;
    y=0;
}
int recieve_client_direction() {
  socket.setBlocking(false);

  std::string message = "";
  int dir = -1;
  if(socket.receive(packet) == sf::Socket::Done)
  {
    std::string nameRec;
    packet >> nameRec >> dir;
  }
  return dir;
}
int send_client_direction(int direction) {
  socket.setBlocking(false);
  packet.clear();
  packet << "Player" << direction;

  socket.send(packet);
}