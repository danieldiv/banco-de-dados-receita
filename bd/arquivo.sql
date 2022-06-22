drop database if exists cefet_receitas;
create database cefet_receitas;
use cefet_receitas;

create table usuarios(
	id binary(16) primary key,
	nome varchar(64) not null,
	telefone char(11) not null unique,
	email varchar(128) not null unique,
	cidade varchar(64) not null,
	estado char(2) not null,
	foto varchar(128) not null
);

create table credenciais(
	id binary(16) primary key,
	senha binary(32) not null,
	foreign key (id) references usuarios(id)
);

create table ingredientes(
	id int primary key auto_increment,
	nome varchar(128) not null unique
);

create table receitas(
	id int primary key auto_increment,
	usuario_id binary(16),
	nome varchar(128) not null,
	rendimento int not null,
	tempo int not null,
	info text,
	foreign key (usuario_id) references usuarios(id)
);

create table receitas_fotos(
	receita_id int not null,
	arquivo varchar(128) not null,
	primary key(receita_id, arquivo),
	foreign key (receita_id) references receitas(id)
);

create table receitas_ingredientes(
	receita_id int not null,
	ingrediente_id int not null,
	quantidade float not null,
	unidade varchar(32) not null,
	primary key(receita_id, ingrediente_id),
	foreign key (receita_id) references receitas(id),
	foreign key (ingrediente_id) references ingredientes(id)
);

create table receitas_etapas (
	receita_id int not null,
	numero int not null,
	titulo varchar(32) not null,
	primary key (receita_id, numero),
	foreign key (receita_id) references receitas (id)
);

create table receitas_passos (
	receita_id int,
	etapa_numero int not null,
	sequencia int not null,
	instrucao varchar(128) not null,
	primary key (receita_id, etapa_numero, sequencia),
	foreign key (receita_id, etapa_numero) references receitas_etapas (receita_id, numero)
);

create table comentarios(
	usuario_id binary(16) not null,
	receita_id int not null,
	data_hora timestamp not null,
	mensagem text,
	primary key(usuario_id, receita_id, data_hora),
	foreign key(usuario_id) references usuarios(id),
	foreign key(receita_id) references receitas(id)
);

create table curtidas(
	usuario_id binary(16) not null,
	receita_id int not null,
	estrelas int not null,
	primary key(usuario_id, receita_id),
	foreign key(usuario_id) references usuarios(id),
	foreign key(receita_id) references receitas(id)
);

create table receitas_salvas(
	usuario_id binary(16) not null,
	receita_id int not null,
	primary key(usuario_id, receita_id),
	foreign key(usuario_id) references usuarios(id),
	foreign key(receita_id) references receitas(id)
);


-- Receita: Patê de frango 
-- Receita: Bolo de chocolate
-- Receita: Pizza de marguerita
-- Receita: Strogonoff de frango
-- Receita: Palha italiana
-- Receita: Bolo de chocolate de caneca
-- Receita: Fricassê de frango
-- Receita: Panqueca

-------------------------------------------------------------------------
------------------------- Receita: Brigadeiro ---------------------------
-------------------------------------------------------------------------

INSERT INTO ingredientes(id,nome) VALUES 
	(1,'Leite condensado'),
    (2,'Margarina sem sal'),
    (3,'Achocolatado em po'),
	(4,'Chocolate granulado');
    
INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(1,'Brigadeiro', 30, 25);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(1,1,1,'caixa'),
    (1,2,1,'colher de sopa'),
    (1,3,4,'colheres de sopa'),
    (1,4,1,'pacote');
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(1,1,'Preparação do brigadeiro'),
    (1,2,'Montagem dos doces');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(1,1,1,'Em uma panela funda, acrescente o leito condensado, margarina e o achocolatado'),
    (1,1,2,'Cozinhe em fogo médio e mexa até que o brigadeiro comece a desgrudar'),
    (1,2,1,'Deixe esfriar.'),
    (1,2,2,'Faça pequenas bolas de brigadeiro com as mãos.'),
    (1,2,3,'Passe as bolas de brigadeiro no chocolate granulado');
    
SELECT * FROM receitas;

-------------------------------------------------------------------------
------------------------- Receita: Patê de Frango -----------------------
-------------------------------------------------------------------------
   
INSERT INTO ingredientes(id,nome) VALUES 
	(6,'Peito de frango cozido e desfiado'),
    (7,'Cenoura média ralada'),
    (8,'Maionese'),
	(9,'Milho verde em conserva'),
	(10,'sal');

INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(2,'Patê de Frango', 5, 30);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(2,6,1,'xícara de chá'),
    (2,7,1,'cenoura'),
    (2,8,1/2,'xícara de chá'),
    (2,9,1/2,'xícara de chá'),
    (2,10,1,'a gosto');
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(2,1,'Preparação do patê');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(2,1,1,'Em uma tigele, misture todos os ingredientes'),
	(2,1,2,'Leve a geladeira por 30 minutos'),
	(2,1,3,'Sirva o patê em uma travessa');


-------------------------------------------------------------------------
---------------------- Receita: Bolo de Chocolate -----------------------
-------------------------------------------------------------------------


INSERT INTO ingredientes(id,nome) VALUES 
	(11,'Ovos'),
    (12,'Óleo de soja'),
    (13,'Água morna'),
	(14,'Farinha de Trigo'),
	(15,'Chocolate em pó solúvel'),
	(16,'Fermento em pó'),
	(17,'Açucar');
    
INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(3,'Bolo de chocolate', 8, 60);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(3,11,4,'unidades'),
    (3,12,'meia','xícara de chá'),
    (3,13,1,'xícara de chá'),
    (3,14,1,'duas e meia','xícara de chá'),
    (3,15,1,'xícara de chá'),
   	(3,16,1,'colher de sopa');
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(3,1,'Preparação da massa'),
    (3,2,'Preparação da calda');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(3,1,1,'Bata as clasras em neve e separe'),
    (3,1,2,'Em outra vasilha bata as gemas com açucar'),
    (3,1,3,'Em seguida, acrescente a água morna, o chocalate e o óleo, misture'),
    (3,1,4,'Acrescente a farinha de trigo e bata na batadeira em velocidade alta por 3 minutos'),
    (3,1,5,'Acrescente o fermento e mexa aos poucos'),
    (3,1,6,'Em seguida, acrescente a clara em neve e mexa de baixo para cima, até ficar totalmente envolvida na massa'),
    (3,1,7,'Asse o forno a 180 C por 50 minutos'),
    (3,2,1,'Para a calda, misture a margarina ou manteiga com achocolatado e 50 ml de leita'),
    (3,2,2,'Deixe levantar fervura por mais 1 minutos'),
    (3,2,3,'Desligue e jogue imediatamente em cima do bolo');
   
   
-------------------------------------------------------------------------
---------------------- Receita: Pizza de marguerita ---------------------
-------------------------------------------------------------------------
   
INSERT INTO ingredientes(id,nome) VALUES 
	(18,'Fermento biológico fresco')
	(19,'Molho de tomate');
	(20,'Orégano'),
	(21,'Manjericão'),
	(22,'Tomate em rodelas'),
	(23,'Azeite'),
	(24,'Mussarela ralada');
    
INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(4,'Pizza de marguerita', 2,100);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(4,14,5,'xícaras de chá'),
 	(4,18,30,'gramas'),
 	(4,17,1,'colher de sopa'),
 	(4,10,1,'colher de sopa'),
 	(4,12,3,'colher de sopa'),
 	(4,13,1/4,'xícara de chá'),
 	(4,19,1,'a gosto'),
 	(4,20,1,'a gosto'),
 	(4,21,1,'a gosto'),
 	(4,22,1,'unidade'),
 	(4,23,1,'a gosto'),
 	(4,24,300,'gramas');

INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(4,1,'Preparação da massa'),
    (4,2,'Montagem da cobertura');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(4,1,1,'Misturar o fermento com o açucar e 1/4 xícara de água'),
    (4,1,2,'Em outro recipiente, dissolver o sal em 1/4 xícara de água'),
    (4,1,3,'Colocar a farinha de trigo em uma vasilha grande e cavar um buraco no meio. Acrescentar neste buraco a mistura do fermento, o azeite e a água salgada'),
    (4,1,4,'Acrescentar o restante da água aos poucos.'),
    (4,1,5,'Sovar bem a massa e fazer uma bola.'),
    (4,1,6,'Cobrir a massa com um pano de prato e deixar descansando por 2 horas.');
   	(4,2,1,'Forrar com azeite (cerca de 2 colheres de sopa) uma assadeira redonda para pizza, pegar a metade da massa e abrir com as mãos sobre a assadeira.'),
   	(4,2,2,'Colocar o molho de tomate sobre a massa, depois orégano, a mussarela, tomates e por fim jogue manjericão.'),
   	(4,2,3,'Regar com azeite. Assar em forno pré-aquecido em temperatura alta por cerca de 15 minutos.');
    
SELECT * FROM receitas;

-------------------------------------------------------------------------
------------------- Receita: Strogonoff de frango------------------------
-------------------------------------------------------------------------

INSERT INTO ingredientes(id,nome) VALUES 
	(25,'Peitos de frango cortados em cubos'),
    (26,'Alho picado'),
    (27,'Pimenta'),
	(28,'Maionese'),
	(29,'Cebola picada'),
	(30,'Ketchup'),
	(31,'Mostarda'),
	(32,'Cogumelos'),
	(33,'Creme de leite'),
	(34,'Batata palha');
    
INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(5,'Strogonoff de frango',10 ,60);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(5,25,3,'unidade'),
	(5,26,1,'unidade'),
	(5,10,1,'a gosto'),
	(5,27,1,'a gosto'),
	(5,28,2,'colher de sopa'),
	(5,32,1,'copo'),
	(5,33,1,'copo'),
	(5,34,1,'a gosto');
    
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(5,1,'Preparação do strogonoff'),

    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(5,1,1,'Em uma panela, misture o frango, o alho, a maionese, o sal e a pimenta'),
    (5,1,2,'Em uma frigideira grande, derreta a manteiga e doure a cebola'),
    (5,1,3,'Junte o frango temperado até que esteja dourado.'),
    (5,1,4,'Adicione os cogumelos, o ketchup e a mostarda.'),
    (5,1,5,'Incorpore o creme de leite e retire do fogo antes de ferver.'),
   	(5,1,6,'Sirva com arroz branco e batata palha.');
    
SELECT * FROM receitas;



-------------------------------------------------------------------------
---------------------- Receita: Palha italiana --------------------------
-------------------------------------------------------------------------

INSERT INTO ingredientes(id,nome) VALUES 
	(35,'Biscoito maisena');
    
INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(6,'Palha italiana', 30, 30);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(6,1,1,'lata'),
    (6,3,8,'colher de sopa'),
    (6,2,1/2,'colheres de sopa'),
    (6,35,1,'pacote');
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(6,1,'Preparação da palha italiana');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(6,1,1,'Pique o biscoito em pedacinhos pequenos e reserve.'),
    (6,1,2,'Com o leite condensado, a margarina e o chocolate em pó, faça um brigadeiro.'),
    (6,1,3,'Assim que o brigadeiro começar a soltar do fundo da panela, misture o biscoito picado até formar uma massa, retire do fogo.'),
    (6,1,4,'Unte uma bancada de mármore, ou alguma superfície lisa, com margarina e despeje essa massa.'),
    (6,1,5,'Abra a massa, batendo com a palma das mãos.'),
    (6,1,6,'Deixe esfriar e corte em quadradinhos');
   
-------------------------------------------------------------------------
------------------ Receita: Bolo de chocolate de caneca -----------------
-------------------------------------------------------------------------
   
   
INSERT INTO ingredientes(id,nome) VALUES 
	(36,'Leite');

INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(7,'Bolo de chocolate de caneca', 1, 5);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(7,11,1,'unidade'),
    (7,36,5,'colher de sopa'),
    (7,12,3,'colher de sopa'),
    (7,15,'duas e meia','colher de sopa'),
    (7,17,4,'colher de sopa'),
    (7,14,3,'colher de sopa'),
    (7,18,1,'colher de café'),
   	(7,2,1/2,'colher de sopa');
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(7,1,'Preparação da massa'),
    (7,2,'Preparação da calda');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(7,1,1,'Bata bem o ovo com um garfo, em uma caneca de 300 ml.'),
    (7,1,2,'Acrescente os outros ingredientes e bata mais até incorporar.'),
    (7,1,3,'Misture bem, para não ficar nenhum grumo.'),
    (7,1,4,'Leve ao microondas por 3 minutos, na potência máxima.'),
    (7,2,1,'Para a calda misture os ingredientes e leve ao microondas por 30 segundos.');
   
   
-------------------------------------------------------------------------
--------------------- Receita: Fricassê de grangp -----------------------
-------------------------------------------------------------------------
   
 INSERT INTO ingredientes(id,nome) VALUES 
	(37,'creme de leite'),
	(38,'milho'),
	(39,'requeijão cremoso'),
	(40, 'azeitona sem caroço'),
	(41,'peito de frango desfiado'),
	(42,'água');
	

INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(8,'Fricassê de frango', 5, 30);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(8,37,1,'lata'),
    (8,38,1,'lata'),
    (8,39,1,'copo'),
    (8,40,100,'gramas'),
    (8,41,2,'unidade'),
    (8,24,200,'gramas'),
    (8,34,100,'gramas'),
   	(8,42,1,'xícara'),
   	(8,10,1,'pitada');
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(8,1,'Preparação do fricassê');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(8,1,1,'Bata no liquidificador o milho, o requeijão, o creme de leite e a água.'),
    (8,1,2,'Refogue o creme do liquidificador com o frango desfiado, as azeitonas e o sal até ficar com uma textura espessa'),
    (8,1,3,'Coloque o refogado numa assadeira, cubra com mussarela e espalhe a batata palha por cima.'),
    (8,1,4,'Leve ao forno até borbulhar.'),
    (8,1,5,'Sirva com arroz branco.');
  

   
-------------------------------------------------------------------------
------------------------ Receita: Massa de Panqueca ---------------------
-------------------------------------------------------------------------
   
 
    
INSERT INTO receitas(id,nome,rendimento,tempo) VALUES 
	(9,'Massa de panqueca', 15, 30);
    
INSERT INTO receitas_ingredientes(receita_id,ingrediente_id,quantidade,unidade) VALUES
	(9,14,2,'xícara de chá'),
    (9,36,2,'xícara de chá'),
    (9,11,3,'unidade'),
    (9,10,1,'pitada');
    
INSERT INTO receitas_etapas(receita_id,numero,titulo) VALUES
	(9,1,'Preparação da massa da panqueca');
    
INSERT INTO receitas_passos( receita_id,etapa_numero, sequencia, instrucao ) VALUES
	(9,1,1,'Bata no liquidificador o milho, o requeijão, o creme de leite e a água.'),
    (9,1,2,'Em seguida desligue e, com uma colher, misture a farinha que grudou no copo do liquidificador.'),
    (9,1,3,'Bata novamente só para misturar e reserve.'),
    (9,1,4,'Unte a frigideira com um fio de óleo e leve ao fogo até aquecer.'),
    (9,1,5,'Com o auxílio de uma concha, pegue uma porção de massa e coloque na frigideira, gire a frigideira para espalhar bem a massa'),
    (9,1,6,'Abaixe o fogo e deixe dourar por baixo, em seguida vire do outro lado e deixe dourar, repita o processo com toda a massa.');


-- Funcionalidade: 
				-- Pesquisar receita por nome
                -- Pesquisar receita por ingredientes
				-- Entrar 
                -- Cadastrar
                -- Sair
                
-- Após Usuário entrar:
				-- Pesquisar receita por nome
                -- Pesquisar receita por ingredientes
				-- Cadastrar receitas
                -- Receitas salvas
                -- Logout
                -- Sair