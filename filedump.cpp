#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

using namespace std;

int addressTracker;
int bytesToComplete, bytesCompleted;
char *bufferPointer;

const char *byteToBinary(int x) {
    static char binaryString[9];
    binaryString[0] = '\0';
    int z;    
    for (z = 128; z > 0; z >>= 1) {
        if ((x & z) == z) {
            strcat(binaryString, "1"); 
        }
        else {
            strcat(binaryString, "0");
        }
    }
    return binaryString;
}

void binaryOut (FILE *inFile) {
    
    char buffer[8];
    while ((bytesToComplete = fread(buffer, sizeof(unsigned char), 6, inFile)) > 0) {
        
        printf("%08x: ", addressTracker);
        addressTracker += 6;
        
        bufferPointer = buffer;
        bytesCompleted = 0;
        int i;
        for (i = 0; i < 6; i++) {
            
            if (bytesCompleted <= bytesToComplete) {
                printf("%s", byteToBinary(*bufferPointer++));
            }
            else {
                cout << "        ";
            }
            bytesCompleted += 1;
            cout << " ";
        }
        
        bytesCompleted = 0;
        int j;
        for (j = 0; j < 6; j++) {
            bytesCompleted++;
            if (bytesCompleted <= bytesToComplete) {
                if ((buffer[j] < 32 || buffer[j] > 126)) {
                    cout << ".";
                }
                else {
                    printf("%c", buffer[j]);
                }
            }
        }
        cout << endl;
    }
}

void hexOut (FILE *inFile){
    
    char buffer[16];
    while ((bytesToComplete = fread(buffer, sizeof(unsigned char), 16, inFile)) > 0) {

        printf("%08x: ", addressTracker);
        addressTracker += 16;

        bufferPointer = buffer;
        bytesCompleted = 0;
        int i;
        for (i = 0; i < 8; i++) {
            if (bytesCompleted <= bytesToComplete) {            
                printf("%02x%02x ", *bufferPointer++, *bufferPointer++);
            }
            else {
                cout << "     ";
            }
            bytesCompleted += 2;
            cout << " ";
        }

        bytesCompleted = 0;
        int j;
        for (j = 0; j < 16; j++) {
            bytesCompleted++;
            if (bytesCompleted <= bytesToComplete) {
                if ((buffer[j] < 32 || buffer[j] > 126)) {
                    cout << ".";
                }
                else {
                    printf("%c", buffer[j]);
                }
            }
        }
        cout << endl;
    }
}

int main (int argc, char **argv) {

    bool binaryOutputDesired;
    FILE *inFile;

	if (argc == 2)  {
        binaryOutputDesired = false;
		inFile = fopen(argv[1], "r");
        if (inFile == NULL) {
            cerr << "Unable to open file, 2 args" << endl;
            exit(-1);
        }
        cout << "Opened Hex output mode" << endl;
	}
    else if (argc == 3 && (strcmp(argv[1], "-b") == 0)) {
        binaryOutputDesired = true;
        inFile = fopen(argv[2], "r");
        if (inFile == NULL) {
            cerr << "Unable to open file, 3 args" << endl;
            exit(-1);
        }
        cout << "Opened Binary output mode" << endl;
    }
    else {
        cerr << "Incorrect runtime parameters" << endl;
        exit(-1);
    }
    
    if (binaryOutputDesired) {
        binaryOut(inFile);
    }
    else {
        hexOut(inFile);
    }
    fclose(inFile);
    return 0;
}
