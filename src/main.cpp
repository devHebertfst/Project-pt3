#include <iostream>
#include "Gerenciador.h"

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    std::cout << "Uso: ./programa <usuarios.txt> <servidores.txt>" << std::endl;
    return 1;
  }
  std::string arquivoUsuarios = argv[1];
  std::string arquivoServidores = argv[2];
  Sistema sistema;
  menu(sistema);
  for (Servidor &servidor : sistema.getAllServers())
  {
    for (Canal *canais : servidor.getCanais())
    {
      delete canais;
    }
  }
  return 0;
}