#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

int timer_duration = 5;     // Default timer duration
string unit_weight = "kgs"; // Default unit for weight
class Exercise
{
protected:
    vector<int> sets;
    int num_sets;
    string name;

public:
    Exercise() {}

    Exercise(string name, int num_sets) : name(name), num_sets(num_sets)
    {
        for (int i = 0; i < num_sets; ++i)
        {
            sets.push_back(0);
        }
    }

    virtual void start()
    {
        cout << "Base class start function." << endl;
    }

    virtual void saveLog()
    {
        cout << "Base class saveLog function." << endl;
    }
};

class StrengthExercise : public Exercise
{
private:
    vector<int> weights;

public:
    StrengthExercise(string name, int num_sets) : Exercise(name, num_sets)
    {
        for (int i = 0; i < num_sets; ++i)
        {
            weights.push_back(0);
        }
    }

    void start() override
    {
        for (int i = 0; i < num_sets; ++i)
        {
            cout << "Enter reps for set " << i + 1 << ": ";
            sets[i] = getIntegerInput();
            while (sets[i] < 1)
            {
                cout << "Invalid input. Please enter a positive integer: ";
                sets[i] = getIntegerInput();
            }

            cout << "Enter the weight done for the above set " << i + 1 << ": ";
            weights[i] = getIntegerInput();
            while (weights[i] < 1)
            {
                cout << "Invalid input. Please enter a positive integer: ";
                weights[i] = getIntegerInput();
            }

            cout << "Timer for the next set started." << endl;
            startTimer(timer_duration); // Start the timer
            cout << endl;
        }
    }

    void saveLog() override
    {
        ofstream log("log.txt", ios::app);

        if (log.is_open())
        {
            log << "Exercise: " << name << endl;

            for (int i = 0; i < num_sets; ++i)
            {
                log << "Set :" << i + 1 << endl;
                log << "Reps: " << sets[i] << endl;
                log << "Weight: " << weights[i] << " " << unit_weight << endl;
                log << endl;
            }

            log.close();
        }
        else
        {
            cout << "Unable to open log file." << endl;
            cout << "\nPress Enter to return to the main menu...";
		    cin.ignore();
		    cin.get();
        }
    }
};

class CardioExercise : public Exercise
{
private:
    int duration;

public:
    CardioExercise(string name, int num_sets) : Exercise(name, num_sets) {}

    void start() override
    {
        for (int i = 0; i < num_sets; ++i)
        {
            cout << "Enter duration (in Minutes): ";
            duration = getIntegerInput();
            cout << endl;
        }
    }

    void saveLog() override
    {
        ofstream log("log.txt", ios::app);

        if (log.is_open())
        {
            log << "Cardio Exercise: " << name << endl;
            log << "Duration: " << duration << " Minutes" << endl;
            log << endl;
            log.close();
        }
        else
        {
            cout << "Unable to open log file." << endl;
            cout << "\nPress Enter to return to the main menu...";
		    cin.ignore();
		    cin.get();
        }
    }
};
