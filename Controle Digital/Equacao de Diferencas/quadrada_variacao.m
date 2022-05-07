%% Controle Digital - equacao de diferencas
clear;
close all;
clc;

%% Sinal de Onda Quadrada

N = 100;%numero de pontos
A = 5;%amplitude do sinal
x_sqr = zeros(1,N);% iniciando vetor de zeros 
y_sqr1 = zeros(1,N+2);% iniciando vetor de zeros
y_sqr2 = zeros(1,N+2);% iniciando vetor de zeros
y_sqr3 = zeros(1,N+2);% iniciando vetor de zeros
k = 0;

for n=3:N
    x_sqr(n) = 5;
    k = k+1;
    
    if k>20 
        x_sqr(n) = 0; 
    end
    if k>40
        k = 0;
    end
    
    a1 = 0.2;
    a0 = 0.9;
    y_sqr1(n) = a0*y_sqr1(n-1) - a1*y_sqr1(n-2) + 0.4*x_sqr(n-1) + 0.1*x_sqr(n-2); 
   
    a1 = 0.5;
    a0 = 0.5;
    y_sqr2(n) = a0*y_sqr2(n-1) - a1*y_sqr2(n-2) + 0.4*x_sqr(n-1) + 0.1*x_sqr(n-2); 
    
    a1 = 0.9;
    a0 = 0.2;
    y_sqr3(n) = a0*y_sqr3(n-1) - a1*y_sqr3(n-2) + 0.4*x_sqr(n-1) + 0.1*x_sqr(n-2); 
   

end
 

% plotando os 3 graficos
% subplot(5,2,1);
% stem(x_sqr, 'k')
% xlim([0 100])
% title('Grafico da onda quadrada')

subplot(3,1,1);
stem(y_sqr1, 'r')
xlim([0 100])
title('Grafico da Saída a0 > a1')

subplot(3,1,2);
stem(y_sqr2, 'b')
xlim([0 100])
title('Grafico da Saída a0 = a1')

subplot(3,1,3);
stem(y_sqr3, 'g')
xlim([0 100])
title('Grafico da Saída a0 < a1')

% subplot(5,2,[5 6]);
% hold on; stem(x_sqr, 'k'); stem(y_sqr1, 'r')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 > a1')
% legend('x[n]', 'y[n]')
% 
% subplot(5,2,[7 8]);
% hold on; stem(x_sqr, 'k'); stem(y_sqr2, 'b')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 = a1')
% legend('x[n]', 'y[n]')
% 
% 
% subplot(5,2,[9 10]);
% hold on; stem(x_sqr, 'k'); stem(y_sqr3, 'g')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 < a1')
% legend('x[n]', 'y[n]')