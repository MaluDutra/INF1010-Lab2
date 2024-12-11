# INF1010-Lab2
Tarefa 2 para a disciplina INF1010.
Alunos: Gustavo Rocha e Maria Luiza Dutra

**Objetivo:**
O objetivo deste trabalho é criar um sistema para gerenciar os atendimentos de pacientes da emergência, utilizando uma lista, que é atualizada de acordo com as prioridades estabelecidas. Essas prioridades são dadas por cores, que indicam o estado do paciente, e seus números de chegada. As cores estão divididas em: vermelha - significa que o paciente precisa ser atendido com maior urgência; amarelo - significa que o paciente requer mais atenção, porém não está em estado crítico; e verde - significa que o paciente não possui nenhuma urgência ou atenção a mais necessária. 
Assim, primeiramente deve-se levar em conta o estado do paciente e, depois, deve-se ordenar o atendimento pela ordem de chegada. Deste modo, quando um novo paciente com uma determinada condição chegar na emergência, ele será adicionado ao final dos pacientes com sua mesma condição, ou seja, cor de prioridade. Além disso, quando um paciente for atendido, ele é retirado da lista.

Para rodar o programa, é necessário ter tanto o arquivo “main.c” quanto o arquivo de entrada “pacientes.txt”, que possui todas as entradas e saídas de pacientes do programa descritas.
