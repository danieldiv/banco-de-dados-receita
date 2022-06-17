# Software de consultas ao banco de dados de receitas

<p>Professor: André Maravilha(CEFET-MG)</p>

## Integrantes:

- Daniel Alvez Sanches
- Julia Mello
- Leonardo Campos
- Thomas

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

- `sudo apt update`
- `sudo apt upgrade`
- `sudo apt update`
- `sudo apt autoremove`
- `sudo apt install mysql-server`
- `sudo apt install libmysqlclient-dev`

<!-->
ar -crv libminhalib.a minhalib.o -> gera a lib estatica
gcc -shared -fPIC -o libminhalib.so minhalib.og -> gera lib dinamica
gcc -c minhalib.c -> compila
gcc -I ../daniel -o foo foo.c
gcc -o abc foo.c -I../daniel -L../daniel -lminhalib -> inclui lib para compilar

sudo apt install libmysqlclient-dev
usr/include/mysql
gcc -o agenda agenda.c -lmysqlclient
<!-->