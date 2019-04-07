#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

#define KONIEC -1

using namespace std;

struct zadanie
{
	int numer;
	int priorytet;
	int pozostalo;
};

class Procesor {
private:
	int S, L, K;
	int Time;
	unsigned int AktualnyProces;
	bool Koniec;
	vector<zadanie> Zadania;

	bool ProcesJuzIstnieje(int nr) {
		for (unsigned int i = 0; i < Zadania.size(); i++) {
			if (Zadania[i].numer == nr) return true;
		}
		return false;
	}

	void WczytajZadania() {
		string linia;
		stringstream ss;
		int time, nr, pr, czas;
		zadanie temp;


		if (cin.eof()) return;
		getline(cin, linia);
		ss << linia;
		ss >> time;
		if (time != Time) return;
		while (true) {
			
			ss >> nr >> pr >> czas;

			if ( (nr>0) && (pr>=0) && (czas>0)) { // jesli poprawne zadanie
				if (ProcesJuzIstnieje(nr)) {
					break;
				}
				temp.numer = nr;
				temp.priorytet = pr;
				temp.pozostalo = czas;
				Zadania.push_back(temp);
			}
			else {
				break;
			}
		}
		
	}

	void AddTime() {
		Time++;
	}

	void FCFS() {

		if (AktualnyProces < Zadania.size()) {

			cout << Time << ": " << Zadania[AktualnyProces].numer << endl;

			if (Zadania[AktualnyProces].pozostalo==1) {
				Zadania[AktualnyProces].pozostalo--;
				AktualnyProces++;
			} else {
				Zadania[AktualnyProces].pozostalo--;
			}
			
		} else {
			cout << Time << ": " << KONIEC << endl;
			Koniec = true;
		}

	}

	void RR() {
		if (Zadania.size() < 1) {
			cout << Time << ": " << KONIEC << endl;
			Koniec = true;
		}
		else {

			if (AktualnyProces >= Zadania.size()) {
				AktualnyProces = 0;
			}

			cout << "Liczba zadan: " << Zadania.size() << ", aktu_proces: " << AktualnyProces << endl;
			cout << Time << ": " << Zadania[AktualnyProces].numer << endl;

			if (Zadania[AktualnyProces].pozostalo == 1) {
				Zadania.erase(Zadania.begin() + AktualnyProces);
			}
			else {
				Zadania[AktualnyProces].pozostalo--;
			}
			AktualnyProces++;
		}
	}

	void PFCFS() {

	}
public:
	Procesor(int a, int b, int c) {
		S = a;
		L = b;
		K = c;
		Time = 0;
		Koniec = false;
		AktualnyProces = 0;
	}

	void Work() {
		do {
			WczytajZadania();

			if (S == 0)	FCFS();
			if (S == 3)	RR();
			if (S == 4)	PFCFS();

			AddTime();
		} while (!Koniec);


	}
	
};


int main(int argc, char *argv[])
{
	int Strategia, LiczbaProc, KwantCzasu;

	// obsluga argumentow funkcji main
	if (argc < 2) {
		cout << "Sposob uzycia: ./" << argv[0] << " KodStrategiiSzeregowania LiczbaProcesorow DlugoscKwantuCzasu" << endl;
		exit(-1);
	}
	Strategia = atoi(argv[1]);
	if (argc > 1) LiczbaProc = atoi(argv[2]); else LiczbaProc = 1;
	if (argc > 2) KwantCzasu = atoi(argv[3]); else KwantCzasu = 1;

	if (!(Strategia == 3 || Strategia == 0 || Strategia == 4)) {
		cout << "Ta strategia nie jest obslugiwana" << endl;
		exit(-1);
	}

	Procesor proc(Strategia, LiczbaProc, KwantCzasu);
	
	proc.Work();
	
    return 0;
}

