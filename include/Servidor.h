#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "Canal.h"
#include "Usuario.h"

class Servidor
{
private:
  int usuarioDonoId;
  std::string nome;
  std::string descricao;
  std::string codigoConvite;
  std::vector<Canal *> canais;
  std::vector<int> participantesIDs;

public:
  Servidor();
  Servidor(std::string nome, int usuarioDonoId);
  Servidor(std::string nome, int usuarioDonoId, std::string codigoConvite, std::string descricao);
  /**
   * @brief Retorna o nome do servidor
   *
   * @return std::string
   */
  std::string getNome();
  /**
   * @brief Retorna o codigo de convite
   *
   * @return std::string
   */
  std::string getCodigoConvite();
  /**
   * @brief Retorna o id do dono
   *
   * @return int
   */
  int getIdDono();
  /**
   * @brief Retorna a descrição do servidor
   *
   * @return std::string
   */
  std::string getDescricao();
  /**
   * @brief Retorna se o participante está no servidor
   *
   * @param id
   * @return true
   * @return false
   */
  bool verificarParticipante(int id);
  /**
   * @brief Muda a descrição do servidor
   *
   * @param descricao
   */
  void setDescricao(std::string descricao);
  /**
   * @brief Muda o codigo de convite
   *
   * @param codigoConvite
   */
  void setCodigoConvite(std::string codigoConvite);
  /**
   * @brief Adiciona um participante no servidor
   *
   * @param participanteId
   */
  void adicionarParticipante(int participanteId);
  /**
   * @brief Retorna o vetor de IDs dos participantes
   *
   * @return std::vector<int>
   */
  std::vector<int> getPartipantesIDs();
  /**
   * @brief Imprime todos os canais
   *
   */
  void listarCanais();
  /**
   * @brief Cria um canal
   *
   * @param tipo
   * @param nome
   */
  void criarCanal(std::string tipo, std::string nome);
  /**
   * @brief Retorna um canal
   *
   * @param nome
   * @return Canal*
   */
  Canal *acessoCanal(std::string nome);
  /**
   * @brief Retorna o vetor de canais
   *
   * @return std::vector<Canal *>
   */
  std::vector<Canal *> getCanais();
};

#endif