// MGayCSCI201Final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Program name: speechTherapyProgram.cpp
//Author: Michele Gay
//Date last updated: 12/18/2020
//Purpose: To read student data from a file, add students to a speech therapist's
//caseload and allow the user to manipulate the caseload and analyze a language sample. 


#include "person.h"
#include <climits>
#include<iomanip>
#include <algorithm>

//function prototypes 
double getNumOfMorphemes(const string);
int getNumOfWords(const string);
double getNumOfUtterances(const string);
string removeMorphemeMarkers(string);
void printMainMenu(speechTherapist&, vector<string>&);
char printLangMenu(string);
void runLangSampleOptions();
void setAllDiagnoses(vector<specialEducationStudent>&);


int main()
{
    //variable declaration
    string studID;
    string studLastName;
    string studFirstName;
    int studGrade = 0;
    string studTeacher;
    string studSchool;
    string studAddress;
    string studPhone;
    
    //vector to hold specialEducationStudents 
    vector<specialEducationStudent> studentList;
    vector<string> lastNameList;
    int numStudents = 0;
    try
    {
        //creates a speech therapist to use for the duration of the program 
        speechTherapist schoolTherapist1("Maria", "Lopez", "123 Division Street, Old Forge, PA", "570-123-4445", "Grades K-5", false, true, 45500, 2.5);

            //variable declaration
        int numCharToPrint = 65;
        char charToPrint = '-';

        //Outputs a line of hyphens to the console 
        cout << string(numCharToPrint, charToPrint) << endl << endl;
        //Outputs a welcome message to the console
        cout << "Welcome to your case management system, " << schoolTherapist1.getFirstName() << " " << schoolTherapist1.getLastName() << "!" << endl << endl;

        cout << "This is the current information we have on file for you: " << endl;
        //output speech therapist information using overloaded operator
        cout << schoolTherapist1 << endl;

        //Outputs a line of hyphens to the console 
        cout << string(numCharToPrint, charToPrint) << endl << endl;

        //create input stream to read student data from file and open file 
        ifstream inSpecEdStudentData;
        inSpecEdStudentData.open("testFile.txt");

        while (inSpecEdStudentData.peek() != EOF) //read student info from file and instantiate special education student objects
        {
            inSpecEdStudentData >> studID >> studLastName >> studFirstName >> studGrade >> studTeacher >> studSchool;
            inSpecEdStudentData.clear();
            inSpecEdStudentData.ignore(INT_MAX, '#');
            getline(inSpecEdStudentData, studAddress);
            getline(inSpecEdStudentData, studPhone);
            specialEducationStudent createdStudent(studFirstName, studLastName, studAddress, studPhone, studTeacher, studID, studGrade, studSchool);
            studentList.push_back(createdStudent);
            lastNameList.push_back(studLastName);
        }

        //Close input file
        inSpecEdStudentData.close();

        cout << "The special education office has added the " << studentList.size() << " requested students to your caseload." << endl << endl;

        //call function to set diagnosis for all students in vector
       setAllDiagnoses(studentList);

        //add students to speech therapist caseload
        for (int i = 0; i < studentList.size(); i++)
        {
            schoolTherapist1.addCaseloadStudent(studentList.at(i));
        }

        printMainMenu(schoolTherapist1, lastNameList);
    }//output string error
    catch (string msg)
    {
        cout << msg << endl;
    }
    catch (...)
    {
        cout << "Unknown error occured!";
    }

    return 0;
}
//**BEGINNING OF FUNCTIONS FOR LANGUAGE ANALYZER
double getNumOfMorphemes(const string usrStr) //count number of '@' characters in the user text
{
     //Variable declaration
    int morphemeCount = 0; 
    unsigned int i; 

     //iterates through all characters in the text entered by the user. 
    for (i = 1; i < usrStr.size(); ++i) {
        //If the current character is a '@' increment count by 1 
        if (usrStr.at(i) == '@') {
            ++morphemeCount; //Increments the variable count by 1
        }
    }

    return morphemeCount; 
}
int getNumOfWords(const string usrStr)//counts number of words user enters
{
    //Variable declaration
    int wordCount = 0; 
    unsigned int i;

    //interate through all characters in the text entered by the user. 
    for (i = 1; i < usrStr.size(); ++i) 
    {
        //If the current character is a space, and the previous character is not, increment wordCount
        if (isspace(usrStr.at(i)) && !isspace(usrStr.at(i - 1))) 
        {
            ++wordCount;
        }
    }

    //If the last character is not a space, add to the word count. 
    if (!isspace(usrStr.at(usrStr.size() - 1))) 
    {
        ++wordCount; //Increments the variable count by 1
    }

    return wordCount; 
}
double getNumOfUtterances(const string usrStr)
{
    //Variable declaration
    int uttCount = 0; 
    unsigned int i; 

     //iterates through all characters in the text entered by the user. 
    for (i = 1; i < usrStr.size(); ++i) 
    {
        //If the current character '.', '!', or '?' increment utterance (sentence) count 
        if (usrStr.at(i) == '.' || usrStr.at(i) == '!' || usrStr.at(i) == '?') 
        {
            ++uttCount; 
        }
    }

    return uttCount;
}
string removeMorphemeMarkers(string usrStr)
{
    //This function will remove the '@' characters previously used to count morphemes from the user's text
    /*The string the user entered will not be permanently changed; the string with the markers removed
    will be saved into the noMorphemeString variable and returned*/

    //Variable declaration
    string noMorphemeString = "";
    int i;
    int inputSize = usrStr.size();

    //interates through string 
    for (i = 0; i < inputSize; ++i) {
        //If the current character is '@', remove it. 
        if (usrStr.at(i) == '@') 
        {
            usrStr.replace(usrStr.find('@'), 1, "");
            //Reduce input size and counter variable i by 1 because the character was removed
            inputSize--;
            i--;
        }
    }
    noMorphemeString.append(usrStr); //Add edited string into noMorphemeString variable

    return noMorphemeString; 
}
//**END OF FUNCTIONS FOR LANGUAGE ANALYZER

//prints out and implements main menu options for program
void printMainMenu(speechTherapist& mySLP, vector<string>& myNames)
{
    //local variable declaration
    char userChoice = ' ';
    string lastName = " ";
    string firstName = " ";
    int progressNum = 0;
    int userNumber = 0;
    int therapyPeriod = 0;

    vector<int> sandersFreePeriods{ 1, 4, 7 };
    vector<int> arnoldFreePeriods{ 2, 4, 8 };
    vector<int> poltFreePeriods{ 3,5,6 };
    vector<int> maherFreePeriods{ 2, 5, 9 };

    string articGoal;
    string expGoal;
    string recGoal;
    string fluencyGoal;
    vector<string> articulationGoals;
    vector<string> expressiveLangGoals;
    vector<string> receptiveLangGoals;
    vector<string> fluencyGoals;

    try
    {
        //for each goal type, read set of goals from file into corresponding vector
        ifstream articGoalsData;
        articGoalsData.open("articulationGoals.txt");
        while (articGoalsData.peek() != EOF)
        {
            getline(articGoalsData, articGoal);
            articulationGoals.push_back(articGoal);
        }

        articGoalsData.close();

        ifstream expLangGoalsData;
        expLangGoalsData.open("expressiveLangGoals.txt");
        while (expLangGoalsData.peek() != EOF)
        {
            getline(expLangGoalsData, expGoal);
            expressiveLangGoals.push_back(expGoal);
        }

        expLangGoalsData.close();

        ifstream recLangGoalsData;
        recLangGoalsData.open("receptiveLangGoals.txt");
        while (recLangGoalsData.peek() != EOF)
        {
            getline(recLangGoalsData, recGoal);
            receptiveLangGoals.push_back(recGoal);
        }

        recLangGoalsData.close();

        ifstream fluencyGoalsData;
        fluencyGoalsData.open("fluencyGoals.txt");
        while (fluencyGoalsData.peek() != EOF)
        {
            getline(fluencyGoalsData, fluencyGoal);
            fluencyGoals.push_back(fluencyGoal);
        }
        fluencyGoalsData.close();

        while (userChoice != 'q')
        {
            //output main menu to user 
            cout << " MAIN MENU" << endl;
            cout << "1 - View speech therapist caseload" << endl;
            cout << "2 - Schedule student" << endl;
            cout << "3 - Set student goal" << endl;
            cout << "4 - Set student progress" << endl;
            cout << "5 - View student progress" << endl;
            cout << "6 - Add student to caseload" << endl;
            cout << "7 - Remove student from caseload" << endl;
            cout << "8 - View student information" << endl;
            cout << "9 - Start language Sample Analyzer" << endl;
            cout << "q - Quit" << endl << endl;

            //Get user's choice 
            cout << "Choose an option:" << endl;
            cin >> userChoice;

            //If the user does not enter one of the valid menu choices, keep prompting the user until they enter the expected input 
            while (userChoice != '1' && userChoice != '3' && userChoice != '4' && userChoice != '2' &&
                userChoice != '5' && userChoice != '6' && userChoice != '7' && userChoice != '8' && userChoice != '9' && userChoice != 'q')
            {
                cin.clear();
                cin.ignore(INT_MAX, '/n');
                //Output text prompting the user to chose an option
                cout << "Choose an option:" << endl;
                //Take text user entered and save in variable 
                cin >> userChoice;
            }
            if (userChoice == '1')
            {
                cout << "Accessing caseload data: " << endl;
                mySLP.printCaseload(); //prints data for all students on speech therapist's caseload
                //Resets to a blank character. 
                userChoice = ' ';
            }
            else if (userChoice == '2')
            {
                cout << "Enter the student's last name to schedule: ";
                cin >> lastName;
                cout << endl;

                //create iterator to find index of target name in vector 
                vector<string>::iterator itr = find(myNames.begin(), myNames.end(), lastName);
                if (itr != myNames.cend())
                {
                    int targetLocation = distance(myNames.begin(), itr); //target index for student 
                    string myTeacher = mySLP.getCaseload().at(targetLocation).getHomeroomTeacher(); //get teacher from corresponding student in speech therapist caseload vector 
                    cout << "Student is in " << myTeacher << "'s class. Free periods are: ";
                   
                    if (myTeacher == "Sanders")
                    {
                        for (int i = 0; i < sandersFreePeriods.size(); i++)
                        {
                            cout << sandersFreePeriods.at(i) << " ";
                        }

                        cout << "Enter one of the periods above to set student therapy period: " << endl;
                        cin >> therapyPeriod;
                        vector<int>::iterator it = find(sandersFreePeriods.begin(), sandersFreePeriods.end(), therapyPeriod);
                        if (it != sandersFreePeriods.cend())
                        {
                            mySLP.setTherapyPeriodinCaseload(targetLocation, therapyPeriod);
                            cout << "Therapy scheduled for period: " << therapyPeriod << endl;
                        }
                        else
                        {
                            cout << "Therapy period not one of the student's free periods. Therapy not scheduled." << endl;
                        }
                    }
                    else if (myTeacher == "Arnold")
                    {
                        for (int i = 0; i < arnoldFreePeriods.size(); i++)
                        {
                            cout << arnoldFreePeriods.at(i) << " ";
                        }
                        cout << "Enter one of the periods above to set student therapy period: " << endl;
                        cin >> therapyPeriod;
                        vector<int>::iterator it = find(arnoldFreePeriods.begin(), arnoldFreePeriods.end(), therapyPeriod);
                        if (it != arnoldFreePeriods.cend())
                        {
                            mySLP.setTherapyPeriodinCaseload(targetLocation, therapyPeriod);
                            cout << "Therapy scheduled for period: " << therapyPeriod << endl;
                        }
                        else
                        {
                            cout << "Therapy period not one of the student's free periods. Therapy not scheduled." << endl;
                        }
                    }
                    else if (myTeacher == "Polt")
                    {
                        for (int i = 0; i < poltFreePeriods.size(); i++)
                        {
                            cout << poltFreePeriods.at(i) << " ";
                        }
                        cout << "Enter one of the periods above to set student therapy period: " << endl;
                        cin >> therapyPeriod;
                        vector<int>::iterator it = find(poltFreePeriods.begin(), poltFreePeriods.end(), therapyPeriod);
                        if (it != poltFreePeriods.cend())
                        {
                            mySLP.setTherapyPeriodinCaseload(targetLocation, therapyPeriod);
                            cout << "Therapy scheduled for period: " << therapyPeriod << endl;
                        }
                        else
                        {
                            cout << "Therapy period not one of the student's free periods. Therapy not scheduled." << endl;
                        }
                    }
                    else if (myTeacher == "Maher")
                    {
                        for (int i = 0; i < maherFreePeriods.size(); i++)
                        {
                            cout << maherFreePeriods.at(i) << " ";
                        }
                        cout << "Enter one of the periods above to set student therapy period: " << endl;
                        cin >> therapyPeriod;
                        vector<int>::iterator it = find(maherFreePeriods.begin(), maherFreePeriods.end(), therapyPeriod);
                        if (it != maherFreePeriods.cend())
                        {
                            mySLP.setTherapyPeriodinCaseload(targetLocation, therapyPeriod);
                            cout << "Therapy scheduled for period: " << therapyPeriod << endl;
                        }
                        else
                        {
                            cout << "Therapy period not one of the student's free periods. Therapy not scheduled." << endl;
                        }
                    }
                    else
                    {
                        cout << "unknown for this homeroom teacher." << endl;
                        cout << "Contact teacher before scheduling this student." << endl;
                    }
                }
                else
                {
                    cout << "Student with name entered not found. " << endl;
                }
                cout << endl;

                    //Resets to a blank character.
                userChoice = ' ';
            }
            else if (userChoice == '3')
            {
                //get last name for student to set goal
                cout << "You chose to set a student's goal. What is the student's last name?: ";
                cin >> lastName;
                cout << endl;

                //create iterator to use in finding index of target student 
                vector<string>::iterator itr = find(myNames.begin(), myNames.end(), lastName);
                if (itr != myNames.cend())
                {
                    int targetLocation = distance(myNames.begin(), itr);
                    string studDiagnosis = mySLP.getCaseload().at(targetLocation).getDiagnosis();//get diagnosis from corresponding student in speech therapist caseload vector 
                    cout << "Student has been diagnosed with an/a " << studDiagnosis << " disorder." << endl;
                    cout << "These are the goals you may choose from: " << endl;
                    if (studDiagnosis == "Articulation") //output goals from articulation goal vector as choices
                    {
                        for (int i = 0; i < articulationGoals.size(); i++)
                        {
                            cout << i + 1 << " - ";
                            cout << articulationGoals.at(i) << endl;
                        }
                        cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                        cin >> userNumber;
                        while (!cin || userNumber < 1 || userNumber > 3)
                        {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Invalid input for goal choice" << endl;
                            cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                            cin >> userNumber;
                        }
                        if (userNumber == 1)
                        {
                            mySLP.setGoalinCaseload(targetLocation, articulationGoals.at(0));
                        }
                        else if (userNumber == 2)
                        {
                            mySLP.setGoalinCaseload(targetLocation, articulationGoals.at(1));
                        }
                        else if (userNumber == 3)
                        {
                            mySLP.setGoalinCaseload(targetLocation, articulationGoals.at(2));
                        }
                        else
                        {
                            cout << "Invalid input. Goal not set" << endl;
                        }
                    }
                    else if (studDiagnosis == "Expressive Language")//output goals from expressive language goal vector as choices
                    {
                        for (int i = 0; i < expressiveLangGoals.size(); i++)
                        {
                            cout << i + 1 << " - ";
                            cout << expressiveLangGoals.at(i) << endl;
                        }
                        cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                        cin >> userNumber;
                        while (!cin || userNumber < 1 || userNumber > 3)
                        {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Invalid input for goal choice" << endl;
                            cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                            cin >> userNumber;
                        }
                        if (userNumber == 1)
                        {
                            mySLP.setGoalinCaseload(targetLocation, expressiveLangGoals.at(0));
                        }
                        else if (userNumber == 2)
                        {
                            mySLP.setGoalinCaseload(targetLocation, expressiveLangGoals.at(1));
                        }
                        else if (userNumber == 3)
                        {
                            mySLP.setGoalinCaseload(targetLocation, expressiveLangGoals.at(2));
                        }
                        else
                        {
                            cout << "Invalid input. Goal not set" << endl;
                        }
                    }
                    else if (studDiagnosis == "Receptive Language")//output goals from receptive language goal vector as choices
                    {
                        for (int i = 0; i < receptiveLangGoals.size(); i++)
                        {
                            cout << i + 1 << " - ";
                            cout << receptiveLangGoals.at(i) << endl;
                        }
                        cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                        cin >> userNumber;
                        while (!cin || userNumber < 1 || userNumber > 3)
                        {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Invalid input for goal choice" << endl;
                            cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                            cin >> userNumber;
                        }
                        if (userNumber == 1)
                        {
                            mySLP.setGoalinCaseload(targetLocation, receptiveLangGoals.at(0));
                        }
                        else if (userNumber == 2)
                        {
                            mySLP.setGoalinCaseload(targetLocation, receptiveLangGoals.at(1));
                        }
                        else if (userNumber == 3)
                        {
                            mySLP.setGoalinCaseload(targetLocation, receptiveLangGoals.at(2));
                        }
                        else
                        {
                            cout << "Invalid input. Goal not set" << endl;
                        }
                    }
                    else if (studDiagnosis == "Fluency")//output goals from fluency goal vector as choices
                    {
                        for (int i = 0; i < fluencyGoals.size(); i++)
                        {
                            cout << i + 1 << " - ";
                            cout << fluencyGoals.at(i) << endl;
                        }
                        cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                        cin >> userNumber;
                        while (!cin || userNumber < 1 || userNumber > 3)
                        {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Invalid input for goal choice" << endl;
                            cout << "Which goal would you like to set? Please enter 1, 2, or 3: ";
                            cin >> userNumber;
                        }
                        if (userNumber == 1)
                        {
                            mySLP.setGoalinCaseload(targetLocation, fluencyGoals.at(0));
                        }
                        else if (userNumber == 2)
                        {
                            mySLP.setGoalinCaseload(targetLocation, fluencyGoals.at(1));
                        }
                        else if (userNumber == 3)
                        {
                            mySLP.setGoalinCaseload(targetLocation, fluencyGoals.at(2));
                        }
                        else
                        {
                            cout << "Invalid input. Goal not set" << endl;
                        }
                    }
                    else
                    {
                        cout << "Student's diagnosis is not currently set." << endl;
                    }
                }
                else
                {
                    cout << "Student with name entered not found. " << endl;
                }

                //Resets to a blank character.
                userChoice = ' ';
            }
            else if (userChoice == '4')
            {
                cout << "Enter the last name of the student you would like to set progress for: ";
                cin >> lastName;
                cout << endl;
                vector<string>::iterator itr = find(myNames.begin(), myNames.end(), lastName);
                if (itr != myNames.cend())
                {
                    int targetLocation = distance(myNames.begin(), itr);
                    cout << "What would you like to set progress to? (Please enter a whole number between 0 and 100): ";
                    cin >> progressNum;
                    mySLP.setProgressinCaseload(targetLocation, progressNum);
                    cout << "Student progress set." << endl;
                }
                else
                {
                    cout << "Student with name entered not found. " << endl;
                }
                //Resets to a blank character.
                userChoice = ' ';
            }
            else if (userChoice == '5')
            {
                cout << "Enter the last name of the student to view progress: ";
                cin >> lastName;
                cout << endl;
                vector<string>::iterator itr = find(myNames.begin(), myNames.end(), lastName);
                if (itr != myNames.cend())
                {
                    int targetLocation = distance(myNames.begin(), itr);
                    int progressNum = mySLP.getCaseload().at(targetLocation).getGoalProgress();
                    string studGoal = mySLP.getCaseload().at(targetLocation).getGoal();
                    //prints goal and current progress 
                    cout << "Student's goal is: " << studGoal << endl;
                    cout << "Student is at " << progressNum << "% accuracy with this goal" << endl;
                }
                else
                {
                    cout << "Student with name entered not found. " << endl;
                }
                //Resets to a blank character.
                userChoice = ' ';
            }
            else if (userChoice == '6')
            {
                //local variable declaration
                string studLastName1;
                string studFirstName1;
                string studAddress1;
                string studPhoneNum1;
                string homeroomTeacher1;
                string studID1;
                int studGrade1;
                string schoolName1;

                //get information about student from user 
                cin.ignore();
                cout << "Enter information about a student to add to your caseload: " << endl << endl; 
                cout << "Enter Student's last name: ";
                cin >> studLastName1;
                cout << endl;
                cout << "Enter Student's first name: ";
                cin >> studFirstName1;
                cout << endl;
                cin.ignore();
                cout << "Enter Student's address: ";
                getline(cin, studAddress1);
                cout << endl;
                cout << "Enter Student's phone number: ";
                getline(cin, studPhoneNum1);
                cout << endl;
                cout << "Enter Student's homeroom teacher (last name only): ";
                cin >> homeroomTeacher1;
                cout << endl;
                cout << "Enter Student's ID: ";
                cin >> studID1;
                cout << endl;
                cout << "Enter student's grade: ";
                cin >> studGrade1;
                cout << endl;
                cout << "Enter name of Student's school: ";
                cin >> schoolName1;

                myNames.push_back(studLastName1);

                //instantiate special education student object 
                specialEducationStudent mySpecEdStudent(studFirstName1, studLastName1, studAddress1, studPhoneNum1, homeroomTeacher1, studID1, studGrade1, schoolName1);
                //add special education student to caseload
                mySLP.addCaseloadStudent(mySpecEdStudent);

                //Resets to a blank character.
                userChoice = ' ';
            }
            else if (userChoice == '7')
            {
                cout << "Enter the last name of the student to remove: ";
                cin >> lastName;
                cout << endl;
                vector<string>::iterator itr = find(myNames.begin(), myNames.end(), lastName);
                if (itr != myNames.cend())
                {
                    int targetLocation = distance(myNames.begin(), itr);
                    mySLP.removeCaseloadStudent(targetLocation);
                }
                else
                {
                    cout << "Student with name entered not found. " << endl;
                }
                //Resets to a blank character.
                userChoice = ' ';
            }
            else if (userChoice == '8')
            {
                cout << "Enter last name of student to view information: ";
                cin >> lastName;
                cout << endl;
                vector<string>::iterator itr = find(myNames.begin(), myNames.end(), lastName);
                if (itr != myNames.cend())
                {
                    int targetLocation = distance(myNames.begin(), itr);
                    cout << mySLP.getCaseload().at(targetLocation) << endl;
                }
                else
                {
                    cout << "Student with name entered not found. " << endl;
                }

                //Resets to a blank character.
                userChoice = ' ';
            }
            else if (userChoice == '9')
            {
                cout << "Starting language analyzer!" << endl;
                runLangSampleOptions();
            }
            cout << endl;
        }
    }//add string error
    catch (string msg)
    {
        cout << msg << endl;
    }
    catch (...)
    {
        cout << "Unknown error occured!" << endl;
    }
}
char printLangMenu(string usrStr)//prints language analyzer menu 
{
    
    //Variable declaration 
    char menuChoice;

    //Outputs text to the console that provides a menu of choices to the user 
    cout << "LANGUAGE SAMPLE ANALYZER MENU" << endl;
    cout << "1 - Number of morphemes" << endl;
    cout << "2 - View text without morpheme markers" << endl; 
    cout << "3 - Number of words" << endl;
    cout << "4 - Number of utterances" << endl;
    cout << "5 - Calculate MLU (mean length of utterance):" << endl;
    cout << "q - Quit and print results" << endl << endl;

    //Initializes to a space
    menuChoice = ' ';

    //If the user does not enter one of the valid menu choices, keep prompting the user until they enter the expected input 
    while (menuChoice != '1' && menuChoice != '3' && menuChoice != '4' && menuChoice != '2' &&
        menuChoice != '5' && menuChoice != 'q') 
    {
        //Output text prompting the user to chose an option
        cout << "Choose an option:" << endl;
        //Take text user entered and save in menuOp variable 
        cin >> menuChoice;
    }
    if (menuChoice == '1') 
    {
        //Output the number of morphemes to the console. Calls the function GetNumOfMorphemes to calculate number of morphemes. 
        cout << "Number of morphemes: " << getNumOfMorphemes(usrStr) << endl
            << endl;
        //Resets to a blank character. 
        menuChoice = ' ';
    }
    else if (menuChoice == '2') 
    {
        //Outputs edited string to the console. Calls the function RemoveMorphemeMarkers to output a string with the markers removed.  
        cout << "Text with morpheme markers removed: " << endl;
        cout << removeMorphemeMarkers(usrStr) << endl << endl;
        //Resets to a blank character.
        menuChoice = ' ';//can I do a clear and ignore?
    }
    else if (menuChoice == '3') 
    {
        //Outputs the number of words to the console. Calls the function GetNumOfWords to calculate number of words. 
        cout << "Number of words: " << getNumOfWords(usrStr) << endl << endl;
        //Resets to a blank character.
        menuChoice = ' ';
    }
    else if (menuChoice == '4') 
    {
        //Outputs the number of utterances to the console. Calls the function GetNumOfUtterances to calculate number of utterances. 
        cout << "Number of utterances: " << getNumOfUtterances(usrStr) << endl << endl;
        //Resets to a blank character.
        menuChoice = ' ';
    }
    else if (menuChoice == '5') 
    {
        //Calculate MLU 
        double MLU = getNumOfMorphemes(usrStr) / getNumOfUtterances(usrStr);

        //Sets output to display 2 decimal places an output MLU
        cout << fixed << setprecision(2);
        cout << "MLU: " << MLU << endl << endl;

        //Resets to a blank character.
        menuChoice = ' ';
    }
    cout << endl;

    return menuChoice;
    //End function definition
}
//starts language sample analyzer
void runLangSampleOptions()
{
  //Variable declaration 
    string userString;
    char menuChoice = ' ';
    string childName;
    string childFirstName;
    string childLastName;
    int childAge;
    int numCharToPrint = 65;
    char charToPrint = '-';
 
     //Outputs a line of hyphens to the console 
    cout << string(numCharToPrint, charToPrint) << endl;
    //Outputs welcome message to the console
    cout << "Welcome to the Pediatric Language Sample Analyzer!" << endl;
   
    //Outputs a line of hyphens to the console
    cout << string(numCharToPrint, charToPrint) << endl << endl;

    //Outputs text to the console prompting user to enter child's name
    cout << "Please enter the first and last name of the child being assessed: " << endl;
    cin >> childFirstName >> childLastName;
  
    //Outputs text to the console prompting user to enter child's age
    cout << "Please enter the child's age (in months):" << endl;
    //Take input entered by user and save to childAge variable 
    cin >> childAge;
    while (!cin || childAge < 0 || childAge > 180)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input for child's age" << endl;
        cout << "Please enter the child's age (in months):" << endl;
        cin >> childAge;
    }

    //Prompt user to enter text within the stated parameters 
    cout << "Enter " << childFirstName << " " << childLastName << "'s language sample. Type @ after each morpheme." << endl;
    cout << "Use a punctuation mark(\".\", \"!\", or \"?\") after each utterance:" << endl;
    //Ignore previous text input 
    cin.ignore();
    //Get text entered by user and save to variable userString
    getline(cin, userString);
    //Output blank line to console
    cout << endl;
    //Output entered text back to user
    cout << "You entered: " << userString << endl << endl;

    //As long as the user has not entered 'q' to quit, call PrintLangMenu function again 
    while (menuChoice != 'q') 
    {
        menuChoice = printLangMenu(userString);//calls function to print out menu for language analyzer
    }

    cout << endl;
    //Outputs a line of hyphens to the console
    cout << string(numCharToPrint, charToPrint) << endl;

    //outputs a summary of results to the console:
    cout << "Language Sample Analysis Summary:" << endl << endl;
    cout << "Child Name: " << childFirstName << " " << childLastName << endl;
    cout << "Child Age: " << childAge / 12 << " years " << childAge % 12 << " months " << endl;
    cout << "Number of Morphemes: " << getNumOfMorphemes(userString) << endl;
    cout << "Number of Words: " << getNumOfWords(userString) << endl;
    cout << "Number of Utterances: " << getNumOfUtterances(userString) << endl;
    cout << fixed << setprecision(2); //Sets output of subsequent numbers to 2 decimal places
    cout << "MLU (mean length of utterance): " << getNumOfMorphemes(userString) / getNumOfUtterances(userString) << endl << endl;

    //Outputs a line of hyphens to the console
    cout << string(numCharToPrint, charToPrint) << endl;
}
//sets diagnoses for all students in vector
void setAllDiagnoses(vector<specialEducationStudent>& studentList)
{
    double standardScore = 0;
    char disorderChar;
    cout << "Please begin by entering your standard scores obtained from your evaluation of each student." << endl << endl;

    try
    {
        //prompts user to enter area tested and diagnosis 
        for (int i = 0; i < studentList.size(); i++)
        {
            cout << "Enter the area tested for Student " << studentList.at(i).getFirstName() << " " << studentList.at(i).getLastName() << ": " << endl;
            cout << "Enter 'A' for articulation, 'E' for expressive language, 'R' for receptive language, or 'F' for fluency: ";
            cin >> disorderChar;
            while (disorderChar != 'A' && disorderChar != 'E' && disorderChar != 'R' && disorderChar != 'F')
            {
                cout << "Invalid entry for disorder" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Enter 'A' for articulation, 'E' for expressive language, 'R' for receptive language, or 'F' for fluency: ";
                cin >> disorderChar;
            }
            if (disorderChar == 'A')
            {
                cout << "Enter standard score for Articulation: ";
                cin >> standardScore;
                while (!cin || standardScore < 0 || standardScore > 150)
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input for standard score" << endl;
                    cout << "Enter standard score for Articulation: ";
                    cin >> standardScore;
                }
                if (standardScore <= 77.5)
                {
                    //set disorder to articulation
                    studentList.at(i).setDiagnosis("Articulation");
                    cout << "Student has been diagnosed with an Articulation disorder" << endl;
                    studentList.at(i).setGoalProgress(23);
                }
                else
                {
                    cout << "Score is out of range for diagnosis with Articulation disorder" << endl;
                }
            }
            else if (disorderChar == 'E')
            {
                cout << "Enter standard score for Expressive Language: ";
                cin >> standardScore;
                while (!cin || standardScore < 0 || standardScore > 150)
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input for standard score" << endl;
                    cout << "Enter standard score for Expressive Language: ";
                    cin >> standardScore;
                }
                if (standardScore <= 77.5)
                {
                    //set disorder to expressive language
                    studentList.at(i).setDiagnosis("Expressive Language");
                    cout << "Student has been diagnosed with an Expressive Language disorder" << endl;
                }
                else
                {
                    cout << "Score is out of range for diagnosis with Expressive Language disorder" << endl;
                }
            }
            else if (disorderChar == 'R')
            {
                cout << "Enter standard score for Receptive Language: ";
                cin >> standardScore;
                while (!cin || standardScore < 0 || standardScore > 150)
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input for standard score" << endl;
                    cout << "Enter standard score for Receptive Language: ";
                    cin >> standardScore;
                }
                if (standardScore <= 77.5)
                {
                    //set disorder to receptive language
                    studentList.at(i).setDiagnosis("Receptive Language");
                    cout << "Student has been diagnosed with a Receptive Language disorder" << endl;
                }
                else
                {
                    cout << "Score is out of range for diagnosis with Receptive Language disorder" << endl;
                }
            }
            else if (disorderChar == 'F')
            {
                cout << "Enter standard score for Fluency: ";
                cin >> standardScore;
                while (!cin || standardScore < 0 || standardScore > 150)
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input for standard score" << endl;
                    cout << "Enter standard score for Fluency: ";
                    cin >> standardScore;
                }
                if (standardScore <= 77.5)
                {
                    //set disorder to expressive language
                    studentList.at(i).setDiagnosis("Fluency");
                    cout << "Student has been diagnosed with a Fluency disorder" << endl;
                }
                else
                {
                    cout << "Score is out of range for diagnosis with a Fluency disorder" << endl;
                }
            }
            cout << endl;
        }
    }
    catch (string msg)
    {
        cout << msg << endl;
    }
    catch (...)
    {
        cout << "Unknown error occured!" << endl;
    }
    
}
