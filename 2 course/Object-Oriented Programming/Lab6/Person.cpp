#include "Person.h"

Employee::Employee(const Employee &e)
{
	age = e.age;
	f_name = e.f_name;
	l_name = e.l_name;
	department = e.department;
	salary = e.salary;
	id = e.id;
}

Employee& Employee::operator=(const Employee &e)
{
	if (this != &e)
	{
		age = e.age;
		salary = e.salary;
		id = e.id;
		f_name = e.f_name;
		l_name = e.l_name;
		department = e.department;
	}
	return *this;
}

void Employee::SetSalary(int s)
{
	salary = s;
}
void Employee::SetDepartment(string dept)
{
	department = dept;
}
void Employee::SetId(int n)
{
	id = n;
}

int Employee::GetId()
{
	return id;
}
string Employee::GetDepartment()
{
	return department;
}

Manager::Manager(const Manager &m)
{
	age = m.age;
	f_name = m.f_name;
	l_name = m.l_name;
	department = m.department;
	salary = m.salary;
	id = m.id;
	subordinates = m.subordinates;
}

Manager& Manager::operator=(const Manager &m)
{
	if (this != &m)
	{
		age = m.age;
		f_name = m.f_name;
		l_name = m.l_name;
		department = m.department;
		salary = m.salary;
		id = m.id;
		subordinates = m.subordinates;
	}
	return *this;
}

Person* Manager::AddSubordinate(Person *p)
{
	if (p == nullptr)
	{
		return nullptr;
	}
	if (typeid(*p) == typeid(Manager))
	{
		return nullptr;
	}

	if (Employee *employee = dynamic_cast<Employee*>(p))
	{
		if (employee->GetDepartment() == department)
			subordinates.push_back(employee);
	}
	return p;
}

void Manager::DisplaySubordinates()
{
	if (subordinates.empty())
	{
		cout << "\tEmpty subordinates" << endl;
		return;
	}
	for (auto i : subordinates)
	{
		Employee *employee = dynamic_cast<Employee*>(i);

		cout << "\tEmpoyeement type: Employee" << endl
			<< "\tFirst name: " << employee->GetFname() << endl
			<< "\tLast Name: " << employee->GetLname() << endl
			<< "\tAge: " << employee->GetAge() << endl
			<< "\tDepartment: " << employee->GetDepartment() << endl
			<< "\tSalary: " << employee->GetSalary() << endl
			<< "\tId: " << employee->GetId() << endl;
	}
}

void Employee::Display(bool b)
{
	cout << "Empoyeement type: Employee" << endl
		<< "Id: " << id << endl
		<< "First name: " << f_name << endl
		<< "Last Name: " << l_name << endl
		<< "Age: " << age << endl
		<< "Department: " << department << endl
		<< "Salary: " << salary << endl;
}

void Manager::Display(bool b)
{
	cout << "Empoyeement type: Manager" << endl
		<< "Id: " << id << endl
		<< "First name: " << f_name << endl
		<< "Last Name: " << l_name << endl
		<< "Age: " << age << endl
		<< "Department: " << department << endl
		<< "Salary: " << salary << endl;

	if (b)
	{
		cout << "Subordinates:" << endl;
		DisplaySubordinates();
		cout << endl;
	}
}

int Employee::GetAge()
{
	return age;
}

int Employee::GetSalary()
{
	return salary;
}

string Employee::GetFname()
{
	return f_name;
}

string Employee::GetLname()
{
	return l_name;
}

list<Person *>  Manager::GetSub()
{
	return subordinates;
}

void Manager::ClearSub()
{
	subordinates.clear();
}