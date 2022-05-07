% Controle Digital - equacao de diferencas
clear;
close all;
clc;


%% Sinal de Onda Impulso

N = 100;%numero de pontos
A = 5;%amplitude do sinal
x_imp = zeros(1,N);% iniciando vetor de zeros 
y_imp1 = zeros(1,N);% iniciando vetor de zeros 
y_imp2 = zeros(1,N);% iniciando vetor de zeros 
y_imp3 = zeros(1,N);% iniciando vetor de zeros 
k = 0;

for n=3:N
    k = k+1;
    if k == 1
        x_imp(n) = A;% impulso 
    end
    
    a1 = 0.2;
    a0 = 0.9;
    y_imp1(n) = a0*y_imp1(n-1) - a1*y_imp1(n-2) + 0.4*x_imp(n-1) + 0.1*x_imp(n-2); 
   
    a1 = 0.5;
    a0 = 0.5;
    y_imp2(n) = a0*y_imp2(n-1) - a1*y_imp2(n-2) + 0.4*x_imp(n-1) + 0.1*x_imp(n-2); 
    
    a1 = 0.9;
    a0 = 0.2;
    y_imp3(n) = a0*y_imp3(n-1) - a1*y_imp3(n-2) + 0.4*x_imp(n-1) + 0.1*x_imp(n-2); 
end
   
% plotando os 3 graficos
% subplot(5,2,1);
% stem(x_imp, 'k')
% xlim([0 100])
% title('Grafico do impulso')

subplot(3,1,1);
stem(y_imp1, 'r')
xlim([0 100])
title('Grafico da Saída a0 > a1')

subplot(3,1,2);
stem(y_imp2, 'b')
xlim([0 100])
title('Grafico da Saída a0 = a1')

subplot(3,1,3);
stem(y_imp3, 'g')
xlim([0 100])
title('Grafico da Saída a0 < a1')

% subplot(5,2,[5 6]);
% hold on; stem(x_imp, 'k'); stem(y_imp1, 'r')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 > a1')
% legend('x[n]', 'y[n]')
% 
% subplot(5,2,[7 8]);
% hold on; stem(x_imp, 'k'); stem(y_imp2, 'b')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 = a1')
% legend('x[n]', 'y[n]')
% 
% 
% subplot(5,2,[9 10]);
% hold on; stem(x_imp, 'k'); stem(y_imp3, 'g')
% xlim([0 100])
% title('Grafico da equacoes de diferencas a0 < a1')
% legend('x[n]', 'y[n]')