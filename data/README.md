# Edificios

* edificio - (inteiro) identificador unico edificio
* nome - (String) nome do edificio
* latitude - (Decimal)
* longitude - (Decimal)
* morada - (String)
* preco_dia_m2 - (Decimal) preco diario por m2. Preco diario estudio = (preco_dia_m2 do edificio) x (area estudio) 

# Estudios

* estudio - (inteiro) identificador unico estudio
* numero - (inteiro) numero estudio relativo ao edificio
* edificio - (inteiro) identificador do edificio
* configuracao - (String) tipologia do estudio
* area - (inteiro) area do estudio em m2

# Eventos

* id - (inteiro) identificador unico do evento
* tipo - (String) tipo de evento
* data_inicio - (Data) marca temporal de inicio de evento, no formato: ano-mes-dia
* data_fim - (Data) marca temporal de fim de evento, no formato: ano-mes-dia
* hospede - (inteiro) identificador do hospede. Aplicado apenas a eventos do tipo estadia
* estudio - (inteiro) identificador do estudio
* plataforma - (String) identificador da plataforma de reserva

# Politicas

* politica - (String) identificador unico da politica de precos
* plataforma - (String) plataforma que adota a dita politica
* regras - (array de strings) conjunto de regras a serem aplicadas na politica. Separadas por espaço.

# Estudio_Politicas

* estudio - (inteiro) identificador do estudio
* politica - (politica) politica a concretizar
* regras - (array de strings) conjunto de regras que materializam a politica selecionada

# Notas

Entende-se por politica de precos um conjunto de regras de custo. Na sua versao base, cada plataforma devera definir uma politica de precos (sem apresentar valores concretos). Cada estudio devera concretizar as politicas de precos de cada uma das plataformas em que esta inserido.

e.g. estudio 2 concretiza a politica p1 com os valores 0.3 -0.2 0.3. Podemos entao assumir que o estudio 2 se encontra inserido na plataforma associada a politica p1 (airbnc) e que define as seguintes taxas/descontos:

* taxa adicional de 30% para estudio com uma configuracao especifica
* desconto de 20% para reservas superiores a um determinado numero de dias
* taxa adicional de 30% para epocas altas 

A parametrizacao da aplicabilidade de cada uma das regras podera ser efetuata de forma dinamica (idealmente) ou atraves de definicoes estaticas.

e.g. #define DURACAO 7 // desconto por duracao a aplicar em estadias superiores a 7 dias 