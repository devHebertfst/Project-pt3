#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <string>

class Usuario
{
private:
  int id;
  std::string nome;
  std::string email;
  std::string senha;

public:
  Usuario();
  Usuario(std::string nome, std::string email, std::string senha);
  /**
   * @brief Retorna o id do usuário
   *
   * @return int
   */
  int getId();
  /**
   * @brief Retorna o nome do usuário
   *
   * @return std::string
   */
  std::string getNome();
  /**
   * @brief Retorna o email do usuário
   *
   * @return std::string
   */
  std::string getEmail();
  /**
   * @brief Retorna a senha do usuário
   *
   * @return std::string
   */
  std::string getSenha();
  /**
   * @brief Define o id do usuário
   *
   * @param id
   */
  void setId(int id);
};

#endif
