#include <list>

sf::UdpSocket socket;
sf::IpAddress serverIP = "192.168.3.2";
sf::IpAddress anotherPlayerIP = "192.168.3.2";
std::size_t received;
sf::IpAddress sender;
unsigned short senderPort;
void interpreter(const char* in);


class Network
{
public:
    virtual void run(bool AreyouHost)
    {
        if (AreyouHost)
        {
            if (socket.bind(50001) != sf::Socket::Done)
                return;
            std::cout << "Server is listening to port " << 50001 << ", waiting for a message... " << std::endl;
            char in[256];
            if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
                return;
            std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;
            const char out[] = "Hi, I'm the server";
            if (socket.send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
                return;
            std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
            senderPort = senderPort;
            sender = sender;
        }
        else
        {
            sender = anotherPlayerIP;
            const char out[] = "Hi, I'm a client";
            if (socket.send(out, sizeof(out), sender, 50001) != sf::Socket::Done)
                return;
            std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
            char in[256];
            if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
                return;
            std::cout << "Received: " << in << "\"" << std::endl;
        }
        std::cout << "connected" << "\n";
        std::cout << senderPort << "\n";
        std::cout << sender << "\n";
        listen(sender, senderPort);

    }
    virtual void listen(sf::IpAddress sender, unsigned short senderPort)
    {
        char in[256];
        std::cout << "Server works " << std::endl;
        std::cout << senderPort << "\n";
        std::cout << sender << "\n";
        if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
            return;
        std::cout << "\n Message received from client " << sender << ": " << in << "\n" << std::endl;
        interpreter(in);
        listen(sender, senderPort);
    }
    virtual void send(std::string out)
    {
        if (!youAreHost) { sender = 
        anotherPlayerIP; 
        senderPort = 50001;
        }
        std::cout << "sent" << "\n";
        std::cout << senderPort << "\n";
        std::cout << sender << "\n";
        const char* x = out.c_str();
        if (socket.send(x, 256, sender, senderPort) != sf::Socket::Done)
            return;
    }

};



void interpreter(const char* in)
{
    std::cout << in << "\n";
    int unitID = 0;
    std::string command;
    switch (char(in[0]))
    {
    case ('m'):
        command = "move";
        std::cout << "Command: " << command << "\n";
        int player = in[1] - 48;
        std::cout << "Player: " << player << "\n";
        int i = 2;
        int id = 0;
        while (in[i] != ' ')
        {
            id = id * 10 + (in[i] - 48);
            ++i;
        }
        ++i;
        std::cout << "ID: " << id << "\n";
        int x_pos = 0;
        while (in[i] != ' ')
        {
            x_pos = x_pos * 10 + (in[i] - 48);
            ++i;
        }   
        ++i;
        std::cout << "X: " << x_pos << "\n";
        int y_pos = 0;
        while (in[i] != ' ')
        {
            y_pos = y_pos * 10 + (in[i] - 48);
            ++i;
        }
        std::cout << "Y: " << y_pos << "\n";
        returnAllunitsOfPlayer(player)[id] -> commandToMove(x_pos, y_pos);
    }
}




Network* network = new Network;
static void runNetwork()
{
    
    char who;
    std::cout << "Do you want to be a server (s) or a client (c) ? ";
    std::cin >> who;
    if (who == 's')
    {
        youAreHost = true;
        network->run(bool (true));
        //server->run();
    }
    else if (who == 'c')
    {
        youAreHost = false;
        network->run(bool (false));
        //client->run();
    }
    else std::cout << "Unknown option";
    
}




