// Student name: Sujan P Registration number: 23CS227
// the account number and passwords are present inside data.txt file

#include <iostream>
#include <fstream>
class Atm
{
private:
    double _accbal;

public:
    double accbal = _accbal;
    double withdraw(double am)
    {
        _accbal = _accbal - am;
        accbal = _accbal;
        return accbal;
    }
    double deposit(double am)
    {
        _accbal = _accbal + am;
        accbal = _accbal;
        return accbal;
    }
    double checkbal()
    {
        accbal = _accbal;
        return accbal;
    }
    void setAccBal(double y)
    {
        _accbal = y;
        accbal = y;
    }
};

// function for input validation on numbers
int checkNum(std::string n)
{
    int number;
    int ref = 1;
    while (ref)
    {
        try
        {
            int num = stoi(n);
            if (std::to_string(num) != n) // or n.size() != to_string(num).size())
            {
                ref = 1;
                std::cout << "Please enter a valid number: " << std::endl;
                getline(std::cin, n);
            }
            else
            {
                ref = 0;
            }
        }
        catch (std::invalid_argument)
        {
            std::cout << "Please enter a valid number: " << std::endl;
            getline(std::cin, n);
        }
    }
    number = stoi(n);
    return number;
}

int main()
{
    std::cout << "Student name: Sujan P, Registration number: 23CS227" << std::endl;
    std::string a, b;
    std::string acc_no, pass;
    int option, inp_amount, acc_index, pass_trycount = 1, acc_number_trycount = 1;
    bool is_present = false;

    // fetching the data from data.txt file and storing it in an array named data
    std::string data[60];
    std::ifstream readFile("./data.txt", std::ifstream::in);
    std::string line;
    int line_no = 1, i = 0;
    while (getline(readFile, line))
    {
        data[i] = line;
        i++;
    }
    readFile.close(); // closing the file after fetching the data

    Atm obj; // creating object for Atm

    std::cout << "Welcome to ABC Bank" << std::endl
              << "Please enter your account number:";
    std::cin >> acc_no;

    // iterating through the array to check if the given account number is present
    for (int i = 1; i < 56; i += 6)
    {
        if (data[i] == acc_no)
        {
            is_present = true;
            acc_index = i;
        }
    }

    // getting the account number again if the given account number is incorrect till 5 times
    while (!is_present && acc_number_trycount < 5)
    {
        std::cout << "wrong account number" << std::endl;
        std::cout << "Exited successfully..." << std::endl
                  << std::endl;
        std::cout << "Welcome to ABC Bank" << std::endl
                  << "Please enter your account number:";
        std::cin >> acc_no;
        acc_number_trycount += 1;
        for (int i = 1; i < 56; i += 6)
        {
            if (data[i] == acc_no)
            {
                is_present = true;
                acc_index = i;
            }
        }
    }

    // 5 unsuccessful attempts result in termination of the program with visit later message
    if (acc_number_trycount == 5)
    {
        std::cout << "Too many wrong tries" << std::endl;
        std::cout << "Visit later!..." << std::endl;
    }
    else
    {
        obj.setAccBal(std::stod(data[acc_index + 4])); // converting the string value to double
        std::cout << "Enter your password: ";
        std::cin >> pass;

        // asking for password again if the given password is incorrect till 3 times
        while (pass != data[acc_index + 2] && pass_trycount < 3)
        {
            std::cout << "Wrong password" << std::endl
                      << "Enter the correct password: ";
            std::cin >> pass;
            pass_trycount++;
        }
        if (pass == data[acc_index + 2])
        {

            std::cout << std::endl
                      << "To withdraw money (maximum 10000 per transaction), press 1"
                      << std::endl
                      << "To deposit money (maximum 10000 per transaction), press 2"
                      << std::endl
                      << "To check available balance, press 3"
                      << std::endl
                      << "To exit, press 4"
                      << std::endl;

            getline(std::cin, a);
            option = checkNum(a);
            while (option < 1 || option > 4)

            {
                std::cout << "Please enter a valid number: " << std::endl;
                getline(std::cin, a);
                option = checkNum(a);
            }
            while (option != 4)
            {
                if (option == 1)
                {
                    std::string avail_notes;
                    if (obj.accbal < 200)
                    {
                        std::cout << "The minimum balance is 100, so cannot withdraw money" << std::endl;
                    }
                    else
                    {
                        if (obj.accbal < 600)
                        {
                            avail_notes = "100 ";
                        }
                        else
                        {
                            avail_notes = "100 and 500 ";
                        }
                        std::cout << "Available notes " << avail_notes << std::endl;
                        double max_withdraw = (obj.checkbal() - 100 <= 10000) ? obj.checkbal() : 10000;
                        std::cout << "Please enter an amount less than or equal to " << max_withdraw << " to withdraw: " << std::endl;
                        getline(std::cin, b);
                        inp_amount = checkNum(b);
                        while (inp_amount < 100 || inp_amount > 10000 || inp_amount % 100 != 0 || inp_amount > obj.accbal - 100)
                        {

                            // different reasons for why the transaction failed
                            if (inp_amount > obj.accbal - 100)
                            {
                                std::cout << "Available balance is only: " << obj.accbal << std::endl
                                          << "Minimum balance is 100" << std::endl
                                          << "please enter a valid amount: " << std::endl;
                            }
                            else if (inp_amount > 10000)
                            {
                                std::cout << "Cannot withdraw more than 10000 in a single transaction" << std::endl
                                          << "please enter a valid amount: " << std::endl;
                            }
                            else if (inp_amount < 100)
                            {
                                std::cout << "cannot withdraw less than 100: " << std::endl
                                          << "Please enter a valid amount: " << std::endl;
                            }
                            else
                            {
                                std::cout << "Invalid amount, available notes are only " << avail_notes << std::endl
                                          << "Please enter a valid amount: " << std::endl;
                            }

                            // getting the valid amount from the user again
                            getline(std::cin, b);
                            inp_amount = checkNum(b);
                        }
                        std::cout << "Here's your money " << inp_amount << std::endl;
                        std::cout << "Available balance: " << obj.withdraw(inp_amount) << std::endl
                                  << std::endl;
                    }
                }
                else if (option == 2)
                {
                    std::string accept_notes;
                    if (obj.checkbal() > 99900)
                    {
                        std::cout << "cannot deposit money as your balance will exceed the limit 100000" << std::endl;
                    }
                    else
                    {
                        if (obj.checkbal() > 99500)
                        {
                            accept_notes = "100 ";
                        }
                        else
                        {
                            accept_notes = "100 and 500 ";
                        }
                        std::cout << "Accepted notes to deposit " << accept_notes << std::endl;
                        double max_deposit = (100000 - obj.checkbal() <= 10000) ? 100000 - obj.checkbal() : 10000;
                        std::cout << "Please enter an amount less than or equal to " << max_deposit << " to deposit: " << std::endl;
                        getline(std::cin, b);
                        inp_amount = checkNum(b);

                        while (inp_amount < 100 || inp_amount > 10000 || inp_amount % 100 != 0 || inp_amount + obj.checkbal() > 100000)
                        {

                            // different reasons for why the transaction failed
                            if (inp_amount > 10000)
                            {
                                std::cout << "Cannot deposit more than 10000 in a single transaction" << std::endl
                                          << "Please enter a valid amount: " << std::endl;
                            }
                            else if (inp_amount + obj.checkbal() > 100000)
                            {
                                std::cout << "cannot deposit this amount of money as your balance will exceed 100000" << std::endl
                                          << "Please enter a valid amount: " << std::endl;
                            }
                            else if (inp_amount < 100)
                            {
                                std::cout << "cannot deposit less than 100" << std::endl
                                          << "Please enter a valid amount: " << std::endl;
                            }
                            else
                            {
                                std::cout << "Invalid amount, accepted notes are only " << accept_notes << std::endl
                                          << "please enter a valid amount: " << std::endl;
                            }

                            // getting the valid amount from the user again
                            getline(std::cin, b);
                            inp_amount = checkNum(b);
                        }
                        std::cout << "Money successfully deposited to account: " << b << std::endl;
                        std::cout << "Available balance: " << obj.deposit(inp_amount) << std::endl
                                  << std::endl;
                    }
                }

                else if (option == 3)
                {
                    std::cout << "Available Balance: " << obj.checkbal() << std::endl

                              << std::endl;
                }

                std::cout << std::endl
                          << "To withdraw money, press 1"
                          << std::endl
                          << "To deposit money, press 2"
                          << std::endl
                          << "To check available balance, press 3"
                          << std::endl
                          << "To exit, press 4"
                          << std::endl;
                getline(std::cin, a);
                option = checkNum(a);

                while (option < 1 || option > 4)
                {
                    std::cout << "Please enter a valid number: " << std::endl;
                    getline(std::cin, a);
                    option = checkNum(a);
                }
            }
            double updated_bal = obj.checkbal();

            // updating the balance to the data.txt file
            int target_line = acc_index + 4;
            std::fstream writeFile("./data.txt", std::ofstream::out);
            for (int i = 0; i < 60; i++)
            {
                if (i == target_line)
                {
                    writeFile << updated_bal << "\n";
                }
                else
                {
                    writeFile << data[i] << "\n";
                }
            }
            writeFile.close(); // closing the file after updating
        }

        // 3 unsuccessful attempts results in termination of the program with try again later message
        else
        {
            std::cout << "Too many wrong attempts, try again later!" << std::endl;
        }
    }

    std::cout << "Exited successfully..." << std::endl;
    return 0;
}