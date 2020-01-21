#include "Database.h"
#include <cstdlib>

int main()
{
	Database db;

	if (!db.LoadFromFile("test.csv"))
		return 1;

	cout << "ORIGINAL" << endl;
	db.DisplayAll();
	cout << endl << endl;

	db.ArrangeSubordinates();
	cout << "ArrangeSubordinates" << endl;
	db.DisplayAll();
	cout << endl << endl;

	cout << "Adding new Manager" << endl;
	Manager* man = new Manager("Endy", "Dufrein", 24, 8);
	man->SetSalary(1000);
	man->SetDepartment("IT");
	db.HireEmployee(man);
	db.DisplayAll();
	cout << endl << endl;

	cout << "Adding new Employee" << endl;
	Employee* emp = new Employee("Den", "Raynolds", 56, 15);
	emp->SetSalary(1500);
	emp->SetDepartment("PR");
	db.HireEmployee(emp);
	db.DisplayAll();
	cout << endl << endl;

	int id = 1;
	cout << "Deleting employee with id = " << id << endl;
	if (db.FireEmployee(1))
		cout << "Success" << endl;
	else
		cout << "Fail, no employee with id = " << id << endl;
	db.DisplayAll();
	cout << endl << endl;

	cout << "Display employees in the IT department" << endl;
	db.DisplayDepartmentEmployees("IT");
	cout << endl << endl;

	cout << "Request to database by salary >= 1000" << endl;
	vector<Person*> sql = db.SQL("salary", "ge", "1000");
	db.ShowRecordSet(sql);
	cout << endl << endl;

	system("pause");
	return 0;
}