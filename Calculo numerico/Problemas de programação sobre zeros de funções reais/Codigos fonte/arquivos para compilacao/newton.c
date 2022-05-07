#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double funcao(double t){  
	double x= (3/(2*t));
	double h=(((20*t)*(sinh(x)))-32);
	return h;
	
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
	double e=0.000000001, x0=0, a=2, fx0=0, mfx0=0; int i=1; // inicializando as variaveis com os valores. 	

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
