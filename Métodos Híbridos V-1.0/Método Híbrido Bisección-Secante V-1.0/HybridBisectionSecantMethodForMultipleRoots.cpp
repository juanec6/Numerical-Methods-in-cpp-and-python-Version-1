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

string function_str(int option)
{
    switch(option)
	{
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
double f(double x, int option)
{
	switch(option)
	{
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


int main()
{
	system("chcp 65001 > nul");
    int repeat;
    
    do
	{
		//Variables and vectors:
		double xi, xf, step, tolBi, tolSec, fx, fx0, fx1, a, b, x0, x_1, x_prev, x_curr, x_next;
		int iterBi, iterSec, maxIter=1000, option;
		vector<double> xValues, yValues, roots;
			
		cout << "----- HYBRID BISECTION AND SECANT METHOD FOR FINDING MULTIPLE ROOTS -----" << endl;
		cout << endl;
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
        
        // Let's validate the the user entered the right option
        while(option < 1 || option > 7)
        {
        	cout << "Invalid option. Please select between 1 and 7: ";
        	cin >> option; 
		}
		
		// How are you?
		cout << "Selected function: " << function_str(option) << endl;
		cout << endl;
		cout << "Select the interval you want to evaluate:" << endl;
		cout << "xi = ";
	    cin >> xi;
	    cout << "xf = ";
	    cin >> xf;
	    
	    //// Validates that xi is minor than xf and that they're not equal
	    while(xf<=xi)
		{
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
        
        //Validates step is not 0 or less or the program will make boom!
        while(step <= 0)
		{
        	cout << "Please select the step for each iteration e.g (1, 0.5, .., 0.1): " << endl;
	        cout << "step = ";
	        cin >> step;
		}
        cout << endl;
        
        //ask the user to enter the tolerance the bisection method
        cout<<"Please enter the tolerance for the bisection method: tolBi = ";
        cin >> tolBi;
        cout << endl;
        cout << "Please enter the tolerance for the secant method: tolSec = ";
        cin >> tolSec;
        
		
		//Now that all these validations are done, let's first save the x values and f(x) values in an csv for simplicity when plotting.
		ofstream file1("XvaluesXvalues.csv");
		for(double i=xi; i<=xf; i+=step)
		{
			fx = f(i, option);
			xValues.push_back(i);
			yValues.push_back(fx);
			file1 << fixed << setprecision(8) << i << ", " << fx << "\n";
		}
		file1.close();
		
		// Ok, now we can start with the hybrid method, first we are going to start with the bisection method
		for(double i=xi; i<=xf; i+=step)
		{
			iterBi = 0;
			iterSec = 0;
			a = i;
			b = i + step;
			
			//It is necessary to validated that b is not equal to zero to avoid division by zero when calculating relative error
			if (b == 0)
			{
				cout<<endl;
				cout << "Skipping b = " << b << " because b ≈ 0 which will implicate a division in the relative error formula" << endl;
			    continue;
			} 
			
			//Lets check the condition of f(a)*f(b) < 0
			if(f(a, option)*f(b, option) < 0)
			{
				do
				{
					x0 =(a+b)/2.0;
					if(f(a, option)*f(x0, option) < 0)
					{
						b = x0;
					} else{
						a = x0;
					}
					iterBi++;
					
					double relErrBi = abs(b-a)/abs(b);
					
					//Now we check if the relative error of the bisection method is maybe less than the tolerance of the secant method
					if(relErrBi <= tolSec || relErrBi >= tolSec)
					{
						x_prev = a;
						x_curr = b;
						double relErrorSec;
						
						do
						{
							fx0 = f(x_prev, option);
							fx1 = f(x_curr, option);
							
							//Let's check that fx1 - fx is not equal to zero
							if(fabs(fx1-fx0) < 1e-12)
							{
								cout<<endl;
								cout << "Division by zero risk in secant method — skipping." << endl;
        						break;
							}
							
							//Secant method formula
							x_next = x_curr - fx1 * (x_curr - x_prev) / (fx1 - fx0);
							
							//Relative error calculation
							relErrorSec = fabs((x_next - x_curr) / x_next);
							
							//now we update the values:
							x_prev = x_curr;
							x_curr = x_next;
							roots.push_back(x_curr);
							iterSec++;
						}while(relErrorSec >= tolSec && iterSec <= maxIter);
						
						cout << fixed << setprecision(8);
						cout << "\nRoot found near x = " << x_curr
							 << " | f(x) = " << f(x_curr, option)
							 << " | Bi iters: " << iterBi
							 << " | Sec iters: " << iterSec
							 << endl;
						break;
					}
				} while(abs(b-a)/abs(b) >= tolBi && iterBi <= maxIter);
			}
		}
		cout<<endl;
        cout << "Want to try a different function? (1 = yes, 0 = no): ";
        cin >> repeat;
    }while(repeat == 1);
        
	return 0;
} 
