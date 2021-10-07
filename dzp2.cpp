#include <iostream>
#include <limits>
using namespace std;
struct cvor {
	cvor* next;
	int info;
};
struct Grana {
	int p; //prvi cvor grane
	int d; //drugi cvor grane
};
struct Cvred {
	Grana info;
	Cvred* next;
	int tezina;
}; //jedan cvor ulancane liste reda
struct Put {
	int info;
	int tip; // 1 moze se napraviti, 2 vec postoji
};
struct Lokacijaa_cvor {
	int info;
	int pretposlednji;
	int nepostojeci = 0;
	Lokacijaa_cvor* next = nullptr;
};
//Sortiran skup
class Skup {
public:
	cvor* head = nullptr;
	cvor* tail = nullptr;
	void dodaj(int br)
	{
		cvor* novi = new cvor;
		novi->info = br;
		novi->next = nullptr;

		if (head == nullptr) {
			head = novi;
			tail = novi;
		}
		else {
			cvor* pom = head;
			while (pom) {
				if (pom->info < novi->info) {
					if (pom == tail) {
						pom->next = novi;
						tail = novi;
						break;
					}
					else
						pom = pom->next;
				}
				else if (pom->info == novi->info) break;
				else {

					int pomm = novi->info;
					novi->info = pom->info;
					pom->info = pomm;

					novi->next = pom->next;
					pom->next = novi;
					if (novi->next == nullptr) tail = novi;
					break;
				}
			}
		}
	}
	~Skup() {
		cvor* pom;
		pom = head;
		while (head) {
			head = head->next;
			delete pom;
			pom = head;
		}
		head = nullptr;
		tail = nullptr;

	}
	void citaj() {
		cvor* pomi = head;
		while (pomi) {
			cout << " " << pomi->info << " ";
			pomi = pomi->next;
		}
	}
	friend Skup* operator+(Skup& s1, Skup& s2) {
		Skup* s3 = new Skup;
		cvor* k = s1.head;
		cvor* p = s2.head;

		while (p != nullptr && k != nullptr) {
			cvor* novi = new cvor;
			novi->next = nullptr;

			if (k->info > p->info) {
				novi->info = p->info;
				p = p->next;
			}
			else if (k->info == p->info)
			{
				novi->info = p->info;
				k = k->next;
				p = p->next;
			}
			else {
				novi->info = k->info;
				k = k->next;
			}


			if (s3->head == nullptr) {
				s3->head = novi;
				s3->tail = novi;
			}
			else {
				s3->tail->next = novi;
				s3->tail = novi;
			}
		}
		if (p != nullptr) {
			while (p) {
				cvor* novi = new cvor;
				novi->next = nullptr;
				novi->info = p->info;

				if (s3->head == nullptr) {
					s3->head = novi;
					s3->tail = novi;
				}
				else {
					s3->tail->next = novi;
					s3->tail = novi;
				}
				p = p->next;
			}
		}
		if (k != nullptr) {
			while (k) {
				cvor* novi = new cvor;
				novi->next = nullptr;
				novi->info = k->info;

				if (s3->head == nullptr) {
					s3->head = novi;
					s3->tail = novi;
				}
				else {
					s3->tail->next = novi;
					s3->tail = novi;
				}
				k = k->next;
			}
		}
		s1.~Skup();
		s2.~Skup();
		return s3;
	}
	friend bool operator!=(Skup& s1, Skup& s2) {
		if (s1.head == s2.head) return false;
		else return true;
	}
	bool pripadnost(int el) {
		cvor* pom = head;
		while (pom) {
			if (pom->info == el)
				return true;
			pom = pom->next;
		}
		return false;
	}
};
//Multiskup grana
class Skup_gr {
public:
	Cvred* head = nullptr;
	Cvred* tail = nullptr;
	void dodaj(int p, int d, int tezina)
	{
		Cvred* novi = new Cvred;
		novi->tezina = tezina;
		novi->info.d = d;
		novi->info.p = p;
		novi->next = nullptr;

		if (head == nullptr) {
			head = novi;
			tail = novi;
		}
		else {
			Cvred* pom = head;
			while (pom) {
				if (pom->tezina < novi->tezina) {
					if (pom == tail) {
						pom->next = novi;
						tail = novi;
						break;
					}
					else
						pom = pom->next;
				}
				else {

					/*int pomm = novi->info;
					novi->info = pom->info;
					pom->info = pomm;*/
					Cvred pomm;
					pomm.info.d = novi->info.d;
					pomm.info.p = novi->info.p;
					pomm.tezina = novi->tezina;
					novi->info.d = pom->info.d;
					novi->info.p = pom->info.p;
					novi->tezina = pom->tezina;
					pom->info.d = pomm.info.d;
					pom->info.p = pomm.info.p;
					pom->tezina = pomm.tezina;

					novi->next = pom->next;
					pom->next = novi;
					if (novi->next == nullptr) tail = novi;
					break;
				}
			}
		}
	}
	~Skup_gr() {
		Cvred* pom;
		pom = head;
		while (head) {
			head = head->next;
			delete pom;
			pom = head;
		}
		head = nullptr;

	}
	void citaj() {
		Cvred* pomi = head;
		while (pomi) {
			cout << " " << pomi->tezina << " (" << pomi->info.p << "," << pomi->info.d << ") ";
			pomi = pomi->next;
		}
	}
	friend Skup_gr* operator+(Skup_gr& s1, Skup_gr& s2) {
		Skup_gr* s3 = new Skup_gr;
		Cvred* k = s1.head;
		Cvred* p = s2.head;
		if (k == nullptr) {
			s1.~Skup_gr();
			return &s2;
		}
		if (p == nullptr) {
			s2.~Skup_gr();
			return &s1;
		}
		while (p != nullptr && k != nullptr) {
			Cvred* novi = new Cvred;
			novi->next = nullptr;

			if (k->tezina >= p->tezina) {
				novi->info.d = p->info.d;
				novi->info.p = p->info.p;
				novi->tezina = p->tezina;
				p = p->next;
			}
			else {
				novi->info.d = k->info.d;
				novi->info.p = k->info.p;
				novi->tezina = k->tezina;
				k = k->next;
			}


			if (s3->head == nullptr) {
				s3->head = novi;
				s3->tail = novi;
			}
			else {
				s3->tail->next = novi;
				s3->tail = novi;
			}
		}
		if (p != nullptr) {
			while (p) {
				Cvred* novi = new Cvred;
				novi->next = nullptr;
				novi->info.d = p->info.d;
				novi->info.p = p->info.p;
				novi->tezina = p->tezina;

				if (s3->head == nullptr) {
					s3->head = novi;
					s3->tail = novi;
				}
				else {
					s3->tail->next = novi;
					s3->tail = novi;
				}
				p = p->next;
			}
		}
		if (k != nullptr) {
			while (k) {
				Cvred* novi = new Cvred;
				novi->next = nullptr;
				novi->info.d = k->info.d;
				novi->info.p = k->info.p;
				novi->tezina = k->tezina;

				if (s3->head == nullptr) {
					s3->head = novi;
					s3->tail = novi;
				}
				else {
					s3->tail->next = novi;
					s3->tail = novi;
				}
				k = k->next;
			}
		}
		s1.~Skup_gr();
		s2.~Skup_gr();
		return s3;
	}
};
// Prioritetni red
class Red {
public:
	Cvred* head = nullptr;
	Cvred* rear = nullptr;
	void dodaj(int prvi, int drugi, int tezinaa) {
		Cvred* novi = new Cvred;
		novi->info.d = drugi;
		novi->info.p = prvi;
		novi->next = nullptr;
		novi->tezina = tezinaa;


		if (head == nullptr) {
			head = novi;
			rear = novi;
		}
		else {
			Cvred* pom = head;
			while (pom) {
				if (pom->tezina < novi->tezina) {
					if (pom == rear) {
						pom->next = novi;
						rear = novi;
						break;
					}
					else
						pom = pom->next;
				}
				else {

					Cvred pomm;
					pomm.info.d = novi->info.d;
					pomm.info.p = novi->info.p;
					pomm.tezina = novi->tezina;
					novi->info.d = pom->info.d;
					novi->info.p = pom->info.p;
					novi->tezina = pom->tezina;
					pom->info.d = pomm.info.d;
					pom->info.p = pomm.info.p;
					pom->tezina = pomm.tezina;

					novi->next = pom->next;
					pom->next = novi;
					if (novi->next == nullptr) rear = novi;
					break;
				}
			}
		}
	}
	Cvred skini() {
		Cvred* pom = head;
		//underflow
		if (head == nullptr) {
			return { 0,0,0 };
		}
		head = head->next;
		Cvred pomm;
		pomm.info.d = pom->info.d;
		pomm.info.p = pom->info.p;
		pomm.tezina = pom->tezina;
		delete pom;
		pom = nullptr;
		return pomm;
	}
	void ispisi() {
		Cvred* pom = head;
		while (pom) {
			cout << " " << pom->tezina << " (" << pom->info.p << "," << pom->info.d << ") ";
			pom = pom->next;
		}
	}
};
//Stek
class Stek {
public:
	cvor* head = nullptr;
	void dodaj(int ubacen) {
		cvor* novi = new cvor;
		novi->info = ubacen;
		novi->next = nullptr;

		if (head == nullptr) {
			head = novi;
		}
		else {
			novi->next = head;
			head = novi;
		}
	}
	void obrisi() {
		cvor* stari = head;
		while (head) {
			head = head->next;
			delete stari;
			stari = nullptr;
		}
	}
	~Stek() {
		obrisi();
	}
	void citaj() {
		cvor* pom = head;
		while (pom) {
			cout << " " << pom->info << " -";
			pom = pom->next;
		}
	}
	bool prazan() {
		if (head == nullptr)
			return true;
		else return false;
	}
};
class Lokacijaa {
public:
	Lokacijaa_cvor* head = nullptr;
	Lokacijaa_cvor* tail = nullptr;
	void dodaj_lokaciju(int duzina, int pretposlednji) {
		if (head != nullptr) obrisi();
		Lokacijaa_cvor* novi = new Lokacijaa_cvor;
		novi->info = duzina;
		novi->next = nullptr;
		novi->pretposlednji = pretposlednji;
		head = novi;
		tail = novi;

	}
	void dodaj_lokaciju_eq(int duzina, int pretposlednji) {
		Lokacijaa_cvor* novi = new Lokacijaa_cvor;
		novi->info = duzina;
		novi->next = nullptr;
		novi->pretposlednji = pretposlednji;
		tail->next = novi;
		tail = novi;
	}
	void obrisi() {
		Lokacijaa_cvor* pom = head;
		while (head) {
			head = head->next;
			delete pom;
			pom = head;
			tail = nullptr;
		}
	}
	void citaj() {
		Lokacijaa_cvor* pomi = head;
		cout << endl;
		while (pomi) {
			cout << " " << pomi->pretposlednji << " " << "(" << pomi->nepostojeci << ")";
			pomi = pomi->next;
		}
	}
	~Lokacijaa() { obrisi(); }
};
//Graf
class Graf {
public:
	int** a = nullptr;
	Put** b = nullptr;
	int n = -1;
	Skup_gr E;
	int v = -1;
	~Graf() { brisi_graf(); }
	void brisi_graf() {
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
		}
	}
	void kreiraj_graf() {
		a = new int* [n];
		for (int i = 0;i < n;i++) {
			a[i] = new int[n] {0};
		}
	}
	void dodaj_granu() {
		if (n == -1 || a == nullptr) {
			cout << "Pokusavate da dodate granu u graf koji ne postoji!" << endl;
		}
		else {
			int prvi_cvor, drugi_cvor;
			cout << "prvi broj:" << endl;
			cin >> prvi_cvor;
			while ((prvi_cvor < 1) || (prvi_cvor > n)) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> prvi_cvor;
			}
			cout << endl;
			cout << "drugi broj:" << endl;
			cin >> drugi_cvor;
			while (drugi_cvor < 1 || drugi_cvor > n) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> drugi_cvor;
			}
			cout << "treci broj:" << endl;
			int tezina;
			cin >> tezina;

			a[prvi_cvor - 1][drugi_cvor - 1] = tezina;
			a[drugi_cvor - 1][prvi_cvor - 1] = tezina;
			E.dodaj(prvi_cvor, drugi_cvor, tezina);
		}
	}
	void dodaj_granu2(int tipp) {
		if (n == -1 || a == nullptr) {
			cout << "Pokusavate da dodate granu u graf koji ne postoji!" << endl;
		}
		else {
			int prvi_cvor, drugi_cvor;
			cout << "prvi broj:" << endl;
			cin >> prvi_cvor;
			while ((prvi_cvor < 1) || (prvi_cvor > n)) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> prvi_cvor;
			}
			cout << endl;
			cout << "drugi broj:" << endl;
			cin >> drugi_cvor;
			while (drugi_cvor < 1 || drugi_cvor > n) {
				cout << "Uneli ste nedozvoljenu vrednost! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> drugi_cvor;
			}
			cout << "treci broj:" << endl;
			int tezina;
			cin >> tezina;
			while (tezina < 0) {
				cout << "Morate uneti pozitivnu tezinu jer Dijkstrin algoritam ne radi sa negativnom tezinom!Pokusatjte ponovo" << endl;
				cin >> tezina;
			}

			(b[prvi_cvor - 1][drugi_cvor - 1]).info = tezina;
			(b[drugi_cvor - 1][prvi_cvor - 1]).info = tezina;
			(b[prvi_cvor - 1][drugi_cvor - 1]).tip = tipp;
			(b[drugi_cvor - 1][prvi_cvor - 1]).tip = tipp;

			E.dodaj(prvi_cvor, drugi_cvor, tezina);
		}
	}
	void izracunaj_cenu() {
		//Kruskalov algoritam
		//napravio sam skupove tako da svaki sadrzi jedan element za sad
		Skup* setskup = new Skup[n];
		for (int i = 0;i < n;i++) {
			setskup[i].dodaj(i + 1);
		}
		Skup_gr Eprim;
		Red r;
		int greska = 0;
		Cvred* pomoc = E.head;
		while (pomoc) {
			r.dodaj(pomoc->info.p, pomoc->info.d, pomoc->tezina);
			pomoc = pomoc->next;
		}

		int num = 0;
		while (num < n - 1) {
			Cvred pomocna = r.skini();
			if (pomocna.info.p == 0)
			{
				cout << "Nemoguce napraviti povezan metro, nedovoljno puteva da se sva bitna mesta povezu! Pokusajte ponovo." << endl;
				greska = 1;
				break;
			}
			if ((setskup[pomocna.info.p - 1].pripadnost(pomocna.info.p)) && (setskup[pomocna.info.d - 1].pripadnost(pomocna.info.d)) && ((setskup[pomocna.info.p - 1]) != (setskup[pomocna.info.d - 1]))) {
				Eprim.dodaj(pomocna.info.p, pomocna.info.d, pomocna.tezina);
				//pomocni pok na skup koji ce pokazivati na skup formiran unijom dva poslata
				Skup* s4 = ((setskup[pomocna.info.p - 1]) + (setskup[pomocna.info.d - 1]));
				cvor* poms = s4->head;
				while (poms) {
					setskup[poms->info - 1].head = s4->head;
					poms = poms->next;
				}
				s4->head = nullptr;
				num = num + 1;
			}
		}

		if (greska != 1) {
			Cvred* sabirac = Eprim.head;
			int rezultat = 0;
			while (sabirac) {
				rezultat += sabirac->tezina;
				sabirac = sabirac->next;
			}
			cout << endl << "Minimalna cena za izgradnju metroa tako da povezuje sva znacajna mesta je " << rezultat << endl;
			cout << "Putevi koji ce biti izgradjeni: " << endl;
			Eprim.citaj();
		}

		Eprim.~Skup_gr();
	}
	void izracunaj_udaljenosti() {
		//Dijkstrin algoritam
		Skup s1;
		Lokacijaa* lokacije = new Lokacijaa[n - 1]; //pamti sve puteve
		s1.dodaj(v);//skup obradjenih cvr
		int* d = new int[n - 1];
		for (int i = 0; i < n - 1; i++) {
			d[i] = INT_MAX;
		}
		int* t = new int[n - 1]{ 0 };


		//inicijalizacija d[i] i t[i]
		for (int i = 0; i < n; i++) {
			if (i != v - 1) {
				if (i > v - 1) {
					d[i - 1] = b[v - 1][i].info;
					if (b[v - 1][i].info != INT_MAX)
						t[i - 1] = v;
					else t[i - 1] = 0;
				}
				else
					d[i] = b[v - 1][i].info;
				if (b[v - 1][i].info != INT_MAX)
					t[i] = v;
				else t[i] = 0;
			}
		}

		for (int i = 0; i < n - 1; i++) {
			lokacije[i].dodaj_lokaciju(d[i], t[i]);
		}

		/*
		for (int y = 0;y < n - 1; y++) {
			cout << " " << d[y] << "(" << t[y] << ")" << " ";
		}*/

		//pronalazenje trenutnog minimuma
		for (int k = 0; k < n - 1;k++) {
			int minimum = INT_MAX;
			int ip = -1; //indeks minimuma
			for (int m = 0; m < n - 1; m++) {
				int pom;
				if (m >= v - 1) pom = m + 2;
				else pom = m + 1;

				if (!s1.pripadnost(pom)) {
					if (d[m] < minimum) {
						minimum = d[m];
						ip = m;
					}
				}
			}

			if (d[ip] == INT_MAX) break;
			if (ip == -1) continue;
			if (ip >= v - 1) {
				s1.dodaj(ip + 2);
			}
			else
				s1.dodaj(ip + 1);

			//relaksacija(promenio granicu sa n-1 na n)
			for (int j = 0;j < n - 1;j++) {
				int pom;
				if (j >= v - 1) pom = j + 2;
				else pom = j + 1;

				if (!s1.pripadnost(pom)) {
					int pomocnica;
					//posto imamo problem sa identifikatorom cvora i indeksiranja u matrici b koje krece od 0 uvodimo pomocnicu koja predstavlja indeks trenutnog minimalnog cvora u matrici b
					if (ip >= v - 1) {
						pomocnica = ip + 1;
					}
					else {
						pomocnica = ip;
					}
					//posto imamo problem sa identifikatorom cvora i indeksirajem u matrici b jer indeksiranje krece od 0 uvodimo pomocnicu2 koja ce biti pozicija cvora koji se relaksira u matrici b
					int pomocnica2;
					if (j >= v - 1) {
						pomocnica2 = j + 1;
					}
					else {
						pomocnica2 = j;
					}

					if ((b[pomocnica][pomocnica2].info) != INT_MAX) {
						if ((d[ip] + b[pomocnica][pomocnica2].info) < d[j]) {
							d[j] = d[ip] + b[pomocnica][pomocnica2].info;
							t[j] = pomocnica + 1;
							lokacije[j].dodaj_lokaciju(d[j], t[j]);
							
							if (lokacije[ip].head->next != nullptr) {
								Lokacijaa_cvor* rezerva = lokacije[ip].head->next;
								while (rezerva) {
									lokacije[j].dodaj_lokaciju_eq(d[j], rezerva->pretposlednji);
									rezerva = rezerva->next;
								}
							}

						}
						else if ((d[ip] + b[pomocnica][pomocnica2].info) == d[j]) {
							t[j] = pomocnica + 1;
							lokacije[j].dodaj_lokaciju_eq(d[j], t[j]);
						}
					}
				}
			}
		}

		/*
		for (int y = 0;y < n - 1; y++) {
			cout << " " << d[y] << "(" << t[y] << ")" << " ";
		}*/

		for (int i = 1; i <= n;i++) {
			int lok;
			if (i != v) {
				if (i > v) {
					lok = i - 2;
				}
				else {
					lok = i - 1;
				}
				Lokacijaa_cvor* pom = lokacije[lok].head;
				Lokacijaa_cvor* pomoc = lokacije[lok].head;
				//odredimo koliko nepostojecih grana ima
				if (lokacije[lok].head->next != nullptr) {

					while (pom) {
						lok = pom->pretposlednji;
						if (lok > v) {
							lok -= 2;
						}
						else {
							lok -= 1;
						}
						if (b[i - 1][pom->pretposlednji - 1].tip == 1)
							pom->nepostojeci++;

						int vr_cvora = pom->pretposlednji;
						while (1) {
							int sl_vre = t[lok];
							if (b[vr_cvora - 1][t[lok] - 1].tip == 1)
								pom->nepostojeci++;
							if (sl_vre == v) break;
							vr_cvora = sl_vre;
							lok = t[lok];
							if (lok > v) {
								lok -= 2;
							}
							else {
								lok -= 1;
							}
						}
						pom = pom->next;
					}


					//sortiramo po njima ulancanu listu
					while (pomoc) {
						Lokacijaa_cvor* druga = pomoc->next;
						while (druga) {
							if (pomoc->nepostojeci > druga->nepostojeci) {
								Lokacijaa_cvor pommo;
								pommo.nepostojeci = pomoc->nepostojeci;
								pommo.pretposlednji = pomoc->pretposlednji;
								pomoc->nepostojeci = druga->nepostojeci;
								pomoc->pretposlednji = druga->pretposlednji;
								druga->nepostojeci = pommo.nepostojeci;
								druga->pretposlednji = pommo.pretposlednji;
							}
							druga = druga->next;
						}
						pomoc = pomoc->next;
					}
				}
			}
		}

		//ispisivanje puteva
		cout << endl;
		for (int i = 1; i <= n;i++) {
			Stek stek1;
			int lok;
			if (i != v) {
				if (i > v) {
					lok = i - 2;
				}
				else {
					lok = i - 1;
				}

				Lokacijaa_cvor* pom = lokacije[lok].head;
				Lokacijaa_cvor* glava = lokacije[lok].head;

				while (pom) {
					lok = pom->pretposlednji;
					if (lok > v) {
						lok -= 2;
					}
					else {
						lok -= 1;
					}
					stek1.dodaj(pom->pretposlednji);
					while (1) {
						if (pom->pretposlednji == v) break;
						if (t[lok] < 0) break;
						int sl_vre = t[lok];
						stek1.dodaj(t[lok]);
						if (sl_vre == v) break;
						lok = t[lok];
						if (lok > v) {
							lok -= 2;
						}
						else {
							lok -= 1;
						}
					}
					//ispisivanje steka
					stek1.citaj();
					int duz;
					if (i > v)
						duz = i - 2;
					else
						duz = i - 1;
					cout << " " << i << " " << "Duzina najkraceg puta do cvora " << i << " je " << d[duz];
					if ((pom->nepostojeci != 0) || (pom->next != nullptr) || (pom != glava)) {
						cout << " (i ovaj put sadrzi " << pom->nepostojeci << " neizgradjenih puteva.)" << "     ";
					}
					stek1.obrisi();
					pom = pom->next;
				}
				cout << endl;

			}
		}
	}
	void stvaranje_metroa() {
		cout << "Unesite broj kljucnih lokacija: " << endl;
		cin >> n;
		while (n < 1) {
			cout << "Morate uneti n vece od 0! Pokusajte ponovo!" << endl;
			cin >> n;
		}
		kreiraj_graf();
		int izb2;
		while (1) {
			cout << endl;
			cout << "Izaberite operaciju brojevima (1-3):" << endl;
			cout << "1. Unesi dve kljucne lokacije izmedju kojih je moguce napraviti metro" << endl;
			cout << "2. Zavrsi sa dodavanjem lokacija izmedju kojih je moguce izgraditi metro i izracunaj minimalnu cenu." << endl;
			cout << "3. Sada kada je zadat broj kljucnih lokacija napusti ovu operaciju i predji na glavni meni kako bi odabrao pronalazenje najkrace rute za vatrogasna kola." << endl;

			cin >> izb2;

			if (izb2 == 1) {
				cout << "Unesite dva broja koji predstavljaju lokacije izmedju kojih je moguce napraviti metro." << endl;
				cout << "Zatim kao treci broj unesite cenu izgradnje metroa izmedju ove dve lokacije:" << endl;
				dodaj_granu();
			}
			else if (izb2 == 2) {
				izracunaj_cenu();
				break;
			}
			else if (izb2 == 3) {
				break;
			}
			else {
				cout << "Uneli ste nepostojeci karakter! Pokusajte ponovo." << endl;
				//ukoliko se ne unese broj ovo resava problem sa beskonacnom petljom(ciscenje bafera)
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}

	}
	void vatrogasna_ruta() {
		if (n == -1 || a == nullptr) {
			cout << "Da biste mogli da koristite ovu funkciju prvo odradite operaciju 1. Stvaranje i ispis metroa! Molim pokusajte ponovo." << endl;
		}
		else {
			b = new Put * [n];
			for (int i = 0;i < n;i++) {
				b[i] = new Put[n];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) {
						b[i][j].info = 0;
						b[i][j].tip = 0;
					}
					else {
						b[i][j].info = INT_MAX;
						b[i][j].tip = 0;
					}
				}
			}

			E.~Skup_gr();
			int izbor3;
			cout << "Ucitajte indeks lokacije V u odnosu na koju ce se nalaziti najkraci putevi do svih ostalih cvorova:" << endl;
			cin >> v;
			while ((v < 1) || (v > n)) {
				cout << "Uneli ste indeks cvora koji ne postoji u grafu! Pokusaje ponovo! Dozvoljene vrednosti su od: 1 do " << n << endl;
				cin >> v;
			}

			while (1) {
				cout << endl;
				cout << "Izaberite operaciju brojevima (1-3):" << endl;
				cout << "1. Dodajte vec izgradjen put izmedju dve kljucne lokacije u gradu." << endl;
				cout << "2. Dodajte put koji trenutno ne postoji, ali se moze izgraditi izmedju dve kljucne lokacije u gradu." << endl;
				cout << "3. Zavrsite sa dodavanjem svih puteva u infrastrukturi." << endl << endl;

				cin >> izbor3;
				if (izbor3 == 3) {
					izracunaj_udaljenosti();
					brisi_graf();
					break;
				}
				switch (izbor3) {
				case 1:
					cout << "Kao prva dva broja unesite lokacije koje zelite da spaja ovaj put." << endl;
					cout << "Zatim kao trecu lokaciju unesite duzinu ovog puta:" << endl;
					dodaj_granu2(2);
					break;
				case 2:
					dodaj_granu2(1);
					break;
				default:
					cout << "Uneli ste nepostojeci karakter! Pokusajte ponovo." << endl;
					//ukoliko se ne unese broj ovo resava problem sa beskonacnom petljom(ciscenje bafera)
					cin.clear();
					cin.ignore(1000, '\n');
				}
			}
		}
	}
};
int main() {
	cout << "ZADATAK 2 - PROBLEM IZGRADNJE PUTNE INFRASTRUKTURE -" << endl << "- Zarko Babic 0044/2019 -" << endl << endl;
	int izbor;
	Graf gr;
	while (1) {
		cout << endl;
		cout << "Izaberite operaciju brojevima (1-3):" << endl;
		cout << "1. Stvaranje i ispis metroa" << endl;
		cout << "2. Pronalazenje najkrace rute za vatrogasna kola" << endl;
		cout << "3. Kraj programa" << endl << endl;

		cin >> izbor;

		switch (izbor) {
		case 1:
			gr.stvaranje_metroa();
			break;
		case 2:
			gr.vatrogasna_ruta();
			break;
		case 3:
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