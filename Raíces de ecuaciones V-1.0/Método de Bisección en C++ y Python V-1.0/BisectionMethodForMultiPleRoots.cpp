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
        case 1: return cos(x) - x;
        case 2: return pow(x, 5) - 4;
        case 3: return exp(x) - 2;
        case 4: return sin(x);
        case 5: return sin(x) * (x - 2) * (x + 3);;
        case 6: return exp(-x)*sin(x);
        case 7: return pow(x, 8) + pow(x, 3) + sin(x + 2) - 0.8;
        default: return 0;
    }
}

int main() {
    system("chcp 65001 > nul");
    int repetir;

    do {
        system("cls");

        int opcion;
        double xi, xf, m, tol, paso, a, b;
        vector<double> xValores, yValores, raices, mValores, fmValores, error;
        cout<<"----- MÉTODO DE BISECCIÓN PARA ENCONTRAR MÚLTIPLES RAÍCES -----"<<endl;
        cout<<endl;
        cout<<"Por favor seleccione una función de prueba:"<<endl;
        cout<<"1. f(x) = cos(x) - x"<<endl;
        cout<<"2. f(x) = pow(x, 5) - 4"<<endl;
        cout<<"3. f(x) = exp(x) - 2"<<endl;
        cout<<"4. f(x) = sin(x)"<<endl;
        cout<<"5. f(x) = sin(x) * (x - 2) * (x + 3)"<<endl;
        cout<<"6. f(x) = exp(-x)*sin(x)"<<endl;
		cout<<"7. pow(x, 8) + pow(x, 3) + sin(x + 2) - 0.8"<<endl;
        cout<<endl;
        cout<<"(ingrese un número del 1 al 7): ";
        cin>>opcion;

        cout<<"\nPor favor seleccione el intervalo:"<<endl;
        cout<<"valor inicial xi = ";
        cin>>xi;
        cout<<"valor final xf = ";
        cin>>xf;

        cout<<"\nIngrese la tolerancia absoluta (ej. 0.001): ";
        cin>>tol;

        cout<<"\nIngrese el paso para cada iteración: ";
        cin>>paso;
        
        // Búsqueda de raíces por intervalos
        for(double i = xi; i<=xf; i += paso){
            a = i;
            b = i + paso;
            xValores.push_back(a);
            yValores.push_back(f(a, opcion));
            
            if(f(a, opcion)*f(b, opcion) < 0){
                do { 
                    m = (a+b)/2.0;
                    if(f(a, opcion)*f(m, opcion) < 0){
                        b = m;
                    } else {
                        a = m;
                    }
                } while ((fabs(b-a)/2) > tol);
                
                raices.push_back(m);
                mValores.push_back(m);
                fmValores.push_back(f(m, opcion));
                error.push_back(fabs(b - a) / 2.0);

                cout << fixed << setprecision(6);
                cout << "Raíz encontrada en: m = " << m
                     << ", |f(" << m << ")| = " << fabs(f(m, opcion))
                     << ", Error absoluto = " << fabs(b-a)/2
                     << " < Tolerancia = " << tol
                     << endl << endl;
            } else {
                raices.push_back(NAN);
                m = (a + b) / 2.0;
                mValores.push_back(m);
                fmValores.push_back(f(m, opcion));
                error.push_back(paso / 2.0);
            }
        }
        
        // Mostrar todos los valores
        for(int i=0; i<xValores.size(); ++i){
            cout<< "x = " << xValores[i]
                << ", f(x) = " << yValores[i]
                << ", m = " << mValores[i]
                << ", f(m) = " << fmValores[i] 
                << endl;
        }
        
        // Guardar resultados en archivo CSV
        ofstream archivo("resultados.csv");
        archivo << "x, f(x), m, f(m), raices, error\n";
        
        for (int i=0; i<xValores.size(); i++){
            archivo << fixed << setprecision(6)
                    << xValores[i] <<", "
                    << yValores[i] <<", "
                    << mValores[i] <<", "
                    << fmValores[i] <<", ";
            
            if(isnan(raices[i])){
                archivo << "-, -";
            } else {
                archivo << raices[i] << ", "
                        << error[i];
            }
            archivo << "\n";
        }

        archivo.close();
        system("\"C:\\Users\\jdecr\\AppData\\Local\\Programs\\Python\\Python313\\python.exe\" VisualizationBisectionMethod.py");
        
        cout << "\nPresiona 0 para salir o 1 para evaluar otra función: ";
        cin >> repetir;

    } while (repetir == 1);

    cout << "Programa terminado." << endl;
    return 0;
}
