# Software de consultas ao banco de dados de receitas

<p>Professor: André Maravilha(CEFET-MG)</p>

## Integrantes:

- Daniel Alvez Sanches
- Julia Mello
- Leonardo Campos
- Thomas

## Funcionamento

- `gcc -o main main.c -lmysqlclient`

## Configuracao (Ubuntu)

- `sudo apt update`
- `sudo apt upgrade`
- `sudo apt update`
- `sudo apt autoremove`
- `sudo apt install mysql-server`
- `sudo apt install libmysqlclient-dev`

/*
ar -crv libminhalib.a minhalib.o -> gera a lib estatica
gcc -shared -fPIC -o libminhalib.so minhalib.og -> gera lib dinamica
gcc -c minhalib.c -> compila
gcc -I ../daniel -o foo foo.c
gcc -o abc foo.c -I../daniel -L../daniel -lminhalib -> inclui lib para compilar

sudo apt install libmysqlclient-dev
usr/include/mysql
gcc -o agenda agenda.c -lmysqlclient
*/