#include "Canal.h"

Canal::Canal(std::string nome)
{
    this->nome = nome;
}

std::string Canal::getNome()
{
    return nome;
}

void CanalTexto::imprimir()
{
    std::cout << getNome() << std::endl;
}

void CanalVoz::imprimir()
{
    std::cout << getNome() << std::endl;
}

std::vector<Mensagem> CanalTexto::getMensagens()
{
    return mensagens;
}

Mensagem CanalVoz::getMensagem()
{
    return ultimaMensagem;
}

void CanalTexto::adicionarMensagem(Mensagem mensagem)
{
    mensagens.push_back(mensagem);
}

void CanalVoz::setMensagem(Mensagem mensagem)
{
    this->ultimaMensagem = mensagem;
}
