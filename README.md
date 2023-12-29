# Iris-lab-perceptron
Lab for AI class. The purpose was to build a neuron that could effectively. take in normalized data from a csv file and determine if the data was one of two iris flowers. Overall I was left with a neuron that had a 98% efficiency in correctly assessing the flower. 

## How it works
In this lab, I used pointers and arrays instead of vectors. I did this so the neuron could handle data sets bigger than the one given to me for the lab assignment. 

The first step was to find the number of rows and columns in the data given, and then dynamically create a 2D array to store the contents of the CSV file. After the the data in the CSV file has been read and stored we shuffle the data to ensure the data has been randomized and to improve the prediction efficiency of the neuron. Next, we attempt to make predictions and do so by randomly creating weights for each column in the data set, only if the prediction is wrong we change the weights.
