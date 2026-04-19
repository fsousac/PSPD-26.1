# Atividade MPI: Contagem Sequencial de 0 ate N

## Objetivo

Implementar um programa MPI que imprime os numeros naturais de `0` ate `N`, em ordem sequencial, com os valores sendo impressos por diferentes processos.

Regras consideradas na implementacao:

- O numero de processos (`P`) deve ser menor ou igual a `N + 1`.
- Cada processo imprime apenas um numero por vez.
- A execucao funciona para quantidade variavel de processos.

## Arquivos

- `mpi_contagem_sequencial.c`: implementacao em C com MPI.

## Como compilar

Requisito: OpenMPI/MPICH instalado no Ubuntu.

```bash
mpicc mpi_contagem_sequencial.c -o mpi_contagem_sequencial
```

## Como executar (mesma maquina)

Exemplo com `4` processos (definidos por `-np`; o programa pedira apenas `N`):

```bash
mpirun --oversubscribe -np 4 ./mpi_contagem_sequencial
```

Entradas interativas esperadas:

```text
Informe o valor final N (contagem de 0 ate N): 20
```

Saida esperada (ordem):

```text
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
```

## Logica usada

A ordenacao visual no terminal eh garantida com coordenacao pelo rank 0:

- Cada numero `i` pertence ao processo `i % P`.
- O processo dono envia `i` para o rank `0`.
- O rank `0` imprime em sequencia de `0` ate `N`.
- Cada processo participa um numero por vez, e a saida final permanece ordenada.

Assim, mesmo com processos em hosts distintos, a saida permanece sequencial.

## Execucao em cluster MPI (Ubuntu, hosts distintos)

### 1) Preparar todas as maquinas

Em **todos os hosts**:

```bash
sudo apt update
sudo apt install -y openmpi-bin libopenmpi-dev openssh-server
```

Verificar MPI:

```bash
mpirun --version
```

### 2) Configurar SSH sem senha (do master para os workers)

No host master:

```bash
ssh-keygen -t ed25519 -N "" -f ~/.ssh/id_ed25519
ssh-copy-id usuario@worker1
ssh-copy-id usuario@worker2
```

Teste:

```bash
ssh usuario@worker1 hostname
ssh usuario@worker2 hostname
```

### 3) Garantir mesmo usuario/caminho do projeto

Opcao simples para aula: copiar o executavel para o mesmo caminho em cada host.

Exemplo:

```bash
scp mpi_contagem_sequencial usuario@worker1:/home/usuario/pspd/
scp mpi_contagem_sequencial usuario@worker2:/home/usuario/pspd/
```

### 4) Criar arquivo de hosts no master

Crie `hosts.txt`:

```text
master slots=1
worker1 slots=1
worker2 slots=1
```

### 5) Rodar em hosts distintos

No master, no diretorio do executavel:

```bash
mpirun -np 3 --hostfile hosts.txt ./mpi_contagem_sequencial
```

Se o OpenMPI bloquear root em laboratorio, use:

```bash
mpirun --allow-run-as-root -np 3 --hostfile hosts.txt ./mpi_contagem_sequencial
```

## Dicas para apresentacao

- Testar antes da aula com varios valores de `N` (ex.: 10, 20, 50).
- Testar com diferentes quantidades de processos (`2`, `3`, `4`, etc.).
- Mostrar que a saida continua ordenada mesmo com hosts diferentes.

## Entrega em sala

Para comprovar funcionamento, mostrem:

1. Compilacao com `mpicc`.
2. Execucao local com `mpirun`.
3. Execucao com `--hostfile` em mais de um host.
