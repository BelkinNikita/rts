

void runUdpServer(unsigned short port)
{
    // Create a socket to receive a message from anyone
    sf::UdpSocket socket;

    // Listen to messages on the specified port
    std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;

    // Wait for a message
    char in[128];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short senderPort;
    if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
        return;
    std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;

    // Send an answer to the client
    const char out[] = "Hi, I'm the server";
    if (socket.send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
}


////////////////////////////////////////////////////////////
/// Send a message to the server, wait for the answer
///
////////////////////////////////////////////////////////////
void runUdpClient(unsigned short port)
{
    // Ask for the server address
    sf::IpAddress server;
    do
    {
        std::cout << "Type the address or name of the server to connect to: ";
        std::cin >> server;
    } while (server == sf::IpAddress::None);

    // Create a socket for communicating with the server
    sf::UdpSocket socket;

    // Send a message to the server
    const char out[] = "Hi, I'm a client";
    if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;

    // Receive an answer from anyone (but most likely from the server)
    char in[128];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short senderPort;
    if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
        return;
    std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;
}


void runNetwork()
{
    char who;
    std::cout << "Do you want to be a server (s) or a client (c) ? ";
    std::cin >> who;

    if (who == 's')
        runUdpServer(50001);
    else if (who == 'c')
        runUdpClient(50001);
    else
    {
        std::cout << "Unknown option";
    }
}
class Network
{


    };

class Server : public Network{};

class Client : public Network{};
