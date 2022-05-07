%% Fecha tudo e limpa variaveis e terminal
clear;
close all;
clc;

%%
format short eng
%% projeto chebyshev
% Para um filtro passa-baixa (PB)
% com ganho na banda passante de 1dB (f1 = 56kHz)
% ateniação da banda de corte de 20dB(f2 = 88kHz)

%% 1 - Especificacoes do filtro
A1 = 1;
A2 = 20;

f1= 56E3;
f2 = 88E3;

%% %% 2 - Conversao de unidades Ganho (dB) e Freq (Rad/s) 
% fazendo a diferenca entre pico menos o ripple minimo e utilizando
% propiedades do log(a/b), isolamos o epsilon o com ganho de A1.
epsilon = sqrt((10^(abs(A1)/20))^2 - 1)

% G_dB = 20 log(Vo/Vi)
% sabendo que Vo/Vi = G
% G = 10^(-|G_dB|/20)
% G1 = 10^(-abs(A1)/20);
G2 = 10^(-abs(A2)/20);

% como w=2*pi*f
w1 = 2*round(pi, 3)*f1
w2 = 2*round(pi, 3)*f2

%% 3 - Obtendo w0 devido transicao abrupta
w0 = w1
f0 = w1/(2*pi);

%% 4 - Analisando FT e obtendo n 
% sabendo que a funcao transferencia
% G2 = 1/ (1 +  (epsilon^2)*cosh²(n* acosh(w2/w1)))
% como G2 é o ganho na frequencia w2, isolamos n e encontramos a ordem 

num1 = acosh(sqrt(((1/abs(G2)^2) - 1) / epsilon^2));
num2 = 1/acosh(w2/w1);
n = num1 * num2
n = ceil(n)

%% 5 - FT filtro projetado utilizando o polinomio chebychev
% polinomio C 

c4 = 8*(w2/w0)^4 - 8*(w2/w0)^2 + 1;
den = sqrt(1 + ((epsilon^2)*(c4)^2));

H = abs(1 / den);
Hdb = 20*log(H);
%% - encontrando Polos da FT
syms k

parte1 = -w0 * sin((((2*k)-1)*pi)/(2*n)) * sinh((1/n) * asinh(1/epsilon));
parte2 =  w0 * cos((((2*k)-1)*pi)/(2*n)) * cosh((1/n) * acosh(1/epsilon));
pk(k) = parte1 + parte2*1j;

p = [1:n];
for i=1:n
    disp(double( pk(i) ))
    p(i) = vpa( pk(i) );
end;

%% Montando funcao transferencia a partir dos polos
%         (-p1)*(-p2)*...*(-pn)
% h(s) = -------------------------
%        (s-p1)* (s-p2)*...*(s-pn) 

% numerador 
% faz a operacao (-p1)*(-p2)*...*(-pn)
num = double(real(prod(-p)));

% denominador 
% cria um vetor com (s-p1)* (s-p2)*...*(s-pn)
syms s
exp = (s - p(1));
for i=2:n
    exp = exp * (s - p(i)) ;
end
% Faz a operacao de multiplicacao deixando na forma
% s^n + coef s^(n-1) + ... + coef
den = expand(vpa(exp));

% pega os coeficientes e coloca em um vetor para criar um FT do filtro
den = double(fliplr(real(coeffs(den))));
Gav = tf(num, den);

%% Plota o lugar de raizes e bode da funcao tranferencia do filtro
% figure
% rlocus(Gav)

figure
subplot(1,2,1)
compass(p)

subplot(1,2,2)
rlocus(Gav)

figure
P = bodeoptions;
P.FreqUnits = 'Hz';
P.Grid='on';    
% P.Xlim = {[10^3 1*10^12]};
% P.Ylim = {[-1000 0]};
bode(Gav,P);
P.XlimMode = 'auto';

%% componentes para montar um filtro sallen-key passa baixa ativo
% filtro com polos (p1 p4)
% comparando a funcao transferencia do filtro com a funcao de um 
% filtro sallen-key obtemos frequencia natural e fator de qualidade.

wn1 = sqrt(-round(p(1),3) * -round(p(4),3));
wn1 = round(wn1, 3)
% freq em Rad/s

% freq em Hz
fn1 = double(wn1 / (2*pi))

%fator de qualidade
Q1 = wn1 / (-p(1) + (-p(4))) 

% Projeto do circuito - 2° Ordem sallen-key
%syms R1 R2 C1 C2
%Qsk1 = (1 / (R1 + R2)) * sqrt( R1*R2*(C1/C2) );
%Wsk1 = 1/sqrt( R1*R2*C1*C2 );

% atribuindo um valor para o resistor e encontrando os capacitores.
R1 = 1000;
R2 = R1;

% fator qualidade e frequencia natural
Qsk1 = Q1;
Wsk1 = wn1;

C2 = double(1 / (sqrt((R1^2) * ((2*Qsk1)^2)) * Wsk1))
C1 = double(((2*Qsk1)^2) * C2)

%% filtro com polos (p2 p3)
wn2 = sqrt(-round(p(2),3) * -round(p(3),3));
wn2 = round(wn2, 3)
% freq em Rad/s

% freq em Hz
fn2 = double(wn2 / (2*pi))

%fator de qualidade
Q2 = wn2 / (-p(2) + (-p(3)))

% Projeto do circuito - 2° Ordem sallen-key
%syms R1 R2 C1 C2
%Qsk2 = (1 / (R1 + R2)) * sqrt( R1*R2*(C1/C2) );
%Wsk2 = 1/sqrt( R1*R2*C1*C2 );

% atribuindo um valor para o resistor e encontrando os capacitores.
R1 = 1000;
R2 = R1;

% fator qualidade e frequencia natural
Qsk2 = Q2;
Wsk2 = wn2;

C2 = double(1 / (sqrt((R1^2) * ((2*Qsk2)^2)) * Wsk2))
C1 = double(((2*Qsk2)^2) * C2)

%% Ganho em 1 kHz
f = 1000;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 3.0225435e-3;
erro = ((Ganho-simulado)/Ganho) *100

%% Ganho em 5 kHz
f = 5000;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 0.109;
erro = ((Ganho-simulado)/Ganho) *100

%% Ganho em f1 kHz
f = f1;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 459.88e-3;
erro = ((Ganho-simulado)/Ganho) *100

%% Ganho em f2 kHz
f = f2;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 23.232;
erro = ((Ganho-simulado)/Ganho) *100
%% Ganho em 10xf2 kHz
f = 10*f2;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 107.388;
erro = ((Ganho-simulado)/Ganho) *100