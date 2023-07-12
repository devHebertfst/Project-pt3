#include "Servidor.h"

Servidor::Servidor() {}

Servidor::Servidor(std::string nome, int usuarioDonoId, std::string codigoConvite, std::string descricao)
{
  this->nome = nome;
  this->descricao = descricao;
  this->codigoConvite = codigoConvite;
  this->usuarioDonoId = usuarioDonoId;
  participantesIDs.push_back(usuarioDonoId);
}

Servidor::Servidor(std::string nome, int usuarioDonoId)
{
  this->nome = nome;
  this->descricao = "";
  this->codigoConvite = "";
  this->usuarioDonoId = usuarioDonoId;
  participantesIDs.push_back(usuarioDonoId);
}

void Servidor::setDescricao(std::string descricao)
{
  this->descricao = descricao;
}

void Servidor::setCodigoConvite(std::string codigoConvite)
{
  this->codigoConvite = codigoConvite;
}

void Servidor::adicionarParticipante(int participanteId)
{
  participantesIDs.push_back(participanteId);
}

std::string Servidor::getNome()
{
  return nome;
}

int Servidor::getIdDono()
{
  return usuarioDonoId;
}

std::string Servidor::getDescricao()
{
  return descricao;
}

std::string Servidor::getCodigoConvite()
{
  return codigoConvite;
}

std::vector<int> Servidor::getPartipantesIDs()
{
  return participantesIDs;
}

bool Servidor::verificarParticipante(int id)
{
  for (auto it = participantesIDs.begin(); it != participantesIDs.end(); ++it)
  {
    if (*it == id)
    {
      return true;
    }
  }
  return false;
}

void Servidor::listarCanais()
{
  std::cout << "#canais de texto" << std::endl;
  for (const auto &canal : canais)
  {
    if (dynamic_cast<CanalTexto *>(canal))
      std::cout << canal->getNome() << std::endl;
  }

  std::cout << "#canais de audio" << std::endl;
  for (const auto &canal : canais)
  {
    if (dynamic_cast<CanalVoz *>(canal))
      std::cout << canal->getNome() << std::endl;
  }
}

void Servidor::criarCanal(std::string tipo, std::string nome)
{
  if (tipo == "texto")
  {
    CanalTexto *canalTexto = new CanalTexto(nome);
    canais.push_back(canalTexto);
  }
  else if (tipo == "voz")
  {
    CanalVoz *canalVoz = new CanalVoz(nome);
    canais.push_back(canalVoz);
  }
}

Canal *Servidor::acessoCanal(std::string nome)
{
  for (auto canal : canais)
  {
    CanalTexto *canalTexto = dynamic_cast<CanalTexto *>(canal);
    if (canalTexto && canalTexto->getNome() == nome)
    {
      return canalTexto;
    }
  }

  for (auto canal : canais)
  {
    CanalVoz *canalVoz = dynamic_cast<CanalVoz *>(canal);
    if (canalVoz && canalVoz->getNome() == nome)
    {
      return canalVoz;
    }
  }
  return nullptr;
}

std::vector<Canal *> Servidor::getCanais()
{
  return canais;
}
