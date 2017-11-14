

#include <iostream>
#include "library/network/SocketClient.h"

using namespace std;
using namespace exploringBB;

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cout << "Incorrect usage: " << endl;
      cout << "   client server_name" << endl;
      return 2;
   }
   
   cout << "Starting EBB Temperature Client Test on : " << argv[1] << " : " << 5555 << endl;
   
   SocketClient sc(argv[1], 5555);
   
   sc.connectToServer();
   
   string message("getTemperature");
   
   cout << "Sending [" << message << "]" << endl;
   
   sc.send(message);
   
   string rec = sc.receive(1024);
   
   cout << "Received [" << rec << "]" << endl;
   cout << "End of EBB Temperature Client Test" << endl;
}
