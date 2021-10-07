#include <iostream>
using namespace std;

class Graf {
public:
	static int velicina;
	int** a = nullptr;
	int n = -1;
	~Graf() {
		brisi_graf();
	}
	void brisi_graf(int bris = 0) {
		if (n == -1 || a == nullptr) {
			cout << "Pokusavate da obrisete graf koji ne postoji!" << endl << "Morate prvo napraviti graf opcijom 1 da biste ga obrisali!" << endl;
		}
		else {
			for (int i = 0;i < n;i++) {
				delete[] a[i];
			}
			delete[] a;
			a = nullptr;
			n = -1;
			if (bris == 1) {
				cout << "Uspesno ste obrisali graf!" << endl;
			}
		}
	}
	void kreiraj_graf() {
		cout << "Ucitajte dimenziju grafa:" << endl;
		//Ukoliko dva puta zaredom pritisnemo kreiraj_graf doci ce do curenja memorije, pa brisem graf pre neko sto napravim novi ako postoji!
		if (n != -1) {
			brisi_graf();
		}
		cin >> n;

		while (n < 1) {
			cout << "Morate uneti n vece od 0! Pokusajte ponovo!" << endl;
			cin >> n;
		}
		velicina = n;
		a = new int* [n];
		for (int i = 0;i < n;i++) {
			a[i] = new int[n] {0};
		}
		cout << endl;
		cout << "Graf je uspesno napravljen!";
		cout << endl;
	}
	void dodaj_cvor() {
		if (n == -1 || a == nullptr) {
			cout << "Pokusavate da dodate cvor u graf koji ne postoji!" << endl << "Morate ga prvo napraviti opcijom 1!" << endl;
		}
		else {
			if (n >= velicina) {
				velicina += n;
				int** pom = a;
				a = nullptr;
				n++;
				a = new int* [velicina];
				for (int i = 0;i < velicina;i++) {
					a[i] = new int[velicina] {0};
				}
				for (int i = 0; i < n - 1; i++)
					for (int j = 0; j < n - 1; j++) {
						a[i][j] = pom[i][j];
					}
				int m = n - 1;
				Graf pomoo;
				pomoo.n = m;
				pomoo.a = pom;
				pom = nullptr;
			}
			else {
				n++;
			}
			cout << "Novi cvor je uspesno dodat sa rednim brojem " << n << "" << endl;
		}
	}
	void ukloni_cvor() {
		if (n == -1 || a == nullptr) {
			cout << "Pokusavate da izbrisete cvor iz grafa koji ne postoji!" << endl << "Morate ga prvo napraviti opcijom 1!" << endl;
		}
		else {
			cout << "Unesite broj cvora koji zelite da uklonite!:" << endl;
			int broj;
			cin >> broj;
			while ((broj < 1) || (broj > n)) {
				cout << "Uneli ste nepostojeci broj za cvor! Pokusajte ponovo. Moguci brojevi su od 1-" << n << endl;
				cin >> broj;
			}
			broj--;
			int** pom = a;
			a = nullptr;
			n--;
			a = new int* [n];
			for (int i = 0;i < n;i++) {
				a[i] = new int[n] {0};
			}
			for (int i = 0; i < n + 1; i++)
				for (int j = 0; j < n + 1; j++) {
					if (i != broj && j != broj) {
						if (i > broj)
							if (j > broj)
								a[i - 1][j - 1] = pom[i][j];
							else
								a[i - 1][j] = pom[i][j];
						else
							if (j > broj)
								a[i][j - 1] = pom[i][j];
							else
								a[i][j] = pom[i][j];
					}
				}
			int m = n + 1;
			Graf pomoo;
			pomoo.n = m;
			pomoo.a = pom;
			velicina = n;
			cout << "Cvor broj " << broj + 1 << " je obrisan iz grafa!" << endl;
		}
	}
	void dodaj_granu() {
		if (n == -1 || a == nullptr) {
			cout << "Pokusavate da dodate granu u graf koji ne postoji!" << endl << "Morate ga prvo napraviti opcijom 1!" << endl;
		}
		else {
			int prvi_cvor, drugi_cvor;
			cout << "Unesite redni broj prvog cvora grane:" << endl;
			cin >> prvi_cvor;
			while ((prvi_cvor < 1) || (prvi_cvor > n)) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> prvi_cvor;
			}
			cout << "Unesite redni broj drugog cvora grane:" << endl;
			cin >> drugi_cvor;
			while (drugi_cvor < 1 || drugi_cvor > n) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> drugi_cvor;
			}
			int tezina;
			cout << "Unesite tezinu zadate grane[1 u slucaju netezinskog grafa:]" << endl;
			cin >> tezina;

			a[prvi_cvor - 1][drugi_cvor - 1] = tezina;
			a[drugi_cvor - 1][prvi_cvor - 1] = tezina;
			cout << endl << "Grana izmedju cvorova " << prvi_cvor << " i " << drugi_cvor << " je uspesno dodata u graf!" << endl;
		}
	}
	void ukloni_granu() {
		if (n == -1 || a == nullptr) {
			cout << "Pokusavate da uklonite granu u grafu koji ne postoji!" << endl << "Morate ga prvo napraviti opcijom 1!" << endl;
		}
		else {
			int prvi_cvor, drugi_cvor;
			cout << "Unesite redni broj prvog cvora grane koju zelite da obrisete:" << endl;
			cin >> prvi_cvor;
			while ((prvi_cvor < 1) || (prvi_cvor > n)) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> prvi_cvor;
			}
			cout << "Unesite redni broj drugog cvora grane koju zelite da obrisete:" << endl;
			cin >> drugi_cvor;
			while (drugi_cvor < 1 || drugi_cvor > n) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> drugi_cvor;
			}
			if (a[prvi_cvor - 1][drugi_cvor - 1] != 0) {
				a[prvi_cvor - 1][drugi_cvor - 1] = 0;
				a[drugi_cvor - 1][prvi_cvor - 1] = 0;
				cout << endl << "Grana izmedju cvorova " << prvi_cvor << " i " << drugi_cvor << " je uspesno obrisana iz grafa!" << endl;
			}
			else
				cout << endl << "Grana izmedju cvorova " << prvi_cvor << " i " << drugi_cvor << " ni ne postoji u grafu!" << endl;
		}
	}
	void ispisi_graf() {
		if (a == nullptr || n == (-1)) {
			cout << "Pokusavate da ispisete graf koji ne postoji!" << endl << "Morate prvo napraviti graf opcijom 1 da biste ga ispisali!" << endl;
		}
		else {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					cout << " " << a[i][j] << " ";
				}
				cout << endl;
			}
		}
	}
};
int Graf::velicina = 0;
int main() {
	cout << "ZADATAK 1- IMPLEMENTACIJA OSNOVNIH ALGORITAMA ZA RAD SA GRAFOM KORISCENJEM MATRICNE REPREZENTACIJE -" << endl << "- Zarko Babic 0044/2019 -" << endl << endl;
	Graf gr;
	int izbor;
	while (1) {
		cout << endl;
		cout << "Izaberite operaciju brojevima (1-8):" << endl;
		cout << "1. Kreiranje prazne strukture podataka za graf zadatih dimenzija" << endl;
		cout << "2. Dodavanje cvora u graf" << endl;
		cout << "3. Uklanjanje cvora iz grafa" << endl;
		cout << "4. Dodavanje grane izmedju dva cvora u grafu" << endl;
		cout << "5. Uklanjanje grane izmedju dva cvora u grafu" << endl;
		cout << "6. Ispis reprezentacije grafa" << endl;
		cout << "7. Brisanje grafa iz memorije" << endl;
		cout << "8. Kraj programa" << endl << endl;

		cin >> izbor;

		switch (izbor) {
		case 1:
			gr.kreiraj_graf();
			break;
		case 2:
			gr.dodaj_cvor();
			break;
		case 3:
			gr.ukloni_cvor();
			break;
		case 4:
			gr.dodaj_granu();
			break;
		case 5:
			gr.ukloni_granu();
			break;
		case 6:
			gr.ispisi_graf();
			break;
		case 7:
			gr.brisi_graf(1);
			break;
		case 8:
			exit(0);
			break;
		default:
			cout << "Uneli ste nepostojeci karakter! Pokusajte ponovo." << endl;
			//ukoliko se ne unese broj ovo resava problem sa beskonacnom petljom(ciscenje bafera)
			cin.clear();
			cin.ignore(1000, '\n');
		}

	}
	return 0;
}