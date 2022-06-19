# Software de consultas ao banco de dados de receitas

<p>Professor: André Maravilha(CEFET-MG)</p>

## Integrantes:

- Daniel Alvez Sanches
- Julia Mello Lopez Gonçalves
- Leonardo de Oliveira Campos
- Thomas Teixeira

## Fazer

| Tabelas               | Leitura             | Cadastro            | Atualizacao         | Remocao             |
| --------------------- | ------------------- | ------------------- | ------------------- | ------------------- |
| usuarios              | :red_circle: :x:    | :red_circle: :x:    | :yellow_circle: :x: | :yellow_circle: :x: |
| ingredientes          | :red_circle: :heavy_check_mark:    | :red_circle: :heavy_check_mark:    | :red_circle: :x:    | :red_circle: :x:    |
| receitas              | :red_circle: :x:    | :red_circle: :x:    | :yellow_circle: :x: | :yellow_circle: :x: |
| receitas fotos        | :green_circle: :x:  | :red_circle: :x:    | :yellow_circle: :x: | :green_circle: :x:  |
| receitas ingredientes | :green_circle: :x:  | :red_circle: :x:    | :yellow_circle: :x: | :green_circle: :x:  |
| receitas etapas       | :green_circle: :x:  | :red_circle: :x:    | :yellow_circle: :x: | :green_circle: :x:  |
| receitas passos       | :green_circle: :x:  | :red_circle: :x:    | :yellow_circle: :x: | :green_circle: :x:  |
| comentarios           | :yellow_circle: :x: | :yellow_circle: :x: | :green_circle: :x:  | :green_circle: :x:  |
| avaliacoes            | :yellow_circle: :x: | :yellow_circle: :x: | :green_circle: :x:  | :green_circle: :x:  |
| curtidas              | :yellow_circle: :x: | :yellow_circle: :x: | :green_circle: :x:  | :green_circle: :x:  |
| receitas salvas       | :yellow_circle: :x: | :yellow_circle: :x: | :green_circle: :x:  | :green_circle: :x:  |

### Legenda (prioridade)

| alta         | media           | baixa          | fazer | feito              |
| ------------ | --------------- | -------------- | ----- | ------------------ |
| :red_circle: | :yellow_circle: | :green_circle: | :x:   | :heavy_check_mark: |

## Compilacao (makefile)

| Comandos     | Funcao                                                                              |
| ------------ | ----------------------------------------------------------------------------------- |
| `make clean` | Apaga a ultima compilacao da pasta build                                            |
| `make`       | Executa a compilacao do programa utilizando g++, o resultado vai para a pasta build |
| `make run`   | Executa o programa da pasta build apoz a compilacao                                 |

## Compilacao alternativa (makefile)

| Comandos     | Funcao                                                                              |
| ------------ | ----------------------------------------------------------------------------------- |
| `make c`     | Apaga a ultima compilacao, compila e executa                                        |
| `make r`     | compila e executa                                                                   |

## Compilacao (padrao)

- `gcc -o main main.c -lmysqlclient`
- `./main`

## Configuracao (Ubuntu)

> sudo apt update
>
> sudo apt upgrade
>
> sudo apt update
>
> sudo apt autoremove
>
> sudo apt install mysql-server
>
> sudo apt install libmysqlclient-dev

<!--
ar -crv libminhalib.a minhalib.o -> gera a lib estatica
gcc -shared -fPIC -o libminhalib.so minhalib.og -> gera lib dinamica
gcc -c minhalib.c -> compila
gcc -I ../daniel -o foo foo.c
gcc -o abc foo.c -I../daniel -L../daniel -lminhalib -> inclui lib para compilar

sudo apt install libmysqlclient-dev
usr/include/mysql
gcc -o agenda agenda.c -lmysqlclient
-->
