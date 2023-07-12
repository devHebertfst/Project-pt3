#ifndef CANAL_H
#define CANAL_H

#include <string>
#include <vector>
#include "Mensagem.h"

class Canal
{
protected:
  std::string nome;

public:
  Canal(std::string nome);
  /**
   * @brief Retorna o nome do canal
   *
   * @return std::string
   */
  std::string getNome();
  virtual void imprimir() = 0;
  virtual ~Canal() = default;
};

class CanalTexto : public Canal
{
private:
  std::vector<Mensagem> mensagens;

public:
  CanalTexto(std::string nome) : Canal(nome) {}
  /**
   * @brief Retorna o vetor de mensagens
   *
   * @return std::vector<Mensagem>
   */
  std::vector<Mensagem> getMensagens();
  /**
   * @brief Adiciona uma mensagem no vetor
   *
   * @param mensagem
   */
  void adicionarMensagem(Mensagem mensagem);
  /**
   * @brief Imprime o vetor de mensagens
   *
   */
  virtual void imprimir();
};

class CanalVoz : public Canal
{
private:
  Mensagem ultimaMensagem;

public:
  CanalVoz(std::string nome) : Canal(nome) {}
  /**
   * @brief Retorna a mensagem do canal
   *
   * @return Mensagem
   */
  Mensagem getMensagem();
  /**
   * @brief Modifica a ultima mensagem do canal
   *
   * @param mensagem
   */
  void setMensagem(Mensagem mensagem);
  /**
   * @brief Imprime a ultima mensagem
   *
   */
  virtual void imprimir();
};

#endif