#include "SelectTcp.hpp"

void Usage(std::string proc)
{
  std::cout << "Usage" << proc << "port" << std::endl; 
}

int main(int argc,char* argv[])
{
  std::cout << sizeof(fd_set)*8 << std::endl;
  if(argc != 2)
  {
    Usage(argv[0]);
    exit(1);
  }
  int port = atoi(argv[1]);
  Server *sp = new Server(port);

  sp->InitServer();
  sp->Start();

  delete sp;
  return 0;
}
