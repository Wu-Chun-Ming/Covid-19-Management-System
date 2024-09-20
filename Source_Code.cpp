// Library
#include <iostream>
#include <iomanip>		// for setw()
#include <fstream>		// for file handling
#include <sstream>		// fors stringstream
#include <string>		// for string
#include <cctype>		// for isdigit()
#include <ctime>		// get current time
using namespace std;

// Global Constant
#define MAX_USER 1000

// Structure
typedef struct{
	string userName;
	string password;
	string name;
	int age;
	string contactNum;
	string address;
	string mySejahteraStatus;
	char isVaccinated;				// Y,N
	string vaccineDate;

	string covid19Test;				// +ve, -ve
	char symptom; 					// Y,N
	string category;		// A,B,C,None
	string classificationDate = "N/A";		// DD/MM/YYYY
	int quarantinePeriod;		// default = 0
} USER_DETAIL;

// Function Prototype
// File Related
int read_File(USER_DETAIL userDetail[]);
void save_User_Data(USER_DETAIL userDetail[], int num_data);
// Get User Data Index
int get_User_Data_Idx(USER_DETAIL userDetail[], int num_data, string *userLogin);
// User
int user_Register(USER_DETAIL userDetail[], int num_data);
void user_Login(USER_DETAIL userDetail[], int num_data, string *userLogin);
void user_Profile(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx);
void user_Classification(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx);
// Vaccination
void register_Vaccine(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx);
void check_Vaccine(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx);

// Main Function
int main(void){
	// Initialize an array
	USER_DETAIL userDetail[MAX_USER];

	// Get the number of data
	int num_data = read_File(userDetail);

	// File required
	if(num_data == -1){
		cout << "Error opening file/File does not exist.\n";
		cout << "Please check the required file (users.txt).";
	}else{
		string opt, userLogin = "NULL";
		do{
			// Get the user data index in userDetail array
			int userDataIdx = get_User_Data_Idx(userDetail, num_data, &userLogin);

			system("CLS");
			// Main Menu
			cout << "--------------------------------------------------------------------------------\n";
			if(userLogin != "NULL"){
				cout << "|" << setw(((58-userLogin.length())/2)+21) << right << "You are logged in as " << userLogin 
					 << setw((58-userLogin.length())/2+(58-userLogin.length())%2) << right << "|" << endl;
			}else if((opt[0] == '3' || opt[0] == '4' || opt[0] == '5' || opt[0] == '6') && userLogin == "NULL")
				cout << "|                          You must Login to Continue                          |\n";
			else
				cout << "|                           Please Register or Login                           |\n";

			cout << "--------------------------------------------------------------------------------\n";
			if(userLogin == "NULL"){
				cout << "Welcome to COVID-19 Management System\n";
			}else{
		        cout << "NOTIFICATIONS:\n";
		        cout << "Please make sure to follow all the SOPs whenever you are outside.\n";
		        cout << "Please do get vaccinated. It's safe and makes you safe around people.\n";
		        cout << "Please do contact or go to Hospital if have any covid symptoms.\n";
		        cout << "TOGETHER WE FIGHT COVID-19!\n";
			}

			cout << "\n1. Register";
			cout << "\n2. Login";
			cout << "\n3. Covid-19 Test";					// Category Changes
			cout << "\n4. View/Update Profile";
			cout << "\n5. Register for Vaccination";
			cout << "\n6. Check Vaccination Appointment";
			cout << "\nPress control-z to Exit";
			cout << "\n--------------------------------------------------------------------------------\n";

			bool optValid = false;
			do{
				cout << "Enter option: ";
				fflush(stdin);			// flush the input buffer
				cin >> opt;
				if(cin.eof()){			// exit the loop if EOF is detected
		            optValid = true;
		       	}else if(isdigit(opt[0]) && opt.length() == 1){
					switch(opt[0]){
						case '1':
							num_data = user_Register(userDetail, num_data);
							optValid = true;
							break;
						case '2':
							user_Login(userDetail, num_data, &userLogin);
							optValid = true;
							break;
						case '3':
							user_Classification(userDetail, num_data, &userLogin, userDataIdx);
							optValid = true;
							break;
						case '4':
							user_Profile(userDetail, num_data, &userLogin, userDataIdx);
							optValid = true;
							break;
						case '5':
							register_Vaccine(userDetail, num_data, &userLogin, userDataIdx);
							optValid = true;
							break;
						case '6':
							check_Vaccine(userDetail, num_data, &userLogin, userDataIdx);
							optValid = true;
							break;
						default:
							cout << "Invalid Option\n";
							break;
					}
				}else{
					cout << "Invalid Option\n";
				}
			}while(!optValid);
		}while(!cin.eof());
	}
	return 0;
}

// Check User Vaccinated Status
void check_Vaccine(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx){
	system("CLS");
	if(*userLogin != "NULL"){
		cout << "--------------------------------------------------------------------------------\n";
		cout << "|                              Vaccination Status                              |\n";
		cout << "--------------------------------------------------------------------------------\n";

		// Check if user is vaccinated or not
		if(userDetail[userDataIdx].isVaccinated == 'Y'){
			cout << "You have been vaccinated.\n";
	        cout << "You are vaccinated on :" << userDetail[userDataIdx].vaccineDate << endl;
	        cout << "Press any key to Continue.\n";
	        system("pause>nul");
		}else{
			cout << "You have not been vaccinated.\n";
	        cout << "Please do register for vaccine by selecting option 5 in the user menu. Thank you.\n";
	        cout << "Press any key to Continue.\n";
	        system("pause>nul");
		}
	}
}

// Vaccination Registration
void register_Vaccine(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx){
	system("CLS");
	if(*userLogin != "NULL"){
		cout << "--------------------------------------------------------------------------------\n";
		cout << "|                           Vaccination Registration                           |\n";
		cout << "--------------------------------------------------------------------------------\n";

		string vaccineDate;
		bool dateValid = false;

		// Check if already register for vaccination
		if(userDetail[userDataIdx].vaccineDate != "N/A"){
	        cout << "You are already vaccinated.\n";
	        cout << "Vaccination date: " << userDetail[userDataIdx].vaccineDate << endl;
	        cout << "Press any key to Continue.\n";
	        system("pause>nul");
		}else{
	    	do{
		        cout << "Enter vaccination date (DD/MM/YYYY): ";
		        fflush(stdin);			// flush the input buffer
		        cin >> vaccineDate;
		        if(vaccineDate.length() != 10 || (vaccineDate[2] != '/' && vaccineDate[5] != '/'))
		        	cout << "Invalid date format\n";
		        else{
		        	// Test for valid date
        			int index = 0;
					while(isdigit(vaccineDate[index]) && index < vaccineDate.length() - 1){
						if(index == 1 || index == 4)			// 2,5 is "/"
							index+=2;
						else
							index++;
					}
					if(!isdigit(vaccineDate[index]))
						cout << "Invalid date\n";
					else
						dateValid = true;
			    }
	    	}while(!dateValid);

	    	userDetail[userDataIdx].isVaccinated = 'Y';
	    	userDetail[userDataIdx].vaccineDate = vaccineDate;

	    	// Save data into txt file
	    	save_User_Data(userDetail, num_data);

	    	cout << "Vaccination registered successfully.\n";
	        cout << "Press any key to Continue.\n";
	        system("pause>nul");
		}
	}
}

// View or Update profile
void user_Profile(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx){
	if(*userLogin != "NULL"){
		bool exit = false;

		do{
			system("CLS");
			cout << "--------------------------------------------------------------------------------\n";
		    cout << "|                                 User Profile                                 |\n";
		    cout << "--------------------------------------------------------------------------------\n";

		    cout << "Username: " << userDetail[userDataIdx].userName << endl;
		    cout << "Name: " << userDetail[userDataIdx].name << endl;
		    cout << "Age: " << userDetail[userDataIdx].age << endl;
		    cout << "Contact number: " << userDetail[userDataIdx].contactNum << endl;
		    cout << "Address: " << userDetail[userDataIdx].address << endl;
		    cout << "MySejahtera Status: " << userDetail[userDataIdx].mySejahteraStatus << endl;
	        cout << "Vaccinated (Y: Yes; N: No): " << userDetail[userDataIdx].isVaccinated << endl;
	        cout << "Vaccine Date: " << userDetail[userDataIdx].vaccineDate << endl;
	        cout << "Category: " << userDetail[userDataIdx].category
	        	 << " (Classification Date: " << userDetail[userDataIdx].classificationDate << ")" << endl;
	       	if(userDetail[userDataIdx].quarantinePeriod != 0)
	        	cout << "Quarantine Period: " << userDetail[userDataIdx].quarantinePeriod << " days" << endl;
			cout << endl;

			string updateOpt, contactNum, address;
			int index = 0;
			bool update = false;

		    cout << "1. Update Contact Number\n";
		    cout << "2. Update Address\n";
		    cout << "3. Return to Main Menu\n";
		    cout << "--------------------------------------------------------------------------------\n";

		    do{
			    cout << "Enter option: ";
			    fflush(stdin);			// flush the input buffer
			    cin >> updateOpt;

			    if(updateOpt.length() != 1 || !isdigit(updateOpt[0])){
			    	cout << "Invalid Option\n";
			    }else{
			    	switch(updateOpt[0]){
			    		case '1':
			    			cout << "Enter your latest contact number (01234567890): ";
			    			fflush(stdin);			// flush the input buffer
			    			cin >> contactNum;
				    		
				    		// Check for a valid contact number
				    		while(isdigit(contactNum[index]) && index < contactNum.length())
				    			index++;
				    		if(!isdigit(contactNum[index]))
				    			cout << "Invalid contact number\n";
				    		else{
			    				userDetail[userDataIdx].contactNum = contactNum;
				    			update = true;
				    		}
			    			break;
			    		case '2':
			    			cout << "Enter your lastest home address: ";
			    			fflush(stdin);
			    			getline(cin, address);

			    			// Convert to upper case
			    			for(int i = 0; i < address.length(); i++){
			    				address[i] = toupper(address[i]);

			    				if(i == address.length() - 1){
				    				userDetail[userDataIdx].address = address;
				    				update = true;
					    		}
			    			}
			    			break;
			    		case '3':
			    			exit = true;
			    			break;
			    		default:
			    			cout << "Invalid Option\n";
			    			break;
			    	}
			    }
		    }while(!update && !exit);

		    if(update){
		    	save_User_Data(userDetail, num_data);
		    }
	    }while(!exit);
	}
}

// User Classfication based on COVID-19 category
void user_Classification(USER_DETAIL userDetail[], int num_data, string *userLogin, int userDataIdx){
	string covid19Test, symptom, closeContact, category;

	if(*userLogin != "NULL"){
		system("CLS");
		
		cout << "--------------------------------------------------------------------------------\n";
	    cout << "|                                 Covid-19 Test                                |\n";
	    cout << "--------------------------------------------------------------------------------\n";

	    // COVID-19 Test Result
		do{
			cout << "Have you tested positive for COVID-19? (Y/N): ";
			fflush(stdin);			// flush the input buffer
			cin >> covid19Test;
			if(covid19Test.length() != 1 || (toupper(covid19Test[0]) != 'Y' && toupper(covid19Test[0]) != 'N'))
				cout << "Invalid Result\n";
		}while(covid19Test.length() != 1 || (toupper(covid19Test[0]) != 'Y' && toupper(covid19Test[0]) != 'N'));

		if(toupper(covid19Test[0]) == 'Y')
			covid19Test = "+ve";
		else
			covid19Test = "-ve";

		// Symptomatic or Asymptomatic
		do{
			cout << "Do you have COVID-19 symptom? (Y/N): ";
			fflush(stdin);			// flush the input buffer
			cin >> symptom;
			if(symptom.length() != 1 || (toupper(symptom[0]) != 'Y' && toupper(symptom[0]) != 'N'))
				cout << "Invalid Option\n";
		}while(symptom.length() != 1 || (toupper(symptom[0]) != 'Y' && toupper(symptom[0]) != 'N'));

		// Covid-19 Category
		if(covid19Test == "+ve"){	// tested positive
			category = "A";
			cout << "You are in Category A: Confirmed COVID-19 Case. Please quarantine and take a COVID test.\n";
		}else{						// tested negative
			if(toupper(symptom[0]) == 'Y'){		// Symptomatic
				if(userDetail[userDataIdx].category == "None"){
					// Close Contact
					do{
						cout << "The Meaning of CLOSE CONTACT is a person who has had any of the following exposures to a probable or confirmed case:\n";
						cout << "- Living or sleeping in the same house with a probable or confirmed case\n";
						cout << "- Face-to-face contact with a probable or confirmed case within 1 meter and for at least 15 minutes, and they are not wearing a face mask or not wearing it properly\n";
						cout << "- Direct physical contact (e.g. hugging, kissing, being coughed or sneezed on etc.) with a probable or confirmed case\n";
						cout << "- Direct care for a patient with probable or confirmed COVID-19 disease without the use of recommended personal protective equipment\n";
						cout << "Are you a close contact of COVID-19 case? (Y/N): ";
						fflush(stdin);			// flush the input buffer
						cin >> closeContact;

						if(closeContact.length() != 1 || (toupper(closeContact[0]) != 'Y' && toupper(closeContact[0]) != 'N'))
							cout << "Invalid Option\n";
						else if(toupper(closeContact[0]) == 'Y'){
							category = "B";
							cout << "You are in Category B: Suspected COVID-19 Case. Please quarantine and look out for more symptoms.\n";
						}else{
							category = "C";
				            cout << "You are in Category C: Casual Contact. Please take a COVID test.\n";		
						}
					}while(closeContact.length() != 1 || (toupper(closeContact[0]) != 'Y' && toupper(closeContact[0]) != 'N'));
				}else if(userDetail[userDataIdx].category == "C"){
					cout << "You are allowed to access campus\n";
				}
			}else{		// No symptom
				if(userDetail[userDataIdx].category == "None"){
					category = "C";
		            cout << "You are in Category C: Casual Contact. Please take a COVID test.\n";
				}else{
					category = "None";
					cout << "You are allowed to access campus\n";
				}
			}
		}
		cout << "Press any key to Continue.\n";
		system("pause>nul");

		// Classfication Date
		char currentDate[11];
		time_t currentTime = time(0);
		strftime(currentDate, 11, "%d/%m/%Y", localtime(&currentTime));

		// Quarantine Period
		int quarantinePeriod = 0;
		if(category == "A")
			quarantinePeriod = 7;
		else if(category == "B"){
			if(toupper(symptom[0]) == 'Y' || (toupper(symptom[0]) == 'N' && toupper(closeContact[0]) == 'Y'))
				quarantinePeriod = 3;
		}

		userDetail[userDataIdx].covid19Test = covid19Test;
		userDetail[userDataIdx].symptom = toupper(symptom[0]);
		userDetail[userDataIdx].category = category;
		userDetail[userDataIdx].classificationDate = currentDate;
		userDetail[userDataIdx].quarantinePeriod = quarantinePeriod;

		// Save data into file
		save_User_Data(userDetail, num_data);
	}
}

// Register as user
int user_Register(USER_DETAIL userDetail[], int num_data){
	system("CLS");

	string userName, password, name, age, contactNum, address, mySejahteraStatus;
	int index = 0;
	bool userExists = true;

	cout << "--------------------------------------------------------------------------------\n";
    cout << "|                                User Register                                 |\n";
    cout << "--------------------------------------------------------------------------------\n";
	do{
		// Request for username
		cout << "Enter username: ";
		fflush(stdin);			// flush the input buffer
		getline(cin, userName);

		if(toupper(userName[0]) == 'Z' && userName.length() == 1){
			userExists = false;
		}else{
			// Convert to upper case
			for(int i = 0; i < userName.length(); i++){
				userName[i] = toupper(userName[i]);
			}
			// Check if the userName has been registered
			while(userName != userDetail[index].userName && index < num_data - 1)
				index++;
			if(userName == userDetail[index].userName){
				cout << "This username has been registered. Try to use another username to register.\n";
				cout << "Enter \"Z\"to go back to menu.\n";
			}else
				userExists = false;
			// --------------------
			if(num_data == 0)
				userExists = false;
		}
	}while(userExists);

	if(userName.length() != 1){
		// Request a password
		cout << "Enter account password: ";
		cin >> password;

		// Request for personal name
		cout << "Enter name: ";
		fflush(stdin);			// flush the input buffer
		getline(cin, name);

		// Convert to upper case
		for(int i = 0; i < name.length(); i++)
			name[i] = toupper(name[i]);

		bool ageValid = false;
		do{
			// Get the age
			cout << "Enter age: ";
			fflush(stdin);			// flush the input buffer
			cin >> age;
			
			// Test for valid age number
			index = 0;
			while(isdigit(age[index]) && index < age.length() - 1)
				index++;
			if(!isdigit(age[index]))
				cout << "Invalid age\n";
			else
				ageValid = true;

		}while(!ageValid);

		bool contactNumValid = false;
		do{
			// Get the contact number
			cout << "Enter contact number (01234567890): ";
			fflush(stdin);			// flush the input buffer
			cin >> contactNum;

			// Test for valid contact number
			index = 0;
			while(isdigit(contactNum[index]) && index < contactNum.length() - 1)
				index++;
			if(!isdigit(contactNum[index]))
				cout << "Invalid contact number\n";
			else
				contactNumValid = true;

		}while(!contactNumValid);

		cout << "Enter home address: ";
		fflush(stdin);			// flush the input buffer
		getline(cin, address);
		for(int i = 0; i < address.length(); i++){
			address[i] = toupper(address[i]);
		}

		// Get the mysejahtera status
		bool statusValid = false;
		cout << "1. Low Risk\n";
		cout << "2. Close Contact\n";
		cout << "3. Person Under Surveillance (PUS)\n";
		cout << "4. Suspected Case\n";
		cout << "5. Confirmed Case - Symptomatic\n";
		do{
			cout << "Enter MySejahtera Status: ";
			fflush(stdin);			// flush the input buffer
			cin >> mySejahteraStatus;
			if(mySejahteraStatus.length() != 1){
				cout << "Invalid Option\n";
			}else if(!isdigit(mySejahteraStatus[0])){
				cout << "Enter number only\n";
			}else{
				switch(mySejahteraStatus[0]){
					case '1':
						mySejahteraStatus = "LowRisk";
						statusValid = true;
						break;
					case '2':
						mySejahteraStatus = "CloseContact";
						statusValid = true;
						break;
					case '3':
						mySejahteraStatus = "PUS";
						statusValid = true;
						break;
					case '4':
						mySejahteraStatus = "SuspectedCase";
						statusValid = true;
						break;
					case '5':
						mySejahteraStatus = "ConfirmedCase";
						statusValid = true;
						break;
					default:
						cout << "Invalid Option\n";
						break;
				}
			}
		}while(!statusValid);

		// Vaccination
		string isVaccinated;
		do{
			cout << "Are you vaccinated? (Y/N): ";
			fflush(stdin);			// flush the input buffer
			cin >> isVaccinated;
			if(isVaccinated.length() != 1 || (toupper(isVaccinated[0]) != 'Y' && toupper(isVaccinated[0]) != 'N'))
				cout << "Invalid Option\n";
		}while(isVaccinated.length() != 1 || (toupper(isVaccinated[0]) != 'Y' && toupper(isVaccinated[0]) != 'N'));

		string vaccineDate;
		bool dateValid = false;
	    if(toupper(isVaccinated[0]) == 'Y'){
	    	do{
		        cout << "Enter vaccination date (DD/MM/YYYY): ";
		        fflush(stdin);			// flush the input buffer
		        cin >> vaccineDate;
		        if(vaccineDate.length() != 10 || (vaccineDate[2] != '/' && vaccineDate[5] != '/'))
		        	cout << "Invalid date format\n";
		        else{
        			index = 0;
					while(isdigit(vaccineDate[index]) && index < vaccineDate.length() - 1){
						if(index == 1 || index == 4)			// 2,5 is "/"
							index+=2;
						else
							index++;
					}
					if(!isdigit(vaccineDate[index]))
						cout << "Invalid date\n";
					else
						dateValid = true;
			    }
	    	}while(!dateValid);
	    }else{
	    	vaccineDate = "N/A";
	    }
	    // Assign values to userDetail array
	    userDetail[num_data].userName = userName;
	    userDetail[num_data].password = password;
	    userDetail[num_data].name = name;
	    userDetail[num_data].age = stoi(age);
	    userDetail[num_data].contactNum = contactNum;
	    userDetail[num_data].address = address;
	    userDetail[num_data].mySejahteraStatus = mySejahteraStatus;
	    userDetail[num_data].isVaccinated = toupper(isVaccinated[0]);
	    userDetail[num_data].vaccineDate = vaccineDate;
	    userDetail[num_data].category = "None";

		// Append mode
		// ios::app = append the data into the file
		ofstream out_file("users.txt", ios::app);

		// Append the data into the file
		out_file << userDetail[num_data].userName << "," << userDetail[num_data].password << "," << userDetail[num_data].name << "," 
				 << userDetail[num_data].age << "," << userDetail[num_data].contactNum << "," 
				 << userDetail[num_data].address << "," << userDetail[num_data].mySejahteraStatus << ","
				 << userDetail[num_data].isVaccinated << "," << userDetail[num_data].vaccineDate << ","
				 << userDetail[num_data].covid19Test << "," << userDetail[num_data].symptom << "," << userDetail[num_data].category << ","
 				 << userDetail[num_data].classificationDate << "," << userDetail[num_data].quarantinePeriod << endl;

		out_file.close();	// Close the output file

		// Increase the number of data
		num_data++;

		cout << "User registration successful.\n";
		cout << "Press any key to Continue.\n";
		system("pause>nul");
	}
	return num_data;
}

// Login as existing user
void user_Login(USER_DETAIL userDetail[], int num_data, string *userLogin){
	system("CLS");
	string userName, password;
	bool userExists = false;

	cout << "--------------------------------------------------------------------------------\n";
	cout << "|                                  User Login                                  |\n";
	cout << "--------------------------------------------------------------------------------\n";
	do{
		cout << "Enter username: ";
		fflush(stdin);
		getline(cin, userName);
		if(userName.length() == 1 && toupper(userName[0]) == 'Z')
			userExists = true;
		else{
			// Convert to upper case
			for(int i = 0; i < userName.length(); i++){
				userName[i] = toupper(userName[i]);
			}

			// Check if the userName has been registered
			int index = 0;
			while(userName != userDetail[index].userName && index < num_data - 1)
				index++;
			if(userName == userDetail[index].userName)
				userExists = true;

			if(!userExists){
				cout << "This userName has not been registered.\n";
				cout << "Enter \"Z\" to go back to menu.\n";
			}
		}
	}while(!userExists);

	if(userName.length() != 1 && toupper(userName[0]) != 'Z'){
		bool pwdMatch = false;
		int count = 0;
		// Check if the password is match
		do{
			cout << "Enter account password: ";
			cin >> password;

			for(int i = 0; i < num_data; i++){
				if(userName == userDetail[i].userName && password == userDetail[i].password){
					pwdMatch = true;
					*userLogin = userName;
				}
			}
			if(!pwdMatch){
				cout << "Password is incorrect\n";
				count++;
			}
		}while(!pwdMatch && count != 3);		// if password does not match 3 times, end the loop
		if(count == 3){
			cout << "Please wait a few seconds before you try again.\n";
			cout << "Press any key to Continue.\n";
			system("pause>nul");
		}
	}
}

// Read data from txt file and store in array, return number of data
int read_File(USER_DETAIL userDetail[]){
	// Open input file
	ifstream in_file("users.txt");

	int num_data = 0;
	string row, age, isVaccinated, symptom, quarantinePeriod;

	if(!in_file){
		num_data = -1;
	}else{
		// read from txt file with comma delimiter
		while(getline(in_file, row)){
			stringstream strInputStream(row);		// read string as input stream

			getline(strInputStream, userDetail[num_data].userName, ',');
			getline(strInputStream, userDetail[num_data].password, ',');
			getline(strInputStream, userDetail[num_data].name, ',');
			getline(strInputStream, age, ',');
			userDetail[num_data].age = stoi(age);									// convert age from string to integer
			getline(strInputStream, userDetail[num_data].contactNum, ',');
			getline(strInputStream, userDetail[num_data].address, ',');
			getline(strInputStream, userDetail[num_data].mySejahteraStatus, ',');
			getline(strInputStream, isVaccinated, ',');
			userDetail[num_data].isVaccinated = isVaccinated.at(0);					// Get first character
			getline(strInputStream, userDetail[num_data].vaccineDate, ',');

			getline(strInputStream, userDetail[num_data].covid19Test, ',');
			getline(strInputStream, symptom, ',');
			userDetail[num_data].symptom = symptom.at(0);							// Get first character
			getline(strInputStream, userDetail[num_data].category, ',');
			getline(strInputStream, userDetail[num_data].classificationDate, ',');
			getline(strInputStream, quarantinePeriod, ',');
			userDetail[num_data].quarantinePeriod = stoi(quarantinePeriod);			// convert quarantinePeriod from string to integer

			// Increas the number of data
			num_data++;
		}
	}

	// Close the input file
	in_file.close();

	return num_data;
}

// Save user data into txt file
void save_User_Data(USER_DETAIL userDetail[], int num_data){
	// Open the output file
	ofstream out_file("users.txt");

	// Write data to the txt file
	for(int i = 0; i < num_data; i++){
		out_file << userDetail[i].userName << "," << userDetail[i].password << "," << userDetail[i].name << "," 
				 << userDetail[i].age << "," << userDetail[i].contactNum << "," 
				 << userDetail[i].address << "," << userDetail[i].mySejahteraStatus << ","
				 << userDetail[i].isVaccinated << "," << userDetail[i].vaccineDate << ","
				 << userDetail[i].covid19Test << "," << userDetail[i].symptom << "," << userDetail[i].category << ","
 				 << userDetail[i].classificationDate << "," << userDetail[i].quarantinePeriod << endl;
	}
	// Close the output file
	out_file.close();
}

// Get the user data index in userDetail array by using username
int get_User_Data_Idx(USER_DETAIL userDetail[], int num_data, string *userLogin){
	int userDataIdx = 0;
	if(*userLogin != "NULL"){
		while(userDetail[userDataIdx].userName != *userLogin){
			userDataIdx++;
		}
	}
	return userDataIdx;
}