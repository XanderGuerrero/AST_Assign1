//FileName:		ast_assign1.cpp
//Project:		ast_assign1
//Author:		Alex Guerrero	
//Date:			January 29, 2014
//Description:	This program asks the user to input their age.  If the input is not a whole number between 1 and 100, 
//				the program prompts the user with an error message stating the type of error and instructs the user 
//				to enter the value again.  The program also logs the user error in a text file called "logError.txt",
//				in a direcotry created called "C:\\tempASTA01".  The lof file contains the type of error, time, date 
//				and file path of the log error file.

//Include files
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#include<ctype.h>
#include<limits.h>
#include<direct.h>
#include<iostream>
#include<string.h>
using namespace std;

//disables a warning to allow the use of the getNum()
#pragma warning(disable: 4996)



//Constants
#define kOutputMechanism "logError.txt"
#define kFilePath "C:\\tempASTA01"
#define kOne 1
#define kHundred 100
const char *kOutOfRange = "Input is out of range";
const char *kNotNumeric = "Input is not numeric";
const char *kNotWholeNumber = "Input is not a whole number";
const char *kNoInput = "Input cannout be blank";


//Prototypes
void logError(const char *errorMsg);
//void getFilePath(char * fileName, char *pFile);



int main()
{
	//variables for use in the program initialized
	int count = 0;
	int age = 0;
	char userInput[80] = {0};
	int exit = 0;
	int i = 0;
	
	//while loop to control flow of program
	while(kOne)
	{
		//reset exit and count parameters
		exit = 0;
		count = 0;

		while(kOne)
		{
			//This section of code prompts the user to enter their age as a whole number
			//The input is retrieved using cin.getline and stored in a buffer.
			//while the count is less than the final element, scan the input. 
			//if the input is alphabetic or not a whole number, call the log error 
			//function and note the error.  Then prompt the user of the error type,
			//set error to 1 and break out of the loop.
			cout << "Please enter your age as a whole number\n" << endl;
			cin.getline(userInput, 80);
			cout << "\n";
			while(count < userInput[count])
			{
				if(isalpha(userInput[count]) != 0)
				{
					logError(kNotNumeric);
					cout << kNotNumeric << endl;
					cout << "\n";
					exit = 1;
					break;
				}
				if(userInput[count] == '.')
				{	
					logError(kNotWholeNumber);
					cout << kNotWholeNumber << endl;
					cout << "\n";
					exit = 1;
					break;
				}
				++count;
			}

			//if exit is equal to 1, break out of the loop and restart the program
			if(exit == 1)
			{
				break;
			}

			//If the input is NULL, call the log error function and report the error,
			//inform the user of the error type and break out of the loop to restart
			//the program.
			if(userInput[0] == NULL || userInput[0] == ' ')
			{
				logError(kNoInput);
				cout << kNoInput << endl;
				cout << "\n";
				break;
			}
			//If the input is a valid integer but out of range, call the log error 
			//function and report the error, inform the user of the error type and 
			//break out of the loop to restart the program.
			age = atoi(userInput);
			if(age < kOne || age > kHundred)
			{
				logError(kOutOfRange);
				cout << kOutOfRange << endl;
				cout << "\n";
				break;
			}//If the input is a valid integer, inform the user of the valid input and 
			//exit the program.  set exit to 5 to exit the program.
			if(age >= kOne || age <= kHundred)
			{
				cout << "Thank You" << endl;
				cout << "\n";
				cout << "\n";
				exit = 5;
				break;
			}
		}

		//if exit = 5, exit the final loop to exit the program
		if(exit == 5)
		{
			break;
		}
	}
	
	return 0;
}



//FunctionName:	logError(const char *errorMsg)
//Project:		ast_assign1
//Author:		Alex Guerrero	
//Date:			January 29, 2014
//Description:	This function creates a directory to store an error log file if it does not already exist.  The program then creates
//				a log file called logError.txt if the file does not already exist and prints to the file the type of error, time, date
//				and file path of the error. Once the file has been written to, the file is closed and the function returns to the calling
//				enviroment.
void logError(const char *errorMsg)
{
	//variables initialized
	FILE *ofp = NULL;
	char dateBuf[128] = "";
	char timeBuf[128] = "";
	char filePath[200] = "";
	int exit = 0;

	//create directory, if the directory already exists continue
	if( _mkdir(kFilePath) == 0 || _mkdir(kFilePath) != 0)
	{
		//this section of code copies the file path to a string and then
		//appends the string with "\\" and the file name to create a proper
		//file name to call fopen() and create a file named logError located in 
		//"C:\tempASTA01" directory
		strcpy(filePath, kFilePath);
		strcat(filePath, "\\");
		strcat(filePath, kOutputMechanism);
		ofp = fopen(filePath, "ab+");
		//if the file was not created, infor the user.
		if(ofp == NULL)
		{
			printf("Error: File not created for writing\n");
		}
	}
	//The following section of code compares the error messages to find a match
	//and if a match is found, assign the porper exit path to log the error
	if(strcmp(errorMsg, "Input is not a whole number") == 0)
	{
		exit = 4;
	}
	if(strcmp(errorMsg, "Input is out of range") == 0)
	{
		exit = 3;
	}
	if(strcmp(errorMsg, "Input cannout be blank") == 0)
	{
		exit = 2;
	}
	if(strcmp(errorMsg, "Input is not numeric") == 0)
	{
		exit = 1;
	}

	//This section of code uses the exit value to enter into a switch statement to
	//determine the proper error message to log and write to logError.txt
	//The error message, time, date and file path are all recorded and the file pointer contents are flushed.
	//the file pointer is then closed and the case is exited and control is passed back 
	//to the calling enviroment. If the file does not close, the user is informed through a printf call.
	switch(exit)
	{
		case 1: _strtime( timeBuf );	
				_strdate( dateBuf );
				fprintf(ofp,"ERROR:[%s] TIME:[%s] DATE:[%s] FILE PATH:[%s] %s", kOutOfRange, timeBuf, dateBuf, kFilePath, "\r\n");
				fflush(ofp);
				if( fclose(ofp) != 0 ) 
				{
					printf("close failed\n");
				}
				break;
		case 2: _strtime( timeBuf );	
				_strdate( dateBuf );
				fprintf(ofp,"ERROR:[%s] TIME:[%s] DATE:[%s] FILE PATH:[%s] %s", kNoInput, timeBuf, dateBuf, kFilePath, "\r\n");	
				fflush(ofp);
				if( fclose(ofp) != 0 ) 
				{
					printf("close failed\n");
				}
				break;
		case 3: _strtime( timeBuf );	
				_strdate( dateBuf );
				fprintf(ofp,"ERROR:[%s] TIME:[%s] DATE:[%s] FILE PATH:[%s] %s", kOutOfRange, timeBuf, dateBuf, kFilePath, "\r\n");
				fflush(ofp);
				if( fclose(ofp) != 0 ) 
				{
					printf("close failed\n");
				}
				break;	
		case 4: _strtime( timeBuf );	
				_strdate( dateBuf );
				fprintf(ofp,"ERROR:[%s] TIME:[%s] DATE:[%s] FILE PATH:[%s] %s", kNotWholeNumber, timeBuf, dateBuf, kFilePath, "\r\n");	
				
				fflush(ofp);
				if( fclose(ofp) != 0 ) 
				{
					printf("close failed\n");
				}
				break;
	}
}




