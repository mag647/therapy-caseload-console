#include "person.h"
person::person(string firstName, string lastName, string address, string phoneNumber)
{
	setFirstName(firstName);
	setLastName(lastName);
	setAddress(address);
	setPhoneNumber(phoneNumber);
}
person::person()//default constructor
{

}
person::~person()//destructor
{

}
//getters
string person::getFirstName()
{
	return firstName;
}
string person::getLastName()
{
	return lastName;
}
string person::getAddress()
{
	return address;
}
string person::getPhoneNumber()
{
	return phoneNumber;
}
//setters
void person::setFirstName(string firstName)
{
	string noFirstNameError = "First Name not provided!";
	if (firstName.length() == 0)//if no name, throw error 
	{
		throw noFirstNameError;
	}
	this->firstName = firstName;
}
void person::setLastName(string lastName)
{
	string noLastNameError = "Last Name not provided!";
	if (lastName.length() == 0)//if no name, throw error 
	{
		throw noLastNameError;
	}
	this->lastName = lastName;
}
void person::setAddress(string address)
{
	string noAddressError = "Address not provided!";
	if (address.length() == 0)//if no address, throw error 
	{
		throw noAddressError;
	}
	this->address = address;
}
void person::setPhoneNumber(string phoneNumber)
{
	string noPhoneNumberError = "Phone Number not provided!";
	if (phoneNumber.length() == 0)//if no phoneNumber, throw error 
	{
		throw noPhoneNumberError;
	}
	this->phoneNumber = phoneNumber;
}
//tostring for person virtual??

//student child class
student::student(string firstName, string lastName, string address, string phoneNumber,
	string homeroomTeacher, string studentID, int grade, string schoolName): person(firstName, lastName, address, phoneNumber)
{
	setHomeroomTeacher(homeroomTeacher);
	setStudentID(studentID);
	setGrade(grade);
	setSchoolName(schoolName);
}
student::student()//default constructor
{

}
student::~student()//destructor
{

}
//getters
string student::getHomeroomTeacher()
{
	return homeroomTeacher;
}
string student::getstudentID()
{
	return studentID;
}
int student::getGrade()
{
	return grade;
}
string student::getSchoolName()
{
	return schoolName;
}
void student::setHomeroomTeacher(string homeroomTeacher)
{
	this->homeroomTeacher = homeroomTeacher;
}
void student::setStudentID(string studentID)
{
	this->studentID = studentID;
}
void student::setGrade(int grade)
{
	this->grade = grade;
}
void student::setSchoolName(string schoolName)
{
	this->schoolName = schoolName;
}
//overload << operator to print student object
ostream& operator<<(ostream& out, student& s)//would I do essentially what I do with a virutal fucntion? 
{
	
	out << "Student Name: " << s.firstName << " " << s.lastName << endl;
	out << "Student Address: " << s.address << endl;
	out << "Student Phone Number: " << s.phoneNumber << endl;
	out << "Student Grade: " << s.grade << endl;
	out << "Student's Homeroom Teacher: " << s.homeroomTeacher << endl;
	out << "Student's ID Number: " << s.studentID << endl;
	out << "Student's Home School: " << s.schoolName << " Elementary" << endl;
	return out;
}
//tostring 
//special education student grandchild class
specialEducationStudent::specialEducationStudent(string firstName, string lastName, string address, string phoneNumber,
	string homeroomTeacher, string studentID, int grade, string schoolName, string caseManager,
	string diagnosis, int goalProgress, bool goalMet) : student(firstName, lastName, address, phoneNumber, homeroomTeacher, studentID, grade, schoolName) 
{
	setCaseManager(caseManager);
	setDiagnosis(diagnosis);
	setGoalProgress(goalProgress);
	setGoalMet(goalMet);
}
specialEducationStudent::specialEducationStudent(string firstName, string lastName, string address, string phoneNumber,
	string homeroomTeacher, string studentID, int grade, string schoolName): student(firstName, lastName, address, phoneNumber, homeroomTeacher, studentID, grade, schoolName)
{
	
}
specialEducationStudent::specialEducationStudent()//default constructor
{

}
specialEducationStudent::~specialEducationStudent()//destructor
{

}
//getters
string specialEducationStudent::getCaseManager()
{
	return caseManager;
}
string specialEducationStudent::getDiagnosis()
{
	return diagnosis;
}
string specialEducationStudent::getGoal()
{
	return goal;
}
int specialEducationStudent::getGoalProgress()
{
	return goalProgress;
}
bool specialEducationStudent::getGoalMet()
{
	return goalMet;
}
int specialEducationStudent::getTherapyPeriod()
{
	return therapyPeriod;
}
//setters
void specialEducationStudent::setCaseManager(string caseManager)
{
	string noCaseManagerError = "Case manager not provided!";
	if (caseManager.length() == 0)//if no case manager, throw error 
	{
		throw noCaseManagerError;
	}
	this->caseManager = caseManager;
}
void specialEducationStudent::setDiagnosis(string diagnosis)
{
	string noDiagnosisError = "Diagnosis not provided!";
	if (firstName.length() == 0)//if no diagnosis, throw error 
	{
		throw noDiagnosisError;
	}
	this->diagnosis = diagnosis;
}
void specialEducationStudent::setGoal(string goal) ///do I want this as a function?
{
	string noGoalError = "Goal not provided!";
	if (goal.length() == 0)//if no name, throw error 
	{
		throw noGoalError;
	}
	this->goal = goal;
}
void specialEducationStudent::setGoalProgress(int goalProgress)
{
	string goalProgressRangeError = "Goal progress out of range";
	if (goalProgress < 0 || goalProgress > 100)//if goal progress out of range, throw error 
	{
		throw goalProgressRangeError;
	}
	this->goalProgress = goalProgress;
}
void specialEducationStudent::setGoalMet(bool goalMet)
{
	this->goalMet = goalMet;
}
void specialEducationStudent::setTherapyPeriod(int therapyPeriod)
{
	string therapyPeriodRangeError = "Therapy period out of range";
	if (therapyPeriod < 0 || therapyPeriod > 9)//if therapy period out of range, throw error
	{
		throw therapyPeriodRangeError;
	}
	this->therapyPeriod = therapyPeriod;
}
//overloaded << operator to print special education student object
ostream& operator<<(ostream& out, specialEducationStudent& sEd)
{
	out << "Student Name: " << sEd.firstName << " " << sEd.lastName << endl;
	out << "Student Address: " << sEd.address << endl;
	out << "Student Phone Number: " << sEd.phoneNumber << endl;
	out << "Student Grade: " << sEd.grade << endl;
	out << "Student's Homeroom Teacher: " << sEd.homeroomTeacher << endl;
	out << "Student's ID Number: " << sEd.studentID << endl;
	out << "Student's Home School: " << sEd.schoolName << " Elementary" << endl;
	out << "Student's Case Manager: " << sEd.caseManager << endl;
	out << "Student's Diagnosis: " << sEd.diagnosis << " disorder" << endl;
	out << "Student's therapy period: " << sEd.therapyPeriod << endl;
	out << "Student's Goal: " << sEd.goal << endl;
	out << "Student is at " << sEd.goalProgress << " % accuracy with their goal" << endl;
	return out;
}
//speech therapist child class
speechTherapist::speechTherapist(string firstName, string lastName, string address, string phoneNumber,
	string gradeLevelServiced, bool tenure, bool bilingual, double salary, double yearsTaught): person(firstName, lastName, address, phoneNumber)//just create in the code I guess 
{
	setGradeLevelServiced(gradeLevelServiced);
	setTenure(tenure);
	setBilingual(bilingual);
	setSalary(salary);
	setYearsTaught(yearsTaught);
}
speechTherapist::speechTherapist()//default constructor
{

}
speechTherapist::~speechTherapist()//destructor
{

}
string speechTherapist::getGradeLevelServiced()
{
	return gradeLevelServiced;
}
bool speechTherapist::getTenure()
{
	return tenure;
}
bool speechTherapist::getBilingual()
{
	return bilingual;
}
double speechTherapist::getSalary()
{
	return salary;
}
double speechTherapist::getYearsTaught()
{
	return yearsTaught;
}
vector<specialEducationStudent> speechTherapist::getCaseload()
{
	return caseLoad;
}
int speechTherapist::getcaseLoadSize()
{
	return caseLoadSize;
}
void speechTherapist::setGradeLevelServiced(string gradeLevelServiced)
{
	string noGradeLevelServiceError = "Grade level serviced not provided!";
	if (gradeLevelServiced.length() == 0)//if no grade level serviced, throw error 
	{
		throw noGradeLevelServiceError;
	}
	this->gradeLevelServiced = gradeLevelServiced;
}
void speechTherapist::setTenure(bool tenure)
{
	this->tenure = tenure;
}
void speechTherapist::setBilingual(bool bilingual)
{
	this->bilingual = bilingual;
}
void speechTherapist::setSalary(double salary)
{
	string salaryRangeError = "Salary out of range";
	if (salary < 0 || salary > 100000) //if salary out of range, throw error 
	{
		throw salaryRangeError;
	}
	this->salary = salary;
}
void speechTherapist::setYearsTaught(double yearsTaught)
{
	string yearsTaughtRangeError = "Years taught out of range";
	if (yearsTaught < 0 || yearsTaught > 65) //if years taught out of range, throw error
	{
		throw yearsTaughtRangeError;
	}
	this->yearsTaught = yearsTaught;
}
//overload << operator to print out information about speech therapist
ostream& operator<<(ostream& out, speechTherapist& slp)
{
	out << "Therapist Name: " << slp.firstName << " " << slp.lastName << endl;
	out << "Therapist Address: " << slp.address << endl;
	out << "Therapist Phone Number: " << slp.phoneNumber << endl;
	out << "Therapist Grade-Levels Serviced: " << slp.gradeLevelServiced << endl;
	out << "Does therapist have tenure?: ";
	if (!slp.tenure)
	{
		out << "No" << endl;
	}
	else
	{
		cout << "Yes" << endl;
	}
	out << "Is therapist bilingual?: ";
	if (!slp.bilingual)
	{
		out << "No" << endl;
	}
	else
	{
		cout << "Yes" << endl;
	}
	out << "Current Therapist Salary: " << slp.salary << endl;
	out << "Years taught in district: " << slp.yearsTaught << endl;

	return out;
}
void speechTherapist::addCaseloadStudent(specialEducationStudent myStud)
{
	caseLoad.push_back(myStud);
}
void speechTherapist::removeCaseloadStudent(int removeIndex)
{
	if (caseLoad.size() > 0)
	{
		caseLoad.erase(caseLoad.begin() + removeIndex);
	}
	else
	{
		cout << "No students to remove. Caseload is empty." << endl;
	}
}
//outputs information on all special education students to console
void speechTherapist::printCaseload()
{
	if (caseLoad.size() > 1)
	{
		for (int i = 0; i < caseLoad.size(); i++)
		{
			cout << caseLoad.at(i) << endl;
		}
	}
	else
	{
		cout << "Caseload is empty" << endl;
	}
}
//functions to change attributes of special education students in caseload
void speechTherapist::setProgressinCaseload(int caseIndex, int progressNumber)
{
	caseLoad.at(caseIndex).setGoalProgress(progressNumber);
}
void speechTherapist::setGoalinCaseload(int goalIndex, string studentGoal)
{
	caseLoad.at(goalIndex).setGoal(studentGoal);
}
void speechTherapist::setTherapyPeriodinCaseload(int periodIndex, int studentSched)
{
	caseLoad.at(periodIndex).setTherapyPeriod(studentSched);
}