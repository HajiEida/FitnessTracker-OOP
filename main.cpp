#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono> // For timer
#include <ctime>
#include "StartTimer.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;
using namespace std::chrono;

// Function to validate integer input
int getIntegerInput();

// Function to validate yes/no choices
string getYesNoInput();

// Function to clear console screen
void clr();

void calculateBMI();

int main()
{
    string option0, option1, name;
    int num_sets, option2;

    while (true)
    {
    	// Get current date and time
	    time_t t = time(0);
	    tm* now = localtime(&t);
	    int year = now->tm_year + 1900;
	    int month = now->tm_mon + 1;
	    int day = now->tm_mday;
	
	    string current_date = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
	    
        clr();
        cout << "\n\t\t\t\t\t\t\tSETGRAPH" << endl << endl;
        cout << "\t\t\t\t\t\t\tMAIN MENU" << endl << endl;
        cout << "1. Start Workout.\n2. Settings.\n3. BMI.\n4. Display Previous Workout.\n5. Exit." << endl;
        cout << "Choose an option: ";
        cin >> option0;
        while (option0 != "1" && option0 != "2" && option0 != "3" && option0 != "4" && option0 != "5")
        {
            cout << "\nInvalid input. Please enter again." << endl;
            cout << "Enter your option: ";
            cin >> option0;
        }

        if (option0 == "1")
        {
            clr();
            cout << "\nWhich muscle groups would you like to train today?" << endl;
            cin.ignore();
            cout << "Muscle Groups: ";
            getline(cin, option1);

            ofstream muscle_group("log.txt", ios::app);
            if (muscle_group.is_open())
            {
                muscle_group << "\t\t\t\t\t\t\t" << option1 << " (" << current_date << ")" << endl << endl;
            }
            muscle_group.close();

            cout << "\nHow many exercises will you perform today? ";
            option2 = getIntegerInput();
            while (option2 < 1)
            {
                cout << "Invalid input. Please enter a positive integer: ";
                option2 = getIntegerInput();
            }

            Exercise *workout[option2];

            for (int i = 0; i < option2; i++)
            {
                cout << "Enter exercise type (1. Strength / 2. Cardio): ";
                string exerciseType;
                cin >> exerciseType;

                while (exerciseType != "1" && exerciseType != "2")
                {
                    cout << "\nInvalid input Please enter again." << endl;
                    cout << "Enter your option: ";
                    cin >> exerciseType;
                }

                if (exerciseType == "1")
                {
                    cout << "Exercise name: ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "\nNumber of sets: ";
                    num_sets = getIntegerInput();
                    while (num_sets < 1)
                    {
                        cout << "Invalid input. Please enter a positive integer: ";
                        num_sets = getIntegerInput();
                    }

                    workout[i] = new StrengthExercise(name, num_sets);
                }
                else if (exerciseType == "2")
                {
                    cout << "Exercise name: ";
                    cin.ignore();
                    getline(cin, name);
                    num_sets = 1;
                    workout[i] = new CardioExercise(name, num_sets);
                }

                workout[i]->start();
                workout[i]->saveLog();
                delete workout[i]; // Free memory
            }
            
        cout << "Log saved successfully." << endl;
        cout << "\nPress Enter to return to the main menu...";
		cin.get();
        }
        else if (option0 == "2")
        {
            cin.ignore();
            while (true)
            {
                clr();
                cout << "\t\t\t\t\t\t\tSETTINGS" << endl << endl;
                cout << "1. Set unit for weight." << endl;
                cout << "2. Clear log." << endl;
                cout << "3. Set rest timer duration (default set to 30 seconds)." << endl;
                cout << "4. Return to main menu." << endl;
                cout << "Choose your option: ";
                cin >> option1;

                while (option1 != "1" && option1 != "2" && option1 != "3" && option1 != "4")
                {
                    cout << "\nInvalid input. Please enter again." << endl;
                    cout << "Enter your option: ";
                    cin >> option1;
                }

                if (option1 == "1")
                {
                    clr();
                    cout << "Which unit would you like to track your weight?" << endl;
                    cout << "1. Kilograms (kgs)." << endl;
                    cout << "2. Pounds (lbs)." << endl;
                    cout << "Choose your option: ";
                    int unitOption = getIntegerInput();

                    while (unitOption != 1 && unitOption != 2)
                    {
                        cout << "Invalid option. Please choose again: ";
                        unitOption = getIntegerInput();
                    }

                    if (unitOption == 1)
                    {
                        unit_weight = "kgs";
                    }
                    else if (unitOption == 2)
                    {
                        unit_weight = "lbs";
                    }

                    cout << "Unit changed successfully." << endl   << endl;
                }
                else if (option1 == "2")
                {
                    ifstream log("log.txt");
                    if(log.is_open())
                    {
                        cout << "File found! Are you sure you want to clear log? (Y/N) " << endl;
                        string confirm = getYesNoInput();

                        if (confirm == "Y" || confirm == "y")
                        {
                            ofstream log("log.txt", ios::trunc);
                            cout << "Log cleared." << endl << endl;
                            cout << "\nPress Enter to return to the main menu...";
                            cin.ignore();
						    cin.get();
						    clr();
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                        cout << "ERROR: file not FOUND!" << endl;
                        cout << "\nPress Enter to return to the main menu...";
					    cin.ignore();
					    cin.get();
                    }
                }
                else if (option1 == "3")
                {
                    clr();
                    cout << "Enter the duration for each set (in seconds): ";
                    timer_duration = getIntegerInput(); // Update the timer duration
                    while (timer_duration < 1)
                    {
                        cout << "Invalid input. Please enter a positive integer: ";
                        timer_duration = getIntegerInput();
                    }
                    cout << endl;
                }
                else if (option1 == "4")
                {
                    break;
                }
            }
        }
        else if (option0 == "3")
        {
            calculateBMI();
        }
        else if (option0 == "4")
        {
            clr();
            cout << "\t\t\t\t\t\t\tDISPLAY LOG" << endl << endl;
            ifstream display_log("log.txt");

            if (display_log.is_open())
            {
                string line;
                while (getline(display_log, line))
                {
                    cout << line << endl;
                }
                display_log.close();
            }
            else
            {
                cout << "FILE DOES NOT EXIST" << endl;
            }
            cout << "\nPress Enter to return to the main menu...";
            cin.ignore();
            cin.get();
        }
        else if (option0 == "5")
        {
        	cout<<"\n\tThank you for using SetGraph. Hope to see you again...fatty"<<endl;
            break;
        }
    }
    return 0;
}
