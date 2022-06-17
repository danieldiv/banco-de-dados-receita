# Software de consultas ao banco de dados de receitas

<p>Professor: André Maravilha(CEFET-MG)</p>

## Integrantes:

- Daniel Alvez Sanches
- Julia Mello
- Leonardo Campos
- Thomas

## Fazer

### Urgencia

- :red_circle: mais urgente
- :yellow_circle: mediano
- :green_circle: menos urgente
- :x: falta fazer
- :heavy_check_mark: feito

</br>

- Leitura usuarios :red_circle: :x:
- Leitura ingredientes :red_circle: :x:
- Leitura receitas :red_circle: :x:
- Leitura receitas fotos :green_circle: :x:
- Leitura receitas ingredientes :green_circle: :x:
- Leitura receitas etapas :green_circle: :x:
- Leitura receitas passos :green_circle: :x:
- Leitura comentarios :yellow_circle: :x:
- Leitura avaliacoes :yellow_circle: :x:
- Leitura gostou :yellow_circle: :x:
- Leitura experimentar :yellow_circle: :x:

</br>

- Cadastro usuarios
- Cadastro ingredientes
- Cadastro receitas
- Cadastro receitas fotos
- Cadastro receitas ingredientes
- Cadastro receitas etapas
- Cadastro receitas passos
- Cadastro comentarios
- Cadastro avaliacoes
- Cadastro gostou
- Cadastro experimentar

</br>

- Atualizar usuarios
- Atualizar ingredientes
- Atualizar receitas
- Atualizar receitas fotos
- Atualizar receitas ingredientes
- Atualizar receitas etapas
- Atualizar receitas passos
- Atualizar comentarios
- Atualizar avaliacoes
- Atualizar gostou
- Atualizar experimentar

</br>

- Remover usuarios
- Remover ingredientes
- Remover receitas
- Remover receitas fotos
- Remover receitas ingredientes
- Remover receitas etapas
- Remover receitas passos
- Remover comentarios
- Remover avaliacoes
- Remover gostou
- Remover experimentar


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
