%% Limpando variaveis
close all;
clear all;
clc; 
%% Sinal de entrada = Sinal Quadrado

% DADOS DA ATIVIDADE
A = 5;        % Amplitude
T = 40;       % Periodo
Ts = 1;       % Tempo de amostragem
NC = 2.5;     % Número de ciclos
NA = 40;      % Número de amostras por ciclo
NT = NA * NC; % Número total de pontos
TT = NT * Ts; % Tempo total de pontos

t = 0:Ts:TT+1;
x = zeros(1,NT+1);   %inicializacao de x
y = zeros(1,NT+1);   %inicializacao de y
k = 0;            %inicializando k

%Laço de repetição
%Contador iniciando em 3 devido ao deslocamento y(n-2) 
for n=3:NT
   
    x(n) = 5;
    k = k+1;
    if k > 20 
        x(n) = 0;
    end
    if k>40
        k=0;
    end
    
    %Equação de diferenças y(n) obtida
    y(n) = (8*y(n-1) - 3*y(n-2) + 4*x(n-1) + x(n-2))/10;
    
    %Teste com outros coeficientes 
    %y(n) = (6*y(n-1) - 1*y(n-2) + 3*x(n-1) + 0.8*x(n-2))/10;
    
end

%Plotando os 3 gráficos
figure
subplot(2,2,1); 
stem(x); 
xlim([0 100]);
title('Entrada X[n]');
grid;
subplot(2,2,2); 
stem(y, 'r'); 
xlim([0 100]);
title('Saída Y[n]');
grid;
subplot(2,2,[3 4]);
title('Equação de diferenças');
hold on; stem(x); 
stem(y,'r');
xlim([0 100]);
grid;
