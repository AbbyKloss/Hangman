// Author - Abby Kloss

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

vector<string> file_to_vec(string filename);
string generate_word();
void output_man(int total_lives, int current_lives, string attempts);

int main(int argc, char *argv[]){
	bool kill = 0;
	char quit;
	while (!kill) {
		string spaces = "";
		string attempts = "";
		size_t found_in_word = string::npos;
		size_t found_in_spaces = string::npos;
		size_t found_in_attempts = string::npos;
		int points = 0;
		string alpha = generate_word();
		for (int i = 0; i < alpha.length()-1; i++) {
	    spaces.append("_ ");
	  }
		int total_lives;
		if (argv[1] == 0) total_lives = 6;
		else total_lives = stoi(string(argv[1]));
		int current_lives = 0;
		char guess;

		while ((current_lives < total_lives) and (points < alpha.length()-1)) {
			cout << spaces << endl;
			output_man(total_lives, current_lives, attempts);
			cout << "Enter a character: ";
			cin >> guess;
			if ((!isalpha(guess)) || (guess == 0)) cout << "Please enter a character" << endl;
			else {
				found_in_word = alpha.find(toupper(guess));
				found_in_spaces = spaces.find(toupper(guess));
				found_in_attempts = attempts.find(toupper(guess));
				if ((found_in_word != string::npos) and (found_in_spaces == string::npos)) {
					for (int i = 0; i < alpha.length(); i++) {
						if (alpha[i] == toupper(guess)) {
							spaces[2*i] = alpha[i];
							points++;
						}
					}
				}
				else if ((found_in_attempts == string::npos) & (found_in_spaces == string::npos) & (found_in_word == string::npos)){
					current_lives++;
					attempts.push_back(toupper(guess));
				}
			}
		}
		if (points == alpha.length()-1){
			cout << "                                 _       " << endl;
			cout << "                                | |      " << endl;
			cout << "  ___ ___  _ __   __ _ _ __ __ _| |_ ___ " << endl;
			cout << " / __/ _ \\| '_ \\ / _` | '__/ _` | __/ __|" << endl;
			cout << "| (_| (_) | | | | (_| | | | (_| | |_\\__ \\" << endl;
			cout << " \\___\\___/|_| |_|\\__, |_|  \\__,_|\\__|___/" << endl;
			cout << "                   __/ |" << endl;
			cout << "                  |___/                   " << endl;
		}
		else {
			output_man(total_lives, current_lives, attempts);
			cout << "The word was: " << alpha << endl;
		}
		cout << "Would you like to play again? (y/n): ";
		cin >> quit;
		if (toupper(quit) == 'N') kill = 1;
	}
}

vector<string> file_to_vec(string filename){
	if (filename == "") filename = "words_alpha.txt";
	ifstream wordsfile (filename);
	vector<string> filevec;
	string line;
	if (wordsfile.is_open()){
		while (getline(wordsfile, line)){ // if a newline exists, we slap one on here
			filevec.push_back(line);                   // note: doesn't add a newline to the final line
			//lineloops++;
		}
	}
	else {
		cout << "Can't find words_alpha.txt." << endl;
		filevec.push_back("DEFAULT\n");
		return filevec;
	}
	return filevec;
}

string generate_word(){
	auto now = chrono::high_resolution_clock::now();
	auto timeMillis = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
	srand(timeMillis);
	string alpha;
	vector<string> stupid = file_to_vec("");
	if (stupid[0] == "DEFAULT\n"){
		alpha = stupid[0];
		return alpha;
	}
	else {
	  alpha = stupid[rand() % 37013];
	  for (int i = 0; i < alpha.length(); i++)
			alpha[i] = toupper(alpha[i]);
		return alpha;
	}
}

void output_man(int total_lives, int current_lives, string attempts){
	int actual_lives = total_lives - current_lives;
	int percentage = (float(actual_lives)/float(total_lives))*100;
	string health;
	for (int i = 0; i < total_lives; i++){
		if (current_lives > i) health.append("¤ ");
		else health.append("♥ ");
	}
	cout << "%" << percentage << endl;
	if (percentage == 100){
		cout << "    +------+" << "    " << health << "\n    |   |\n" << "        |\n" << "        |\n" << "        |\n" << "        |\n" << "    =========    attempts: " << attempts << endl;
	}
	else if (percentage >= 83){
		cout << "    +------+" << "    " << health << "\n    |   |\n" << "    o   |\n" << "        |\n" << "        |\n" << "        |\n" << "    =========    attempts: " << attempts << endl;
	}
	else if (percentage >= 66){
		cout << "    +------+" << "    " << health << "\n    |   |\n" << "    o   |\n" << "    |   |\n" << "        |\n" << "        |\n" << "    =========    attempts: " << attempts << endl;
	}
	else if (percentage >= 50){
		cout << "    +------+" << "    " << health << "\n    |   |\n" << "    o   |\n" << "   /|   |\n" << "        |\n" << "        |\n" << "    =========    attempts: " << attempts << endl;
	}
	else if (percentage >= 33){
		cout << "    +------+" << "    " << health << "\n    |   |\n" << "    o   |\n" << "   /|\\  |\n" << "        |\n" << "        |\n" << "    =========    attempts: " << attempts << endl;
	}
	else if (percentage >= 16){
		cout << "    +------+" << "    " << health << "\n    |   |\n" << "    o   |\n" << "   /|\\  |\n" << "   /    |\n" << "        |\n" << "    =========    attempts: " << attempts << endl;
	}
	else{
		cout << "    +------+" << "    " << health << "\n    |   |\n" << "    o   |\n" << "   /|\\  |\n" << "   / \\  |\n" << "        |\n" << "    =========    attempts: " << attempts << endl;
	}
}
