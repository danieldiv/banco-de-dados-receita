# Software de consultas ao banco de dados de receitas

<p>Professor: André Maravilha(CEFET-MG)</p>

## Integrantes:

- Daniel Alvez Sanches
- Julia Mello Lopez Gonçalves
- Leonardo de Oliveira Campos
- Thomás Teixeira

## Fazer

| Tabelas               | Leitura                            | Cadastro                           | Atualizacao                         | Remocao                            |
| --------------------- | -----------------------------------|----------------------------------- | ----------------------------------- | ---------------------------------- |
| usuarios              | :red_circle: :heavy_check_mark:    | :red_circle: :heavy_check_mark:    | :yellow_circle: :heavy_check_mark:  | :yellow_circle: :heavy_check_mark: |
| ingredientes          | :red_circle: :heavy_check_mark:    | :red_circle: :heavy_check_mark:    | :red_circle: :heavy_check_mark:     | :red_circle: :heavy_check_mark:    |
| receitas              | :red_circle: :heavy_check_mark:    | :red_circle: :heavy_check_mark:    | :yellow_circle: :heavy_check_mark:  | :yellow_circle: :heavy_check_mark: |
| receitas fotos        | :green_circle: :heavy_check_mark:  | :red_circle: :heavy_check_mark:    | :yellow_circle: :heavy_check_mark:  | :green_circle: :heavy_check_mark:  |
| receitas ingredientes | :green_circle: :heavy_check_mark:  | :red_circle: :heavy_check_mark:    | :yellow_circle: :heavy_check_mark:  | :green_circle: :heavy_check_mark:  |
| receitas etapas       | :green_circle: :heavy_check_mark:  | :red_circle: :heavy_check_mark:    | :yellow_circle: :heavy_check_mark:  | :green_circle: :heavy_check_mark:  |
| receitas passos       | :green_circle: :heavy_check_mark:  | :red_circle: :heavy_check_mark:    | :yellow_circle: :heavy_check_mark:  | :green_circle: :heavy_check_mark:  |
| comentarios           | :yellow_circle: :heavy_check_mark: | :yellow_circle: :heavy_check_mark: |                                     | :green_circle: :heavy_check_mark:  |
| curtidas              | :yellow_circle: :heavy_check_mark: | :yellow_circle: :heavy_check_mark: |                                     | :green_circle: :heavy_check_mark:  |
| receitas salvas       | :yellow_circle: :x:                | :yellow_circle: :x:                | :green_circle: :x:                  | :green_circle: :x:                 |

### Legenda (prioridade)

| alta         | media           | baixa          | fazer | feito              |
| ------------ | --------------- | -------------- | ----- | ------------------ |
| :red_circle: | :yellow_circle: | :green_circle: | :x:   | :heavy_check_mark: |

## Compilacao (makefile)

| Comandos     | Funcao                                                                              |
| ------------ | ----------------------------------------------------------------------------------- |
| `make clean` | Apaga a ultima compilacao
| `make`       | Executa a compilacao do programa utilizando g++ |
| `make run`   | Executa o programa apoz a compilacao                                                |
| `make r`     | Compila e Executa                                                                   |

## Compilacao (padrao)

- `gcc -o main main.c -lmysqlclient`
- `./main`

## Configuracao (Ubuntu)

- Dentro da pasta bd execute o comando para criar o banco e inserir os dados

`mysql -u admin -p < arquivo.sql`

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

## Funcionamento

<p>
    O banco de dados usado como parâmetro da aplicação se encontra na pasta DB neste repositório. O Aplicativo em questão trata-se de um acesso através da linguagem C ao banco de dados de Receitas elaborado em sala de aula. Em bora tenha sido confeccionado com linguagem C o Makefile que o executa está configurado em C++ visto que como são linguagens subjacentes, o processo de compilação se mantem, aproveitando as utilidades de C e C++. Para o funcionamento do aplicativo é necessário que o usuário execute o banco de dados em sua máquina e em seguida instale a biblioteca do mysql que permite a compilação com C(Este processo está acima na documentação). Após isso configure suas credenciais no software e está tudo pronto para execução do mesmo.
</p>

## Menu

<p>
Através do menu o usuário pode pesquisar por receitas e ingredientes cadastrados no banco de dados, além de poder logar no sistema em questão:
</p>

<p align = "">
    <img src="https://github.com/danieldiv/banco-de-dados-receita/blob/main/imagens/menu1.jpeg" alt="MYSQL-server" width="300"></img>
</p>

<p>
Já no menu de administrador, poderá fazer pesquisa por receita e ingrediente, tendo também acesso ao gerenciamento do banco de dados, onde poderá fazer inserções, atualização e exclusões de receitas no banco de dados.
</p>

<p align = "">
    <img src="https://github.com/danieldiv/banco-de-dados-receita/blob/main/imagens/menu2.jpeg" alt="MYSQL-server" width="300"></img>
</p>

<p>
Dentro de menu de gerenciamento o usuário:
</p>

<p align = "">
    <img src="https://github.com/danieldiv/banco-de-dados-receita/blob/main/imagens/menu3.jpeg" alt="MYSQL-server" width="300"></img>
</p>

<p>
Dentro do menu de cadastros:
</p>

<p align = "">
    <img src="https://github.com/danieldiv/banco-de-dados-receita/blob/main/imagens/menu4.jpeg" alt="MYSQL-server" width="300"></img>
</p>

## Conclusões

<p>
asdfasdfafd
</p>
