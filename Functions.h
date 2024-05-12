#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

int getIntegerInput()
{
     string num;
    int confirmed;
    getline(cin, num); 

    // Check if input is empty
    if(num.empty()) {
        return getIntegerInput(); // recursively call itself until valid input
    }

    // Check each character in the string
    for (int i = 0; i < num.size(); i++) 
    {
        if (!isdigit(num[i])) 
        { // If a character is not a digit
            cout << "Invalid input. Please enter a positive integer: ";
            return getIntegerInput(); // recursively call itself until valid input
        }
    }

    confirmed = stoi(num);
    return confirmed;
}

// Function to validate yes/no choices
string getYesNoInput()
{
    string input;
    while (true)
    {
        cout << "Enter your choice (Y/N): ";
        cin >> input;
        
        if(input == "Y" || input == "N" || input == "y" || input == "n")
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
        }
    }
    return input;
}

// Function to clear console screen
void clr() 
{
    system("cls");
}

void calculateBMI()
{
    clr();
    float BMI;
    string option;

    cout << "\t\t\t\t\t\t\tBMI Calculator" << endl << endl;
    cout << "1. Calculate in kilograms and centimeters." << endl;
    cout << "2. Calculate in pounds and inches." << endl;
    cout << "Choose an option: ";
    cin >> option;

    while (option != "1" && option != "2")
    {
        cout << "\nInvalid input. Please enter again." << endl;
        cout << "Enter your option: ";
        cin >> option;
    }

    if (option == "1")
    {
        float weight_kg, height_cm;

        cout << endl << "Enter weight in kilograms: ";
        weight_kg = getIntegerInput();
        
        while (weight_kg < 1)
        {
            cout << "Invalid input. Please enter weight again: ";
            weight_kg = getIntegerInput();
        }

        cout << "Enter height in centimeters: ";
        height_cm = getIntegerInput();
        while (height_cm < 1)
        {
            cout << "Invalid input. Please enter height again: ";
            height_cm = getIntegerInput();
        }

        BMI = (weight_kg / (height_cm * height_cm)) * 10000.0;
    }

    if (option == "2")
    {
        float weight_lbs, height_in;
        int height_feet;

        cout << endl << "Enter weight in pounds: ";
        weight_lbs = getIntegerInput();
        
        while (weight_lbs < 1)
        {
            cout << "Invalid input. Please enter weight again: ";
            weight_lbs = getIntegerInput();
        }

        cout << "Enter height in feet: ";
        height_feet = getIntegerInput();
        
        while (height_feet < 1)
        {
            cout << "Invalid input. Please enter height again: ";
            height_feet = getIntegerInput();
        }

        cout << "Enter height inches:";
        height_in = getIntegerInput();
        
        while (height_in < 1 || height_in > 11)
        {
            cout << "Invalid input. Please enter height again: ";
            height_in = getIntegerInput();
        }

        height_in = (height_feet * 12) + height_in;

        BMI = (weight_lbs / (height_in * height_in)) * 703.0;
    }

    cout << endl << "Your BMI is " << BMI << "." << endl;

    if (BMI < 18.5)
    {
        cout << "You are underweight." << endl;
    }

    else if (BMI >= 18.5 && BMI <= 24.9)
    {
        cout << "Your bodyweight is healthy for your height." << endl;
    }

    else if (BMI > 24.9 && BMI <= 29.9)
    {
        cout << "You are overweight." << endl;
    }

    else
    {
        cout << "You are obese." << endl;
    }

    cout << "\nPress Enter to return to the main menu...";
    cin.get();
}
