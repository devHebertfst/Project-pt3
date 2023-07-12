#include "Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(std::string nome, std::string email, std::string senha)
{
  this->nome = nome;
  this->email = email;
  this->senha = senha;
}

std::string Usuario::getEmail()
{
  return email;
}

std::string Usuario::getSenha()
{
  return senha;
}

std::string Usuario::getNome()
{
  return nome;
}

int Usuario::getId()
{
  return id;
}

void Usuario::setId(int id)
{
  this->id = id;
}