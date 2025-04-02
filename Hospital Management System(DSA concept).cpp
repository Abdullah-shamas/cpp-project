#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string disease;
    Patient* next;

    Patient(int i, string n, int a, string d) {
        id = i;
        name = n;
        age = a;
        disease = d;
        next = NULL;
    }
};

class PatientList {
private:
    Patient* head;

public:
    PatientList() {
        head = NULL;
    }

    ~PatientList() {
        while (head) {
            Patient* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addPatient(int id, string name, int age, string disease) {
        Patient* newPatient = new Patient(id, name, age, disease);
        if (!head) {
            head = newPatient;
        } else {
            Patient* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newPatient;
        }
        cout << "Patient " << name << " added successfully!\n";
    }

    void displayPatients() {
        if (!head) {
            cout << "No patients in the list.\n";
            return;
        }

        Patient* temp = head;
        cout << "\nPatient List:\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Age" << "Disease" << endl;
        cout << string(50, '-') << endl;
        while (temp) {
            cout << left << setw(10) << temp->id << setw(20) << temp->name << setw(10) << temp->age << temp->disease << endl;
            temp = temp->next;
        }
    }

    Patient* getPatientById(int id) {
        Patient* temp = head;
        while (temp) {
            if (temp->id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    bool removePatient(int id) {
        if (!head) {
            cout << "No patients to remove.\n";
            return false;
        }

        if (head->id == id) {
            Patient* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Patient with ID " << id << " removed successfully!\n";
            return true;
        }

        Patient* temp = head;
        while (temp->next && temp->next->id != id) {
            temp = temp->next;
        }

        if (temp->next) {
            Patient* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Patient with ID " << id << " removed successfully!\n";
            return true;
        }

        cout << "Patient with ID " << id << " not found.\n";
        return false;
    }

    void searchPatient(int id) {
        Patient* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Patient Found:\n";
                cout << "ID: " << temp->id << ", Name: " << temp->name << ", Age: " << temp->age << ", Disease: " << temp->disease << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Patient with ID " << id << " not found.\n";
    }

    void editPatient(int id) {
        Patient* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Editing details for Patient ID " << id << ":\n";
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, temp->name);
                cout << "Enter new age: ";
                cin >> temp->age;
                cout << "Enter new disease: ";
                cin.ignore();
                getline(cin, temp->disease);
                cout << "Patient details updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Patient with ID " << id << " not found.\n";
    }

    void saveToFile() {
        ofstream outFile("patients.txt");
        if (!outFile) {
            cout << "Error opening file for writing.\n";
            return;
        }

        Patient* temp = head;
        while (temp) {
            outFile << temp->id << "," << temp->name << "," << temp->age << "," << temp->disease << endl;
            temp = temp->next;
        }
        outFile.close();
        cout << "Patient data saved to patients.txt successfully!\n";
    }

    void loadFromFile() {
        ifstream inFile("patients.txt");
        if (!inFile) {
            cout << "Error opening file for reading. Ensure patients.txt exists.\n";
            return;
        }

        string line;
        while (getline(inFile, line)) {
            int id, age;
            string name, disease;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            id = stoi(line.substr(0, pos1));
            name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            disease = line.substr(pos3 + 1);

            addPatient(id, name, age, disease);
        }
        inFile.close();
        cout << "Patient data loaded from patients.txt successfully!\n";
    }
};

class DischargedPatients {
private:
    stack<string> dischargedStack;

public:
    void addDischargedPatient(string name) {
        dischargedStack.push(name);
        cout << "Patient " << name << " discharged and added to stack!\n";
    }

    void displayDischargedPatients() {
        if (dischargedStack.empty()) {
            cout << "No discharged patients.\n";
            return;
        }

        stack<string> tempStack = dischargedStack;
        cout << "\nDischarged Patients:\n";
        while (!tempStack.empty()) {
            cout << tempStack.top() << endl;
            tempStack.pop();
        }
    }
};

class BedManagement {
private:
    int beds[10];
    int capacity;

public:
    BedManagement() : capacity(10) {
        for (int i = 0; i < capacity; i++) {
            beds[i] = 0;
        }
    }

    void allocateBed(int patientId) {
        for (int i = 0; i < capacity; i++) {
            if (beds[i] == 0) {
                beds[i] = patientId;
                cout << "Bed " << i + 1 << " allocated to patient with ID " << patientId << "\n";
                return;
            }
        }
        cout << "No beds available.\n";
    }

    void freeBed(int patientId) {
        for (int i = 0; i < capacity; i++) {
            if (beds[i] == patientId) {
                beds[i] = 0;
                cout << "Bed " << i + 1 << " freed for patient with ID " << patientId << "\n";
                return;
            }
        }
        cout << "Patient with ID " << patientId << " not found in any bed.\n";
    }

    void displayBeds() {
        cout << "\nBed Status:\n";
        for (int i = 0; i < capacity; i++) {
            cout << "Bed " << i + 1 << ": " << (beds[i] == 0 ? "Empty" : "Occupied") << endl;
        }
    }

    void displayBedAllocation(PatientList& patientList) {
        cout << "\nBed Allocation:\n";
        cout << left << setw(10) << "Bed No." << setw(10) << "Patient ID" << "Patient Name" << endl;
        cout << string(30, '-') << endl;

        for (int i = 0; i < capacity; i++) {
            if (beds[i] != 0) {
                Patient* patient = patientList.getPatientById(beds[i]);
                if (patient) {
                    cout << left << setw(10) << (i + 1) << setw(10) << patient->id << patient->name << endl;
                } else {
                    cout << left << setw(10) << (i + 1) << setw(10) << beds[i] << "Unknown" << endl;
                }
            } else {
                cout << left << setw(10) << (i + 1) << "Empty" << endl;
            }
        }
    }
};

int main() {
    PatientList patientList;
    DischargedPatients dischargedPatients;
    BedManagement bedManagement;

    patientList.loadFromFile();

    int choice;
    do {
        cout << "\n=======================================\n";
        cout << "        HOSPITAL MANAGEMENT SYSTEM     \n";
        cout << "=======================================\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Remove Patient\n";
        cout << "4. Search Patient\n";
        cout << "5. Edit Patient Details\n";
        cout << "6. Discharge Patient\n";
        cout << "7. Display Discharged Patients\n";
        cout << "8. Allocate Bed\n";
        cout << "9. Free Bed\n";
        cout << "10. Display Bed Status\n";
        cout << "11. Display Bed Allocation\n";
        cout << "12. Save and Exit\n";
        cout << "=======================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            int id, age;
            string name, disease;
            cout << "Enter Patient ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Patient Name: ";
            getline(cin, name);
            cout << "Enter Patient Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Disease: ";
            getline(cin, disease);
            patientList.addPatient(id, name, age, disease);
            break;
        }
        case 2:
            patientList.displayPatients();
            break;
        case 3: {
            int id;
            cout << "Enter Patient ID to remove: ";
            cin >> id;
            patientList.removePatient(id);
            break;
        }
        case 4: {
            int id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            patientList.searchPatient(id);
            break;
        }
        case 5: {
            int id;
            cout << "Enter Patient ID to edit: ";
            cin >> id;
            patientList.editPatient(id);
            break;
        }
        case 6: {
            string name;
            cout << "Enter Patient Name to discharge: ";
            cin.ignore();
            getline(cin, name);
            dischargedPatients.addDischargedPatient(name);
            break;
        }
        case 7:
            dischargedPatients.displayDischargedPatients();
            break;
        case 8: {
            int id;
            cout << "Enter Patient ID to allocate bed: ";
            cin >> id;
            bedManagement.allocateBed(id);
            break;
        }
        case 9: {
            int id;
            cout << "Enter Patient ID to free bed: ";
            cin >> id;
            bedManagement.freeBed(id);
            break;
        }
        case 10:
            bedManagement.displayBeds();
            break;
        case 11:
            bedManagement.displayBedAllocation(patientList);
            break;
        case 12:
            patientList.saveToFile();
            cout << "Exiting system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 12);

    return 0;
}
