//Name Alexis Torres
//Date 11/14/2023
//file lab8.cpp
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>
using namespace std;

void readCSV(double** array, string filename, int rows, int cols) {
    ifstream file(filename);

    for (int row = 0; row < rows; row++){
        string line;
        getline(file, line);

        if (!file.good()){
            cout << "File was not read" << endl;
        }
        stringstream iss(line);
        for (int col = 0; col < cols; col++){
            string val;
            getline(iss, val, ',');

            stringstream convertor(val);
            convertor >> *(*(array+row)+col);
        }
    }
    file.close();
}

void displayValues(double** array, int rows, int cols){
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            cout << *(*(array+row)+col) << ' ';
        }
        cout << endl;

    }
}

void displayValues(double* array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

float PercentCorrect(float correct, float sample_size){
	float result = (correct / sample_size)*100;
	return result;
}

double dotProduct(double* row, double* weights, int numCols) {
    double result = 0.0;
    for (int col = 0; col < numCols; ++col) {
        result += row[col] * weights[col];
    }
    return result;
}

// find the number of rows and columns in a csv file
void findRowsCols(string filename, int& r, int& c) {
	ifstream file(filename);
	if(!file.good()) {
		cout << "File was not read" << endl;
	}
	else {
		string line;
		while (getline(file, line)) {
			r++;
			stringstream iss(line);
			string val;

			if (r == 1) {
				while (getline(iss,val,',')) {
					c++;
				}
			}
		}
		// cout << "Rows: " << r << endl;
		// cout << "Columns: " << c << endl;
        file.close();
	}
}

void changeWeights(double* input, double* weights, int cols, int error) 
{
    for (int i = 0; i < cols; ++i) {
        weights[i] = weights[i] + (error * input[i]);
    }
}

void copyWeights(double* weights, double* BestWeights, int cols) {
    for (int i = 0; i < cols; ++i) {
        BestWeights[i] = weights[i];
    }
}

void printOutcome(double arr ,double* weights, int cols, int iteration, int prediction) {
    cout << "Iter " << iteration << ": ";
    cout << "Weights are [" ;
    for (int i = 0; i < cols; ++i) {
        if ( i == (cols - 1)) {
            cout << weights[i];
        } else {
            cout << weights[i] << ", ";
        }
    }
    cout << "], classification was ";
    if (prediction == arr) {
        cout << "CORRECT" << endl;
    } else {
        cout << "an ERROR" << endl;
    }
}

void shuffleArray(double** array, int rows, int cols){
    srand(time(0));

    // Start from the end and swap with a random element before it
    for(int i = rows -1; i > 0; --i){
        int j = rand() % (i+1); // Random index between 0 and i
        
        // swap the rows
        for (int col = 0; col < cols; ++col){
            swap(array[i][col], array[j][col]);
        }
    }
}

int main(int argc, char* argv[])
{
    /* -----------------Initalize variables/ arraya -------------------------*/
    int rows = 0;
    int columns = 0;
    int sample_size = 0;
    int correct_prediction = 0;
    double result = 0.0;
    
    string filename = "iris_full_normalized.csv";

    // must get called to determine row and column sizes
    findRowsCols(filename, rows, columns); 

    srand(time(0)); // Seed for random initialization
    // Create arrays dynamically
    double** arr = new double*[rows];
    // double** bias = new double*[rows];
    for(int i = 0; i < rows; ++i) {
        arr[i] = new double[columns];
        // bias[i] = 1.0;
    }

    // Create vectors instead of arrays
    // Allocate and initialize weights dynamically
    double* weights = new double[columns];
    double* BestWeights = new double[columns];
    
    for (int col = 0; col < columns; ++col) {
        // Random number between -0.5 and 0.5
        weights[col] = static_cast<double>(rand()) / RAND_MAX - 0.5; 
    }
    /* --------------End of Initalize variables/ arrays----------------------*/   

    /* --------------------Main Logic---------------------*/   
    //column of the first array
    readCSV(arr, filename, rows, columns);
    //displayValues(arr, rows , columns);
    
    // shuffle for fast and more efficient training process
    shuffleArray(arr, rows, columns);
    //displayValues(arr, rows , columns);

    // Perform dot product and output the result
    // int count = 0;
    // int MAX_EPOCHS = 10;   
    // do {   
    for (int i = 0; i < rows; ++i) {
        double result = dotProduct(arr[i], weights, columns);
        ++sample_size;
        // if postive then set prediction to 1, else set to -1
        int prediction = (result >= 0) ? 1 : -1;

        // Output the result
        if (arr[i][columns - 1] == prediction) {
    		correct_prediction++;
            printOutcome(arr[i][columns - 1], weights, columns, i, prediction);

        } else {
            
            int error = arr[i][columns - 1] - prediction;
            changeWeights(arr[i], weights, columns, error);
            printOutcome(arr[i][columns - 1], weights, columns, i, prediction);
    	}
    }
    //     ++count;
    // } while(count < MAX_EPOCHS);
    displayValues(weights, columns);

    cout << "Total predictions: " << sample_size <<endl;
    cout << "Number correct: " << correct_prediction << endl;
    cout << "percent correct: " << PercentCorrect(correct_prediction, rows) 
        << "%	" << endl;
    /* --------------------End of Main Logic---------------------*/

    /*----------------------------- Free Memory ----------------------------*/
    for(int i = 0; i < rows; ++i){
        delete [] arr[i];
        // delete [] bias[i];
    }
    delete [] arr;
    // delete [] bias;
    delete [] weights;
    delete [] BestWeights;
    /* --------------------End of Free Memory----------------------*/   

    return 0;
}
