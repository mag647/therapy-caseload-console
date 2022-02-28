#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <iomanip>

using namespace std;
//base person class
class person
{
protected:
	string firstName;
	string lastName;
	string address;
	string phoneNumber;
public:
	//constructors
	person(string, string, string, string);
	person();
	//destructors
	~person();
	//getters
	string getFirstName();
	string getLastName();
	string getAddress();
	string getPhoneNumber();
	//setters
	void setFirstName(string);
	void setLastName(string);
	void setAddress(string);
	void setPhoneNumber(string);
};
//child student class
class student : public person
{
protected:
	string homeroomTeacher;
	string studentID;
	int grade = 0;
	string schoolName;

public:
	//constructors
	student(string firstName, string lastName, string address, string phoneNumber,
		string homeroomTeacher, string studentID, int grade, string schoolName);
	student();
	//destructor
	~student();
	//getters
	string getHomeroomTeacher();
	string getstudentID();
	int getGrade();
	string getSchoolName();
	//setters
	void setHomeroomTeacher(string);
	void setStudentID(string);
	void setGrade(int);
	void setSchoolName(string);
	//overloaded << operator 
	friend ostream& operator<<(ostream&, student&);
};
//grandchild special education student class
class specialEducationStudent : public student
{
private:
	string caseManager = "No set case manager";
	string diagnosis = "No current diagnosis";
	string goal = "No current goal";
	int goalProgress = 0;
	bool goalMet = false;
	int therapyPeriod = 0;
	
public:
	//constructors
	specialEducationStudent(string firstName, string lastName, string address, string phoneNumber,
		string homeroomTeacher, string studentID, int grade, string schoolName, string caseManager,
		string diagnosis, int goalProgress, bool goalMet); 
	specialEducationStudent(string firstName, string lastName, string address, string phoneNumber,
		string homeroomTeacher, string studentID, int grade, string schoolName);
	specialEducationStudent();
	//destructor
	~specialEducationStudent();
	//getters
	string getCaseManager();
	string getDiagnosis();
	string getGoal();
	int getGoalProgress();
	bool getGoalMet();
	int getTherapyPeriod();
	//setters
	void setCaseManager(string);
	void setDiagnosis(string);
	void setGoal(string);
	void setGoalProgress(int);
	void setGoalMet(bool);
	void setTherapyPeriod(int);
	void assignSpecEdStudentGoal();
	//overloaded << operator 
	friend ostream& operator<<(ostream&, specialEducationStudent&);
};
//child speech therapist class
class speechTherapist : public person
{
private: 
	string gradeLevelServiced = "No grade level set";
	bool tenure = false;
	bool bilingual = false;
	double salary = 0.00;
	double yearsTaught = 0;
	vector<specialEducationStudent> caseLoad;
	int caseLoadSize = 0;
public:
	//constructors
	speechTherapist(string firstName, string lastName, string address, string phoneNumber,
		string gradeLevelServiced, bool tenure, bool bilingual, double salary, double yearsTaught);
	speechTherapist();
	//destructor
	~speechTherapist();
	//getters
	string getGradeLevelServiced();
	bool getTenure();
	bool getBilingual();
	double getSalary();
	double getYearsTaught();
	vector<specialEducationStudent> getCaseload();
	int getcaseLoadSize();
	//setters
	void setGradeLevelServiced(string);
	void setTenure(bool);
	void setBilingual(bool);
	void setSalary(double);
	void setYearsTaught(double);
	//add/remove students from caseload
	void addCaseloadStudent(specialEducationStudent);
	void removeCaseloadStudent(int);
	//output all members of caseload to console
	void printCaseload();
	//set attributes of special education students in caseload
	void setProgressinCaseload(int, int);
	void setGoalinCaseload(int, string);
	void setTherapyPeriodinCaseload(int, int);
	//overloaded << operator 
	friend ostream& operator<<(ostream&, speechTherapist&);
};