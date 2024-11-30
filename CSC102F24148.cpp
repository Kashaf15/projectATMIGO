#include <iostream>
#include <string>
#include <iomanip>
#include<fstream>
using namespace std;

//Validations
bool validInput(bool isValid, string inputStr,int &input);
bool validPin(bool isValid,string &pin);
bool validFloat(string &input);

//Conversion
float stringToFloat(string &input);

//Interface Functions
void displayAtmigo();//Function to display the Interface
int showMenu(int &input);//Main Menu Function
int adminLogIn(string pin, string username, int loggedInUserType);//Admin Login Function
int accounteeLogIn(string pin, string username, bool accounteeAuthenticity, int loggedInUserType, string accountee[], const int asize, int securityThreats[], string pins[]);//Account Holder Login Function
int showAdminMenu(int &input);//Admin Menu Function
int showAccounteeMenu(int &input);//Account Holder Menu Function

//Input Data
void inputData(string accountee[], string pins[], string complaints[], string allianceResponse[],
              int securityThreats[], float deposits[], float totalAmount[],
              float withdraws[], float transferFunds[], const int asize);

//Load Data function
void loadData(string accountee[], string pins[], string complaints[], string allianceResponse[],
              int securityThreats[], float deposits[], float totalAmount[],
              float withdraws[], float transferFunds[], const int asize);


//Admin Functions
void addUser(int &count,const int asize,string accountee[],string pins[],float totalAmount[]);//Add User Function
void removeUser(const int asize,string accountee[],string pins[],float totalAmount[]);//Remove User Function
void updateUser(const int asize,string accountee[],string pins[]);//Update User Function
void totalUser(const int asize, string accountee[], string pins[]);//Total Users List Function
void securityThreat(const int asize, string accountee[], int securityThreats[]);//Security Threats Function
void transactionHistory(const int asize, string accountee[],float withdraws[]);//Transaction history Function
void customerAlliance(const int asize,string complaints[], string allianceResponse[]);//Customer Support Function


//Account Holder Functions
void cashDeposit(int index, float deposits[], float totalAmount[]);//Cash Deposit Function
void cashWithdraw(int index,float withdraws[],float totalAmount[]);//Cash Withdrawl Function
void cashWithdrawalMultiCurrency(int index, float withdraws[], float totalAmount[]);//Cash withdrawl through multiCurrency Function
void cashDepositMultiCurrency(int index, float deposits[], float totalAmount[]);//Cash Deposit through multiCurrency Function
void fundsTransfer(int index, const int asize, float transferFunds[], float totalAmount[], string accountee[]);//Transfer Funds to another account Holder Function
void accountBalanceCheck(int index, float totalAmount[]);//Account Balance Check Function
void accounteeTransactionHistory(int index, float transferFunds[], float withdraws[], float deposits[]);//Account holder transaction history function
void threatAlert(int index, int securityThreats[]);//Threat Notification to account Holder
void feedback(int index, string allianceResponse[], string complaints[]);//Feedback Function

//The User Name and Paasword for Admin iS "Admin" and "1234" respectively
int main()
{
    int input=0, i=0, count = 0;
    string username="", pin=""; // Input for Pin and username
    bool accounteeAuthenticity = false;// To check if the credentials entered by the user are match or not
    const int asize = 80;// This atm management system can manage the data of upto 20 account holders
    string accountee[asize], pins[asize], complaints[asize], allianceResponse[asize]; // Array to store the account holders names
    float deposits[asize], totalAmount[asize], withdraws[asize], transferFunds[asize];
    int securityThreats[asize];
    float temp=0;

    int loggedInUserType = -10; // 1 for administrator, 2 for user

    //File Handling Function Call
    inputData(accountee,pins,complaints,allianceResponse, securityThreats,deposits,totalAmount,withdraws,transferFunds,asize);
    
    // Initiallizing all array elements
    for (i = 0; i < asize; i++)
    {
        accountee[i] = "";
        pins[i] = "";
        complaints[i] = "";
        allianceResponse[i] = "";
        deposits[i] = 0;
        totalAmount[i] = 0;
        withdraws[i] = 0;
        transferFunds[i] = 0;
        securityThreats[i] = 0;
    }

    // program header
    displayAtmigo();
    cout << endl;

    do
    {
        cout << endl;
        input=showMenu(input);
        switch (input)
        {
        case 1: 
        {
            // Admin login
            loggedInUserType = adminLogIn(pin, username, loggedInUserType);
            break;
        }

        case 2:
        {
            loggedInUserType=accounteeLogIn(pin,username,accounteeAuthenticity,loggedInUserType, accountee,asize,securityThreats,pins);
            break;
        }
        case 0:
        {
            loggedInUserType = -10;
            cout << "------------->>>>>>The System has been Exited<<<<<<-------------" << endl;
            break;
        }
        default:
            cout << "Invalid choice!!!"<<endl;
            break;
        }

        if (loggedInUserType == 1) // administrator
        {
            do
            {
                switch (showAdminMenu(input))
                {
                case 1:
                {
                    addUser(count,asize,accountee,pins,totalAmount);
                    break;
                }
                case 2:
                {
                    removeUser(asize,accountee,pins,totalAmount);
                    break;
                }
                case 3:
                {
                    updateUser(asize,accountee,pins);
                    break;
                }
                case 4:
                {
                    totalUser(asize,accountee,pins);
                    break;
                }
                case 5:
                {
                    securityThreat(asize,accountee,securityThreats);
                    break;
                }
                case 6:
                {
                    transactionHistory(asize,accountee,withdraws);
                    break;
                }
                case 7:
                {
                    customerAlliance(asize,complaints,allianceResponse);
                    break;
                }
                case 0:
                    cout <<endl<< "         Administrator is logged out!!" << endl;
                    break;

                default:
                    cout << "Invalid choice!!!"<<endl;
                    break;
                }
            } while (input != 0);
            input = -1; // this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == 2)
        {
           for (int index = 0; index < asize; index++)
            {
                if (username == accountee[index] && pin == pins[index]) 
                {
                    do
                    {   
                    switch (showAccounteeMenu(input))
                    {

                        case 1:
                        {
                            cashDeposit(index,deposits,totalAmount);
                            break;
                        }
                        case 2:
                        {
                            cashWithdraw(index,withdraws,totalAmount);
                            break;
                        }
                        case 3:
                        {
                            cashWithdrawalMultiCurrency(index, withdraws, totalAmount);
                            break;
                        }
                        case 4:
                        {
                            cashDepositMultiCurrency(index,deposits,totalAmount);
                            break;
                        }
                        case 5:
                        {
                            fundsTransfer(index,asize,transferFunds, totalAmount, accountee);
                            break;
                        }
                        case 6:
                        {
                            accountBalanceCheck(index, totalAmount);
                            break;
                        }
                        case 7:
                        {
                            accounteeTransactionHistory(index, transferFunds,withdraws,deposits);
                            break;
                        }
                        case 8:
                        {
                            threatAlert(index,securityThreats);
                            break;
                        }
                        case 9:
                        {
                            feedback(index, allianceResponse, complaints);
                            break;
                        }
                        case 0:
                            cout <<endl<< "          You are logged out!!         " << endl;
                            break;
                        default:
                        cout << "Invalid choice!!!"<<endl;
                        break;
                    }
                    } while (input != 0);

                }
            }
            input = -1; // this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == -1)
        {
            cout << "You have entered invalid Credentials!!!" << endl;
        }
    } while (input != 0);
    loadData(accountee,pins,complaints,allianceResponse, securityThreats,deposits,totalAmount,withdraws,transferFunds,asize);
    return 0;
}
// Function Implementations
bool validInput(bool isValid, string inputStr,int &input) {
    // Validate that the input is numeric
    isValid = true;

    for (int i = 0; i < inputStr.length(); i++) {
        if (inputStr[i] < '0' || inputStr[i] > '9') {
            isValid = false; // Non-digit character found
            break;
        }
    }

    if (!isValid) {
        cout << "Invalid input! Please enter a valid number." << endl;
    } else {
        // Convert the valid string to an integer
        input = 0;
        for (int i = 0; i < inputStr.length(); i++) {
            input = input * 10 + (inputStr[i] - '0');
        }

        // Check if the input is within the valid range
        if (input < 0 || input > 9) {
            isValid = false;
            cout << "Invalid input!" << endl;
        }
    }
    return isValid;
}
bool validPin(bool isValid,string &pin)
{
    while (!isValid) {
        cout << "Enter a 4-digit PIN: ";
        cin >> pin;

        // Validate length
        if (pin.length() != 4) {
            cout << "PIN must be exactly 4 digits long. Try again." << endl;
            continue;
        }

        // Validate all characters are digits
        isValid = true; // Assume valid initially
        for (int i = 0; i < 4; i++) {
            if (pin[i] < '0' || pin[i] > '9') { // Check if character is not a digit
                cout << "PIN must contain only numeric digits. Try again." << endl;
                isValid = false;
                break;
            }
        }
    }
    return isValid;
}
void displayAtmigo() {
    system("Color 06");
    cout << " __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __  " << endl;
    cout << "|                                                                 |" << endl;
    cout << "|     ___      ____    __  __      _____      ____     ______     |" << endl;
    cout << "|    /___\\    (_  _)  (  \\/  )    (_   _)    / ___)   (   _  )    |" << endl;
    cout << "|   /(___)\\     )(     )    (      _) (_    ( (_ -.    ) (_)(     |" << endl;
    cout << "|  (__) (__)   (__)   (_/\\/\\_)    (_____)    \\____/   (______)    |" << endl;
    cout << "|                                                                 |" << endl;
    cout << "|__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __|" << endl;
    return;
}

int showMenu(int &input) {
    cout << "------------------->>>>> Sign In Options <<<<<<---------------------" << endl;
    cout << "1. Administrator\n2. Account Holder\n0. Exit" << endl;
    
    bool isValid = false;
    string inputStr;
    do{
        cout << "Enter a number: ";
        cin >> inputStr;
        isValid=validInput(isValid,inputStr,input);
    }
    while(!isValid);
    return input;
}

int adminLogIn(string pin, string username, int loggedInUserType) {
    system("cls");
    cout << "----------------->>>>>>Administrator Log-IN<<<<<<----------------" << endl;
    cout << " ________________" << endl;
    cout << "| Enter Username:|";
    cin.ignore(1000, '\n');
    getline(cin, username);
    cout << endl;
    cout << " ___________" << endl;
    cout << "| Enter Pin:|";
    cin >> pin;
    cout << endl;

    if (username == "Admin" && pin == "1234") {
        loggedInUserType = 1; // Admin logged in
    } else {
        loggedInUserType = -1; // Invalid credentials
    }
    return loggedInUserType;
}

int accounteeLogIn(string pin, string username, bool accounteeAuthenticity, int loggedInUserType, string accountee[], const int asize, int securityThreats[], string pins[]) {
    system("cls");
    cout << "----------------->>>>>>Accountee Log-IN<<<<<<----------------" << endl;
    cout << " ________________" << endl;
    cout << "| Enter Username:|";
    cin.ignore(1000, '\n');
    getline(cin, username);
    cout << endl;
    cout << " ___________" << endl;
    cout << "| Enter Pin:|";
    cin >> pin;
    cout << endl;

    for (int i = 0; i < asize; i++) {
        if (username == accountee[i] && pin == pins[i]) {
            accounteeAuthenticity = true;
            break;
        }
        if (username == accountee[i] && pin != pins[i]) {
            securityThreats[i]++;
        }
    }

    loggedInUserType = accounteeAuthenticity ? 2 : -1;
    return loggedInUserType;
}

int showAdminMenu(int &input) {
    cout << "-------------->>>>>> Administrator Menu <<<<<<-------------------" << endl<<endl;
    cout <<"1. Add User\n2. Remove User\n3. Update User\n4. Total Users \n5. Threat Warnings \n6. Transaction History\n7. Assistance Alliance\n0. Log out" << endl;
    
    bool isValid = false;
    string inputStr;
    do{
        cout << "Enter a number: ";
        cin >> inputStr;
        isValid=validInput(isValid,inputStr,input);
    }
    while(!isValid);
    system("cls");
    return input;
}
int showAccounteeMenu(int &input)
{
    cout << "-------------->>>>>>accounteeountee Menu<<<<<<<-------------------" << endl;
    cout << endl;
    cout << "1. Cash Deposit\n2. Cash Withdrawl\n3. Multi-Currency Withdrawl\n4. MultiCurrency Deposit\n5. Funds Transfer\n6. Accountee Statement\n7. Transaction History\n8. Accountee Threat Alerts\n9. Feedback\n0. Sign out" << endl;
    
    bool isValid = false;
    string inputStr;
    do{
        cout << "Enter a number: ";
        cin >> inputStr;
        isValid=validInput(isValid,inputStr,input);
    }
    while(!isValid);

    system("cls");
    return input;
}
void addUser(int &count, const int asize, string accountee[], string pins[], float totalAmount[]) 
{
    system("cls");
    cout << "----------------->>>>>>Add User<<<<<<----------------" << endl<<endl;
    if (count >= asize) {
        cout << "No more space for additional users." << endl;
        return;
    }

    cin.ignore(1000, '\n'); // Clear input buffer
    cout << "Enter Account Holder's Name: ";
    getline(cin, accountee[count]);

    // Custom PIN validation

    string pin="";
    bool isValid = false;
    do{
        isValid=validPin(isValid,pin);
    }
    while(!isValid);
    pins[count] = pin; // Store the validated PIN

    //ammount validation
    string input;
    bool isValidFloat=false;
    do 
    {
        cout << "Enter total Amount in the Account in Pkr: ";
        cin >> input;

        isValidFloat = validFloat(input);

        if (!isValidFloat) {
            cout << "Invalid input. Please enter a valid amount" << endl;
        }
        cin.clear();

    } while (!isValidFloat);
    totalAmount[count] = stringToFloat(input);
    count++;
    cout << "User added successfully!" << endl;
    return;
}
float stringToFloat(string &input) {
    float result = 0.0;
    float fractionPart = 0.0;
    bool isFraction = false;
    float divisor = 10.0;

    // Loop through each character in the string
    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        if (c == '.') {
            isFraction = true; // Switch to processing the fractional part
            continue;
        }

        // Calculate the integer or fractional part
        if (!isFraction) {
            result = result * 10 + (c - '0'); // Build the integer part
        } else {
            fractionPart += (c - '0') / divisor; // Build the fractional part
            divisor *= 10;
        }
    }

    return result + fractionPart; // Combine integer and fractional parts
}
bool validFloat(string &input) {
    bool hasDecimalPoint = false; // To track if there's a decimal point

    // Check if the input is empty
    if (input.empty()) {
        return false;
    }

    // Handle the first character (it could be + or - or a digit)
    int startIndex = 0;
    if (input[0] == '+' || input[0] == '-') {
        startIndex = 1; // If it starts with + or -, we start checking from the next character
    }

    // Loop through each character in the string, starting from the second character if there's a sign
    for (int i = startIndex; i < input.length(); i++) {
        char c = input[i];


        // Check for a decimal point
        if (c == '.') {
            if (hasDecimalPoint) { // More than one decimal point is invalid
                return false;
            }
            hasDecimalPoint = true;
            continue; // Skip the decimal point check for the next character
        }

        // Check if the character is a digit (valid digits 0-9)
        if (c < '0' || c > '9') {
            return false; // Invalid character found (not a digit)
        }
    }

    // Ensure the input is not just a sign or decimal point
    if (input == "+" || input == "-" || input == "." || input == "+." || input == "-.") {
        return false;
    }

    return true; // Input passes all checks
}
void removeUser(const int asize,string accountee[],string pins[],float totalAmount[])
{
    system("cls");
//Remove User Functionalities
    cout << "----------------------->>>>>>Remove User<<<<<<--------------------------" << endl;
    string choice;//to ask from administrator user's name
    bool accounteeFound = false;
    cout << "Enter The Account Holder's Name to remove: ";
    getline(cin, choice);
    cin.ignore();
    for (int i = 0; i < asize; i++)
    {
        if (choice == accountee[i])
        {
            accountee[i] = "";
            pins[i] = "";
            totalAmount[i]=0;
            accounteeFound = true;
            cout << "Account removed successfully!!\n";
            break;
            }
    }
    //to check if the user exists
    if (!accounteeFound)
    {
    cout << "User Doesn't Exist Yet!!" << endl
    << endl;
    }
    return;
}
void updateUser(const int asize,string accountee[],string pins[])
{
    system("cls");
//Updating user portal
    cout << "----------------------->>>>>>Update User<<<<<<--------------------------" << endl;
    string choice;
    bool accounteeFound = false;
    cin.ignore(1000, '\n');
    cout << "Enter the Account Holder's name to update:";
    getline(cin, choice);
    for (int i = 0; i < asize; i++)
    {
        if (choice == accountee[i])
        {
            cin.ignore(1000, '\n');
            cout << "Enter new name for accountee: ";
            getline(cin, accountee[i]);
            cout << "Enter new pin: ";
            cin >> pins[i];
            accounteeFound = true;
            cout << "Account Updated successfully!!\n";
            break;
        }
    }
    //searching user to update
    if (!accounteeFound)
    {
    cout << "User Doesn't Exist Yet!!" << endl
     << endl;
    }
    return;
}
void totalUser(const int asize, string accountee[], string pins[]) {
    // Total Users List
    cout << "----------------------->>>>>> Total Users <<<<<<--------------------------" << endl;

    bool accounteeExists = false;
    cout << setw(30) << left << "Account Holder Names" 
         << setw(10) << right << "PIN Code" << endl
         << "---------------------------------------------" << endl;

    for (int i = 0; i < asize; i++) {
        if (!accountee[i].empty()) { // Skip empty entries
            cout << setw(30) << left << accountee[i] 
                 << setw(10) << right << pins[i] << endl;
            accounteeExists = true;
        }
    }

    // Checking if any user exists
    if (!accounteeExists) {
        cout << "\nNo Account Holders Yet!\n" << endl;
    }

    cout << "---------------------------------------------------------------------" << endl;
    return;
}
void securityThreat(const int asize, string accountee[],int securityThreats[])
{
    // Security Threat Notifications
    bool threatMade = false;

    cout << "----------------------->>>>>> Security Complaints <<<<<<--------------------------" << endl
         << endl;
    cout << "....................................................................." << endl;

    for (int i = 0; i < asize; i++)
    {
        if (securityThreats[i] != 0)
        {
            cout << "An Unauthorized Person tried to break into account number 1212-UBL-234" 
                 << i + 1 
                 << " under the Account Holder's Name: " << accountee[i] 
                 << " " << securityThreats[i] 
                 << " times but Failed!!\nKindly Look into that!!" << endl;
            cout << endl;
            cout << "....................................................................." << endl;
            threatMade = true;
        }
    }

    if (!threatMade)
    {
        cout << "No Threat Made to Any Account Yet!!" << endl << endl;
    }
    return;
}
void transactionHistory(const int asize, string accountee[], float withdraws[])
{
    // Transaction History Portal
    bool transactionMade = false;

    cout << "----------------------->>>>>> Transaction History <<<<<<--------------------------" << endl
         << endl;
    cout << "********************************************************************************" << endl;
    cout << "The transaction history of all accounts listed below:" << endl;

    for (int i = 0; i < asize; i++)
    {
        if (withdraws[i] != 0)
        {
            cout << "Transaction made by ACC No. 111-UBL-231" << (i + 1) 
                 << " under the Account Holder name: " << accountee[i] << endl
                 << " Dated on September, " << i + 11 
                 << " 2024 was Pkr. " << withdraws[i] << endl;
            cout << "********************************************************************************" << endl;
            transactionMade = true;
        }
    }

    // To check if any transaction has been made
    if (!transactionMade)
    {
        cout << "No Transaction Made by Any User Yet!!" << endl;
    }
    return;
}
void customerAlliance(const int asize,string complaints[], string allianceResponse[])
{
    bool feedback=false;
    // Feedback Portal
    cout << "----------------------->>>>>> Feedback <<<<<<--------------------------" << endl
         << endl;

    for (int i = 0; i < asize; i++)
    {
        if (complaints[i] != "")
        {
            cout << "Feedback: " << complaints[i] << endl;
            cout << "Response: ";
            cin.ignore(1000, '\n');
            getline(cin, allianceResponse[i]);
            feedback=true;
        }
    }
    if(!feedback)
    {
        cout<<"No Complaints Registered Yet!!"<<endl<<endl;
    }
    cout << "........................................................................" << endl;
    return;
}
void cashDeposit(int index, float deposits[], float totalAmount[])
{
    system("cls");
    cout << "---------------------------->>>>>>>>Cash Deposit<<<<<<<<--------------------------" << endl
         << endl;

    string input;
    bool isValidFloat=false;
    do 
    {
        cout << "Enter the amount you want to deposit (Maximum: Rs. 50000 && Minimum: Rs. 1000): Pkr. ";
        cin >> input;

        isValidFloat = validFloat(input);

        if (!isValidFloat) {
            cout << "Invalid input. Please enter a valid amount" << endl;
        }
        cin.clear();

    } while (!isValidFloat);
    deposits[index] = stringToFloat(input);

    if (deposits[index] < 1000)
    {
        cout << "The Amount is too low to deposit!!" << endl;
    }
    else if (deposits[index] > 50000)
    {
        cout << "The Amount is exceeding the limit!" << endl;
    }
    else if (deposits[index] >= 1000 && deposits[index] <= 50000)
    {
        totalAmount[index] += deposits[index];
        cout << "Amount entered in your account successfully!!" << endl;
    }
    else
    {
        cout << "Invalid Input!!" << endl;
    }

    cout << "............................................................................" << endl
         << endl;
    return;
}
void cashWithdraw(int index,float withdraws[],float totalAmount[])
{
    system("cls");
    cout << "--------------------------->>>>>>>>Cash Withdraw<<<<<<<<-------------------------" << endl
         << endl;

    string input;
    bool isValidFloat=false;
    do 
    {
        cout << "Enter the amount you want to withdraw (Maximum: Rs. 50000 && Minimum: Rs. 1000): Pkr. ";
        cin >> input;

        isValidFloat = validFloat(input);

        if (!isValidFloat) {
            cout << "Invalid input. Please enter a valid amount" << endl;
        }
        cin.clear();

    } while (!isValidFloat);
    withdraws[index] = stringToFloat(input);
    
    if(withdraws[index]>totalAmount[index])
    {
        cout<<"No Sufficient balance to make this Withdrawl!!"<<endl;
    }
    else if (withdraws[index] < 1000)
    {
        cout << "The Amount is too low to withdraw!!" << endl;
    }
    else if (withdraws[index] > 50000)
    {
        cout << "The Amount is exceeding the limit!" << endl;
    }
    else if (withdraws[index] >= 1000 && withdraws[index] <= 50000 && withdraws[index] <= totalAmount[index])
    {
        totalAmount[index] -= withdraws[index];
        cout << "Amount withdrawn from your account successfully!!" << endl;
    }
    else
    {
        cout << "Insufficient balance for this withdrawal!!" << endl;
    }

    cout << ".................................................................................." << endl
         << endl;
    return;
}
void cashWithdrawalMultiCurrency(int index, float withdraws[], float totalAmount[]) {
    system("cls");
    // Multi Currency Withdrawal
    cout << "-------------------------->>>>>>>>Multi Currency Withdraw<<<<<<<<--------------------------" << endl << endl;

    int choice;
    cout << "Choose your Currency for Cash Withdrawal (1 for USD, 2 for SAR): ";
    cin >> choice;
    cout << endl;

    if (choice == 1) {
        // USD Withdrawal

        string input;
        bool isValidFloat=false;
        do 
        {
            cout << "Enter the amount you want to Withdraw (Max: $5000, Min: $500):";
            cin >> input;

            isValidFloat = validFloat(input);

            if (!isValidFloat) {
            cout << "Invalid input. Please enter a valid amount" << endl;
            }
            cin.clear();

        } while (!isValidFloat);
        withdraws[index] = stringToFloat(input);

        if((withdraws[index]*300)>totalAmount[index])
        {
            cout<<"No Sufficient balance to make this Withdrawl!!"<<endl;
        }
        else if (withdraws[index] < 500) {
            cout << "The Amount is too low to Withdraw!!" << endl;
        } else if (withdraws[index] > 5000) {
            cout << "The Amount is exceeding the Limit!!" << endl;
        } else if (withdraws[index] >= 500 && withdraws[index] <= 5000) {
            withdraws[index] = withdraws[index] * 300;
            totalAmount[index] -= withdraws[index];
            cout << "The Amount has been Withdrawn from your Account Successfully!!" << endl;
        } else {
            cout << "Invalid Input!!" << endl;
        }
    } else if (choice == 2) {
        // SAR Withdrawal

        string input;
        bool isValidFloat=false;
        do 
        {
            cout << "Enter the amount you want to Withdraw (Max: SAR 10000, Min: SAR 1000): SAR ";
            cin >> input;

            isValidFloat = validFloat(input);

            if (!isValidFloat) {
            cout << "Invalid input. Please enter a valid amount" << endl;
            }
            cin.clear();

        } while (!isValidFloat);
        withdraws[index] = stringToFloat(input);

        if((withdraws[index]*80)>totalAmount[index])
        {
            cout<<"No Sufficient balance to make this Withdrawl!!"<<endl;
        }
        else if (withdraws[index] < 1000) {
            cout << "The Amount is too low to Withdraw!!" << endl;
        } else if (withdraws[index] > 10000) {
            cout << "The Amount is exceeding the Limit!!" << endl;
        } else if ((withdraws[index] >= 1000) && (withdraws[index] <= 10000) && (withdraws[index] < (totalAmount[index] / 80))) {
            withdraws[index] = withdraws[index] * 80;
            totalAmount[index] -= withdraws[index];
            cout << "The Amount has been Withdrawn from your Account Successfully!!" << endl;
        } else {
            cout << "Invalid Input!!" << endl;
        }
    } else {
        cout << "Invalid Input!!" << endl;
    }

    cout << ".................................................................................." << endl;
    return;
}
void cashDepositMultiCurrency(int index, float deposits[], float totalAmount[])
{
    system("cls");
    // Deposit for MultiCurrency
    cout << "------------------------->>>>>>>> Multi Currency Deposit <<<<<<<<-----------------------" << endl
         << endl;

    int choice;
    cout << "Choose your Currency for Cash Deposit (choose 1 for USD / 2 for SAR): ";
    cin >> choice;
    cout << endl;

    if (choice == 1)
    {
        cout << "Enter the amount you want to Deposit (Maximum: $5000 && Minimum: $500): $ ";
        cin >> deposits[index];

        string input;
        bool isValidFloat=false;
        do 
        {
            cout << "Enter the amount you want to deposit (Max: $5000, Min: $500):";
            cin >> input;

            isValidFloat = validFloat(input);

            if (!isValidFloat) {
            cout << "Invalid input. Please enter a valid amount" << endl;
            }
            cin.clear();

        } while (!isValidFloat);
        deposits[index] = stringToFloat(input);

        if (deposits[index] < 500)
        {
            cout << "The Amount is too low to deposit!!" << endl;
        }
        else if (deposits[index] > 5000)
        {
            cout << "The Amount is exceeding the Limit!!" << endl;
        }
        else
        {
            deposits[index] = deposits[index] / 300; // Assuming 300 is the exchange rate
            totalAmount[index] += deposits[index];
            cout << "The Amount has been deposited in your Account Successfully!!" << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "Enter the amount you want to Deposit (Maximum: SAR 10000 && Minimum: SAR 1000): SAR ";
        cin >> deposits[index];

        string input;
        bool isValidFloat=false;
        do 
        {
            cout << "Enter the amount you want to Deposit (Maximum: SAR 10000 && Minimum: SAR 1000): SAR ";
            cin >> input;

            isValidFloat = validFloat(input);

            if (!isValidFloat) {
            cout << "Invalid input. Please enter a valid amount" << endl;
            }
            cin.clear();

        } while (!isValidFloat);
        deposits[index] = stringToFloat(input);

        if (deposits[index] < 1000)
        {
            cout << "The Amount is too low to deposit!!" << endl;
        }
        else if (deposits[index] > 10000)
        {
            cout << "The Amount is exceeding the Limit!!" << endl;
        }
        else
        {
            deposits[index] = deposits[index] / 80; // Assuming 80 is the exchange rate
            totalAmount[index] += deposits[index];
            cout << "The Amount has been deposited in your Account Successfully!!" << endl;
        }
    }
    else
    {
        cout << "Invalid Input!!" << endl;
    }

    cout << ".................................................................................." << endl;
    return;
}
void fundsTransfer(int index, const int asize, float transferFunds[], float totalAmount[], string accountee[]) 
{
    system("cls");
    // Funds Transfer
    cout << "------------------------>>>>>>>> Funds Transfer <<<<<<<<-----------------------" << endl
         << endl;

    string accounteeName, currency;
    int choice;
    bool accounteeFound = false;

    cout << "Enter the Name of Account Holder you want to transfer funds to: ";
    cin >> accounteeName;
    cout << endl;

    // Loop through accounts to find matching accountee
    for (int i = 0; i < asize; i++) 
    {
        if (accounteeName == accountee[i]) 
        {
            accounteeFound = true;
            cout << "The Account Number 1212-UBL-234" << i + 1 << " has been found under Account Holder's Name: " << accounteeName << "." << endl;

            cout << "Choose the currency (Pkr, USD, SAR): ";
            cin >> currency;

            // Input validation for currency type
            if (currency != "Pkr" && currency != "USD" && currency != "SAR") 
            {
                cout << "Invalid currency choice!! Please select a valid currency (Pkr, USD, SAR)." << endl;
                return; // exit if invalid currency
            }

            // Enter amount to transfer

            string input;
            bool isValidFloat=false;
            do 
            {
                cout << "Enter the amount you want to transfer:  ";
                cin >> input;

                isValidFloat = validFloat(input);

                if (!isValidFloat) {
                cout << "Invalid input. Please enter a valid amount" << endl;
                }
                cin.clear();

            } while (!isValidFloat);
            transferFunds[index] = stringToFloat(input);

            cout << endl;

            // Validate amount is not negative or zero
            if (transferFunds[index] <= 0) 
            {
                cout << "Invalid amount! Please enter a positive value." << endl;
                return; // exit if invalid amount
            }

            // Check if the user has enough balance to transfer
            if (transferFunds[index] > totalAmount[index]) 
            {
                cout << "Insufficient balance! You only have Pkr " << totalAmount[index] << " in your account." << endl;
                return; // exit if insufficient balance
            }

            // Currency-wise transfer logic
            if (currency == "Pkr") 
            {
                cout << "Are you sure you want to transfer Pkr. " << transferFunds[index] 
                     << " to the Account Holder ID 1212-UBL-234" << i + 1 << " (1/0)? ";
                cin >> choice;
                cout << endl;

                if (choice == 1) 
                {
                    totalAmount[index] -= transferFunds[index];
                    totalAmount[i] += transferFunds[index];
                    cout << "The Amount Pkr. " << transferFunds[index] 
                         << " has been transferred to the Account Holder ID 1212-UBL-234" << i + 1 
                         << " Successfully!!" << endl;
                } 
                else if (choice == 0) 
                {
                    cout << "Thank you for your Cooperation!!" << endl;
                } 
                else 
                {
                    cout << "Invalid Input!!" << endl;
                }
            } 
            else if (currency == "USD") 
            {
                cout << "Are you sure you want to transfer $ " << transferFunds[index] 
                     << " to the Account Holder ID 1212-UBL-234" << i + 1 << " (1/0)? ";
                cin >> choice;
                cout << endl;

                if (choice == 1) 
                {
                    totalAmount[index] -= (transferFunds[index] * 300); // Assuming exchange rate is 300
                    totalAmount[i] += (transferFunds[index] * 300);
                    cout << "The Amount $ " << transferFunds[index] 
                         << " has been transferred to the Account Holder ID 1212-UBL-234" << i + 1 
                         << " Successfully!!" << endl;
                } 
                else if (choice == 0) 
                {
                    cout << "Thank you for your Cooperation!!" << endl;
                } 
                else 
                {
                    cout << "Invalid Input!!" << endl;
                }
            } 
            else if (currency == "SAR") 
            {
                cout << "Are you sure you want to transfer SAR " << transferFunds[index] 
                     << " to the Account Holder ID 1212-UBL-234" << i + 1 << " (1/0)? ";
                cin >> choice;

                if (choice == 1) 
                {
                    totalAmount[index] -= (transferFunds[index] * 80); // Assuming exchange rate is 80
                    totalAmount[i] += (transferFunds[index] * 80);
                    cout << "The Amount SAR " << transferFunds[index] 
                         << " has been transferred to the Account Holder ID 1212-UBL-234" << i + 1 
                         << " Successfully!!" << endl;
                } 
                else if (choice == 0) 
                {
                    cout << "Thank you for your Cooperation!!" << endl;
                } 
                else 
                {
                    cout << "Invalid Input!!" << endl;
                }
            }

            break; // Exit the loop once the accountee is found and processed
        }
    }

    // If accountee is not found
    if (!accounteeFound) 
    {
        cout << "Error: The Customer ID cannot be Found!!" << endl;
    }

    cout << ".................................................................................." << endl
         << endl;
    return;
}
void accountBalanceCheck(int index, float totalAmount[])
{
    system("cls");
    cout << "------------------------->>>>>>>> Account Balance <<<<<<<<<<--------------------" << endl
         << endl;

    cout << "||||||||||||||||||||||||||||||||||||" << endl;
    cout << "                LAHORE              " << endl
         << endl;
    cout << "11/10/2024       11:57:03      0076" << endl;
    cout << "        ACCOUNT BALANCE DETAILS    " << endl
         << endl;

    cout << "Card No: 52967*********6328\n"
         << "Account No.: 54533******4343\n"
         << "STAN: 78786" << endl
         << endl;

    cout << "Available Balance: PKR " << totalAmount[index] << endl
         << endl;

    cout << "               THANK YOU            " << endl
         << endl;

    cout << "||||||||||||||||||||||||||||||||||||" << endl
         << endl;

    cout << ".................................................................................." << endl
         << endl;
    return;
}
void accounteeTransactionHistory(int index, float transferFunds[], float withdraws[], float deposits[])
{
    system("cls");
    // To check transaction history
    cout << "---------------------->>>>>>>> Transaction History <<<<<<<<-------------------" << endl
         << endl;

    cout << "Below is a detailed record of your last transaction, including date and amount." << endl;
    cout << ".................................................................................." << endl
         << endl;

    if (withdraws[index] != 0 || deposits[index] != 0 || transferFunds[index] != 0)
    {
        // Check withdrawals
        if (withdraws[index] != 0)
        {
            if (withdraws[index] > 50000)
            {
                cout << "The Amount " << withdraws[index] << " has been withdrawn from your Account\n"
                     << "through International Currency on September " << index + 1 << ", 2024." << endl;
            }
            else
            {
                cout << "The Amount PKR " << withdraws[index] << " has been withdrawn from your\n"
                     << "Account on September " << index + 1 << ", 2024." << endl;
            }
            cout << ".................................................................................." << endl;
        }

        // Check deposits
        if (deposits[index] != 0)
        {
            if (deposits[index] > 50000)
            {
                cout << "The Amount " << deposits[index] << " has been deposited to your Account\n"
                     << "through International Currency on September " << index + 2 << ", 2024." << endl;
            }
            else
            {
                cout << "The Amount PKR " << deposits[index] << " has been deposited to your\n"
                     << "Account on September " << index + 2 << ", 2024." << endl;
            }
            cout << ".................................................................................." << endl;
        }

        // Check transfers
        if (transferFunds[index] != 0)
        {
            if (transferFunds[index] < 50000)
            {
                cout << "The Amount " << transferFunds[index] << " has been transferred from your Account\n"
                     << "through International Currency on September " << index + 4 << ", 2023." << endl;
            }
            else
            {
                cout << "The Amount PKR " << transferFunds[index] << " has been transferred from your\n"
                     << "Account on September " << index + 4 << ", 2023." << endl;
            }
            cout << ".................................................................................." << endl;
        }
    }
    else
    {
        cout << "No Transactions Made Yet!!" << endl;
        cout << ".................................................................................." << endl
             << endl;
    }
    return;
}
void threatAlert(int index, int securityThreats[])
{
    system("cls");
    // Security Threats to your Account
    cout << "------------------------>>>>>>>> Security Threats <<<<<<<<-------------------" << endl
         << endl;

    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "An Unauthorized Person tried to break into your account " 
         << securityThreats[index] << " times but Failed!!" << endl;
    cout << "Be Careful to whom you share your PIN with!!" << endl;
    cout << endl;

    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl
         << endl;
    return;
}
void feedback(int index, string allianceResponse[], string complaints[])
{
    system("cls");
    // Feedback
    cout << "----------------->>>>>> Feedback Portal <<<<<<----------------" << endl;
    cout << "Enter your Feedback: ";
    cin.ignore(1000, '\n'); // To handle newline characters in the input buffer
    getline(cin, complaints[index]);
    cout << endl
         << endl;

    cout << "...................Thank you for using our ATM.................." << endl
         << endl;

    // Display response to previous feedback if available
    if (allianceResponse[index] != "")
    {
        
        cout << "Response to your previous feedback:" << endl;
        cout << "............................................................................." << endl
             << endl;
        cout << allianceResponse[index] << endl;
        cout << "............................................................................." << endl
             << endl;
    }
    return;
}
void loadData(string accountee[], string pins[], string complaints[], string allianceResponse[],
              int securityThreats[], float deposits[], float totalAmount[],
              float withdraws[], float transferFunds[], const int asize) {

    ofstream fout("OutputData.txt");
    if (!fout.is_open()) {
        cout << "Unable to open file" << endl; // Fixed missing operator
        return;
    }

    // Write the header to the file
    fout << "Accountee\tPIN\tComplaint\tAlliance Response\tSecurity Threats\tDeposits\tTotal Amount\tWithdrawals\tTransfer Funds\n";
    
    // Write each account's data to the file
    for (int i = 0; i < asize; i++) {
        if (!accountee[i].empty()) { // Skip empty records
            fout << accountee[i] << "\t"
                 << pins[i] << "\t"
                 << complaints[i] << "\t"
                 << allianceResponse[i] << "\t"
                 << securityThreats[i] << "\t"
                 << deposits[i] << "\t"
                 << totalAmount[i] << "\t"
                 << withdraws[i] << "\t"
                 << transferFunds[i] << endl;
        }
    }
    
    fout.close(); // Close the file
    cout << "Data successfully written to OutputData.txt" << endl; // Confirmation message
    return;
}
void inputData(string accountee[], string pins[], string complaints[], string allianceResponse[],
              int securityThreats[], float deposits[], float totalAmount[],
              float withdraws[], float transferFunds[], const int asize)
{
    ifstream fin("inputData.txt");
    if (!fin.is_open()) {
        cout << "Unable to open file" << endl; // Fixed missing operator
        return;
    }	
    for(int i=0;i<asize;i++)
    {
        getline(fin,accountee[i],',');
        getline(fin,pins[i],',');
        getline(fin,complaints[i],',');
        getline(fin,allianceResponse[i],',');
        fin>>securityThreats[i];
        fin>>deposits[i];
        fin>>totalAmount[i];
        fin>>withdraws[i];
        fin>>transferFunds[i];
        fin.ignore();
    }
    fin.close();
    return;
}











