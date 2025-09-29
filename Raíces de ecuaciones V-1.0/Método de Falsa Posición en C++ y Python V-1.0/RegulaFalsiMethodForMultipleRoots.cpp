#include <iostream> // Permite entrada y salida estándar: cin, cout, cerr0
#include <cmath> // Incluye funciones matemáticas como sin(), cos(), sqrt(), pow(), exp(), etc.
#include <vector> // Permite usar vectores dinámicos (arreglos que pueden cambiar de tamaño).
#include <iomanip> // Para formatear la salida, como número de decimales, ancho de campo, alineación.
#include <string> // Permite usar cadenas de texto (std::string) y operaciones con ellas.
#include <cstdlib> //Incluye funciones de utilidad general:/ srand() para números aleatorios system() 
					//para ejecutar comandos del sistemaabs(), exit(), conversión de cadenas a números (atoi, atof)
#include <fstream> // Para manejar archivos: lectura (ifstream), escritura (ofstream) y ambos (fstream).
#include <windows.h> // Librería específica de Windows para usar funciones del sistema operativo

using namespace std;

double f(double x, int opcion){
    switch(opcion){
        case 1: return sin(x) + 0.5 * sin(3.0 * x) + 0.25 * sin(5.0 * x);
        case 2: return sin(50.0 * x) * exp(-(x * x) / 100.0);
        case 3: return sin(x) + sin(3 * x);
        case 4: return sin(x) * cos(x);
        case 5: return sin(x) * (x - 2) * (x + 3);
        case 6: return cos(x) - exp(-x / 10.0);
        case 7: return cos(x);
        default: return 0;
    }
}

int main(){
	system("chcp 65001 > nul");
    int repetir;
    
    do {
    	system("cls");
    	int opcion;
    	double xi, xf, paso, tol, xr;
    	vector<double> xValues, yValues, raices, errorAb, errorRel;
    	bool encontro =  false;
    	cout<<"----- MÉTODO DE FALSA POSICIÓN PARA ENCONTRAR MÚLTIPLES RAÍCES -----"<<endl;
        cout<<endl;
        cout<<"Por favor seleccione una función de prueba:"<<endl;
        cout<<"1. f(x) = sin(x) + 0.5 * sin(3.0 * x) + 0.25 * sin(5.0 * x)"<<endl;
        cout<<"2. f(x) = sin(50.0 * x) * exp(-(x * x) / 100.0)"<<endl;
        cout<<"3. f(x) = sin(x) + sin(3 * x)"<<endl;
        cout<<"4. f(x) = sin(x)*cos(x)"<<endl;
        cout<<"5. f(x) = sin(x) * (x - 2) * (x + 3)"<<endl;
        cout<<"6. f(x) = cos(x) - exp(-x / 10.0)"<<endl;
		cout<<"7. f(x) = cos(x)"<<endl;
        cout<<endl;
        cout<<"Escoja una función ingresando un número del 1 al 7: ";
        cin>>opcion;
        cout<<"Por favor ingrese el intervalo [xi, xf] en el cual desea encontrar raíces"<<endl;
        cout<<"Valor inicial xi = ";
        cin>>xi;
        cout<<"Valor final xf = ";
        cin>>xf;
        cout<<"Ingrese la tolerancia permitida tol = ";
        cin>>tol;
        cout<<"Ingrese el paso para evaluar la función en cada iteración paso = ";
        cin>>paso;
        cout<<"Iterando y graficando con raíces..."<<endl;
        
        for(double i=xi; i<=xf; i=i+paso){
        	double x0 = i;
        	double x1 = i + paso;
        	xValues.push_back(x0);
        	yValues.push_back(f(x1, opcion));
        	
        	if(f(x0, opcion)*f(x1, opcion) < 0){
        		encontro = true;
        		do {
        			xr =  x1 - (f(x1, opcion)*(x1 - x0))/(f(x1, opcion) - f(x0, opcion));
        			if(f(x0, opcion)*f(xr, opcion) < 0){
        				x1 = xr;
					} else {
						x0 = xr;
					}	
				} while (abs(x1 - x0) > tol && abs(f(xr, opcion)) > tol);
				
				// Redonde de raíz cercana a cero.
				if(abs(xr) < 1e-10){
                    xr = 0; // Se guarda e imprime como cero exacto
                }
                
				double errAbs = abs((x1 - x0)); // error absoluto
				double errRel; // error relativo
				
				if(abs(xr) > 1e-10){
					errRel = abs(errAbs/xr)*100;
				} else {
					errRel = 0; // cuando el error relativo es muy pequeño
				}
				
				raices.push_back(xr);
				errorAb.push_back(errAbs);
				errorRel.push_back(errRel);
				
				// Imprimimos valores con formato fijo
				cout << fixed << setprecision(6);
				cout << "xr = " << xr // Raiz encontrada
					 << ", Error Absoluto = " << errAbs
				     << ", Error relativo = " << errRel << "%" // Error relativo
				     << endl;
			}
        }

        if(!encontro){
		    cout<<"No se encontraron raíces en el intervalo dado."<<endl;
		}

		// Para graficar
		ofstream archivo1("ValoresXeY.csv");
		archivo1 <<"x, f(x)\n";
		for(int i = 0; i < xValues.size(); i++){
			archivo1 << fixed << setprecision(6)
					 << xValues[i] <<", "
					 << yValues[i] <<"\n";
		}
		archivo1.close();

		// Guardar resultados de las raices y errores
		ofstream archivo2("RaicesyErrores.csv");
		archivo2 << "raices, ErrorAbsoluto, ErrorRelativo\n";
		for(int j = 0; j < raices.size(); j++){
			archivo2 << fixed << setprecision(6)
					 << raices[j]<<", "
					 << errorAb[j]<<", "
					 << errorRel[j]<<"\n";
		}
		archivo2.close();
		
		cout<<"¡¡CIERRE LA VENTANA DEL GRÁFICO PARA CONTINUAR!!"<<endl;
		system("\"C:\\Users\\jdecr\\AppData\\Local\\Programs\\Python\\Python313\\python.exe\" VisualizationRegulaFalsiMethod.py");

    	cout << "\nPresiona 0 para salir o 1 para evaluar otra función: ";
        cin >> repetir;

	} while(repetir == 1);
}