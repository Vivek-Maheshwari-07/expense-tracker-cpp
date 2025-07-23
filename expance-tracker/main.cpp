#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

struct Expense {
    string date;
    string category;
    float amount;
    string note;
};

class ExpenseTracker {
private:
    vector<Expense> expenses;
    const string fileName = "expenses.txt";

public:
    ExpenseTracker() {
        loadFromFile();
    }

    void addExpense() {
        Expense e;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> e.date;
        cout << "Enter category (e.g. Food, Travel): ";
        cin >> e.category;
        cout << "Enter amount: ";
        cin >> e.amount;
        cin.ignore();
        cout << "Enter note: ";
        getline(cin, e.note);

        expenses.push_back(e);
        saveToFile(e);
        cout << " Expense added successfully!\n";
    }

    void viewExpenses() {
        if (expenses.empty()) {
            cout << "⚠️ No expenses recorded yet.\n";
            return;
        }

        cout << left << setw(12) << "Date"
             << setw(15) << "Category"
             << setw(10) << "Amount"
             << "Note\n";
        cout << "--------------------------------------------------\n";
        for (auto &e : expenses) {
            cout << left << setw(12) << e.date
                 << setw(15) << e.category
                 << setw(10) << e.amount
                 << e.note << "\n";
        }
    }

    void totalSpent() {
        float total = 0;
        for (auto &e : expenses) {
            total += e.amount;
        }
        cout << " Total spent: ₹" << total << "\n";
    }

    void filterByCategory() {
        string category;
        cout << "Enter category to filter: ";
        cin >> category;

        cout << "\nExpenses in category '" << category << "':\n";
        bool found = false;
        for (auto &e : expenses) {
            if (e.category == category) {
                cout << left << setw(12) << e.date
                     << setw(10) << e.amount
                     << e.note << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << " No expenses found in this category.\n";
        }
    }

private:
    void saveToFile(const Expense &e) {
        ofstream fout(fileName, ios::app);
        fout << e.date << "," << e.category << "," << e.amount << "," << e.note << "\n";
        fout.close();
    }

    void loadFromFile() {
        ifstream fin(fileName);
        Expense e;
        string line;

        while (getline(fin, line)) {
            stringstream ss(line);
            string amountStr;

            getline(ss, e.date, ',');
            getline(ss, e.category, ',');
            getline(ss, amountStr, ',');
            getline(ss, e.note);

            e.amount = stof(amountStr);
            expenses.push_back(e);
        }

        fin.close();
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\n Expense Tracker Menu\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. View Total Spent\n";
        cout << "4. Filter by Category\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: tracker.addExpense(); break;
            case 2: tracker.viewExpenses(); break;
            case 3: tracker.totalSpent(); break;
            case 4: tracker.filterByCategory(); break;
            case 0: cout << "Exiting..."; break;
            default: cout << " Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
