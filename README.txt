Trabalho linguagens de programação 1, projeto 3, parte 1
Componentes: Hebert França da Silva Torres

O seguinte projeto fo realizado utilizando a linguagem c++ e compilado via cmake.
Para fazer a compilação basta acessar a pasta build via terminal e digitar "make".
Caso haja algum problema delete a pasta build, crie a novamente, acesse e digite "cmake .." e depois "make".
Para rodar o programa com mais facilidade use o arquivo txt. Na pasta build inicial terá um arquivo
script.txt com alguns comandos. Lembre-se que caso precise apagar a pasta build
mova o arquivo para outro diretorio e depois de todo o processo mova o arquivo de volta.
Para executar o programa acesse a pasta build via terminal e digite "./program < script.txt".

Nessa primeira parte do programa foi feita a estrutura básica de um usuário, como a criação, login, 
listagem de servidores, desconectar o usuário e entre outros.
Também foram adicionadas algumas funcionalidades do servidor como a criação, a listagem de participantes,
remoção, mudança de código e descrição, entre outros.
Os comandos no script.txt tentam abordar todos os casos de erro possível, como inserção de comandos inválidos,
falta de informações, verificação de usuário, senha e servidor, inserção de espaços incorretos e outros.

*UPDATE

Nesse segunda parte do programa foram adicionados os metódos necessários para o funcionamento do sistemas de
canai e mensagens. Qualquer usuário pode criar um canal de tipo texto ou voz. O canal de tipo voz armazena apenas a
ultima mensagem enviada, diferente do canal de tipo texto que salva todas as mensagens enviadas.
Como na primeira parte o script.txt tenta abordar todos os casos de erro possível, como criação de canais
de tipos inexistentes, comandos diferentes e entre outros.

Considerações finais:
Nesse projeto houve um dificuldade considerável para acessar o usuário via id e fazer suas operações.
Também houveram problemas na verificação de alguns tipos de entrada com excesso de dados.
A utilização de ponteiros foi bastante complicada a principio e em certo ponto o programa fucionava
sem vazamentos mas após a remoção de servidores o vazamento ocorria. Mas isso foi resolvido com
a remoção dos canais antes da remoção do servidor

Link github pt1: github.com/devHebertfst/Projeto
Link github pt2: github.com/devHebertfst/Concordo-LP1-PT2
