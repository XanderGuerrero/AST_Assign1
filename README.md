# AST_Assign1
Advanced Software Techniques - Assignment 1: Creating directories, error logs, validating input

Advanced Software Techniques
Assignment 01 – Advanced Debugging
Individual submission
Introduction
Well-designed applications should never “crash”; they should deal with exception or error scenarios in a
clean and controlled manner. However, there are times when these exception conditions (even in
production) should be noted and reviewed by the development team. A “logger” is often used to record
key data when a problem occurs in your code. In the Windows environment, the Event Log is an
example of a repository for logged information. Often, a simple text file can be used as well.
In this assignment, you will be implementing a simple logging facility.
Requirements
Here are the requirements for error logging:
- A function called LogError must write an error message to a text file, to the debug console, or to
the program console. This message must contain the following information:
o Date and time of occurrence
o Error message (passed to the function as a parameter)
- Use #define statements to identify:
o The output mechanism for the errors (text file, debug console or program console)
o The file path for the text file for the error log
- Use conditional compile statements in the LogError function to determine where the error
message output should go
Write a test program that demonstrates the use of the LogError function. Initially, write a program that
does the following WITHOUT the error logging:
- Ask for the user’s age
- If the input is non-numeric, you should give the user a friendly message stating that the input is
non-numeric
- If the input is null (empty string), you should give the user a friendly message stating that the
input cannot be blank
- If the input is less than 1 or greater than 110, you should give the user a friendly message stating
that the input is out of range
- If the age is valid (positive integer), simply say “Thank You” and end the program
- If there is any error in the age, the age should be asked for again
Once the program works, add error logging function calls in appropriate places to record where users
make errors.
Please submit your solution to the D2L dropbox in a zipped folder. To minimize the size of the file, make
sure you delete any files with an .sdf extension and any folder that is named either Debug or Release.
