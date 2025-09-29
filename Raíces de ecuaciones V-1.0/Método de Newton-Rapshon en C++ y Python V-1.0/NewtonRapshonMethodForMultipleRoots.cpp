#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <sstream>
#include <thread>

using namespace std;

double f(double x, int opcion){
    switch(opcion){
        case 1: return sin(x)*pow(x, 2) - x;               
        case 2: return pow(x, 5) - 4;                 
        case 3: return tanh(x) - 0.5*x;     // THis has to be evaluated for later since it has a lot of noise and it seems is not continues so I have to create like some sort of condition when this               
        case 4: return exp(-x)*sin(x) + 0.1*x;            
        case 5: return pow(x, 3) - 3*x + sin(x);           
        case 6: return cos(x)*pow(x, 3) - x;               
        case 7: return sin(x)*pow(x-2, 2) - cos(x);        
        default: return 0;
    }
}

double df(double x, int opciondf){
    switch(opciondf){
        case 1: return cos(x)*pow(x, 2) + 2*x*sin(x) - 1;                      
        case 2: return (x-1)*(-x*sin(x) + sin(x) + 2*cos(x));                   
        case 3: return 1.0/pow(cosh(x), 2) - 0.5;          
        case 4: return exp(-x)*(cos(x) - sin(x)) + 0.1;                       
        case 5: return 3*pow(x, 2) - 3 + cos(x);                               
        case 6: return -sin(x)*pow(x, 3) + 3*pow(x, 2)*cos(x) - 1;              
        case 7: return (2*x - 3)*sin(x) + pow(x - 2, 2)*cos(x);           
        default: return 0;
    }
}

double ddf(double x, int opcionddf){
    switch(opcionddf){
        case 1: return -sin(x)*pow(x, 2) + 4*x*cos(x) + 2*sin(x);               
        case 2: return (-pow(x, 2) + 2*x + 1)*cos(x) - 4*(x - 1)*sin(x);         
        case 3: return -2*tanh(x)/pow(cosh(x), 2);    
        case 4: return -2*exp(-x)*cos(x);                                     
        case 5: return 6*x - sin(x);                                          
        case 6: return -6*pow(x, 2)*sin(x) - pow(x, 3)*cos(x) + 6*x*cos(x);     
        case 7: return (4*x - 7)*cos(x) - sin(x)*(pow(x, 2) -4*x + 2);        
        default: return 0;
    }
}

int main() {
    system("chcp 65001 > nul");
    int repetir;
    do{
        system("cls");

        int opcion;
        double xi, xf, x0, xn, xn1, paso, dfx;
        int iter, maxIter=100;
        double tol = 1e-6;               // tolerancia de convergencia
        double toleranciaRaiz = 1e-10;   // tolerancia para comparar raíces repetidas

        vector<double> xValores, yValores, raices, RaicesP, erroresP, errores;

        cout<<"----- MÉTODO DE NEWTON-RAPHSON PARA ENCONTRAR MÚLTIPLES RAÍCES -----"<<endl;
        cout<<endl;
        cout<<"Por favor seleccione una función de prueba:"<<endl;
        cout<<"1. f(x) = sin(x)*pow(x, 2) - x"<<endl;
        cout<<"2. f(x) = pow(x, 5) - 4"<<endl;
        cout<<"3. f(x) = tanh(x) - 0.5*x"<<endl;
        cout<<"4. f(x) = exp(-x)*sin(x) + 0.1*x"<<endl;
        cout<<"5. f(x) = pow(x, 3) - 3*x + sin(x)"<<endl;
        cout<<"6. f(x) = cos(x)*pow(x, 3) - x"<<endl;
        cout<<"7. f(x) = sin(x)*pow(x-2, 2) - cos(x)"<<endl;
        cout<<endl;
        cout<<"(ingrese un número del 1 al 7): ";
        cin>>opcion;
        
        cout<<endl;
        cout<<"Paso 1: Hacer la gráfica de f(x) para diferentes valores x."<<endl;
        cout<<"Ingrese xi: ";
        cin>>xi;
        cout<<"Ingrese xf: ";
        cin>>xf;
        cout<<"Por favor ingrese el paso de cada iteración (Ej: 1, 0.5, .., 0.1 ): ";
        cin>>paso;
        cout<<endl;
        cout<<"Evaluando función en el intervalo ["<< xi <<", "<< xf <<"]..."<<endl;
        Sleep(1000);
        cout<<endl;
        
        ofstream archivo1("xValoresYvalores.csv");
        archivo1 << "x, f(x)\n";
        for(double i = xi; i <= xf; i += paso) {
            double fx = f(i, opcion);
            xValores.push_back(i);
            yValores.push_back(fx);
            archivo1 << fixed << setprecision(4) << i << ", " << fx << "\n";
        }
        archivo1.close();
        
        for(double i = xi; i <= xf; i = i + paso) {
            x0 = i;
        
            if(abs(f(x0, opcion) * ddf(x0, opcion)) < pow(abs(df(x0, opcion)), 2)) {// Condición de Kantorovich, que garantizan la existencia de una solución y la convergencia del método de Newton hacia ella,
                xn = x0;
                iter = 0;
        
                do {
                    dfx = df(xn, opcion);
                    if(dfx == 0) break; 
                    xn1 = xn - f(xn, opcion) / dfx;
        
                    // Criterio de parada
                    if(fabs(xn1 - xn) <= tol) break;
                    xn = xn1;
                    iter++;
                    if(iter > maxIter) break;
        
                } while(fabs(f(xn, opcion)) > tol);
        
                // Si converge, verificar duplicados
                
				if(fabs(f(xn, opcion)) <= tol) {
				    bool esRaizRepetida = false;
				    
				    // Verificar si esta raíz ya existe comparando con todas las raíces encontradas
				    for(int j = 0; j < raices.size(); j++) {
				        if(fabs(raices[j] - xn) <= toleranciaRaiz) {
				            
				            esRaizRepetida = true;
				            break;
				        }
				    }
				    
				    // Si no es repetida, agregarla como nueva raíz
				    if(!esRaizRepetida) {
				        raices.push_back(xn);
				    }
				}
            }
        }

        // Guardar raíces y errores en archivo
        ofstream archivo2("RaicesYerrores.csv");
        archivo2 << "Raiz, Error\n";
        for(int i=0; i<raices.size(); i++){
            archivo2 << fixed << setprecision(4)
                     << raices[i] << ", "
                     << (fabs(f(raices[i], opcion))) << "\n";
        }
        archivo2.close();
        

        cout<<"Creando Gráfica..."<<endl;
        Sleep(1000);
        system("\"C:\\Users\\jdecr\\AppData\\Local\\Programs\\Python\\Python313\\python.exe\" VisualizationNewtonRaphsonMethod.py");
        archivo1.close();
		archivo2.close();
        cout<<"Marque 1 para escoger otra función o 0 para salir: ";
        cin>>repetir;
    } while(repetir == 1);

    return 0;
}
