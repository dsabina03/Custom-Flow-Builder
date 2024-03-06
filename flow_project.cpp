#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Define steps
class Step {
public:
    virtual void execute() = 0;
    virtual void writeOutput(FILE *fName) = 0;
};

class TitleStep : public Step {
private:
    string title, subtitle;

public:
    TitleStep(const string& t, const string& st) : title(t), subtitle(st) {}

    void execute() override {
        cout << "Title: " << title << "\nSubtitle: " << subtitle << endl;
    }

    void writeOutput(FILE *fName) override {
        fprintf(fName, "Title: %s\nSubtitle: %s\n", title.c_str(), subtitle.c_str());
    }
};

class TextStep : public Step {
private:
    string title, copy;
    
public:
    TextStep(const string& t, const string& c) : title(t), copy(c) {}
    
    void execute() override {
        cout << "Title: " << title << "\nCopy: " << copy << endl;
    }

    void writeOutput(FILE *fName) override {
        try {
            fprintf(fName, "Title: %s\nCopy: %s\n", title.c_str(), copy.c_str());
        } catch (const std::exception& e) {
            std::cerr << "Error writing to the file: " << e.what() << std::endl;
        }
    }

};

class TextInputStep : public Step {
private:
    string description;

public:
    TextInputStep(const string& desc) : description(desc) {}

    void execute() override {
        string input;
        cout << description << ": ";
        cin >> input;
    }

    void writeOutput(FILE *fName) override {
        fprintf(fName, "%s: ", description.c_str());
    }
};

class NumberInputStep : public Step {
private:
    string description;
    int numberInput;

public:
    NumberInputStep(const string& desc, int num) : description(desc), numberInput(num) {}

    void execute() override {
        cout << description << ": " << numberInput << endl;
    }

    int getNumber() {
        return numberInput;
    }

    void writeOutput(FILE *fName) override {
    try {
        fprintf(fName, "%s: %d\n", description.c_str(), numberInput);
    } catch (const std::exception& e) {
        std::cerr << "Error writing to the file: " << e.what() << std::endl;
    }
}
    
};

class CalculusStep : public Step {
private:
    int numbersFromSteps[3];
    char operation;
    float result;

public:
    CalculusStep(int s[3], const char op) : operation(op) {
        for (int i = 0; i < 3; ++i) {
            numbersFromSteps[i] = s[i];
        }
    }

    void execute() override {
        cout << "The result is: ";

        switch (operation) {
            case '+':
                result = numbersFromSteps[0] + numbersFromSteps[1];
                break;

            case '-':
                result = numbersFromSteps[0] - numbersFromSteps[1];
                break;

            case '*':
                result = numbersFromSteps[0] * numbersFromSteps[1];
                break;

            case '/':
                if (numbersFromSteps[1] != 0) {
                    result = numbersFromSteps[0] / numbersFromSteps[1];
                } else {
                    std::cout << "Error: Division by zero!" << std::endl;
                }
                break;

            case 'm':
                result = std::min(numbersFromSteps[0], numbersFromSteps[1]);
                break;

            case 'M':
                result = std::max(numbersFromSteps[0], numbersFromSteps[1]);
                break;

            default:
                std::cout << "Invalid operation!" << std::endl;
        }

        cout << result << endl;
    }

    void writeOutput(FILE *fName) override {
    try {
        fprintf(fName, "The result is: %f\n", result);
    } catch (const std::exception& e) {
        std::cerr << "Error writing to the file: " << e.what() << std::endl;
    }
}
};

class DisplayStep : public Step {
private:
    string fName;

public:
    DisplayStep(string& s) : fName(s) {}

    void execute() override {
        // Check if the file with .txt extension exists
        if (fileExists(fName + ".txt")) {
            fName += ".txt";
            displayFileContents();
            return;
        }

        // Check if the file with .csv extension exists
        if (fileExists(fName + ".csv")) {
            fName += ".csv";
            displayFileContents();
            return;
        }

        // If file doesn't exist with either .txt or .csv extension
        std::cerr << "File '" << fName << "' not found.\n";
    }

    void writeOutput(FILE *outputFile) override {
        // Open the input file for reading
        if (fileExists(fName + ".txt")) {
            fName += ".txt";
        } else if (fileExists(fName + ".csv")) {
            fName += ".csv";
        }

        FILE *inputFile = fopen(fName.c_str(), "r"); // Open the concatenated filename in read mode

        if (inputFile && outputFile) { // Ensure both files are open
            char line[512]; // Buffer to hold each line

            fprintf(outputFile, "Content of file '%s':\n", fName.c_str()); // Write header

            // Read each line from the input file and write it to the output file
            while (fgets(line, sizeof(line), inputFile)) {
                fprintf(outputFile, "%s", line);
            }

            // Close the files
            fclose(inputFile);
            fclose(outputFile);

            std::cout << "Content of file '" << fName << "' written to the output file successfully.\n";
        } else {
            std::cerr << "Unable to open either file '" << fName << "' or the provided output file.\n";
        }
    }

private:
    // Helper function to check if file exists
    bool fileExists(const std::string& filename) const {
        std::ifstream file(filename.c_str());
        return file.good();
    }

    // Helper function to display file contents
    void displayFileContents() const {
        std::ifstream inFile(fName);
        
        if (inFile.is_open()) {
            std::string line;
            
            std::cout << "Content of file '" << fName << "':\n";
            while (std::getline(inFile, line)) {
                std::cout << line << '\n';
            }
            
            inFile.close();
        } else {
            std::cerr << "Unable to open file '" << fName << "'.\n";
        }
    }
};

class TextFileInputStep : public Step {
private:
    string description, fileName;

public:
    TextFileInputStep(const string& desc, const string& fName) : description(desc), fileName(fName + ".txt") {}

    void execute() override {
        // Create or append to the TXT file based on your requirements
        std::ofstream outFile(fileName);  // Create or overwrite the file

        if (outFile.is_open()) {
            // Write TXT data (for demonstration)
            outFile << "it works!\n";
            outFile << "Data1,Data2,Data3\n";
            
            outFile.close();
            std::cout << "TXT file '" << fileName << "' created successfully.\n";
        } else {
            std::cerr << "Unable to create/open TXT file '" << fileName << "'.\n";
        }
    }

    void writeOutput(FILE *fName) override {
        fprintf(fName, "%s: ", description.c_str());
    }
};

class CsvFileInputStep : public Step {
private:
    string description, fileName;

public:
    CsvFileInputStep(const std::string& desc, const std::string& fName)
        : description(desc), fileName(fName + ".csv") {}

    void execute() override {
        // Create or append to the CSV file based on your requirements
        std::ofstream outFile(fileName);  // Create or overwrite the file

        if (outFile.is_open()) {
            // Write CSV header and data (for demonstration)
            outFile << "Header1,Header2,Header3\n";
            outFile << "Data1,Data2,Data3\n";
            
            outFile.close();
            std::cout << "CSV file '" << fileName << "' created successfully.\n";
        } else {
            std::cerr << "Unable to create/open CSV file '" << fileName << "'.\n";
        }
    }

    void writeOutput(FILE *fName) override {
        fprintf(fName, "%s: ", description.c_str());
    }
};

class OutputStep : public Step {
private:
    string fName, title, description, information;

public:
    OutputStep(const string& file, const string& t, const string& desc, const string& info) : 
        fName(file), title(t), description(desc), information(info) {}

    void execute() override {
        // Create or overwrite the file with the given fName
        std::ofstream outFile(fName);

        if (outFile.is_open()) {
            // Write the title, description, and information to the file
            outFile << "Title: " << title << "\n\n";
            outFile << "Description: " << description << "\n\n";
            outFile << "Information: " << information << "\n";

            cout << "File '" << fName << "' created and data written successfully.\n";
            outFile.close();  // Close the file stream
        } else {
            std::cerr << "Unable to create/open file '" << fName << "'.\n";
        }
    }

    void writeOutput(FILE *fName) override {
        fprintf(fName, "");
    }
};

class Flow {
private:
    string name;
    vector<Step*> steps;
    time_t creationTime;

public:
    Flow(const string& n) : name(n) {
        creationTime = time(0);  // Current timestamp
    }

    void addStep(Step* step) {
        steps.push_back(step);
    }

    void deleteStep(Step* step) {
        for (auto it = steps.begin(); it != steps.end(); ++it)
        {
            if (*it == step) {
                steps.erase(it);
                return;
            }
        }
    }

    void execute() {
        for (Step* step : steps) {
            step->execute();
        }
    }

    void writeOutput(FILE *fName) {
        for (Step* step : steps) {
            step->writeOutput(fName);
        }
    }

    string getName(){
        return name;
    }

    vector<Step*> getSteps() {
        return steps;
    }
};

int main() {
    int choice;
    vector<Flow*> existingFlows; // Vector pentru a stoca flow-urile existente (doar pentru acest exemplu)

invalid_option:
    while (1)
    {
        cout << "To use an existing flow, press 1; to create a new one, press 2; to delete a flow, press 3; and to exit, press 4: ";
        cin >> choice;
        switch (choice) {
            case 1:
            {
                if (existingFlows.empty()) {
                    cout << "There are no available flows for use.\n";
                } else {
                    cout << "Choose an existing flow:\n";
                    for (size_t i = 0; i < existingFlows.size(); ++i) {
                        cout << i + 1 << ". " << existingFlows[i]->getName() << "\n"; // Presupunând că avem o funcție getName() în clasa Flow
                    }
                    int chosenFlow;
                    cin >> chosenFlow;
                    if (chosenFlow > 0 && chosenFlow <= existingFlows.size()) {
                        existingFlows[chosenFlow - 1]->execute();
                    } else {
                        cout << "Invalid option.\n";
                    }
                }
                break;
            }
            case 2:
            {
                cout << "Create a new flow.\n";
                Flow* newFlow;

                char inputLine[100];
                int nrSteps = 9;
                char flowName[50];

                cout << "Please enter the flow name:";
                cin >> flowName;
                newFlow = new Flow(flowName); // Alocăm un nou flow dinamic
                cout << "Available step types: title, text, number, calculation, textfile, csvfile, output, displaytxt, displaycsv, end" << endl;
                
                cout << "Do you want to add a title step?" << endl;
                cout << "1. Add a new title step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                
                int choice;
                cin >> choice;
                if (choice == 1) {
                    string title, subtitle;
                    cout << "Enter title: ";
                    cin >> title;
                    cout << "Enter subtitle: ";
                    cin >> subtitle;
                    // luam flowul nou creat, ii luam vector de steps deja existent, adaugam noul step cerut de utilizator in el
                    newFlow->addStep(new TitleStep(title, subtitle));
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add a text step?" << endl;
                cout << "1. Add a new text step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    string title, copy;
                    cout << "Enter title: ";
                    cin >> title;
                    cout << "Enter text copy: ";
                    cin >> copy;
                    newFlow->addStep(new TextStep(title, copy));
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add a number step?" << endl;
                cout << "1. Add a new number step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    string description;
                    float num;
                    cout << "Enter number description: ";
                    cin >> description;
                    cout << "Enter a number: ";
                    cin >> num;
                    // (*newFlow).getSteps()
                    newFlow->addStep(new NumberInputStep(description, num));
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add a number step?" << endl;
                cout << "1. Add a new number step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    string description;
                    float num;
                    cout << "Enter number description: ";
                    cin >> description;
                    cout << "Enter a number: ";
                    cin >> num;
                    // (*newFlow).getSteps()
                    newFlow->addStep(new NumberInputStep(description, num));
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add a calculus step?" << endl;
                cout << "1. Add a new calculus step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    int steps[3];
                    char operation;
                    cout << "Enter number of steps: ";
                    for (int i = 0; i < 2; i++) {
                        cout << "Number of the " << i << " step:" << endl;
                        cin >> steps[i];
                    }

                    int numbersFromSteps[3];
                    for (int i = 0; i < 2; i++) {
                        NumberInputStep *numberStep = dynamic_cast<NumberInputStep*>(newFlow->getSteps().at(steps[i]));
                        numbersFromSteps[i] = numberStep->getNumber();
                    }
                    
                    cout << "Enter operation (e.g., '+' for Addition, '-' for Subtraction, etc...): ";
                    cin >> operation;
                    //calculusStep->execute();
                    newFlow->addStep(new CalculusStep(numbersFromSteps, operation));
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add a text file step?" << endl;
                cout << "1. Add a new text file step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    string desc, fileName;
                    cout << "Enter file description: ";
                    cin >> desc;
                    cout << "Enter file name: ";
                    cin >> fileName;
                    TextFileInputStep *textFileInputStep = new TextFileInputStep(desc, fileName);
                    //textFileInputStep->execute();
                    newFlow->addStep(textFileInputStep);
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add a CSV file step?" << endl;
                cout << "1. Add a new CSV file step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    string desc, fileName;
                    cout << "Enter CSV description: ";
                    cin >> desc;
                    cout << "Enter CSV file name: ";
                    cin >> fileName;
                    CsvFileInputStep *csvFileInputStep = new CsvFileInputStep(desc, fileName);
                    //csvFileInputStep->execute();
                    newFlow->addStep(csvFileInputStep);
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add a displaytxt/displaycsv step?" << endl;
                cout << "1. Add a new display step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    string fName;
                    cout << "Enter file name to display: ";
                    cin >> fName;
                    DisplayStep* dispStep = new DisplayStep(fName);
                    //dispStep->execute();
                    newFlow->addStep(dispStep);
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }

                cout << "Do you want to add an output step?" << endl;
                cout << "1. Add a new output step" << endl;
                cout << "2. Skip step" << endl;
                cout << "3. End" << endl;
                cin >> choice;

                if (choice == 1) {
                    int stepNum;
                    string outFile, outTitle, outDesc, outInfo;
                    cout << "Enter output file name: ";
                    cin >> outFile;
                    cout << "Enter output title: ";
                    cin >> outTitle;
                    cout << "Enter output description: ";
                    cin >> outDesc;
                    
                    FILE* file = fopen(outFile.c_str(), "w");
                    newFlow->writeOutput(file);
                    fclose(file);
                    newFlow->addStep(new OutputStep(outFile, outTitle, outDesc, outInfo));
                } else if (choice == 2) {
                    cout << "Skipping step...\n";
                } else if (choice == 3) {
                    existingFlows.push_back(newFlow);
                    break;
                }
                
                existingFlows.push_back(newFlow); // Adăugăm flow-ul nou creat în vectorul de flow-uri existente
                break;
            }
            case 3:
            {
                if (existingFlows.empty()) {
                    cout << "There are no flows to be deleted.\n";
                } else {
                    cout << "Choose a flow to delete it:\n";
                    for (size_t i = 0; i < existingFlows.size(); ++i) {
                        cout << i + 1 << ". " << existingFlows[i]->getName() << "\n";
                    }
                    int deleteFlow;
                    cin >> deleteFlow;
                    if (deleteFlow > 0 && deleteFlow <= existingFlows.size()) {
                        delete existingFlows[deleteFlow - 1]; // Ștergem flow-ul
                        existingFlows.erase(existingFlows.begin() + deleteFlow - 1); // Ștergem referința la flow-ul șters din vector
                        cout << "The flow has been successfully deleted.\n";
                    } else {
                        cout << "Invalid option.\n";
                    }
                }
            }
        }

        if (choice == 4) {
            cout << "Exit..\n";
            break;
        }

        if (choice > 4 || choice <= 0) {
            cout << "Invalid option, choose again.\n";
            goto invalid_option;
        }
    }


    // Eliberăm resursele alocate dinamic (pentru flow-urile rămase)
    for (Flow* flow : existingFlows) {
        delete flow;
    }

    return 0;
}