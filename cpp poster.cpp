
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
using namespace std;

// ---------- INPUT VALIDATION ----------
int readInt(string message) {
    string input;
    int value;

    while (true) {
        cout << message;
        getline(cin, input);

        try {
            size_t pos;
            value = stoi(input, &pos);

            while (pos < input.length() &&
                   input[pos] == ' ')
                pos++;

            if (pos != input.length())
                throw invalid_argument("Invalid input");

            return value;
        }
        catch (...) {
            cout << "Please enter a valid whole number.\n";
        }
    }
}

string readText(string message) {
    string value;

    while (true) {
        cout << message;
        getline(cin, value);

        if (value.find_first_not_of(" \t") != string::npos)
            return value;

        cout << "This field cannot be empty.\n";
    }
}

// ---------- BASE CLASS ----------
class Person {
private:
    int id;
    string name;
    int age;

public:
    Person(int i, string n, int a)
        : id(i), name(n), age(a) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    virtual void display() const = 0;

    virtual ~Person() {}
};

// ---------- DOCTOR CLASS ----------
class Doctor : public Person {
private:
    string specialization;

public:
    Doctor(int id, string name, int age, string spec)
        : Person(id, name, age), specialization(spec) {}

    void display() const override {
        cout << "Doctor ID: " << getId()
             << " | Name: " << getName()
             << " | Specialization: " << specialization
             << " | Age: " << getAge() << '\n';
    }
};

// ---------- PATIENT BASE CLASS ----------
class Patient : public Person {
public:
    Patient(int id, string name, int age)
        : Person(id, name, age) {}

    virtual double calculateBill() const = 0;
    virtual string getCategory() const = 0;

    void display() const override {
        cout << "Patient ID: " << getId()
             << " | Name: " << getName()
             << " | Age: " << getAge()
             << " | Category: " << getCategory() << '\n';
    }
};

// ---------- GENERAL PATIENT ----------
class GeneralPatient : public Patient {
public:
    GeneralPatient(int id, string name, int age)
        : Patient(id, name, age) {}

    double calculateBill() const override {
        return 500.0;
    }

    string getCategory() const override {
        return "General";
    }
};

// ---------- SENIOR CITIZEN ----------
class SeniorCitizen : public Patient {
public:
    SeniorCitizen(int id, string name, int age)
        : Patient(id, name, age) {
        if (age < 60)
            throw invalid_argument(
                "Senior citizen must be at least 60 years old.");
    }

    double calculateBill() const override {
        return 400.0;  // 20% discount on Rs. 500
    }

    string getCategory() const override {
        return "Senior Citizen";
    }
};

// ---------- EMERGENCY PATIENT ----------
class EmergencyPatient : public Patient {
public:
    EmergencyPatient(int id, string name, int age)
        : Patient(id, name, age) {}

    double calculateBill() const override {
        return 1500.0; // Rs. 500 consultation + Rs. 1000 emergency fee
    }

    string getCategory() const override {
        return "Emergency";
    }
};

// ---------- APPOINTMENT CLASS ----------
class Appointment {
private:
    int patientId;
    int doctorId;
    string date;
    string time;

public:
    Appointment(int pId, int dId, string dt, string tm)
        : patientId(pId), doctorId(dId),
          date(dt), time(tm) {}

    int getDoctorId() const {
        return doctorId;
    }

    string getDate() const {
        return date;
    }

    string getTime() const {
        return time;
    }

    void display() const {
        cout << "Patient ID: " << patientId
             << " | Doctor ID: " << doctorId
             << " | Date: " << date
             << " | Time: " << time << '\n';
    }
};

// ---------- HOSPITAL MANAGEMENT ----------
class Hospital {
private:
    vector<Doctor> doctors;
    vector<unique_ptr<Patient>> patients;
    vector<Appointment> appointments;

    Doctor* findDoctor(int id) {
        for (auto& d : doctors)
            if (d.getId() == id)
                return &d;
        return nullptr;
    }

    Patient* findPatient(int id) {
        for (auto& p : patients)
            if (p->getId() == id)
                return p.get();
        return nullptr;
    }

    bool patientIdExists(int id) {
        return findPatient(id) != nullptr;
    }

    bool doctorIdExists(int id) {
        return findDoctor(id) != nullptr;
    }

public:
    // Register a doctor
    void addDoctor() {
        int id = readInt("Enter doctor ID: ");

        if (id <= 0 || doctorIdExists(id))
            throw invalid_argument(
                "Doctor ID must be positive and unique.");

        string name = readText("Enter doctor name: ");
        int age = readInt("Enter doctor age: ");

        if (age < 18 || age > 100)
            throw invalid_argument("Invalid doctor age.");

        string spec = readText("Enter specialization: ");

        doctors.emplace_back(id, name, age, spec);
        cout << "Doctor registered successfully.\n";
    }

    // Register a patient
    void addPatient() {
        int id = readInt("Enter patient ID: ");

        if (id <= 0 || patientIdExists(id))
            throw invalid_argument(
                "Patient ID must be positive and unique.");

        string name = readText("Enter patient name: ");
        int age = readInt("Enter patient age: ");

        if (age < 0 || age > 120)
            throw invalid_argument("Invalid patient age.");

        cout << "\nSelect patient category:\n";
        cout << "1. General\n";
        cout << "2. Senior Citizen (60+)\n";
        cout << "3. Emergency\n";

        int choice = readInt("Enter choice: ");

        switch (choice) {
            case 1:
                patients.push_back(
                    make_unique<GeneralPatient>(id, name, age));
                break;

            case 2:
                patients.push_back(
                    make_unique<SeniorCitizen>(id, name, age));
                break;

            case 3:
                patients.push_back(
                    make_unique<EmergencyPatient>(id, name, age));
                break;

            default:
                throw invalid_argument(
                    "Invalid patient category.");
        }

        cout << "Patient registered successfully.\n";
    }

    // Book an appointment
    void bookAppointment() {
        int pId = readInt("Enter patient ID: ");
        int dId = readInt("Enter doctor ID: ");

        if (!patientIdExists(pId))
            throw invalid_argument("Patient not found.");

        if (!doctorIdExists(dId))
            throw invalid_argument("Doctor not found.");

        string date = readText("Enter date (DD-MM-YYYY): ");
        string time = readText("Enter time (e.g. 10:00 AM): ");

        // Prevent two appointments for the same doctor
        // at the same date and time.
        for (const auto& a : appointments) {
            if (a.getDoctorId() == dId &&
                a.getDate() == date &&
                a.getTime() == time) {
                throw invalid_argument(
                    "This doctor's time slot is already booked.");
            }
        }

        appointments.emplace_back(pId, dId, date, time);
        cout << "Appointment booked successfully.\n";
    }

    void showDoctors() const {
        if (doctors.empty()) {
            cout << "No doctors registered.\n";
            return;
        }

        for (const auto& d : doctors)
            d.display();
    }

    void showPatients() const {
        if (patients.empty()) {
            cout << "No patients registered.\n";
            return;
        }

        for (const auto& p : patients)
            p->display();
    }

    void showAppointments() const {
        if (appointments.empty()) {
            cout << "No appointments booked.\n";
            return;
        }

        for (const auto& a : appointments)
            a.display();
    }

    // Generate bill using runtime polymorphism
    void generateBill() {
        int id = readInt("Enter patient ID: ");
        Patient* p = findPatient(id);

        if (p == nullptr)
            throw invalid_argument("Patient not found.");

        cout << "\n========== HOSPITAL BILL ==========\n";
        cout << "Patient ID   : " << p->getId() << '\n';
        cout << "Patient Name : " << p->getName() << '\n';
        cout << "Category     : " << p->getCategory() << '\n';

        cout << fixed << setprecision(2);

        if (p->getCategory() == "Senior Citizen") {
            cout << "Consultation : Rs. 500.00\n";
            cout << "Discount     : Rs. 100.00\n";
        }
        else if (p->getCategory() == "Emergency") {
            cout << "Consultation : Rs. 500.00\n";
            cout << "Emergency fee: Rs. 1000.00\n";
        }
        else {
            cout << "Consultation : Rs. 500.00\n";
        }

        cout << "-----------------------------------\n";
        cout << "Total Amount : Rs. "
             << p->calculateBill() << '\n';
        cout << "===================================\n";
    }
};

// ---------- MAIN FUNCTION ----------
int main() {
    Hospital hospital;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "    HOSPITAL MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Register Doctor\n";
        cout << "2. Register Patient\n";
        cout << "3. Book Appointment\n";
        cout << "4. View Doctors\n";
        cout << "5. View Patients\n";
        cout << "6. View Appointments\n";
        cout << "7. Generate Patient Bill\n";
        cout << "0. Exit\n";

        choice = readInt("Enter your choice: ");

        try {
            switch (choice) {
                case 1:
                    hospital.addDoctor();
                    break;
                case 2:
                    hospital.addPatient();
                    break;
                case 3:
                    hospital.bookAppointment();
                    break;
                case 4:
                    hospital.showDoctors();
                    break;
                case 5:
                    hospital.showPatients();
                    break;
                case 6:
                    hospital.showAppointments();
                    break;
                case 7:
                    hospital.generateBill();
                    break;
                case 0:
                    cout << "Thank you for using the system.\n";
                    break;
                default:
                    cout << "Invalid menu choice.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }

    } while (choice != 0);

    return 0;
}
