////////////////////////////////////////////////////////////
/// Send a message to the server, wait for the answer
///
////////////////////////////////////////////////////////////
void runUdpClient(unsigned short port)
{
    // Ask for the server address
    std::optional<sf::IpAddress> server;
    do
    {
        std::cout << "Type the address or name of the server to connect to: ";
        std::cin >> server;
    } while (!server.has_value());

    // Create a socket for communicating with the server
    sf::UdpSocket socket;

    // Send a message to the server
    static constexpr std::string_view out = "Hi, I'm a client";
    if (socket.send(out.data(), out.size(), server.value(), port) != sf::Socket::Status::Done)
        return;
    std::cout << "Message sent to the server: " << std::quoted(out.data()) << std::endl;

    // Receive an answer from anyone (but most likely from the server)
    std::array<char, 128>        in{};
    std::size_t                  received = 0;
    std::optional<sf::IpAddress> sender;
    unsigned short               senderPort = 0;
    if (socket.receive(in.data(), in.size(), received, sender, senderPort) != sf::Socket::Status::Done)
        return;
    std::cout << "Message received from " << sender.value() << ": " << std::quoted(in.data()) << std::endl;
}