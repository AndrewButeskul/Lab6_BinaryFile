#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

struct Student
{
	string name;
	short group_number;
	string subjects[3];
	int marks[3];
	double grant;
};

void Input_data(Student *student, int k)
{
	for (size_t i = 0; i < k; i++)
	{
		cout << "Enter your name\n";
		cin >> student[i].name;
		cout << "Enter number your group\n";
		cin >> student[i].group_number;

		for (size_t j = 0; j < 3; j++)
		{
			cout << "Enter subject " << j << "\n";
			cin >> student[i].subjects[j];
			do
			{
				cout << "Enter mark " << j << ": \n";
				cin >> student[i].marks[j];
			} while (student[i].marks[j] > 6 && student[i].marks[j] < 0);
			
		}
		cout << "Enter your grant \n";
		cin >> student[i].grant;
	}
}

void Check_grant(Student *student, int k)
{
	int count = 0;
	for (size_t i = 0; i < k; i++)
	{
		count = 0;
		for (size_t j = 0; j < 3; j++)
		{
			if (student[i].marks[j] > 3)
				count++;
		}
		if (count == 3)
			student[i].grant += (0.3 * student[i].grant);
	}
}

void Write_to_file(Student *student, int k, ofstream &out)
{
	for (size_t i = 0; i < k; i++)
	{
		out << student[i].name << "\n";
		out << student[i].group_number << "\n";
		for (size_t j = 0; j < 3; j++)
		{
			out << student[i].subjects[j] << "\n";
			out << student[i].marks[j] << "\n";
		}		
		out << student[i].grant << "\n";
		out << "\n";
	}
}

void Print(Student *student, int k)
{
	for (size_t i = 0; i < k; i++)
	{
		cout << endl << "Name: " << student[i].name << endl;
		cout << "Group number: " << student[i].group_number << endl;		
		for (size_t j = 0; j < 3; j++)
		{
			cout << "Subject " << j + 1 << ": " << student[i].subjects[j] << " - " << student[i].marks[j] << endl;
		}		
		cout << "Size your grant: " << student[i].grant << endl << endl;
	}
}

int main()
{
	int k = 0, selection = 0;
	cout << "Enter size students" << endl;
	cin >> k;
	ofstream out;
	Student *student = new Student[k];

	out.open("Students.txt", ios::binary);
	Input_data(student, k);
	
	if (!out.is_open())
		cout << "Error!" << endl;
	else
	{
		Write_to_file(student, k, out);
		system("cls");
		cout << "File created and all data writen" << endl;
		Print(student, k);
		link:
		cout << "You want to increase grants for every student who doesn’t have triples? (1 - Yes or 2 - Exit)" << endl;
		cin >> selection;
		if (selection == 1)
		{
			Check_grant(student, k);
			system("cls");
			cout << endl << "Grant increased!" << endl;
			Write_to_file(student, k, out);
			system("cls");
			cout << "Information rewtited" << endl;
			Print(student, k);
		}
		else if (selection == 2)
		{
			exit(0);
		}
		else
			cout << "Error! Wrong input" << endl;
		goto link;
	}

	out.close();

	delete[] student;
	system("pause");
	return 0;
}