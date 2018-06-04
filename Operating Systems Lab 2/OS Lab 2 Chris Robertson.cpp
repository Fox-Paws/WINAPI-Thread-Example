/*
Chris Robertson
Student ID: 001174618
Operating Systems Lab 2
2-21-18
*/

#include <windows.h>
#include <stdio.h>

DWORD output;
//Global variable so it is shared by threads

DWORD WINAPI Factorial(LPVOID Param)
{
	DWORD Upper = *(DWORD*)Param;
	output = Upper;

	// start from the given value and go down to 1
	for (DWORD i = Upper - 1; i > 0; i--)
	{
		// definition of factorial; input multiplied by all previous integers to 1
		output *= i;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	DWORD ThreadId;
	HANDLE ThreadHandle;
	int Param;

	// standard error checking
	if (argc != 2)
	{
		fprintf(stderr, "An integer parameter is required\n");
		return -1;
	}
	Param = atoi(argv[1]);
	if (Param < 0)
	{
		fprintf(stderr, "An integer >= 0 is required\n");
		return -1;
	}

	ThreadHandle = CreateThread(
		NULL,		// default security attributes
		0,			// default stack size
		Factorial,	// thread function as described above
		&Param,		// parameter to thread function
		0,			// default creation flags
		&ThreadId);	//returns the thread identifier

	if (ThreadHandle != NULL)
	{
		// waiting for thread to return for an indefinite amount of time
		WaitForSingleObject(ThreadHandle, INFINITE);

		// close the thread handle
		CloseHandle(ThreadHandle);

		printf("Factorial of input: %d\n", output);
	}

	// system command is required on my system to display "Press any key to continue..."
	system("pause");
	return 0;
}