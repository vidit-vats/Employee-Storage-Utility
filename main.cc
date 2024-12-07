/* In our project,we are assuming that EID is the primary key of the employee table */
#include "Employee.hpp"
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <map>
#include <tuple>

using namespace std;
using namespace emp;

string emp::Employee::fileName = "Employee_Record";
string emp::Employee::column_EMPID = "Employee ID";
string emp::Employee::column_NAME = "Name";
string emp::Employee::column_AGE = "Age";


void Employee::showDetails(){
	cout<<"ID: "<<eid<<endl;
	cout<<"Name: "<<name<<endl;
	cout<<"ID: "<<age<<endl;
}

void Employee::setDetails(int eid,string name,int age){
	this->eid = eid;
	this->name = name;
	this->age = age;
}

void Employee::setName(string name){
	this->name = name;
}

void Employee::setAge(int age){
	this->age = age;
}

void Employee::setEID(int eid){
	this->eid = eid;
}

string Employee::getName(){
	return name;
}

int Employee::getEID(){
	return eid;
}

int Employee::getAge(){
	return age;
}


void Employee::displayTable(){
	string line;

	ifstream ifs(fileName,ios::in);

	while (getline(ifs,line)) 
		cout<<line<<endl;

	cout<<endl;

	ifs.close();
}

void Employee::insertRecord(ofstream &ofs){
	cout<<"Enter the EID,Name and Age of the Employee:-\n";
	cin>>eid;
	cin.ignore();
	getline(cin,name);
	cin>>age;

	ifstream ifs(fileName,ios::in);

	string line;
	int ieid;

	while (getline(ifs,line)) {
		istringstream ss(line);

		ss>>ieid;

		if(ieid == eid){
			cerr<<"Can't have same EID. Constraint Violated\n";
			ifs.close();
			return;
		}
	}

	/* This handles the case when the file is totally empty and since it is so, */
	/* 	 the 'put' pointer will point to 0 */
	if(ofs.tellp() == 0){
		ofs<<left<<setw(15)<<"Employee ID"<<left<<setw(25)<<"Name"<<left<<setw(15)<<"Age"<<endl;

		ofs<<left<<setw(15)<<eid
			<<left<<setw(25)<<name
			<<left<<setw(15)<<age<<endl;
	}

	/* This handles the case when the file is not empty and */
	/* there are no duplicate records in the file */
	else{
		ofs<<left<<setw(15)<<eid
			<<left<<setw(25)<<name
			<<left<<setw(15)<<age<<endl;
	}
}

void Employee::updateRecord(ofstream &ofs){
	if(ofs.tellp() == 0){
		cerr<<"Can't update Table. Table Empty\n";
		return;
	}

	else{
		int opt;

		int ieid;
		string iname;
		int iage;

		int searchId;

		map<int,tuple<int,string,int>>employee_data;
		string line;

		ifstream ifs(fileName,ios::in);

		/* Below is record of column names. It is written intentionally */
		/* This is of no use, since we want records only to get stored in the map instead of column names */

		getline(ifs,line);

		while (getline(ifs,line)) {
			istringstream ss(line);
			ss>>ieid;
			ss>>iname;
			ss>>iage;
			employee_data[ieid] = make_tuple(ieid,iname,iage);
		}

		cout<<"Enter the EID whose data is to be updated: ";
		cin>>searchId;

		if(employee_data.find(searchId) != employee_data.end()){
			cout<<"Enter the field that you want to update:-\n";
			cout<<"1. EID\n";
			cout<<"2. Name\n";
			cout<<"3. Age\n";
			cout<<"Option: ";
			cin>>opt;

			if(opt == 1){
				int new_EID;
				cout<<"Enter the new EID: ";
				cin>>new_EID;

				get<0>(employee_data[ieid]) = new_EID;
			}

			else if(opt == 2){
				string new_Name;
				cout<<"Enter the new Name: ";
				cin>>new_Name;

				get<1>(employee_data[ieid]) = new_Name;
			}

			else if(opt == 3){
				int new_Age;
				cout<<"Enter the new Age: ";
				cin>>new_Age;

				get<2>(employee_data[ieid]) = new_Age;
			}
			
			/* Now, we will write the whole map data into the file. */ 
			/* 	And we will have to open the file in write mode. */
			/* 	(To overwrite the existing data) */

			ofstream nofs(fileName,ios::out);

			nofs<<left<<setw(15)<<column_EMPID<<left<<setw(25)<<column_NAME<<left<<setw(15)<<column_AGE<<endl;

			for(auto [key,val] : employee_data)
			nofs<<left<<setw(15)<<get<0>(val)<<left<<setw(25)<<get<1>(val)<<left<<setw(15)<<get<2>(val)<<endl;

			nofs.close();
		}

		else{
			cout<<"Entered ID doesn't exists\n";
			return;
		}
	}
}

void Employee::deleteRecord(ofstream &ofs){
	if(ofs.tellp() == 0){
		cerr<<"Can't update Table. Table Empty\n";
		return;
	}

	else{
		int opt;

		int ieid;
		string iname;
		int iage;

		int searchId;

		map<int,tuple<int,string,int>>employee_data;
		string line;

		ifstream ifs(fileName,ios::in);

		/* Below is record of column names. It is written intentionally */
		/* This is of no use, since we want records only to get stored in the map instead of column names */

		getline(ifs,line);

		while (getline(ifs,line)) {
			istringstream ss(line);
			ss>>ieid;
			ss>>iname;
			ss>>iage;
			employee_data[ieid] = make_tuple(ieid,iname,iage);
		}

		cout<<"Enter the EID whose data is to be deleted: ";
		cin>>searchId;

		if(employee_data.find(searchId) != employee_data.end())
			employee_data.erase(searchId);

		else{
			cout<<"No record with EID "<<searchId<<" exists\n";
			return;
		}

		ofstream nofs(fileName,ios::out);

		nofs<<left<<setw(15)<<column_EMPID<<left<<setw(25)<<column_NAME<<left<<setw(15)<<column_AGE<<endl;

		for(auto [key,val] : employee_data)
			nofs<<left<<setw(15)<<get<0>(val)<<left<<setw(25)<<get<1>(val)<<left<<setw(15)<<get<2>(val)<<endl;

		nofs.close();
	}
}

int main(){
	ofstream ofs(emp::Employee::fileName,ios::app);

	Employee e;
	int option;

	while (1) {
		cout<<"Choose from following options: -\n";
		cout<<"1. Display Table\n";
		cout<<"2. Insert a Record\n";
		cout<<"3. Update a Record\n";
		cout<<"4. Delete a Record\n";
		cout<<"5. Exit Program\n";

		cout<<"Option: ";
		cin>>option;
		cout<<"\n";

		switch (option) {
			case 1:
				e.displayTable();
				break;

			case 2:
				e.insertRecord(ofs);
				break;

			case 3:
				e.updateRecord(ofs);
				break;

			case 4:
				e.deleteRecord(ofs);
				break;

			case 5:
				cout<<"Program Exited\n";
				exit(0);
		}
	}

	ofs.close();
	return 0;
}
