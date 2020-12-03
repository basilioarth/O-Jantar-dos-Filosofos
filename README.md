# :mortar_board: O Problema do Jantar dos Filósofos 

    O repositório tem como objetivo registrar uma solução para o problema do jantar dos filósofos. Trata-se de um dos 
problemas clássicos de comunicação entre processos. O código foi utilizado como resposta para uma atividade proposta na 
disciplina de Sistemas Operacionais. 

# :thought_balloon: Definindo o Problema

    O contexto se trata de um conjunto de cinco filósofos reunidos em uma mesa circular que irão jantar macarronada. 
Ao todo são cinco pratos de macarronada e cinco garfos para a alimentação. O problema surge quando cada filósofo 
precisa usar dois garfos para se alimentar (aqui não vale querer facilitar as coisas :satisfied:); um dos garfos estando no ao seu lado direito, o outro ao seu lado esquerdo.
	O filósofos podem se encontrar em três estados diferentes: comendo (efetivamente se alimentado e, portanto, utilizando
os dois garfos a sua volta), com fome (ele quer comer, porém não pode pois não há garfos suficientes disponíveis) ou pensando (apenas filosofando sobre a vida).

# :computer: O Programa 

    A ideia era desenvolver um algoritmo que resolvesse o problema do jantar dos filósofos de forma que mais de um filósofo
possa comer ao mesmo tempo (garantindo assim a multiprogramação), mas sem permitir que eles sejam vizinhos (garantindo assim o acesso restrito ao recurso compartilhado, os garfos, evitando possíveis condições de corrida). Para demonstrar de maneira visual o funcionamento o programa da maneira como foi pedido, resolvi gerar como saída do código o print de uma lista circular com o estado de cada filósofo. Dá uma olhada em como ficou:

                                            [coloca o gif aqui]

    O algoritmo se resume ao código <nome_do_código>. Ele tem alguns comentários com o intuito de auxiliar no entendimento 
do funcionamento do código. Confere lá =).

# :gear: Como usar

    Para gerar o executável do algoritmo na sua máquina, basta abrir o prompt de comando no diretório do arquivo e 
executar o comando:

Windows:

Linux: 

