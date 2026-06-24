#include <iostream>
#include <windows.h>
#include <ctime>
#include<string>
#include<iomanip>
#include <vector>
#include<fstream>
using namespace std;

const string FileName = "ClintsDetails.txt";

void ShowMainMenue();

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccounBalance;
	bool MarkFoeDelete = false;
};

vector<string>SplitString(string Line, string Delim)
{
	vector<string>vString;
	short Pos;
	string sWord;
	while ((Pos = Line.find(Delim)) != std::string::npos)
	{
		sWord = Line.substr(0, Pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		Line.erase(0, Pos + Delim.length());
	}
	if (Line != "")
	{
		vString.push_back(Line);
	}
	return vString;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string>vString = SplitString(Line, Seperator);
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccounBalance = stod(vString[4]);
	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string Line = "";
	Line += Client.AccountNumber + Seperator;
	Line += Client.PinCode + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.Phone + Seperator;
	Line += to_string(Client.AccounBalance);

	return Line;
}

bool ClientExistByAccountNumber(string AccountNumber, string FileName)
{
	vector<sClient>vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();

	}
	return false;
}


sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number : ";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistByAccountNumber(Client.AccountNumber, FileName))
	{
		cout << "\nClient with [ " << Client.AccountNumber << " ] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "\nEnter PinCode : ";
	getline(cin, Client.PinCode);
	cout << "\nEnter your name : ";
	getline(cin, Client.Name);
	cout << "\nEnter Phone number : ";
	getline(cin, Client.Phone);
	cout << "\nEnter Account balance : ";
	cin >> Client.AccounBalance;

	return Client;
}


vector<sClient>LoadDataFromFile(string FileName)
{
	vector<sClient>vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	return vClients;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(20) << left << Client.AccountNumber;
	cout << "| " << setw(20) << left << Client.PinCode;
	cout << "| " << setw(30) << left << Client.Name;
	cout << "| " << setw(20) << left << Client.Phone;
	cout << "| " << setw(20) << left << Client.AccounBalance << endl;
}

void ShowAllClientsScreen()
{
	vector<sClient>vClients = LoadDataFromFile(FileName);

	cout << "\n\t\t\t\tClients list ( " << vClients.size() << " ) Client(s) \n";

	cout << "\n------------------------------------------------------------------";
	cout << "----------------------------------------------------\n" << endl;

	cout << "| " << left << setw(20) << "Account Number";
	cout << "| " << left << setw(20) << "Pin Code";
	cout << "| " << left << setw(30) << "Name";
	cout << "| " << left << setw(20) << "Phone Number";
	cout << "| " << left << setw(20) << "Account balance";

	cout << "\n------------------------------------------------------------------";
	cout << "----------------------------------------------------\n" << endl;
	if (vClients.size() == 0)
	{
		cout << "\t\t\tNo Clients Available in the system!";
	}
	else
	{
		for (sClient& C : vClients)
		{
			PrintClientRecordLine(C);
		}
		cout << endl;
	}

	cout << "\n------------------------------------------------------------------";
	cout << "----------------------------------------------------\n" << endl;

}

void PrintClientCard(sClient C)
{
	cout << "The following are client details : " << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Account number : " << C.AccountNumber << endl;
	cout << "Pin Code: " << C.PinCode << endl;
	cout << "Name: " << C.Name << endl;
	cout << "Phone number: " << C.Phone << endl;
	cout << "Account Blalnce: " << C.AccounBalance << endl;
	cout << "-----------------------------------------------" << endl;

}

bool FindClientByAccountNumber(vector<sClient>& Clients, string AccountNumber, sClient& Client)
{
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}


sClient ChangeClientRecoed(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\nEnter Pin code : ";
	getline(cin >> ws, Client.PinCode);
	cout << "\nEnter Name : ";
	getline(cin, Client.Name);
	cout << "Enter Phone number : ";
	getline(cin, Client.Phone);
	cout << "Enter Account balance : ";
	cin >> Client.AccounBalance;

	return Client;
}

bool MarkAccountNumberToDelet(vector<sClient>& Clients, string AccountNumber)
{

	for (sClient& C : Clients)
	{

		if (C.AccountNumber == AccountNumber)
		{
			C.MarkFoeDelete = true;
			return true;
		}
	}
	return false;
}

vector<sClient> SaveClientDataToFile(vector<sClient>Clients, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string Line;

	if (MyFile.is_open())
	{
		for (sClient& C : Clients)
		{
			if (C.MarkFoeDelete == false)
			{
				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;

			}
		}
		MyFile.close();
	}
	return Clients;
}

void AddDataLineToFile(string FileName, string DataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << DataLine << endl;

		MyFile.close();

	}

}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(FileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
	char AddMore = 'Y';
	do
	{

		cout << "Adding new Client: \n\n";
		AddNewClient();
		cout << "\nClient Addedsuccessfuly, do you want do Add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}


bool DeleteclientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(vClients, AccountNumber, Client))
	{

		PrintClientCard(Client);

		cout << "Are you sure you want delete this account ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkAccountNumberToDelet(vClients, AccountNumber);
			SaveClientDataToFile(vClients, FileName);
			vClients = LoadDataFromFile(FileName);

			cout << "\n\nClient Deleted successfuly.";

			return true;

		}

	}
	else
	{

		cout << "\nClient with account number [" << AccountNumber << "] is not found!";

		return false;
	}

}

bool UpdateClientByAccountNumber(vector<sClient>& vClient, string AccountNumber)
{
	sClient Client;

	char Answer = 'n';
	if (FindClientByAccountNumber(vClient, AccountNumber, Client))
	{
		PrintClientCard(Client);

		cout << "Are you sure you want delete this account ? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecoed(AccountNumber);
					break;
				}
			}
		}
		SaveClientDataToFile(vClient, FileName);

		cout << "\n\nClient Updated successfuly.";
		return true;

	}
	else
	{
		cout << "\nClient with account number [" << AccountNumber << "] is not found!";

		return false;
	}

}

string ReadClientAccountNumber()
{
	string AccountNumber;
	cout << "\nPlease enter account number? ";
	cin >> AccountNumber;
	return AccountNumber;
}


void ShowDeleteClientScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\tDelete Client Screen ";
	cout << "\n------------------------------------------------\n";

	vector<sClient>vClients = LoadDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteclientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\tUpdate Client Screen ";
	cout << "\n------------------------------------------------\n";

	vector<sClient>vClients = LoadDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(vClients, AccountNumber);
}

void ShowAddNewClientScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\tAdd New Client Screen ";
	cout << "\n------------------------------------------------\n";

	AddNewClients();
}

void ShowFindClientScreen()
{

	cout << "\n------------------------------------------------\n";
	cout << "\tFind Client Screen ";
	cout << "\n------------------------------------------------\n";

	vector<sClient>vClients = LoadDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	sClient Client;

	if (FindClientByAccountNumber(vClients, AccountNumber, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with account number [" << AccountNumber << "] is not found!";
	}
}

void ShowEndScreen()
{
	cout << "\n------------------------------------------------\n";
	cout << "\tProgram Ends :-) ";
	cout << "\n------------------------------------------------\n";
}

int ReadWithDrawAccount(sClient Client)
{
	int Amount;
	cout << "\nPlease enter Deposit Amount? ";
	cin >> Amount;
	
	
	while (Amount > Client.AccounBalance)
	{
		cout << "Amount Exceeds the balance, you can Withdraw up to : " << Client.AccounBalance << endl;
		cout << "Please enter anther amount? ";
		cin >> Amount;
	}
	
	return Amount;
}

int ReadAmountAccount()
{
	int Amount;
	cout << "\nPlease enter Deposit Amount? ";
	cin >> Amount;
	return Amount;
}

void ChaingAccountBlalnce(int Amount, sClient&C)
{
	C.AccounBalance += Amount;
}

bool ChingDepositClientRecord(vector<sClient>& Clients, string AccountNumber, int DepositAmount)
{
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			ChaingAccountBlalnce(DepositAmount, C);

			cout << "Done Successfuly New balance is [" << C.AccounBalance << "]..." << endl;
			return true;

		}
	}
	return false;
}

void DepositClientByAccountNumber(vector<sClient>&Clients, string AccountNumber)
{
	sClient Client;
	char DoAgain = 'y';
	char Answer = 'n';

	int DepositAmount;
	do
	{

		if (FindClientByAccountNumber(Clients, AccountNumber, Client))
		{
			PrintClientCard(Client);

			DepositAmount = ReadAmountAccount();

			cout << "\n\nAre you sure you want perfrom this transaction? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				ChingDepositClientRecord(Clients, AccountNumber, DepositAmount);
				Clients = SaveClientDataToFile(Clients, FileName);

			}

			cout << "Prees Any Key To Exit... ";
			system("pause>0");
			DoAgain = 'n';

		}
		else
		{
			cout << "Client with account number [" << AccountNumber << "] dose not Exist.";
			DoAgain = 'y';
		}
	} while (DoAgain == 'y');
}


void PrintClientBalanceRecord(sClient Client)
{

	cout << "| " << setw(30) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(40) << left << Client.AccounBalance << endl;

}

void ShowTotalBalanceScreen()
{
	vector<sClient>vClients = LoadDataFromFile(FileName);

	double TotalAccountBalance = 0;

	cout << "\n\t\t\t\tBalance list ( " << vClients.size() << " ) Client(s) \n";

	cout << "\n------------------------------------------------------------------";
	cout << "----------------------------------------------------\n" << endl;

	cout << "| " << left << setw(30) << "Account Number";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(40) << "Account balance";

	cout << "\n------------------------------------------------------------------";
	cout << "----------------------------------------------------\n" << endl;
	
	if (vClients.size() == 0)
	{
		cout << "\t\t\tNo Clients Available in the system!";
	}
	else
	{
		for (sClient& C : vClients)
		{
			PrintClientBalanceRecord(C);
			TotalAccountBalance += C.AccounBalance;
		}
	}
	cout << "\n------------------------------------------------------------------";
	cout << "----------------------------------------------------\n" << endl;
	cout << "\t\t\t\t\t\t\t    Total Balance = " << TotalAccountBalance << endl;

	cout << "Prees any key to go back to Transaction Menue...";
	system("pause>0");

}

void WithdrawClientByAccountNumber(vector<sClient>Clients, string AccountNumber)
{

	sClient Client;
	char DoAgin = 'n';
	char Answer = 'n';
	int Withdraw;
	do
	{
		if (FindClientByAccountNumber(Clients, AccountNumber, Client))
		{
			PrintClientCard(Client);
			Withdraw = ReadWithDrawAccount(Client);
			
			cout << "\n\nAre you sure you want perfrom this transaction? y/n? ";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				ChingDepositClientRecord(Clients, AccountNumber, Withdraw*-1);
				Clients = SaveClientDataToFile(Clients, FileName);

			}
			cout << "Prees any key to exit ..." << endl;
			system("pause>0");
			DoAgin = 'n';
		}
		else
		{
			cout << "Client with account number [" << AccountNumber << "] dose not Exist.";
			AccountNumber = ReadClientAccountNumber();
			DoAgin = 'Y';
		}
	} while (DoAgin == 'Y');


}


void ShowDepositClientScreen()
{

	cout << "\n------------------------------------------------\n";
	cout << "\tDeposit Client Screen ";
	cout << "\n-------------------=----------------------------\n";

	vector<sClient>vClients = LoadDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();

	DepositClientByAccountNumber(vClients, AccountNumber);
}


void ShowWithdrawClientScreen()
{

	cout << "\n------------------------------------------------\n";
	cout << "\tWithdraw Client Screen ";
	cout << "\n------------------------------------------------\n";

	vector<sClient>vClients = LoadDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();

	WithdrawClientByAccountNumber(vClients, AccountNumber);
}

enum enMainMenueOption
{
	eListClient = 1, eAddNewClient = 2,
	eDlelteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransactionMenue, eExit = 7
};

enum enTransactionMenueOption
{
	eDeposit = 1, eWithdraw = 2, eTotalBalance = 3, enExit = 4
};

void ShowTransactionMenue();

void GoBackToMainMenue()
{
	cout << "\n\nPress any Key to go back Main Menue...";
	system("pause>0");
	ShowMainMenue();

}

void GoBackToTransactionMenue()
{
	cout << "\n\nPress any Key to go back Transaction Menue...";
	system("pause>0");
	ShowTransactionMenue();
}

short ReadMainMenueOpration()
{
	cout << "Choose do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;

}


void PerfromTransactionsMenueScreen(enTransactionMenueOption TransactionMenueOption)
{

	switch (TransactionMenueOption)
	{

	case enTransactionMenueOption::eDeposit:
		system("cls");
		ShowDepositClientScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionMenueOption::eWithdraw:
		system("cls");
		ShowWithdrawClientScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionMenueOption::eTotalBalance:
		system("cls");
		ShowTotalBalanceScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionMenueOption::enExit:
		system("cls");
		cout << "\nExit....\nPrees  any key to go Main Menue ";
		system("pause>0");
		GoBackToMainMenue();
	}

}



void PerfromMainMenueOption(enMainMenueOption MainMenueOption)
{

	switch (MainMenueOption)
	{
	case enMainMenueOption::eListClient:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::eDlelteClient:
		system("cls");;
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::eTransactionMenue:
		system("cls");
		ShowTransactionMenue();
		break;

	case enMainMenueOption::eExit:
		system("cls");
		ShowEndScreen();
		break;

	}

}

short ReadTransactionMenueOpration()
{
	cout << "Choose do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;

}


void ShowTransactionMenue()
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tTransation Menue Screen \n";
	cout << "====================================================\n";
	cout << "\t[1] Deposit." << endl;
	cout << "\t[2] Withdraw." << endl;
	cout << "\t[3] Total Balance." << endl;
	cout << "\t[4] Exit." << endl;
	cout << "====================================================\n";

	PerfromTransactionsMenueScreen((enTransactionMenueOption)ReadTransactionMenueOpration());
}

void ShowMainMenue()
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\tMain Menue Screen \n";
	cout << "====================================================\n";
	cout << "\t[1] Print All Clients." << endl;
	cout << "\t[2] Add New client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client Info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Transaction Menue." << endl;
	cout << "\t[7] Exit." << endl;
	cout << "====================================================\n";

	PerfromMainMenueOption((enMainMenueOption)ReadMainMenueOpration());

}

int main()
{
	ShowMainMenue();
	
	system("pause>0");

	return 0;
}
