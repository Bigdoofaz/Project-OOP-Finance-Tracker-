#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================= BASE CLASS =================
class Transaction {
protected:
    int id;
    double amount;
    string date;

public:
    Transaction(int id, double amount, string date)
        : id(id), amount(amount), date(date) {}

    virtual void display() const = 0;   // Pure virtual function

    double getAmount() const {
        return amount;
    }

    virtual ~Transaction() {}
};

// ================= INCOME CLASS =================
class Income : public Transaction {
private:
    string source;

public:
    Income(int id, double amount, string date, string source)
        : Transaction(id, amount, date), source(source) {}

    void display() const override {
        cout << "[Income] ID: " << id
             << " | Source: " << source
             << " | Amount: " << amount
             << " | Date: " << date << endl;
    }
};

// ================= EXPENSE CLASS =================
class Expense : public Transaction {
private:
    string category;

public:
    Expense(int id, double amount, string date, string category)
        : Transaction(id, amount, date), category(category) {}

    void display() const override {
        cout << "[Expense] ID: " << id
             << " | Category: " << category
             << " | Amount: " << amount
             << " | Date: " << date << endl;
    }
};

// ================= INVESTMENT CLASS =================
class Investment {
private:
    string assetName;
    double quantity;
    double pricePerUnit;

public:
    Investment(string name, double qty, double price)
        : assetName(name), quantity(qty), pricePerUnit(price) {}

    double calculateValue() const {
        return quantity * pricePerUnit;
    }

    void display() const {
        cout << "[Investment] Asset: " << assetName
             << " | Quantity: " << quantity
             << " | Price per Unit: " << pricePerUnit
             << " | Total Value: " << calculateValue()
             << endl;
    }
};

// ================= SAVINGS GOAL =================
class SavingsGoal {
private:
    string goalName;
    double targetAmount;
    double savedAmount;

public:
    SavingsGoal() : targetAmount(0), savedAmount(0) {}

    void setGoal(string name, double target) {
        goalName = name;
        targetAmount = target;
        savedAmount = 0;
    }

    void updateProgress(double amount) {
        savedAmount += amount;
    }

    void displayGoal() const {
        cout << "Savings Goal: " << goalName << endl;
        cout << "Target: " << targetAmount << endl;
        cout << "Saved: " << savedAmount << endl;
        cout << "Remaining: " << (targetAmount - savedAmount) << endl;
    }
};

// FINANCE MANAGER 
class FinanceManager {
private:
    vector<Transaction*> transactions;
    vector<Investment> investments;
    SavingsGoal goal;
    int transactionCounter = 1;

public:
    void addIncome(double amount, string date, string source) {
        transactions.push_back(
            new Income(transactionCounter++, amount, date, source));
    }

    void addExpense(double amount, string date, string category) {
        transactions.push_back(
            new Expense(transactionCounter++, amount, date, category));
    }

    void addInvestment(string name, double qty, double price) {
        investments.push_back(Investment(name, qty, price));
    }

    double calculateBalance() const {
        double balance = 0;
        for (auto t : transactions) {
            if (dynamic_cast<Income*>(t))
                balance += t->getAmount();
            else
                balance -= t->getAmount();
        }
        return balance;
    }

    double calculatePortfolioValue() const {
        double total = 0;
        for (const auto& inv : investments)
            total += inv.calculateValue();
        return total;
    }

    void showSummary() const {
        cout << "\n---- Transactions ----\n";
        for (auto t : transactions)
            t->display();

        cout << "\nCurrent Balance: " << calculateBalance() << endl;

        cout << "\n---- Investments ----\n";
        for (const auto& inv : investments)
            inv.display();

        cout << "\nTotal Portfolio Value: "
             << calculatePortfolioValue() << endl;
    }

    ~FinanceManager() {
        for (auto t : transactions)
            delete t;
    }
};

// ================= MAIN FUNCTION =================
int main() {
    FinanceManager manager;
    int choice;

    do {
        cout << "\n==== Finance Tracker ====\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. Add Investment\n";
        cout << "4. View Summary\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            string date, source;
            cout << "Amount: "; cin >> amount;
            cout << "Date: "; cin >> date;
            cout << "Source: "; cin >> source;
            manager.addIncome(amount, date, source);
        }
        else if (choice == 2) {
            double amount;
            string date, category;
            cout << "Amount: "; cin >> amount;
            cout << "Date: "; cin >> date;
            cout << "Category: "; cin >> category;
            manager.addExpense(amount, date, category);
        }
        else if (choice == 3) {
            string name;
            double qty, price;
            cout << "Asset Name: "; cin >> name;
            cout << "Quantity: "; cin >> qty;
            cout << "Price per Unit: "; cin >> price;
            manager.addInvestment(name, qty, price);
        }
        else if (choice == 4) {
            manager.showSummary();
        }

    } while (choice != 5);

    return 0;
}
