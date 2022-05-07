%% Limpando variaveis
close all;
clear all;
clc; 
%% Sinal de entrada = Sinal Senoidal

% DADOS DA ATIVIDADE
A = 5;        % Amplitude
T = 40;       % Periodo
Ts = 1;       % Tempo de amostragem
NC = 2.5;     % Número de ciclos
NA = 40;      % Número de amostras por ciclo
NT = NA * NC; % Número total de pontos
TT = NT * Ts; % Tempo total de pontos
To = NA*Ts;   % período fundamental
fo = 1/To;    % frequência fundamental

t=0:Ts:TT;
y = zeros(1,NT+2);     %Raízes de y(n)
x = A*sin(2*pi*fo*t);  %Onda senoidal

%Laço de repetição
%Contador iniciando em 3 devido ao deslocamento y(n-2) 
for n=3:NT+1 
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
hold on; 
stem(x); 
stem(y,'r');
xlim([0 100]);
grid;
