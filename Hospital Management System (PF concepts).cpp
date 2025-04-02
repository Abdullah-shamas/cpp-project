#include <iostream>
using namespace std;


const int MAX_PATIENTS = 100;
const int MAX_DOCTORS = 50;
const int MAX_NAME_LENGTH = 50;
const int MAX_SPECIALTY_LENGTH = 50;
const int MAX_PROBLEM_LENGTH = 50;

int displayMenu();
int addPatient(char patientNames[][MAX_NAME_LENGTH], char problem[][MAX_PROBLEM_LENGTH], int& totalpatient);
void viewPatientRecords(const char patientNames[][MAX_NAME_LENGTH],const char problem[][MAX_PROBLEM_LENGTH], int totalPatients);
int addDoctor(char doctorNames[][MAX_NAME_LENGTH], char specialties[][MAX_SPECIALTY_LENGTH], int& totalDoctors);
void viewDoctorRecords(const char doctorNames[][MAX_NAME_LENGTH], const char specialties[][MAX_SPECIALTY_LENGTH], int totalDoctors);

int main() {
    char patientNames[MAX_PATIENTS][MAX_NAME_LENGTH];
    char doctorNames[MAX_DOCTORS][MAX_NAME_LENGTH];
    char problem[MAX_PATIENTS][MAX_PROBLEM_LENGTH];
    char specialties[MAX_DOCTORS][MAX_SPECIALTY_LENGTH];
    int totalPatients = 0;
    int totalDoctors = 0;
    int choice;

    do {
        choice = displayMenu();

        switch (choice) {
            case 1:
                	addPatient(patientNames, problem, totalPatients);
                break;
            case 2:
                    viewPatientRecords(patientNames, problem, totalPatients);
                break;
            case 3:
                    addDoctor(doctorNames, specialties, totalDoctors); 
                break;
            case 4:
                    viewDoctorRecords(doctorNames, specialties, totalDoctors);
                break;
            case 5:
                    cout << "Exiting the program. Thank you!\n";
                break;
            default:
                   cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}


int displayMenu() {
    cout << "\nHospital Management System\n";
    cout << "1. Add Patients\n";
    cout << "2. View Patient Records\n";
    cout << "3. Add Doctor\n";
    cout << "4. View Doctor Records\n";
    cout << "5. Exit\n";
    
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    return choice;
}
int addPatient(char patientNames[][MAX_NAME_LENGTH], char problem[][MAX_PROBLEM_LENGTH], int& totalpatient){
	 cout << "\nEnter Patient Details:\n";
    
    cout << "Name: ";
    cin>>patientNames[totalpatient];

    cout << "Problem: ";
    cin>>problem[totalpatient];

    totalpatient++;
    cout << "Patient added successfully.\n";

    return totalpatient;}


void viewPatientRecords(const char patientNames[][MAX_NAME_LENGTH],const char problem[][MAX_PROBLEM_LENGTH], int totalPatients) {
    cout << "\nPatient Records:\n";
    if (totalPatients == 0) {
        cout << "No patients in the records.\n";
        return ;
    }

    cout << "Patient ID\tPatient Name\tProblem\n";
    for (int i = 0; i < totalPatients; ++i) {
        cout << i + 1 << "\t\t" << patientNames[i] << "\t\t" << problem[i] << endl;
    }

    }

int addDoctor(char doctorNames[][MAX_NAME_LENGTH], char specialties[][MAX_SPECIALTY_LENGTH], int& totalDoctors) {
    cout << "\nEnter Doctor Details:\n";
    
    cout << "Name: ";
    cin>>doctorNames[totalDoctors];

    cout << "Specialty: ";
    cin>>specialties[totalDoctors];

    totalDoctors++;
    cout << "Doctor added successfully.\n";

    return totalDoctors;
}


void viewDoctorRecords(const char doctorNames[][MAX_NAME_LENGTH], const char specialties[][MAX_SPECIALTY_LENGTH], int totalDoctors) {
    cout << "\nDoctor Records:\n";
    if (totalDoctors == 0) {
        cout << "No doctors in the records.\n";
        return;
    }

    cout << "Doctor ID\tDoctor Name\tSpecialty\n";
    for (int i = 0; i < totalDoctors; ++i) {
        cout << i + 1 << "\t\t" << doctorNames[i] << "\t\t" << specialties[i] << endl;
    }
}



