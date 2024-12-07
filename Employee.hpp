#ifndef EMPLOYEE

#define EMPLOYEE

#include <string>
using namespace std;

namespace emp{
	class Employee{

		int eid;
		string name;
		int age;

		public:
		static string fileName;
		static string column_EMPID;
		static string column_NAME;
		static string column_AGE;

		/* Setters */
		void showDetails();

		private:
		void setDetails(int eid,string name,int age);

		public:
		void setName(string);
		void setAge(int);
		void setEID(int);

		/* Getters */
		string getName();
		int getEID();
		int getAge();

		/* Function for displaying table */
		void displayTable();

		/* Function for inserting the record */
		void insertRecord(ofstream&);

		/* Function for updfating the record */
		void updateRecord(ofstream&);

		/* Function for delfeting the record */
		void deleteRecord(ofstream&);
	};
}
#endif
