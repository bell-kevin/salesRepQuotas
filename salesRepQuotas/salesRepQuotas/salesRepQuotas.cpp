// salesRepQuotas.cpp
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct SalesRep
{
	char firstName[20];
	char lastName[20];
	double quota;
	double quarterlySales[4];
	
};

int main()
{
	cout << "Sales Rep. Quotas by Kevin Bell\n\n";

	//Create an array of 3 sales reps
	SalesRep salesReps[3];

	//Get the data for each sales rep
	for (int i = 0; i < 3; i++)
	{
		cout << "Enter the first name of the sales rep: ";
		cin >> salesReps[i].firstName;
		cout << "Enter the last name of the sales rep: ";
		cin >> salesReps[i].lastName;
		cout << "Enter the sales rep's quota: ";
		cin >> salesReps[i].quota;
		cout << "Enter the sales rep's quarterly sales for the last 4 quarters: ";
		for (int j = 0; j < 4; j++)
		{
			cin >> salesReps[i].quarterlySales[j];
		}
		cout << endl;
	}

	//Write the data to a binary file
	ofstream outputFile;
	outputFile.open("salesReps.dat", ios::binary);
	if (!outputFile)
	{
		cout << "Error opening file. Program terminating.\n";
		exit(1);
	}

	for (int i = 0; i < 3; i++)
	{
		outputFile.write(reinterpret_cast<char*>(&salesReps[i]), sizeof(SalesRep));
	}

	outputFile.close();

	//Read the data from the binary file
	ifstream inputFile;
	inputFile.open("salesReps.dat", ios::binary);
	if (!inputFile)
	{
		cout << "Error opening file. Program terminating.\n";
		exit(1);
	}


	//Display each sales rep
	cout << "Sales Rep. Quotas" << endl;
	cout << "-----------------" << endl;
	cout << "Name\t\t\t\tQuota\t\t\tTotal Sales\t\t\tMet Quota" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < 3; i++)
	{
		inputFile.read(reinterpret_cast<char*>(&salesReps[i]), sizeof(SalesRep));
		double totalSales = 0;
		for (int j = 0; j < 4; j++)
		{
			totalSales += salesReps[i].quarterlySales[j];
		}
		cout << salesReps[i].firstName << " " << salesReps[i].lastName << "\t\t\t$" << fixed << setprecision(2) << salesReps[i].quota << "\t\t$" << totalSales << "\t\t\t";
		if (totalSales >= salesReps[i].quota)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}

	//display total sales
	cout << endl;
	cout << "Total Sales for Each Quarter" << endl;
	cout << "----------------------------" << endl;
	cout << "Quarter\t\tTotal Sales" << endl;
	cout << "--------------------------" << endl;
	for (int i = 0; i < 4; i++)
	{
		double totalSales = 0;
		for (int j = 0; j < 3; j++)
		{
			totalSales += salesReps[j].quarterlySales[i];
		}
		cout << "Q" << i + 1 << "\t\t$" << fixed << setprecision(2) << totalSales << endl;
	}
	
	// display total sales for the year 
	cout << endl;
	cout << "Total Sales for the Year" << endl;
	cout << "------------------------" << endl;
	double totalSales = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			totalSales += salesReps[i].quarterlySales[j];
		}
	}
	cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
	cout << endl;
	
	//close file
	inputFile.close();
	
	system("pause");
	return 0;
}