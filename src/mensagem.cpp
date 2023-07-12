#include "Mensagem.h"

Mensagem::Mensagem() {}

Mensagem::Mensagem(std::string dataHora, int enviadaPor, std::string conteudo)
{
  this->dataHora = dataHora;
  this->conteudo = conteudo;
  this->enviadaPor = enviadaPor;
}

std::string Mensagem::getConteudo() const
{
  return conteudo;
}

std::string Mensagem::getDataHora() const
{
  return dataHora;
}

int Mensagem::getEnviadaPor() const
{
  return enviadaPor;
}