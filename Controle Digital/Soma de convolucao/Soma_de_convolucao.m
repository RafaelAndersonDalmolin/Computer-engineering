%% RESET
close all; % Fechar figuras
clear all; % Limpar variaveis
clc; % Limpar Command Window

%% Function g[n]

% DADOS DA ATIVIDADE
Tg = 0.5;    % Periodo
alpha = 0.2; % Alpha
omega = 1;   % Omega

for n = 1:81 % Iniciando vetor da função g[n] com 80 pontos
    g(1,n) = 1 - exp(-alpha*Tg*(n-1)) .* cos(omega * Tg * (n-1)); % Função g[n]
end

%% Function x[n] (Onda triangular)

% DADOS DA ATIVIDADE ATRAVÉS DO GRÁFICO
A = 4;        % Amplitude
T = 20;       % Periodo
Ts = 0.5;     % Tempo de amostragem
NC = 2;       % Número de ciclos
NA = 40;      % Número de amostras por ciclo
NT = NA * NC; % Número total de pontos
TT = NT * Ts; % Tempo total de pontos

% Inicializacao de um vetor para criação da onda triangular
x = zeros(1, NT+1);

for k=1:NA+1 % Gerando sinal triangular
    if(k >= 1 && k<=21) % SUBIDA
        x(1,k) = 0.2*(k-1);
    end
    
    if(k > 21 && k<=41) % DESCIDA
        x(1,k) = 0.2*(40-(k-1));
    end
end

% Preenchendo o vetor x com 80 pontos de um sinal triangular
for j=NA+1:NT+1 
  x(1,j) = x(1,j-NA);
end

% O script para a convolução é apresentado abaixo podendo ser usado função
% nativa do matlab ou script feito ? .
%% CONVOLUÇÃO - USANDO FUNÇÃO MATLAB - g[n] * x[n]
y1 = conv(g, x); % Convolução
% Como a função conv() retorna mais que 80 pontos 
% vamos pegar somente os 80 primeiros pontos (NT)
y = y1(1:1:NT+1);


%% CONVOLUÇÃO - CRIANDO FUNÇÃO - g[n] * x[n]
for n=1:NT+1    
    for k=1:NT+1 % Convolucao
        if (k<n) 
            y(n)=y(n)+x(k)*g(n-k);
        end
    end
end

%% A ONDA TRIANGULAR DA ENTRADA E A RESPOSTA A ESTA ONDA - PLOT
t=0:Ts:TT; % Criando vetor de tempo com 80 pontos

% Criando uma figura
figure  
% Criando um subplot na figura
subplot(311) 
% Plot do gráfico da resposta g[n]
stem(t, g, 'r:', 'Linewidth',1); 
% Título do gráfico
title('Resposta ao degrau')
% Nome e unidade do eixo X
xlabel('Tempo (s)') 
% Nome e unidade do eixo Y
ylabel('g[n]') 

% Plot do sinal de entrada triangular
subplot(312) 
stem(t, x, 'b:','Linewidth',1);
title('Sinal de entrada (Sinal triangular)') 
xlabel('Tempo (s)') 
ylabel('x[n]') 

% Plot do gráfico do sinal de saída (resultado da convolução)
subplot(313) 
stem(t,y,'g:','Linewidth',1); 
title('Sinal de saída')
xlabel('Tempo (s)') 
ylabel('y[n]') 

%% A RESPOSTA AO DEGRAU E A RESPOSTA AO IMPULSO

% DEGRAU
x1 = ones(1, 81); % Criando um vetor de um com tamanho de 80
w= conv(g, x1);   % Convolução de g[n] com o degrau (x1)

% Pegando somente os 80 primeiros pontos (NT)
result = w(1:1:NT+1);

figure % Criando uma nova figura
stem(t, result) % Plot da resposta ao degrau (convolução)
title('Resposta da convolução g[n] com degrau') % Título do gráfico
xlabel('Tempo (s)') % Nome e unidade do eixo X
ylabel('y[n]') % Nome e unidade do eixo Y

% IMPULSO
x2 = zeros(1,81); % Criando um vetor de zero com tamanho de 80
x2(1,1) = 1; % Definindo o primeiro indice igual a 1
w2 = conv(g, x2); % Convolução de g[n] com impulso unitário (x2)

% Pegando somente os 80 primeiros pontos (NT)
result2 = w2(1:1:NT+1);

figure % Criando uma nova figura
stem(t, result2) % Plot da resposta ao impulso (convolução)
title('Resposta da convolução g[n] com impulso') % Título do gráfico
xlabel('Tempo (s)') % Nome e unidade do eixo X
ylabel('y[n]') % Nome e unidade do eixo Y

%% A RESPOSTA A ONDA TRIANGULAR COM UM RUÍDO RANDÔMICO
%  COM DISTRIBUIÇÃO NORMAL E DESVIO PADRÃO DE 0.5.

% Definindo desvio padrão igual a 0.5 (conforme enunciado)
desvioPadrao = 0.5; 
%Escolhendo um valor de média arbitrária
media = 0.5; 

% Gerando um vetor randômico com desvio Padrão e média definida
% anteriormente
R = media + desvioPadrao .* (randn(1,81));

% Aplicando o ruído a onda triangular
Ruido = x + R;

figure % Criando uma nova figura
stem(t, Ruido) % Plot do gráfico da onda triangular com ruído
title('Sinal triangular com ruído')
xlabel('Tempo (s)')
ylabel('x[n]')

% CONVOLUÇÃO COM RUIDO
w3 = conv(Ruido, g); % Convolução do ruído com o sinal g[n]
result3 = w3(1:1:NT+1);

% PLOT DO SINAL DE SAÍDA COM E SEM RUÍDO

% COM RUÍDO
figure
subplot(211)
stem(t, result3)% Plot do sinal triangular com ruído (convolução)
title('Resposta a onda triangular com ruído')
xlabel('Tempo (s)')
ylabel('y[n]')

% SEM RUÍDO
subplot(212)
stem(t, y,'b:','Linewidth',1);% Plot do sinal sem ruído
title('Sinal de saída sem ruido')
xlabel('Tempo (s)')
ylabel('y[n]')



