#include <iostream>
#include <string.h>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

// Algorithm KNAPSACK
int max2Num(int num1, int num2)
{
	return (num1 > num2) ? num1 : num2;
}

int max3Num(int num1, int num2, int num3)
{
	return max2Num(num1, max2Num(num2, num3));
}

int max4Num(int num1, int num2, int num3, int num4)
{
	return max2Num(num1, max3Num(num2, num3, num4));
}


int LCS_2D(char* s1, char* s2)
{
	int tableRow = strlen(s1) + 1;
	int tableCol = strlen(s2) + 1;
	
	//Allocatate Memories for 2D table
	int** table = new int*[tableRow];
	for (int i = 0; i < tableRow; i++) {
		table[i] = new int[tableCol];
	}

	//Calculate longest sequence
	for (int x = 0; x < tableRow; x++) {
		for (int y = 0; y < tableCol; y++) {
			
			if (x == 0 || y == 0) {
				table[x][y] = 0;
			}
			else if (s1[x-1] == s2[y-1]) {
				table[x][y] = table[x - 1][y - 1] + 1;
			}
			else {
				table[x][y] = max2Num(table[x - 1][y], table[x][y - 1]);
			}
		}
	}

	return table[tableRow-1][tableCol-1];
}


int LCS_3D(char* s1, char* s2, char* s3)
{
	int tableX = strlen(s1) + 1;
	int tableY = strlen(s2) + 1;
	int tableZ = strlen(s3) + 1;

	//Allocate memory for 3D table;
	int*** table = new int** [tableX];
	for (int i = 0; i < tableX; i++) {
		table[i] = new int*[tableY];
		for (int ii = 0; ii < tableY; ii++) {
			table[i][ii] = new int[tableZ];
		}
	}

	for (int x = 0; x < tableX; x++) {
		for (int y = 0; y < tableY; y++) {
			for (int z = 0; z < tableZ; z++) {

				if (x == 0 || y == 0 || z == 0) {
					table[x][y][z] = 0;
				}
				else if (s1[x-1] == s2[y-1] && s1[x-1] == s3[z-1]) {
					table[x][y][z] = table[x-1][y-1][z-1] + 1;
				}
				else {
					table[x][y][z] = max3Num(table[x - 1][y][z], table[x][y - 1][z], table[x][y][z - 1]);
				}
			}
		}
	}

	return table[tableX - 1][tableY - 1][tableZ - 1];
}


int LCS_4D(char* s1, char* s2, char* s3, char* s4)
{

	int tableA = strlen(s1) + 1;
	int tableB = strlen(s2) + 1;
	int tableC = strlen(s3) + 1;
	int tableD = strlen(s4) + 1;
	int a, b, c, d;


	//Allocate space for 4D table
	int**** table = new int***[tableA];
	for (a = 0; a < tableA; a++) {
		table[a] = new int**[tableB];
		for (b = 0; b < tableB; b++) {
			table[a][b] = new int*[tableC];
			for (c = 0; c < tableC; c++) {
				table[a][b][c] = new int[tableD];
			}
		}
	}

	for (a = 0; a < tableA; a++) {
		for (b = 0; b < tableB; b++) {
			for (c = 0; c < tableC; c++) {
				for (d = 0; d < tableD; d++) {

					if (a == 0 || b == 0 || c == 0 || d == 0) {
						table[a][b][c][d] = 0;
					}
					else if (s1[a - 1] == s2[b - 1] && s1[a - 1] == s3[c - 1] && s1[a - 1] == s4[d - 1]) {
						table[a][b][c][d] = table[a - 1][b - 1][c - 1][d - 1] + 1;
					}
					else {
						table[a][b][c][d] = max4Num(table[a - 1][b][c][d], table[a][b - 1][c][d], table[a][b][c - 1][d], table[a][b][c][d - 1]);
					}

				}
			}
		}
	}

	return table[tableA - 1][tableB - 1][tableC - 1][tableD - 1];
}


int main(int argc, char* argv[]){

	//Set up arguments manager
	ArgumentManager am(argc, argv);
	string inputFileName = am.get("input");
	string outputFileName = am.get("output");

	ifstream inputFile;
	ofstream outputFile;
	int counter = 0;
	char tempLine[1000];
	char** inputStrings;
	int result = 0;

	//Allocate space to store input strings
	inputStrings = new char*[4];
	for (int i = 0; i < 4; i++)
		inputStrings[i] = new char[1000];

	inputFile.open(inputFileName);
	outputFile.open(outputFileName);

	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			inputFile.getline(tempLine, 1000);
			if (strlen(tempLine) > 0)
			{
				strcpy(inputStrings[counter], tempLine);
				counter++;
			}
		}

		switch (counter) {
		case 2:
			result = LCS_2D(inputStrings[0], inputStrings[1]);
			break;
		case 3:
			result = LCS_3D(inputStrings[0], inputStrings[1], inputStrings[2]);
			break;
		case 4:
			result = LCS_4D(inputStrings[0], inputStrings[1], inputStrings[2], inputStrings[3]);
			break;
		default:
			break;
		}
        outputFile << "Len: " << result << endl;
	}else{
	    outputFile << "Cannot open input file" << endl;
	}

	outputFile.close();
	inputFile.close();

	return 0;
}