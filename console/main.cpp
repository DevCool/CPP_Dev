#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
using namespace std;

bool running = true;

bool some_stuff ( char *text );

int main ( int argc, char **argv ) {

	cout << "Welcome to a console.." << endl;

	char input[256];

	while ( running ) {
		cout << "Input : ";
		cin.getline ( input, sizeof (input), '\n' );
		bool res = some_stuff ( input );
		running = res;
	}

	return 0;

}

bool some_stuff ( char *text ) {

	char *pch[10];
	int i = 0;

	if ( ( pch [i] = strtok ( text, " " ) ) == NULL ) {
		cout << "You need to enter something..." << endl;
	}

	i++;

	while (( pch [i] = strtok ( NULL, " " ) )) i++;

	if ( pch [1] && strcmp ( pch [0], "exit" ) == 0 ) {
		if ( strcmp ( pch[1], "true" ) == 0 ) {
			cout << "Quiting              " << flush;
			for ( int i = 0; i<2; i++ ) { cout << "." << flush; sleep ( 1 ); }
			cout << " [SUCCESS]" << endl;
		}
		else if ( strcmp ( pch [1], "false" ) == 0 ) {
			cout << "Quiting              " << flush;
			for ( int i = 0; i<2; i++ ) { cout << "." << flush; sleep ( 1 ); }
			cout << " [FAILED]" << endl;
			return true;
		}
		return false;
	}
	else if ( strcmp ( pch [0], "exit" ) == 0 ) {
		cout << "Usage: exit [true/false]" << endl;
		return true;
	}
	else if ( strcmp ( pch [0], "help" ) == 0 ) {
		cout << "\nCommands:" << endl <<
			"  help - You're looking at it." << endl <<
			"  exit - Quit the console." << endl << endl;
	}
	else if ( pch[1] && strcmp ( pch [0], "enc" ) == 0 ) {
		char tmp[256];
		if ( strcmp ( pch[1], "block" ) == 0 ) { cout << endl << "  Enter block of text to encrypt:" << endl << endl; cin.getline (tmp, sizeof(tmp), '\n'); }
		else { memcpy ( tmp, pch [1], sizeof (tmp) ); }
		char byte, bit;

		cout << "Original String: " << tmp << endl;

		for ( unsigned int j = 0; j < sizeof (tmp); j++ ) {
			byte = tmp[j];
			bit = byte>>7;
			byte = (byte<<1)|(bit);
			tmp[j] = byte;
		}

		cout << "Encrypted String: " << tmp << endl;

		FILE *myFile;
		myFile = fopen("enc.txt", "w+b");
		fprintf(myFile, "%s", tmp);
		fclose(myFile);
	}
	else if ( strcmp ( pch [0], "enc" ) == 0 ) {
		cout << "Usage: enc [passcode|block]" << endl;
	}
	else if ( pch[1] && strcmp ( pch [0], "dec" ) == 0 ) {
		char tmp[256];
		if ( strcmp ( pch[1], "block" ) == 0 ) { cout << endl << "  Enter block of text to encrypt:" << endl << endl; cin.getline (tmp, sizeof(tmp), '\n'); }
		else { memcpy ( tmp, pch [1], sizeof (tmp) ); }
		char byte, bit;

		cout << "Original String: " << tmp << endl;

		for ( unsigned int j = 0; j < sizeof (tmp); j++ ) {
			byte = tmp[j];
			bit = byte&1;
			byte = (bit<<7)|(byte>>1);
			tmp[j] = byte;
		}

		cout << "Decrypted String: " << tmp << endl;

		FILE *myFile;
		myFile = fopen("dec.txt", "w+b");
		fprintf(myFile, "%s", tmp);
		fclose(myFile);
	}
	else if ( strcmp ( pch [0], "dec" ) == 0 ) {
		cout << "Usage: dec [passcode|block]" << endl;
	}
	else {
		cout << "You need to enter a command.\n" << flush;
	}

	return true;

}

