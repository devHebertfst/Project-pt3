#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <iostream>
#include <string>

class Mensagem
{
private:
  std::string dataHora;
  int enviadaPor;
  std::string conteudo;

public:
  Mensagem();
  Mensagem(std::string dataHora, int enviadaPor, std::string conteudo);
  /**
   * @brief Retorna a data e hora de uma mensagem
   *
   * @return std::string
   */
  std::string getDataHora() const;
  /**
   * @brief Retorna o id do usuário que fez o envio da mensagem
   *
   * @return int
   */
  int getEnviadaPor() const;
  /**
   * @brief Retorna o conteúdo da mensagem
   *
   * @return std::string
   */
  std::string getConteudo() const;
};

#endif