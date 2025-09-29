/* Ya que el método de la secante no funciona solo para hallar raíces en un intervarlo definido,
sino que solo funciona para hallar una sola raíz, ya más adelante se implementará con un método numérico híbrido
	
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
using namespace std;

double f(double x, int opcion){
    switch(opcion){
        case 1: return sin(x)*pow(x, 2) - x;
        case 2: return pow(x, 5) - 4;
        case 3: return tanh(x) - 0.5*x;
        case 4: return exp(-x)*sin(x) + 0.1*x;
        case 5: return pow(x, 3) - 3*x + sin(x);
        case 6: return cos(x)*pow(x, 3) - x;
        case 7: return sin(x)*pow(x-2, 2) - cos(x);
        default: return 0;
    }
}

int main(){
	system("chcp 65001 > nul");
	int repetir;
	
	do {
		system("cls");
		int opcion;
		double x_1, x0, xn, f_1, f0, tol = 1e-6;
		
		cout<<"----- MÉTODO DE LA SECANTE PARA ENCONTRAR UNA ÚNICA RAÍZ -----"<<endl;
        cout<<endl;
        cout<<"Por favor eleccione una función de prueba:"<<endl;
		cout<<"1. f(x) = sin(x)*pow(x, 2) - x"<<endl;
        cout<<"2. f(x) = pow(x, 5) - 4"<<endl;
        cout<<"3. f(x) = tanh(x) - 0.5*x"<<endl;
        cout<<"4. f(x) = exp(-x)*sin(x) + 0.1*x"<<endl;
        cout<<"5. f(x) = pow(x, 3) - 3*x + sin(x)"<<endl;
        cout<<"6. f(x) = cos(x)*pow(x, 3) - x"<<endl;
        cout<<"7. f(x) = sin(x)*pow(x-2, 2) - cos(x)"<<endl;
		cout<<endl;
		cout<<"Ingrese un número del 1 al 7 de la función que desea probar: ";
		cin>>opcion;
		cout<<endl;
		cout<<"Ingrese dos valores iniciales para encontrar la raiz (x0, x1)"<<endl;
		cout<<"valor inicial x_1 = ";
        cin>>x_1;
        cout<<"valor inicial x0 = ";
        cin>>x0;
		cout<<endl;
		cout<<"Buscando raiz..."<<endl;
        Sleep(1000);
        cout<<endl;
        
		int iterations = 0;
		int maxIterations = 100;
		bool foundRoot = false;
		
		do{
			f_1 = f(x_1, opcion);
			f0 = f(x0, opcion);
			
			if(abs(f_1 - f0) < 1e-10) {
				cout << "Error: La division por cero es inminente. Los valores iniciales son muy cercanos." << endl;
				break;
			}
			
			xn = x0 - f0 * ((x_1 - x0) / (f_1 - f0));
			x_1 = x0;
			x0 = xn;
			iterations++;
			if(abs(x0-x_1)/abs(x0) < tol){
				foundRoot = true;
			}
		} while(!foundRoot && iterations < maxIterations);
		
		if(foundRoot){
			cout << "Raíz encontrada en: " << fixed << setprecision(10) << x0 << endl;
		} else {
			cout << "No se pudo encontrar una raíz después de " << maxIterations << " iteraciones." << endl;
			cout << "Intente con diferentes valores iniciales." << endl;
		}
		
		cout << endl << "Presione 1 para probar otra funcion o 0 para salir: ";
        cin >> repetir;
	} while(repetir == 1);
	
	return 0;
}