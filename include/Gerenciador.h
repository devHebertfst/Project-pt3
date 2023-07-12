#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "Sistema.h"

/**
 * @brief Menu inicial
 *
 * @param sistema
 */
void menu(Sistema &sistema);
/**
 * @brief Criação de usuário
 *
 * @param sistema
 * @param entrada
 */
void criarUsuario(Sistema &sistema, std::string entrada);
/**
 * @brief Login de usuário
 *
 * @param sistema
 * @param entrada
 */
void loginUsuario(Sistema &sistema, std::string entrada);
/**
 * @brief Menu com usuário conectado
 *
 * @param sistema
 */
void menuLogado(Sistema &sistema);
/**
 * @brief Criação de servidores
 *
 * @param sistema
 * @param entrada
 */
void criarServidor(Sistema &sistema, std::string entrada);
/**
 * @brief Mudar a descrição do servidor
 *
 * @param sistema
 * @param entrada
 */
void descServidor(Sistema &sistema, std::string entrada);
/**
 * @brief Remover servidor
 *
 * @param sistema
 * @param entrada
 */
void removerServidor(Sistema &sistema, std::string entrada);
/**
 * @brief Mudar o codigo de convite do servidor
 *
 * @param sistema
 * @param entrada
 */
void setServerCode(Sistema &sistema, std::string entrada);
/**
 * @brief Entrar no servidor
 *
 * @param sistema
 * @param entrada
 */
void entrarServidor(Sistema &sistema, std::string entrada);
/**
 * @brief Menu do servidor
 *
 * @param sistema
 */
void servidor(Sistema &sistema);
/**
 * @brief Criação de canais
 *
 * @param sistema
 * @param entrada
 */
void criarCanais(Sistema &sistema, std::string entrada);
/**
 * @brief Entrar em um canal
 *
 * @param sistema
 * @param entrada
 */
void entrarCanal(Sistema &sistema, std::string entrada);
/**
 * @brief Menu de canais
 *
 * @param sistema
 */
void canal(Sistema &sistema);
/**
 * @brief Criação de mensagens
 *
 * @param sistema
 * @param entrada
 */
void criarMensagem(Sistema &sistema, std::string entrada);
/**
 * @brief Envio de mensagens para um canal
 *
 * @param sistema
 * @param mensagem
 */
void enviarMensagem(Sistema &sistema, Mensagem mensagem);

#endif