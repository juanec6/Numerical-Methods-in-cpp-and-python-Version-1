// Validar las entradas del usuario (intervalos correctos, pasos >0, opciones válidas) 
// Validar que xi < xf 

#include <iostream> // Allows standard input and output: cin, cout, cerr
#include <cmath> // Includes mathematical functions such as sin(), cos(), sqrt(), pow(), exp(), etc.
#include <vector> // Allows the use of dynamic vectors (arrays that can change size).
#include <iomanip> // For formatting output, e.g. number of decimals, field width, alignment.
#include <string> // Enables use of text strings (std::string) and operations with them.
#include <cstdlib> // Includes general utility functions: srand() for random numbers, system() 
                  // to execute system commands, abs(), exit(), string-to-number conversions (atoi, atof).
#include <fstream> // For file handling: reading (ifstream), writing (ofstream), and both (fstream).
#include <windows.h> // Windows-specific library for using operating system functions.


using namespace std;

string funcion_str(int option) {
    switch(option) {
        case 1: return "f(x) = sin(x) + 0.5*sin(3x) + 0.25*sin(5x)";
        case 2: return "f(x) = sin(50x)*exp(-x^2/100)";
        case 3: return "f(x) = sin(x) + sin(3x)";
        case 4: return "f(x) = sin(x)*cos(x)";
        case 5: return "f(x) = sin(x)*(x-2)*(x+3)";
        case 6: return "f(x) = cos(x) - exp(-x/10)";
        case 7: return "f(x) = cos(x)";
        default: return "Function not defined";
    }
}


// This are the functions to evaluate the method. You can change it if you want
double f(double x, int option){
	switch(option){
		case 1: return sin(x) + 0.5*sin(3.0*x) + 0.25*sin(5.0*x);
		case 2: return sin(50.0*x)*exp(-(pow(x, 2))/100.00);
		case 3: return sin(x)+ sin(3.0*x);
		case 4: return sin(x)*cos(x);
		case 5: return sin(x)*(x-2.0)*(x+3.0);
		case 6: return cos(x) - exp(-x/10.0);
		case 7: return cos(x);
		default: return 0; 
	}
}


// This will be the first derivate of f(x) which will need to be updated if updated f(x, opcion)
// Wich means that you need to calculate the first derivate of the functions updated in the previous functions 
double df(double x, int option){
	switch(option){
		case 1: return cos(x) + 1.5*cos(3.0*x) + 1.25*cos(5.0*x);
		case 2: return exp(-(x*x)/100.0)*(50.0*cos(x*50.0)- 0.02*x*sin(50.0*x));
		case 3: return cos(x) + 3.0*cos(3.0*x);
		case 4: return pow(cos(x), 2) - pow(sin(x), 2);
		case 5: return (-6.0 + x + pow(x, 2))*cos(x) + (1.0 + 2.0*x)*sin(x);
		case 6: return exp(-x/10.0)/10.0 - sin(x);
		case 7: return -sin(x);
		default: return 0;
	}
}

// Now we need the second derivate to check convergence of NewtonRapshon's method
// if f(x, opcion) you will ned find the second derivates for this function ddf as well

double ddf(double x, int option){
	switch(option){
		case 1: return -sin(x) - 4.5*sin(3.0*x) - 6.25*sin(5.0*x);
		case 2: return ( exp(-pow(x, 2) / 100.0) * 
              ( (pow(x, 2) - 6250050.0) * sin(50.0 * x) - 5000.0 * x * cos(50.0 * x) ) 
             ) / 2500.0;
        case 3: return -9.0*sin(3.0*x) - sin(x);
        case 4: return -4.0*cos(x)*sin(x);
        case 5: return((-pow(x, 2) - x + 8.0) * sin(x)) + ((4.0 * x + 2.0) * cos(x));
        case 6: return -cos(x) - (exp(-x / 10.0) / 100.0);
        case 7: return -cos(x);
		default: return 0;
	}
}

int main() {
	system("chcp 65001 > nul");
    int repeat;
    
    do {
        system("cls"); 
        int option, option2, option3, maxIter = 2000, iter = 0;
		double xi, xf, tolBi = 1e-3, tolUserBi, tolNR = 1e-3, tolUserNR, absErr = 1e-8 , relErr = absErr*100.00, step;
		double a, b, fx, x0;
		vector<double> xValues, yValues;
		/* I choose this tolBi to be the deffect tolerance for the bisection method to stop,
		since the purpose of this hybrid method is to use less computational power and get a faster result with newton method. 
		tolUser is in case the the user knows or requires an specific tolerance and understand that it will take more computational power.
		Now, */ 
        cout << "----- HYBRID BISECTION AND NEWTON-RAPHSON FOR FINDING MULTIPLE ROOTS -----" << endl;
        cout <<endl;
        cout<<endl;
        cout<<"List of functions: "<<endl;
        cout<<endl; 
        cout << "1. f(x) = sin(x) + 0.5*sin(3.0*x) + 0.25*sin(5.0*x)" << endl;
        cout << "2. f(x) = sin(50.0*x)*exp(-(pow(x, 2))/100)" << endl;
        cout << "3. f(x) = sin(x)+ sin(3.0*x)" << endl;
        cout << "4. f(x) = sin(x)*cos(x)" << endl;
        cout << "5. f(x) = sin(x)*(x-2)*(x+3)" << endl;
        cout << "6. f(x) = cos(x) - exp(-x/10.0)" << endl;
        cout << "7. f(x) = cos(x)" << endl;
        cout << endl;
        cout << "Please select a function to test (select one number from 1 to 7): ";
        cin >> option;
        
        // Validates user is entering the right option.
        while(option < 1 || option > 7){
		    cout << "Invalid option. Please select between 1 and 7: ";
		    cin >> option;
		}
        cout << "\nSelected function: " << funcion_str(option) << endl;
        cout << endl;
        cout << "Please select the interval [xi, xf] you want to evaluate:"<<endl;
        cout << "xi = ";
        cin >> xi;
        cout << "xf = ";
        cin >> xf;
        
        // Validates that xi is less or not equal to xf
        while(xi>=xf){
        	cout << "xi can't be bigger or equal to xf, please try again."<< endl;
        	cout << "Please select the interval [xi, xf] you want to evaluate:"<< endl;
	        cout << "xi = ";
	        cin >> xi;
	        cout << "xf = ";
	        cin >> xf;
		}
        cout << "Please select the step for each iteration e.g (1, 0.5, .., 0.1): " << endl;
        cout << "step = ";
        cin >> step;
        while(step <= 0){
        	cout << "Please select the step for each iteration e.g (1, 0.5, .., 0.1): " << endl;
	        cout << "step = ";
	        cin >> step;
		}
        cout << endl;
        
        cout << "¡¡TOLERANCE AND ERROR DISCLAIMER!!"<<endl;
        // let's talk about tolerance and error management 
        cout << "In metrology, tolerance is the margin of error or variation allowed\n"
     		 << "in the manufacturing of a part with respect to its dimension or\n"
     		 << "characteristic specified in the drawing, guaranteeing its functionality."
     		 << endl;
    	cout << endl;
    	cout << "In numerical methods, tolerance is the error threshold we decide\n"
     		 << "to accept so that the iterations stop when the solution is\n"
     		 << "close enough to the true root.\n"
			 << "\n"
			 << "This program uses the relative error as stopping criterion,\n"
			 << "defined as: |x(k) - x(k-1)| / |x(k)|.\n"
			 << "The tolerance must be entered as a value between 0 and 1.\n"
			 << "Example: a tolerance of 1e-3 means iterations stop when\n"
			 << "the relative error is smaller than 0.001.\n"
			 << endl;
			
			 
		cout << endl;
		cout << "If you need an specific tolerance for the bisection method press 1, otherwise, press 2: ";
		cin >> option2;
		cout << endl;	
		// In case the user needs an specific tolerance for the bisection method to stop, he/him will be able to do it, otherwise, a default tolerance will be used
		if(option2 == 1){
			cout << "Please enter the tolerance needed to stop iterations for bisection method: ";
			cin >> tolUserBi;
			cout << endl;
		} else {
			cout <<"Default tolerance to stop bisection method iterations is: "<< tolBi << endl;
		}
		
		
		cout<<endl;
		cout << "If you need an specific tolerance to stop the Newton-Rapshon method iterations, press 1, otherwise, press 2: ";
		cin >> option3;
		cout << endl;
		//In case the user needs an specific relative error
		if(option3 == 1){
			cout << "Please enter the tolerance required to stop iterations: ";
			cin >> tolUserNR;
			cout << endl;
		} else {
			cout << "Default tolerance for stopping newton-rapshon iterations is: " << tolNR << endl;
		}
		cout << endl;
		cout << "This program will stop at 2000 iterations if it has not reached the parameters entered" << endl;
		cout << "Iterating..."<<endl;
		cout << endl;
        

        cout << "Want to try a different function? (1 = yes, 0 = no): ";
        cin >> repeat;
        
        /* For simplicity I'm going to save the values for x and f(x) in a csv
		   apart from the results so both data of the iterations and the values of the function create discrepancies. 
		*/
    	
    	ofstream file1("xValues&yValues.csv");
    	file1 << "x, f(x)\n";
    	for(double i=xi; i<=xf; i = i + step){
    		fx = f(i, option);
    		xValues.push_back(i);
    		yValues.push_back(fx);
    		file1 << fixed << setprecision(8) << i << ", " << fx << "\n";
		}
		file1.close();
		    
        // Iterations start here, first I will start with the bisection method and then when the tolerance is achieved, it will jump right into Newton's-Rapshon method
        for(double i=xi; i<=xf; i = i + step){
			iter = 0;	
        	a = i;
        	b = i + step;
        	if(f(a, option)*f(b, option) < 0 && option2 == 1){
        		do {
        			x0 = (a+b)/2.0;
        			if(f(a, option)*f(x0, option) < 0){
        				b = x0;
					} else{
						a = x0;
					}
					iter++;
				} while(abs((b-a)/b) >= tolUserBi && iter <= maxIter ); // This will be for user tolerance input
			} else {
				do {
        			x0 = (a+b)/2.0;
        			if(f(a, option)*f(x0, option) < 0){
        				b = x0;
					} else{
						a = x0;
					}
					iter++;
				} while(abs(b-a)/abs(b) >= tolBi && iter <= maxIter); // Defatul tolerance 1e-3
			}
		}
		// Now that we got our first approximation x0 when can use it with newton-rapshon method

    } while (repeat == 1);

    return 0;
}


