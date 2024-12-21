// World Series Winners Program
// Your Name: [Lukaman ISLAM]
// Example Usage: ./WorldSeriesProgram WorldSeriesWinnersTeams.txt WorldSeriesWinnersDates.txt

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // For toupper and tolower
#include <cctype>    // For isspace
using namespace std;

// Function Prototypes
void Introduction(char c, string message);
bool ReadFile(string fileName, string data[], const int maxArraySize);
const int GetCountOfTeam(string teamName, const string teams[], const int maxArraySize);
const string GetMostWinningTeam(const string teams[], const int maxArraySize);
const string GetTeamForDate(const string date, const string teams[], const string dates[], const int maxArraySize);
void ConvertTeamNameCase(bool to_upper, string teams[], const int maxArraySize);
string Trim(const string& str);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Error! Not enough file names. Expecting 2!" << endl;
        return -1;
    }

    // Const representing the number of lines of data in both files.
    const int SIZE_DATA = 120;

    string teams[SIZE_DATA];
    string dates[SIZE_DATA];

    // Read the files
    if (!ReadFile(argv[1], teams, SIZE_DATA)) {
        cout << "Error reading file: " << argv[1] << endl;
        return -1;
    }

    if (!ReadFile(argv[2], dates, SIZE_DATA)) {
        cout << "Error reading file: " << argv[2] << endl;
        return -1;
    }

    // Display the introduction
    Introduction('*', "** Welcome to the World Series Winners Program **");

    // Menu loop
    char choice;
    do {
        cout << "\nMenu Options:\n";
        cout << "Enter 'c' to find the number of wins for a team.\n";
        cout << "Enter 'w' to find the most winning team.\n";
        cout << "Enter 'd' to find the team that won in a specific year.\n";
        cout << "Enter 'v' to change the case of team names.\n";
        cout << "Enter 'x' to exit the program.\n";
        cout << "\nPlease enter an operation to perform: ";
        cin >> choice;

        if (choice == 'c') {
            // Get count of wins for a team
            cout << "Please enter the team name: ";
            cin.ignore(); // Clear the input buffer
            string teamName;
            getline(cin, teamName);
            teamName = Trim(teamName);
            int count = GetCountOfTeam(teamName, teams, SIZE_DATA);
            cout << "The number of times '" << teamName << "' won the World Series is: " << count << endl;
        }
        else if (choice == 'w') {
            // Get the most winning team
            string mostWinningTeam = GetMostWinningTeam(teams, SIZE_DATA);
            cout << "The most winning team is: " << mostWinningTeam << endl;
        }
        else if (choice == 'd') {
            // Get the team for a specific year
            cout << "Please enter the year: ";
            string year;
            cin >> year;
            string team = GetTeamForDate(year, teams, dates, SIZE_DATA);
            if (team.empty()) {
                cout << "No team found for the year " << year << "." << endl;
            }
            else {
                cout << "The team that won in " << year << " is: " << team << endl;
            }
        }
        else if (choice == 'v') {
            // Change case of team names
            cout << "Enter 'u' for uppercase or 'l' for lowercase: ";
            char caseOption;
            cin >> caseOption;
            bool toUpperCase = (caseOption == 'u');
            ConvertTeamNameCase(toUpperCase, teams, SIZE_DATA);
            cout << "Team names have been converted to " << (toUpperCase ? "uppercase." : "lowercase.") << endl;
        }
        else if (choice == 'x') {
            // Exit program
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'x');

    // Return 0 to indicate success.
    return 0;
}

// Function to display a decorative introduction message
void Introduction(char c, string message) {
    for (int i = 0; i < 50; i++) {
        cout << c;
    }
    cout << endl;
    cout << message << endl;
    for (int i = 0; i < 50; i++) {
        cout << c;
    }
    cout << endl;
}

// Function to read data from a file into an array
bool ReadFile(string fileName, string data[], const int maxArraySize) {
    ifstream inFile(fileName);
    if (!inFile) {
        return false; // File could not be opened
    }

    int i = 0;
    string line;
    while (i < maxArraySize&& getline(inFile, line)) {
        data[i++] = Trim(line); // Trim whitespace from each line
    }
    inFile.close();
    return i > 0; // Return false if no lines were read
}

// Function to count the number of wins for a team
const int GetCountOfTeam(string teamName, const string teams[], const int maxArraySize) {
    int count = 0;
    transform(teamName.begin(), teamName.end(), teamName.begin(), ::tolower); // Convert input to lowercase
    for (int i = 0; i < maxArraySize; i++) {
        string teamInArray = teams[i];
        transform(teamInArray.begin(), teamInArray.end(), teamInArray.begin(), ::tolower); // Convert array value to lowercase
        if (teamInArray == teamName) {
            count++;
        }
    }
    return count;
}

// Function to find the most winning team
const string GetMostWinningTeam(const string teams[], const int maxArraySize) {
    string mostWinningTeam;
    int maxWins = 0;

    for (int i = 0; i < maxArraySize; i++) {
        int currentWins = GetCountOfTeam(teams[i], teams, maxArraySize);
        if (currentWins > maxWins) {
            maxWins = currentWins;
            mostWinningTeam = teams[i];
        }
    }

    return mostWinningTeam;
}

// Function to find the team that won in a specific year
const string GetTeamForDate(const string date, const string teams[], const string dates[], const int maxArraySize) {
    for (int i = 0; i < maxArraySize; i++) {
        if (dates[i] == date) {
            return teams[i];
        }
    }
    return ""; // No match found
}

// Function to convert a team name to uppercase or lowercase
void ConvertTeamNameCase(bool to_upper, string teams[], const int maxArraySize) {
    for (int i = 0; i < maxArraySize; i++) {
        for (char& c : teams[i]) {
            c = to_upper ? toupper(c) : tolower(c);
        }
    }
}

// Function to trim leading and trailing whitespace
string Trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}
