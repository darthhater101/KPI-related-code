#include "Database.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

bool Database::LoadFromFile(const char* file)
{
	if (file == nullptr)
		return false;

	string line;
	ifstream f(file);

	if (!f.is_open())
	{
		cout << "Fail!" << endl;
		return false;
	}


	while (getline(f, line)) 
	{
		stringstream ss(line);
		string type, f_name, l_name, id, age, department, salary;

		getline(ss, type, ';');
		getline(ss, id, ';');
		getline(ss, f_name, ';');
		getline(ss, l_name, ';');
		getline(ss, age, ';');
		getline(ss, department, ';');
		getline(ss, salary);


		if (stoi(type) == 0)
		{
			Employee *employee = new Employee(f_name, l_name, stoi(age), stoi(id));

			employee->SetSalary(stoi(salary));
			employee->SetDepartment(department);

			employees.push_back(employee);
		}
		else
		{
			Manager *manager = new Manager(f_name, l_name, stoi(age), stoi(id));

			manager->SetId(stoi(id));
			manager->SetSalary(stoi(salary));
			manager->SetDepartment(department);

			employees.push_back(manager);
		}
	}

	f.close();
	return true;
}

void Database::ArrangeSubordinates()
{
	for (auto &i : employees)
	{
		if (Manager *manager = dynamic_cast<Manager*>(i))
		{
			if (!(manager->GetSub().empty()))
			{
				manager->ClearSub();
			}

			for (auto &j : employees)
			{
				if (typeid(*j) == typeid(Employee))
				{
					Employee *employee = dynamic_cast<Employee*>(j);
					if (employee->GetDepartment() == manager->GetDepartment() && employee != manager)
						manager->AddSubordinate(employee);
				}
			}
		}
	}
}

Person* Database::HireEmployee(Person *p)
{
	if (p == nullptr) 
	{
		return nullptr;
	}

	employees.push_back(p);

	ArrangeSubordinates();

	return p;
}

void Database::DisplayDepartmentEmployees(string _department)
{
	cout << _department << endl;
	if (_department.empty() || (_department != "IT" && _department != "PR"))
	{
		cout << "DisplayDepartmentEmployees FAIL" << endl;
		return;
	}

	for (auto i : employees)
	{
		Employee *employee = dynamic_cast<Employee*>(i);

		if (employee->GetDepartment() == _department)
		{
			employee->Display(1);
		}
	}
}

bool Database::FireEmployee(int id)
{
	for (auto &i : employees)
	{
		Employee *employee = dynamic_cast<Employee*>(i);
		if (employee->GetId() != id)
		{
			continue;
		}
		else
		{
			employees.erase(remove(employees.begin(), employees.end(), employee), employees.end());
			if (typeid(employee) == typeid(Employee*))
				ArrangeSubordinates();
			return true;
		}
	}

	return false;
}

void Database::DisplayAll()
{
	for (auto i : employees)
	{
		i->Display(1);
	}
}

vector<Person*> Database::SQL(const char *field, const char * cond, const char* value)
{
	vector<Person*> sql;
	if ((strcmp(field, "age") != 0) && (strcmp(field, "salary") != 0))
	{
		cout << "Wrong parametr1" << endl;
		return sql;
	}
	if (strcmp(cond, "le") != 0 && strcmp(cond, "ge") != 0)
	{
		cout << "Wrong parametr2" << endl;
		return sql;
	}

	int val = atoi(value);

	for (auto i : employees)
	{
		Employee *employee = dynamic_cast<Employee*>(i);
		if (strcmp(field, "age") == 0)
		{
			if (strcmp(cond, "ge") == 0 && employee->GetAge() >= val)
				sql.push_back(i);
			if (strcmp(cond, "le") == 0 && employee->GetAge() <= val)
				sql.push_back(i);
		}
		if (strcmp(field, "salary") == 0)
		{
			if (strcmp(cond, "ge") == 0 && employee->GetSalary() >= val)
				sql.push_back(i);
			if (strcmp(cond, "le") == 0 && employee->GetSalary() <= val)
				sql.push_back(i);
		}
	}
	return sql;
}

void Database::ShowRecordSet(vector<Person*> rs)
{
	if (rs.empty())
	{
		return;
	}
	for (auto i : rs)
	{
		i->Display(1);
	}
}