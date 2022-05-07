% Controle Digital - equacao de diferencas
clear;
close all;
clc;

%% Sinal de Onda Senoidal

N = 100;%numero de pontos
A = 5; % amplitude do sinal
Ts = 1e-1; % periodo de amostragem
NC = 3; % numero de ciclos
NA = 40; % numero de amostras/ciclo
To = NA*Ts;%periodo da onda
NT = NA * NC; % numero total de pontos
TT = NT * Ts; % tempo total do grafico

fo = 1/To;%frequencia da onda

t=0:Ts:TT;

x_sin = A*sin (2*pi*fo*t);% iniciando senoide 
y_sin1 = zeros(1,N+2);% iniciando vetor de zeros
y_sin2 = zeros(1,N+2);% iniciando vetor de zeros
y_sin3 = zeros(1,N+2);% iniciando vetor de zeros


%% Variando apenas o r
for n=3:N
    % equacao de diferencas y[n]
%     y_sin(n) = 0.8*y_sin(n-1) - 0.3*y_sin(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2);
    
%     0 < r < 1 e 0 <= theta <= pi
%    theta = 0 -> filtro passa baixa
%    theta entre 0 e pi passa faixas
%    thehta = pi passa altas
    r = 0.1;
    theta = pi;
    y_sin1(n) = r*cos(theta)*y_sin1(n-1) - (r^2)*y_sin1(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2); 
   
    r = 0.5;
    theta = pi;
    y_sin2(n) = r*cos(theta)*y_sin2(n-1) - (r^2)*y_sin2(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2); 
    
    r = 0.8;
    theta = pi;
    y_sin3(n) = r*cos(theta)*y_sin3(n-1) - (r^2)*y_sin3(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2); 
end
 
figure 
% plotando os 3 graficos
subplot(5,2,1);
stem(x_sin, 'k')
xlim([0 100])
title('Grafico da Senoide')

subplot(5,2,2);
stem(y_sin1, 'r')
xlim([0 100])
title('Grafico da Senoide')

subplot(5,2,3);
stem(y_sin2, 'r')
xlim([0 100])
title('Grafico da Senoide')

subplot(5,2,4);
stem(y_sin3, 'r')
xlim([0 100])
title('Grafico da Senoide')

subplot(5,2,[5 6]);
hold on; stem(x_sin, 'k'); stem(y_sin1, 'r')
xlim([0 100])
title('Grafico da equacoes de diferencas')
legend('x[n]', 'y[n]')

subplot(5,2,[7 8]);
hold on; stem(x_sin, 'k'); stem(y_sin2, 'r')
xlim([0 100])
title('Grafico da equacoes de diferencas')
legend('x[n]', 'y[n]')


subplot(5,2,[9 10]);
hold on; stem(x_sin, 'k'); stem(y_sin3, 'r')
xlim([0 100])
title('Grafico da equacoes de diferencas')
legend('x[n]', 'y[n]')

%% Variando apenas o theta
for n=3:N
    % equacao de diferencas y[n]
%     y_sin(n) = 0.8*y_sin(n-1) - 0.3*y_sin(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2);
 
    a1 = 0.2;
    a0 = 0.9;
    y_sin1(n) = a0*y_sin1(n-1) - a1*y_sin1(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2); 
   
    a1 = 0.5;
    a0 = 0.5;
    y_sin2(n) = a0*y_sin2(n-1) - a1*y_sin2(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2); 
    
    a1 = 0.9;
    a0 = 0.2;
    y_sin3(n) = a0*y_sin3(n-1) - a1*y_sin3(n-2) + 0.4*x_sin(n-1) + 0.1*x_sin(n-2); 
end
 
% plotando os 3 graficos
% subplot(5,2,1);
% stem(x_sin, 'k')
% xlim([0 100])
% title('Grafico da Senoide')

subplot(3,1,1);
stem(y_sin1, 'r')
xlim([0 100])
title('Grafico da Saída a0 > a1')

subplot(3,1,2);
stem(y_sin2, 'b')
xlim([0 100])
title('Grafico da Saída a0 = a1')

subplot(3,1,3);
stem(y_sin3, 'g')
xlim([0 100])
title('Grafico da Saída a0 < a1')

% subplot(5,2,[5 6]);
% hold on; stem(x_sin, 'k'); stem(y_sin1, 'r')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 > a1')
% legend('x[n]', 'y[n]')
% 
% subplot(5,2,[7 8]);
% hold on; stem(x_sin, 'k'); stem(y_sin2, 'b')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 = a1')
% legend('x[n]', 'y[n]')
% 
% 
% subplot(5,2,[9 10]);
% hold on; stem(x_sin, 'k'); stem(y_sin3, 'g')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 < a1')
% legend('x[n]', 'y[n]')