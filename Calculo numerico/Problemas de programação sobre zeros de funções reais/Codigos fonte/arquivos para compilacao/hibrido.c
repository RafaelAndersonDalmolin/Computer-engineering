#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double funcao(double t){  
	double x= (3/(2*t));
	double h=(((20*t)*(sinh(x)))-32);
	return h;
	
}
double bisseccao(double a, double b){  
	double x= ((a+b)/2);
	return x;
}
double dfuncao(double t){  
	double x= (3/(2*t));
	double h=(20*(sinh(x)));
	double y= ((30/t) * cosh(x));
	double v= h-y;
	return v;
	
}
double newton(double a){  
  double x= a - (funcao(a)/dfuncao(a));
	return x;
}

double main(){
	double e=0.001,a=2, b=3, x0=0, fx0=0 ,mab=0, ab=0,mfx0=0; int i=1; // inicializando as variaveis com os valores. 	

		x0=bisseccao(a,b);    // faz a primeira iteraçao gerando xo como primeira raiz
		fx0=funcao(x0);		 // retorna o valor f(x0);
		printf("Raiz= %.11f\n",x0);	
		printf("fx0= %.11f\n",fx0);
		ab=b-a;
		if(ab < 0){     // gera o modulo do valor de f(x0)
			mab= ab * -1;	
		}
		else{
				mab=ab;
		}
		printf("modulo ab= %.11f\n\n",mab);

		while(mab > e){		//repete enquanto o modulo do valor x0 aplicado na funçao seja maior que o erro, condiçao de parada do metodo.	
			i++;
			if(fx0 < 0 && (funcao(a)) < 0 || fx0 > 0 && (funcao(a)) > 0 ){ // f(x0) tem sinal igual a f(a)?
				a=0; a=x0;    // troca o intervalo a=x0
			}
			else{			// caso f(x0) tenha sinal igual f(b)
				b=0; b=x0;     // troca o intervalo b=x0
			}
			x0=0,fx0=0; ab=0;  // zera as variaveis para evitar lixo na memoria
			x0=bisseccao(a,b);  // chama a funçao falsa posicao para a nova raiz x0
			fx0=funcao(x0);  // chama a funçao que retorna o valor de f(x0)
			ab=b-a;
			if(ab < 0){     // gera o modulo do valor de f(x0)
				mab= ab * -1;	
			}
			else{
					mab=ab;
			}
			printf("Raiz= %.11f\n",x0);	
			printf("fx0= %.11f\n",fx0);
			printf("modulo ab= %.11f\n\n",mab);
		}
		printf("Precisao do erro= %.9f\n",e);
		printf("Raiz= %.11f\n",x0);	
		printf("%d Numero de iteracoes\n",i);	
		printf("\n\n\n");	
		printf("troca de metodo *newton* \n\n");	
		printf("\n\n\n");	
//////////////////////////////////////////////////////
		e=0; e=0.000000001; a=0; a=x0; x0=0; fx0=0; mfx0=0; i=0; i=1;
		x0=newton(a);   // faz a primeira iteraçao gerando xo como primeira raiz
		fx0=funcao(x0);		 // retorna o valor f(x0);
		printf("Raiz= %.11f\n",x0);	
		printf("fx0= %.11f\n",fx0);
		if(fx0 < 0){     // gera o modulo do valor de f(x0)
			mfx0= fx0 * -1;	
		}
		else{
				mfx0= fx0;
		}
		printf("modulo f(x0)= %.11f\n\n",mfx0);	
		while(mfx0 > e){		//repete enquanto o modulo do valor x0 aplicado na funçao seja maior que o erro, condiçao de parada do metodo.	
			i++;
			a=0; a=x0; x0=0,fx0=0; // zera as variaveis para evitar lixo na memoria
			x0=newton(a);  // chama a funçao falsa posicao para a nova raiz x0
			fx0=funcao(x0);  // chama a funçao que retorna o valor de f(x0)

			if(fx0 < 0){     // gera o modulo do valor de f(x0)
				mfx0= fx0 * -1;	
			}
			else{
					mfx0= fx0;
			}
			printf("Raiz= %.11f\n",x0);	
			printf("fx0= %.11f\n",fx0);
			printf("modulo f(x0)= %.11f\n\n",mfx0);
		}
		printf("Precisao do erro= %.9f\n",e);
		printf("Raiz= %.11f\n",x0);	
		printf("%d Numero de iteracoes\n",i);		

														
}
