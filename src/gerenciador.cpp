#include "Gerenciador.h"

#include <sstream>
#include <cctype>
#include "time.h"
#include <iomanip>

void menu(Sistema &sistema)
{
  std::string entrada;
  std::getline(std::cin, entrada);
  while (true)
  {
    if (entrada == "quit")
    {
      std::cout << "Saindo do concordo" << std::endl;
      break;
    }
    else if (entrada.substr(0, 11) == "create-user")
    {
      criarUsuario(sistema, entrada);
      break;
    }
    else if (entrada.substr(0, 5) == "login")
    {
      loginUsuario(sistema, entrada);
      break;
    }
    else if (entrada == "disconnect")
    {
      std::cout << "Não está conectado" << std::endl;
      menu(sistema);
      break;
    }
    else
    {
      std::cout << "Comando invalido" << std::endl;
      menu(sistema);
      break;
    }
  }
}

void criarUsuario(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, email, senha, nome;

  iss >> comando >> email >> senha;
  std::getline(iss, nome);

  if (!email.empty() && !senha.empty() && !nome.empty())
  {
    nome = nome.substr(nome.find_first_not_of(' '));
    Usuario user(nome, email, senha);

    if (sistema.verificarUsuario(user.getEmail()) == nullptr)
    {
      user.setId(sistema.getTamUsuarios() + 1);
      sistema.adicionarUsuario(user);
      sistema.salvar();
      std::cout << "Usuário criado" << std::endl;
      menu(sistema);
    }
    else
    {
      std::cout << "Usuário já existe!" << std::endl;
      menu(sistema);
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
    menu(sistema);
  }
}

void loginUsuario(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, email, senha;
  iss >> comando >> email;
  std::getline(iss, senha);

  if (!email.empty() && !senha.empty())
  {
    senha = senha.substr(senha.find_first_not_of(' '));
    if (sistema.verificarUsuario(email) != nullptr && sistema.verificarUsuario(email)->getSenha() == senha)
    {
      std::cout << "Logado como " << email << std::endl;
      sistema.setUsuarioLogado(sistema.verificarUsuario(email)->getId());
      menuLogado(sistema);
    }
    else
    {
      std::cout << "Senha ou usuário inválidos!" << std::endl;
      menu(sistema);
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
    menu(sistema);
  }
}

void menuLogado(Sistema &sistema)
{
  sistema.carregar();
  std::string entrada;
  std::getline(std::cin, entrada);
  while (true)
  {
    if (entrada == "disconnect")
    {
      std::cout << "Desconectando usuario " << sistema.getUsuario(sistema.getUsuarioLogado())->getEmail() << std::endl;
      sistema.setUsuarioLogado(0);
      menu(sistema);
      break;
    }
    else if (entrada == "quit")
    {
      std::cout << "Saindo do concordo" << std::endl;
      break;
    }
    else if (entrada.substr(0, 13) == "create-server")
    {
      criarServidor(sistema, entrada);
      break;
    }
    else if (entrada.substr(0, 15) == "set-server-desc")
    {
      descServidor(sistema, entrada);
      break;
    }
    else if (entrada.substr(0, 22) == "set-server-invite-code")
    {
      setServerCode(sistema, entrada);
      break;
    }
    else if (entrada == "list-servers")
    {
      sistema.carregar();
      sistema.imprimirServidores();
      menuLogado(sistema);
      break;
    }
    else if (entrada.substr(0, 13) == "remove-server")
    {
      removerServidor(sistema, entrada);
      break;
    }
    else if (entrada.substr(0, 12) == "enter-server")
    {
      entrarServidor(sistema, entrada);
      break;
    }
    else if (entrada == "leave-server")
    {
      std::cout << "Você não está visualizando nenhum servidor" << std::endl;
      menuLogado(sistema);
      break;
    }
    else
    {
      std::cout << "Comando invalido" << std::endl;
      menuLogado(sistema);
      break;
    }
  }
}

void criarServidor(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, nome, vazio;
  iss >> comando >> nome >> vazio;
  if (!nome.empty() && vazio.empty())
  {
    nome = nome.substr(nome.find_first_not_of(' '));
    if (!sistema.acessarServidor(nome))
    {
      Servidor novo(nome, sistema.getUsuarioLogado());
      std::cout << "Servidor criado" << std::endl;
      sistema.adicionarServidor(novo);
    }
    else
    {
      std::cout << "Servidor com esse nome já existe" << std::endl;
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
  }
  sistema.salvar();
  menuLogado(sistema);
}

void descServidor(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, nome, desc;
  iss >> comando >> nome;
  std::getline(iss, desc);
  if (!desc.empty())
  {
    desc = desc.substr(desc.find_first_not_of(' '));
  }
  if (!nome.empty())
  {
    if (sistema.acessarServidor(nome) != nullptr)
    {
      if (sistema.acessarServidor(nome)->getIdDono() == sistema.getUsuarioLogado())
      {
        sistema.acessarServidor(nome)->setDescricao(desc);
        sistema.salvar();
        std::cout << "Descricao do servidor '" << nome << "' modificada" << std::endl;
      }
      else
      {
        std::cout << "Você não pode alterar a descrição de um servidor que não foi criado por você" << std::endl;
      }
    }
    else
    {
      std::cout << "Servidor " << nome << " nao existe" << std::endl;
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
  }
  menuLogado(sistema);
}

void removerServidor(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, nome;
  iss >> comando >> nome;
  if (!nome.empty())
  {
    if (sistema.acessarServidor(nome) != nullptr)
    {
      if (sistema.acessarServidor(nome)->getIdDono() == sistema.getUsuarioLogado())
      {
        sistema.removerServidor(nome);
        sistema.salvar();
        std::cout << "Servidor '" << nome << "' removido" << std::endl;
      }
      else
      {
        std::cout << "Voce não é dono do servidor '" << nome << "'" << std::endl;
      }
    }
    else
    {
      std::cout << "Servidor " << nome << " nao existe" << std::endl;
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
  }
  menuLogado(sistema);
}

void setServerCode(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, nome, codigo, vazio;
  iss >> comando >> nome >> codigo >> vazio;

  if (!nome.empty() && vazio.empty())
  {
    if (sistema.acessarServidor(nome) != nullptr)
    {
      if (sistema.acessarServidor(nome)->getIdDono() == sistema.getUsuarioLogado())
      {
        if (codigo != "")
        {
          sistema.acessarServidor(nome)->setCodigoConvite(codigo);
          std::cout << "Codigo de convite do servidor '" << nome << "' modificado" << std::endl;
        }
        else
        {
          sistema.acessarServidor(nome)->setCodigoConvite(codigo);
          std::cout << "Codigo de convite do servidor " << nome << " removido" << std::endl;
        }
      }
      else
      {
        std::cout << "Você não pode alterar o codigo de convite de um servidor que não foi criado por você" << std::endl;
      }
    }
    else
    {
      std::cout << "Servidor " << nome << " nao existe" << std::endl;
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
  }
  sistema.salvar();
  menuLogado(sistema);
}

void entrarServidor(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, nome, codigo;
  iss >> comando >> nome >> codigo;
  if (!nome.empty())
  {
    if (sistema.acessarServidor(nome) != nullptr)
    {
      if (sistema.acessarServidor(nome)->getCodigoConvite() == codigo || sistema.acessarServidor(nome)->getIdDono() == sistema.getUsuarioLogado() || sistema.acessarServidor(nome)->verificarParticipante(sistema.getUsuarioLogado()) == true)
      {
        std::cout << "Entrou no servidor com sucesso" << std::endl;
        if (sistema.acessarServidor(nome)->getDescricao() != "")
        {
          std::cout << sistema.acessarServidor(nome)->getDescricao() << std::endl;
        }
        else
        {
          std::cout << "Descrição vazia" << std::endl;
        }
        if (sistema.acessarServidor(nome)->verificarParticipante(sistema.getUsuarioLogado()) == false)
        {
          sistema.acessarServidor(nome)->adicionarParticipante(sistema.getUsuarioLogado());
          sistema.salvar();
        }
        sistema.setServerVizualizado(nome);
        servidor(sistema);
      }
      // Usuario insere um codigo em um servidor aberto, e nao consegue entrar
      else if (sistema.acessarServidor(nome)->getCodigoConvite() != codigo && codigo == "" && sistema.acessarServidor(nome)->getIdDono() != sistema.getUsuarioLogado())
      {
        std::cout << "Servidor requer codigo de convite" << std::endl;
        menuLogado(sistema);
      }
      else
      {
        std::cout << "Codigo invalido" << std::endl;
        menuLogado(sistema);
      }
    }
    else
    {
      std::cout << "Servidor '" << nome << "' nao existe" << std::endl;
      menuLogado(sistema);
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
    menuLogado(sistema);
  }
}

void criarCanais(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, nome, tipo, vazio;
  iss >> comando >> nome >> tipo >> vazio;
  if (!nome.empty() && !tipo.empty() && vazio.empty())
  {
    if (sistema.acessarServidor(sistema.getServerVizualizado())->acessoCanal(nome) == nullptr)
    {
      if (tipo == "texto" || tipo == "voz")
      {
        std::cout << "Canal de " << tipo << " " << nome << "' criado" << std::endl;
        sistema.acessarServidor(sistema.getServerVizualizado())->criarCanal(tipo, nome);
        sistema.salvar();
      }
      else
      {
        std::cout << "Tipo inválido" << std::endl;
      }
    }
    else
    {
      std::cout << "Canal '" << nome << "' já existe" << std::endl;
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
  }
  servidor(sistema);
}

void servidor(Sistema &sistema)
{
  std::string entrada;
  std::getline(std::cin, entrada);
  while (true)
  {
    sistema.carregar();
    if (entrada.substr(0, 17) == "list-participants")
    {
      sistema.imprimirParticipantes(sistema.getServerVizualizado());
      servidor(sistema);
      break;
    }
    else if (entrada == "leave-server")
    {
      std::cout << "Saindo do servidor '" << sistema.getServerVizualizado() << "'" << std::endl;
      sistema.setServerVizualizado("");
      menuLogado(sistema);
      break;
    }
    else if (entrada == "quit")
    {
      std::cout << "Saindo do concordo" << std::endl;
      break;
    }
    else if (entrada == "list-channels")
    {
      sistema.acessarServidor(sistema.getServerVizualizado())->listarCanais();
      servidor(sistema);
      break;
    }
    else if (entrada.substr(0, 14) == "create-channel")
    {
      criarCanais(sistema, entrada);
      break;
    }
    else if (entrada.substr(0, 13) == "enter-channel")
    {
      entrarCanal(sistema, entrada);
      break;
    }
    else
    {
      std::cout << "Comando invalido" << std::endl;
      servidor(sistema);
      break;
    }
  }
}

void entrarCanal(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, nome, vazio;
  iss >> comando >> nome >> vazio;
  if (!nome.empty() && vazio.empty())
  {
    if (sistema.acessarServidor(sistema.getServerVizualizado())->acessoCanal(nome) != nullptr)
    {
      std::cout << "Entrou no canal '" << nome << "'" << std::endl;
      sistema.setCanalVizualizado(nome);
      canal(sistema);
    }
    else
    {
      std::cout << "Canal '" << nome << "' não existe" << std::endl;
      servidor(sistema);
    }
  }
  else
  {
    std::cout << "Dados invalidos" << std::endl;
    servidor(sistema);
  }
}

void criarMensagem(Sistema &sistema, std::string entrada)
{
  sistema.carregar();
  std::istringstream iss(entrada);
  std::string comando, conteudo, data, horas, minutos;
  iss >> comando;
  std::getline(iss, conteudo);
  if (!conteudo.empty())
  {
    conteudo = conteudo.substr(conteudo.find_first_not_of(' '));
    time_t tempoAtual = time(nullptr);
    struct tm *dataHoraAtual = localtime(&tempoAtual);
    std::ostringstream oss;
    oss << std::put_time(dataHoraAtual, "<%d/%m/%Y - %H:%M>");
    std::string dataHora = oss.str();
    Mensagem mensagem(dataHora, sistema.getUsuarioLogado(), conteudo);
    enviarMensagem(sistema, mensagem);
  }
  else
  {
    std::cout << "Conteudo da mensagem não pode ser vazio" << std::endl;
    canal(sistema);
  }
}

void enviarMensagem(Sistema &sistema, Mensagem mensagem)
{
  sistema.carregar();
  Canal *channel = sistema.acessarServidor(sistema.getServerVizualizado())->acessoCanal(sistema.getCanalVizualizado());
  CanalTexto *canalTexto = dynamic_cast<CanalTexto *>(channel);
  if (canalTexto)
  {
    canalTexto->adicionarMensagem(mensagem);
  }
  else
  {
    CanalVoz *canalVoz = dynamic_cast<CanalVoz *>(channel);
    if (canalVoz)
    {
      canalVoz->setMensagem(mensagem);
    }
  }
  sistema.salvar();
  canal(sistema);
}

void canal(Sistema &sistema)
{
  sistema.carregar();
  std::string entrada;
  std::getline(std::cin, entrada);
  while (true)
  {
    if (entrada == "leave-channel")
    {
      std::cout << "Saindo do canal" << std::endl;
      sistema.setCanalVizualizado("");
      servidor(sistema);
      break;
    }
    else if (entrada == "list-messages")
    {
      sistema.carregar();
      sistema.imprimirMensagens();
      canal(sistema);
      break;
    }
    else if (entrada.substr(0, 12) == "send-message")
    {
      criarMensagem(sistema, entrada);
      break;
    }
    else if (entrada == "quit")
    {
      std::cout << "Saindo do concordo" << std::endl;
      break;
    }
    else
    {
      std::cout << "Comando invalido" << std::endl;
      canal(sistema);
      break;
    }
  }
}