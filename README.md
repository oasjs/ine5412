# Simulação de Algoritmos de Escalonamento
**Disciplina:** INE5412 – Sistemas Operacionais I
**Professores:** Giovani Gracioli e Márcio Bastos Castro
**Alunos:** João Pedro Schmidt Cordeiro e Otávio Augusto de Santana Jatobá
## Objetivo
O presente trabalho tem por objetivo escrever um programa para simular o escalonamento e abstração de um conjunto de processos/threads através do uso de algoritmos de escalonamento de processos conhecidos na literatura. 

---
## Execução padrão
Estando na raiz do repositório, com comandos `make` e compilador `g++` instalados, rodar o seguinte comando
```make all```

---
## Execução passo a passo

### Gerar entrada
Para gerar uma entrada aleatória utilize os seguintes comandos (Estando na raiz do repositório)

```make build-input-generator```

```make run-input-generator ARGS="<number_of_processes> <max_creation_time> <max_duration> <max_priority>"```

### Gerar arquivo executável
Para gerar o arquivo executável utilize o seguinte comando (Estando na raiz do repositório)

```make build```

### Executar o escalonador
Para executar o escalonador utilize o seguinte comando (Estando na raiz do repositório)

```make run-<type>```

Onde `<type>` pode ser as seguintes opções:
- `default` (Estabelecido o escolonador First Come First Serve)
- `fcfs` (First Come First Serve)
- `sjf` (Shortest Job First)
- `pnp` (Por prioridade, sem preempção)
- `pwp` (Por prioridade, com preempção por prioridade)
- `rr` (Round-Robin com quantum = 2s, sem prioridade)

---
## Execução personalizada
Caso você possua seu próprio arquivo de entrada, basta inserir-lo na pasta `inputs` (Caso a pasta não exista, você terá que criar). 

Também é necessário que esteja com o nome padrão indicado em seguida:  `./inputs/input.txt` 

Em seguida é necessário reproduzir os passos "Gerar arquivo executável" e "Executar o escalonador" referênciados na etapa anterior.

---
## Requisitos

O programa deve suportar os seguintes algoritmos de escalonamento de processos:
- FCFS (First Come, First Served)
- Shortest Job First
- Por prioridade, sem preempção
- Por prioridade, com preempção por prioridade
- Round-Robin com quantum = 2s, sem prioridade

O programa deve ler os dados dos processos através de um arquivo de entrada, onde cada linha do arquivo corresponde a um processo, com as seguintes informações inteiras separadas por um espaço em branco:
- data da criação do processo
- duração em segundos
- prioridade estática (escala de prioridades positiva, ex: prioridade 3 > 2).

Para cada algoritmo, o programa de simulação de escalonamento de processos deverá produzir as seguintes informações em sua saída padrão (stdout):
- Turnaround time (tempo transcorrido desde o momento em que o processo é criado até o instante em que termina sua execução). Imprimir o turnaround time para cada processo e também o valor médio.
- Tempo média de espera (soma dos períodos em que o processo estava no seu estado pronto).
- Número total de trocas de contexto (considerar que na primeira execução do primeiro processo há uma troca de contexto).
- Diagrama de tempo de execução.

## Arquivo de entrada
Um exemplo de arquivo de entrada para o programa seria (note que não tem linha em branco ao final do arquivo):
```txt
0 5 2
0 2 3
1 4 1
3 3 4
```

Neste exemplo, o processo P1 tem data de criação 0, sua execução dura 5 segundos e sua prioridade é definida como 2. Esse formato deve ser respeitado e não deve ser modificado em nenhuma hipótese (a avaliação seguirá esse formato e caso haja erro de leitura o programa não executará e consequentemente terá sua nota zerada). Note que a ordem dos processos não precisa estar ordenada por data de criação de cada processo.

## Saída esperada

Para simplificar, o diagrama de tempo de cada execução pode ser gerado na vertical, de cima para baixo (uma linha por segundo), conforme mostra o exemplo a seguir:

```txt
tempo P1 P2 P3 P4
 0- 1 ## --
 1- 2 ## -- --
 2- 3 -- ## --
 3- 4 -- ## -- --
 4- 5 --    ## --
 5- 6 --    ## --
 6- 7 ##    -- --
 7- 8 ##    -- --
 8- 9 --    -- ##
 9-10 --    -- ##
10-11 --    ## --
11-12 --    ## --
12-13 ##       --
13-14          ##
```

Sendo que “##” significa que o processo em questão está em execução, “--” significa que o processo já foi criado e está esperando, “ “ (espaço em branco) o processo ainda não iniciou ou já acabou, ou seja, não está na fila de prontos.

Sugere-se definir para cada processo as seguintes informações:
- identificador
- datas de inicio e de conclusão
- duração (tempo necessário no processador)
- prioridades estática e dinâmica (se houver)
- estado atual (novo, pronto, executando, terminado)
- tempo já executado (total e no quantum atual)
- … (outros campos podem ser necessários para algumas políticas de escalonamento)

## Informações do Sistema 
Além disso, o programa de simulação deve abstrair o contexto de um processador (CPU) hipotético chamado INE5412 que possui 6 registradores de propósito geral, SP (stack pointer), PC (program counter) e ST (status), todos com 64 bits. Desta forma, cada abstração de processo também deve ter um contexto (como implementar o contexto de forma a permitir a mudança de processador para a abstração processo?). O programa de simulação deve então realizar a troca de contexto (salvar e restaurar o contexto do processo que estava em execução e do próximo processo a ser executado - Onde salvar o contexto do processo?)