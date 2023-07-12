#include "Sistema.h"
#include <fstream>
#include <algorithm>
#include <limits>

Sistema::Sistema() {}

void Sistema::adicionarServidor(Servidor server)
{
  servidores.push_back(server);
}

void Sistema::removerServidor(std::string nome)
{

  for (Canal *canais : acessarServidor(nome)->getCanais())
  {
    delete canais;
  }
  servidores.erase(std::remove_if(servidores.begin(), servidores.end(), [&nome](Servidor &servidor)
                                  { return servidor.getNome() == nome; }),
                   servidores.end());
}

void Sistema::adicionarUsuario(Usuario user)
{
  usuarios.push_back(user);
}

Usuario *Sistema::verificarUsuario(std::string email)
{
  for (auto it = usuarios.begin(); it != usuarios.end(); ++it)
  {
    if (it->getEmail() == email)
    {
      return &(*it);
    }
  }

  return nullptr;
}

Servidor *Sistema::acessarServidor(std::string server)
{
  for (auto it = servidores.begin(); it != servidores.end(); ++it)
  {
    if (it->getNome() == server)
    {
      return &(*it);
    }
  }

  return nullptr;
}

void Sistema::setUsuarioLogado(int userLogado)
{
  this->userLogadoId = userLogado;
}

int Sistema::getUsuarioLogado()
{
  return userLogadoId;
}

void Sistema::imprimirServidores()
{
  if (servidores.size() != 0)
  {
    for (auto it = servidores.begin(); it != servidores.end(); ++it)
    {
      std::cout << it->getNome() << std::endl;
    }
  }
  else
  {
    std::cout << "Não há servidores cadastrados no momento" << std::endl;
  }
}

void Sistema::imprimirParticipantes(std::string nome)
{
  Servidor *server = acessarServidor(nome);
  if (server != nullptr)
  {
    for (int participantId : server->getPartipantesIDs())
    {
      Usuario *participant = nullptr;
      for (auto it = usuarios.begin(); it != usuarios.end(); ++it)
      {
        if (it->getId() == participantId)
        {
          participant = &(*it);
          break;
        }
      }
      if (participant != nullptr)
      {
        std::cout << participant->getNome() << std::endl;
      }
    }
  }
}

void Sistema::setServerVizualizado(std::string nome)
{
  this->serverVisualizado = nome;
}

std::string Sistema::getServerVizualizado()
{
  return serverVisualizado;
}

Usuario *Sistema::getUsuario(int id)
{
  for (auto it = usuarios.begin(); it != usuarios.end(); ++it)
  {
    if (it->getId() == id)
    {
      return &(*it);
    }
  }

  return nullptr;
}

int Sistema::getTamUsuarios()
{
  return usuarios.size();
}

std::string Sistema::getCanalVizualizado()
{
  return channelVizualizado;
}

void Sistema::setCanalVizualizado(std::string nome)
{
  this->channelVizualizado = nome;
}

void Sistema::imprimirMensagens()
{
  Canal *channel = acessarServidor(getServerVizualizado())->acessoCanal(getCanalVizualizado());
  CanalTexto *canalTexto = dynamic_cast<CanalTexto *>(channel);
  if (canalTexto != nullptr)
  {
    const auto &mensagens = canalTexto->getMensagens();
    if (mensagens.empty())
    {
      std::cout << "Sem mensagens cadastradas no momento" << std::endl;
    }
    else
    {
      for (const auto &mensagem : mensagens)
      {
        std::cout << getUsuario(mensagem.getEnviadaPor())->getNome() << mensagem.getDataHora() << ": " << mensagem.getConteudo() << std::endl;
      }
    }
  }
  else
  {
    CanalVoz *canalVoz = dynamic_cast<CanalVoz *>(channel);
    if (canalVoz != nullptr)
    {
      const Mensagem &mensagem = canalVoz->getMensagem();
      if (mensagem.getDataHora().empty() && mensagem.getConteudo().empty())
      {
        std::cout << "Sem mensagens cadastradas no momento" << std::endl;
      }
      else
      {
        std::cout << getUsuario(mensagem.getEnviadaPor())->getNome() << mensagem.getDataHora() << ": " << mensagem.getConteudo() << std::endl;
      }
    }
  }
}

std::vector<Servidor> Sistema::getAllServers()
{
  return servidores;
}

void Sistema::salvarServidores()
{
  std::ofstream arquivo("servidores.txt");

  if (arquivo.is_open())
  {
    arquivo << servidores.size() << "\n";

    for (auto &servidor : servidores)
    {
      arquivo << servidor.getIdDono() << "\n";
      arquivo << servidor.getNome() << "\n";
      arquivo << servidor.getDescricao() << "\n";
      arquivo << servidor.getCodigoConvite() << "\n";

      int numParticipantes = servidor.getPartipantesIDs().size();
      arquivo << numParticipantes << "\n";

      for (const auto &participanteId : servidor.getPartipantesIDs())
      {
        arquivo << participanteId << "\n";
      }

      int numCanais = servidor.getCanais().size();
      arquivo << numCanais << "\n";

      for (const auto &canal : servidor.getCanais())
      {
        arquivo << canal->getNome() << "\n";

        if (CanalTexto *canalTexto = dynamic_cast<CanalTexto *>(canal))
        {
          arquivo << "texto"
                  << "\n";
          const std::vector<Mensagem> &mensagens = canalTexto->getMensagens();
          int numMensagens = mensagens.size();
          arquivo << numMensagens << "\n";

          for (const auto &mensagem : mensagens)
          {
            arquivo << mensagem.getEnviadaPor() << "\n";
            arquivo << mensagem.getDataHora() << "\n";
            arquivo << mensagem.getConteudo() << "\n";
          }
        }
        else if (CanalVoz *canalVoz = dynamic_cast<CanalVoz *>(canal))
        {
          arquivo << "voz"
                  << "\n";
          const Mensagem &mensagem = canalVoz->getMensagem();
          arquivo << "1\n";

          arquivo << mensagem.getEnviadaPor() << "\n";
          arquivo << mensagem.getDataHora() << "\n";
          arquivo << mensagem.getConteudo() << "\n";
        }
      }
    }

    arquivo.close();
  }
}

void Sistema::salvarUsuarios()
{
  std::ofstream arquivo("usuarios.txt");

  if (arquivo.is_open())
  {
    arquivo << usuarios.size() << "\n";

    for (auto &usuario : usuarios)
    {
      arquivo << usuario.getId() << "\n";
      arquivo << usuario.getNome() << "\n";
      arquivo << usuario.getEmail() << "\n";
      arquivo << usuario.getSenha() << "\n";
    }

    arquivo.close();
  }
}

void Sistema::salvar()
{
  salvarServidores();
  salvarUsuarios();
}

void Sistema::carregarUsuarios()
{
  std::ifstream arquivo("usuarios.txt");
  usuarios.clear();
  int totalUsuarios;
  arquivo >> totalUsuarios;
  if (totalUsuarios == 0)
  {
    arquivo.close();
    return;
  }
  if (arquivo.is_open())
  {

    for (int i = 0; i < totalUsuarios; i++)
    {
      int id;
      std::string nome, email, senha;

      arquivo >> id;
      arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(arquivo, nome);
      std::getline(arquivo, email);
      std::getline(arquivo, senha);

      Usuario user(nome, email, senha);
      user.setId(id);

      usuarios.push_back(user);
    }

    arquivo.close();
  }
}

void Sistema::carregarServidores()
{
  std::ifstream arquivo;
  for (Servidor &ser : servidores)
  {
    for (Canal *canais : ser.getCanais())
    {
      delete canais;
    }
  }
  servidores.clear();
  arquivo.open("servidores.txt");
  int TamServers;
  arquivo >> TamServers;
  if (TamServers == 0)
  {
    arquivo.close();
    return;
  }
  int particpantes, tamCanais, mensagensSize;
  int idDono;
  std::string nome;
  std::string descricao;
  std::string codigoConvite;

  while (arquivo >> idDono)
  {
    arquivo.ignore();
    std::getline(arquivo, nome);
    std::getline(arquivo, descricao);
    std::getline(arquivo, codigoConvite);
    arquivo >> particpantes;
    arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Servidor server(nome, idDono, codigoConvite, descricao);
    for (int i = 0; i < particpantes; i++)
    {
      int id;
      arquivo >> id;
      server.adicionarParticipante(id);
    }
    arquivo >> tamCanais;
    arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string nomeCanal;
    std::string tipoCanal;
    std::string dataHora;
    std::string conteudo;
    for (int i = 0; i < tamCanais; i++)
    {
      std::getline(arquivo, nomeCanal);
      std::getline(arquivo, tipoCanal);
      arquivo >> mensagensSize;
      arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (tipoCanal == "texto")
      {

        CanalTexto canal(nomeCanal);
        for (int j = 0; j < mensagensSize; j++)
        {
          int enviadaPor;
          arquivo >> enviadaPor;
          arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::getline(arquivo, dataHora);
          std::getline(arquivo, conteudo);

          Mensagem novaMensagem(dataHora, enviadaPor, conteudo);
          canal.adicionarMensagem(novaMensagem);
        }
        server.criarCanal(tipoCanal, nomeCanal);
        CanalTexto *channel = dynamic_cast<CanalTexto *>(server.acessoCanal(nomeCanal));
        for (Mensagem &mesag : canal.getMensagens())
        {
          channel->adicionarMensagem(mesag);
        }
      }
      else if (tipoCanal == "voz")
      {
        int enviadaPor;
        arquivo >> enviadaPor;
        arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(arquivo, dataHora);
        std::getline(arquivo, conteudo);
        Mensagem ultimaMensagem(dataHora, enviadaPor, conteudo);
        server.criarCanal(tipoCanal, nomeCanal);
        CanalVoz *channel = dynamic_cast<CanalVoz *>(server.acessoCanal(nomeCanal));
        channel->setMensagem(ultimaMensagem);
      }
    }

    servidores.push_back(server);
  }
  arquivo.close();
}

void Sistema::carregar()
{
  carregarUsuarios();
  carregarServidores();
}
