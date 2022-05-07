%% Fecha tudo e limpa variaveis e terminal
clear;
close all;
clc;

%%
format short eng
%% projeto Butterworth
% Para um filtro passa-baixa (PB)
% com ganho na banda passante de 1dB (f1 = 56kHz)
% ateniação da banda de corte de 20dB(f2 = 88kHz)

%% Qual a FT de um filtro butterworth que satisfaca esses requisitos
% ordem do filtro?
% frequencia de corte?

%% 1 - Especificacoes do filtro
A1 = 1;
A2 = 20;

f1= 56E3;
f2 = 88E3;

%% 2 - Conversao de unidades Ganho (dB) e Freq (Rad/s) 
% G_dB = 20 log(Vo/Vi)
% sabendo que Vo/Vi = G
% G = 10^(-|G_dB|/20)
G1 = 10^(-abs(A1)/20)
G2 = 10^(-abs(A2)/20)

% como w=2*pi*f
w1 = 2*round(pi, 3)*f1
w2 = 2*round(pi, 3)*f2

%% 3 - Analisando FT e obtendo n 
% sabendo que a funcao transferencia
% G1 = 1/ (1 + (w1/w0)^(2*n))^(1/2);
% temos w1 e w2, isolamos w0 nas duas equacoes
syms w0 n 
eqn1 = 1/(1 + (w1/w0)^(2*n)) - (G1)^2 ;
eqn2 = 1/(1 + (w2/w0)^(2*n)) - (G2)^2;

w01 = solve(eqn1, w0)
w02 = solve(eqn2, w0)

%igualamos w01 e w02 e encontramos a ordem n, arredondando a ordem sempre
%para cima
n_simp = solve(w01 == w02, n)
disp(double(n_simp))
n = ceil(n_simp)

%% 4- Obtido ordem n, encontrar a freq w0 
% note  w1 < w0 < w2
%       f1 < f0 < f2
% utlizamos a FT basta substituir n com G1 ou G2, isolando w0

% FT ->  G1 = 1/ (1 + (w1/w0)^(2*n))^(1/2);
% w0 = ((w1^(2*n))/(((1)/(G1^2)) - 1))^(1/(2*n)

num = w1^(2*n);
den = ((1)/(G1^2)) - 1;
w0 = double((num/den)^(1/(2*n)));
f0 = double(w0 / (2*pi));
disp("w1 < w0 < w2");
disp(w1+" < "+w0+" < "+w2+" Rad/s");
disp("f1 < f0 < f2");
disp(f1+" < "+f0+" < "+f2+" Hz");

%% 5 - FT do filtro projetado
% ganhos do filtro dado uma frequencia f
f = f1;
num = 1 ;
den = sqrt(1 + ( (2*pi*f) / (w0) ) )^( 2*n );
Hf = abs(num/den);

disp(double(Hf));
Hdb = 20 * log10( Hf );
disp(double(Hdb));


%% - Encontrando Polos da FT
syms k

pk(k) = w0 * exp( (j*pi) / 2 ) * exp( (j * pi * ((2*k)-1)) / (2*n));

p = [1:n];
for i=1:n
    disp(double( pk(i) ));
    p(i) = round(pk(i), 3);
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
% filtro com polos (p1 p7)
% comparando a funcao transferencia do filtro com a funcao de um 
% filtro sallen-key obtemos frequencia natural e fator de qualidade.

wn1 = sqrt(-round(p(1),3) * -round(p(7),3));
wn1 = round(wn1, 3)
% freq em Rad/s

% freq em Hz
fn1 = double(wn1 / (2*pi))

%fator de qualidade
Q1 = wn1 / (-p(1) + (-p(7)))   

% Projeto do circuito - 2° Ordem sallen-key
%syms R1 R2 C1 C2
%Qsk1 = (1 / (R1 + R2)) * sqrt( R1*R2*(C1/C2) );
%Wsk1 = 1/sqrt( R1*R2*C1*C2 );

% atribuindo um valor para o resistor e encontrando os capacitores.
R1 = 1000
R2 = R1

% fator qualidade e frequencia natural
Qsk1 = Q1;
Wsk1 = wn1;

C2 = double(1 / (sqrt((R1^2) * ((2*Qsk1)^2)) * Wsk1))
C1 = double(((2*Qsk1)^2) * C2)

%% filtro com polos (p2 p6)
wn2 = sqrt(-round(p(2),3) * -round(p(6),3));
wn2 = round(wn2, 3)
% freq em Rad/s

% freq em Hz
fn2 = double(wn2 / (2*pi))

%fator de qualidade
Q2 = wn2 / (-p(2) + (-p(6)))

% Projeto do circuito - 2° Ordem sallen-key
%syms R1 R2 C1 C2
%Qsk2 = (1 / (R1 + R2)) * sqrt( R1*R2*(C1/C2) );
%Wsk2 = 1/sqrt( R1*R2*C1*C2 );

% atribuindo um valor para o resistor e encontrando os capacitores.
R1 = 1000
R2 = R1

% fator qualidade e frequencia natural
Qsk2 = Q2;
Wsk2 = wn2;

C2 = double(1 / (sqrt((R1^2) * ((2*Qsk2)^2)) * Wsk2))
C1 = double(((2*Qsk2)^2) * C2)

%% filtro com polos p3 p5
wn3 = sqrt(-round(p(3),3) * -round(p(5),3));
wn3 = round(wn3, 3)
% freq em Rad/s
        
% freq em Hz
fn3 = double(wn3 / (2*pi))

%fator de qualidade
Q3 = wn3 / (-p(3) + (-p(5)))

% Projeto do circuito - 2° Ordem sallen-key
%syms R1 R2 C1 C2
%Qsk3 = (1 / (R1 + R2)) * sqrt( R1*R2*(C1/C2) );
%Wsk3 = 1/sqrt( R1*R2*C1*C2 );

% atribuindo um valor para o resistor e encontrando os capacitores.
R1 = 1000
R2 = R1

% fator qualidade e frequencia natural
Qsk3 = Q3;
Wsk3 = wn3;

C2 = double(1 / (sqrt((R1^2) * ((2*Qsk3)^2)) * Wsk3))
C1 = double(((2*Qsk3)^2) * C2)

%% Projeto do circuito - 1° Ordem

R = 1000
% wc = 1 / (R*C);
wc = abs(p(4))
C = double(1 / (R*wc))
fc = 1 / (2 * pi * R * C)

%% Ganho em 1 kHz
f = 1000;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 2.277627e-3;
erro = ((Ganho-simulado)/Ganho) *100


%% Ganho em f1 kHz
f = f1;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 1.0059;
erro = ((Ganho-simulado)/Ganho) * 100

%% Ganho em f0 kHz
f = f0;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 3.065;
erro = ((Ganho-simulado)/Ganho) *100
%% Ganho em f2 kHz
f = f2;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 21.750;
erro = ((Ganho-simulado)/Ganho) *100
%% Ganho em 10xf2 kHz
f = 10*f2;
Hs = evalfr(Gav, 2*pi*f*j);
Ganho = abs(double(20*log10(abs(Hs))))

simulado = 162.360;
erro = ((Ganho-simulado)/Ganho) *100