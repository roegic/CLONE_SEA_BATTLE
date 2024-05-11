#include "../headers/network.h"
sf::TcpSocket socket;
sf::Packet  packet;
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
std::string recieve_client_coords() {
  socket.setBlocking(false);

  std::string message = "";

    if(socket.receive(packet) == sf::Socket::Done)
    {
      std::string nameRec;


      packet    >> nameRec >> message;

    }
    return message;
}

void send_client_coords() {
  socket.setBlocking(false);
  std::string message = "";

  std::getline(std::cin, message);

  if(message != "" || message.length() >= 1)
  {
    packet.clear();
    packet << "Player" << message;

    socket.send(packet);

    message = "";
  }
}