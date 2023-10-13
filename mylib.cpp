#include "mylib.h"

void padalinimas(const vector<studentas>& grupe,vector<studentas>& kietiakai, vector<studentas>& vargsiukai) {

    for (auto &a: grupe) {
        if (a.balasv >= 5) {
            kietiakai.push_back(a);
        } else {
            vargsiukai.push_back(a);
        }
    }
}


        //Spauzdinimo funkcija vargsiuku ir kietiaku failams
void padalinto_sapuzdinimas(const vector<studentas>& studentai, const string& failo_pav) {
    ofstream out(failo_pav);
    out << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis" << endl;
    out << endl;

    for (const auto& stud : studentai) {
        out << left << setw(20) << stud.pav << setw(20) << stud.var << setw(20) << fixed << setprecision(2) << stud.balasv << endl;
    }

    out.close();
    cout << "Duomenys įrašyti į failą '" << failo_pav << "'" << endl;
}


        //Failo generavimas
void gen_failas(int stud_gen_sk, int stud_gen_nd) {
    srand(static_cast<unsigned>(time(nullptr)));

    vector<studentas> studentai;

    ofstream out("Kursiokai" + to_string(stud_gen_sk) + ".txt");
    out << left << setw(20) << "Vardas" << setw(20) << "Pavarde";

    for (int m = 1; m <= stud_gen_nd; m++) {
        out << setw(7) << "ND" + to_string(m);
    }

    out << setw(7) << "Egz." << setw(15) << endl;
    out << endl;

    for (int i = 1; i <= stud_gen_sk; i++) {
        studentas stud;
        stud.var = "Vardas" + to_string(i);
        stud.pav = "Pavarde" + to_string(i);
        out << left << setw(20) << stud.var << setw(20) << stud.pav;
        stud.egz = (rand() % 10) + 1;

        double suma = 0;

        for (int j = 0; j < stud_gen_nd; j++) {
            int pazymys = (rand() % 10) + 1;
            stud.paz.push_back(pazymys);
            suma += pazymys;

            out << setw(7) << pazymys;
        }

        out << setw(7) << stud.egz<< endl;
    }


    out.close();

}






            // Vidurkio ir medianos skaiciavimo funkcija

void skaiciavimas(vector<studentas> &grupe, studentas &temp)
{

    // Skaiciuojame vidurki
    double suma = 0;
    for (int i = 0; i < temp.paz.size(); i++)
        {
            suma += temp.paz[i];
        }

    temp.vid = 0.4 * (suma / temp.paz.size()) + 0.6 * temp.egz;

    // Sukuriame vektoriu su visais gautais pazymiais ir egzaminu
    vector<int> visipaz = temp.paz; // vektorius saugos int tipo objektus, vadinsis visipaz, ji priliginam temp.paz (reiskaisi cia desim pazymius)
    visipaz.push_back(temp.egz);


    //Skaiciuojame mediana
    double med = 0.0;
    sort(visipaz.begin(), visipaz.end());
    if (visipaz.size() % 2 == 0)
        {
            med = (visipaz[(visipaz.size() / 2) - 1] + visipaz[visipaz.size() / 2]) / 2.0;
        }
    else
        {
            med = visipaz[visipaz.size() / 2];
        }

    temp.med = med;

    grupe.push_back(temp);
}






void skaiciavimas_2(int &suma, int paz_sk, studentas &temp, vector<studentas> &grupe) {

    temp.vid = static_cast<float>(suma)/paz_sk;


    // Mediana
    sort(temp.paz.begin(), temp.paz.end());

    double mediana = 0.0;
    int dydis = temp.paz.size();
    if (dydis % 2 == 0) {
        temp.med = static_cast<double>(temp.paz[(dydis - 1) / 2] + temp.paz[dydis / 2]) / 2.0;
    } else {
        temp.med = temp.paz[dydis / 2];
    }

    //Skaiciuojam galutinius balus
    temp.balasv = static_cast<float>(temp.vid*0.4 + temp.egz*0.6);


    grupe.push_back(temp);
    temp.paz.clear();
    suma = 0;
}


bool palyginimas(studentas &a, studentas &b, string rus_index) {
    if (rus_index == "P") {
        return a.pav < b.pav;
    } else if (rus_index == "V") {
        return a.var < b.var;
    } else if (rus_index == "G") {
        return a.balasv < b.balasv;
    } else {
        // Automatinis nustatymas, kai rus_index neatpazintas
        return false;
    }
}


void pal_pav(vector<studentas> &grupe, string rus_index) {
    sort(grupe.begin(), grupe.end(), [rus_index](studentas &a, studentas &b) {
        return palyginimas(a, b, rus_index);
    });
}



// Iskvieciama funkcija "ivesk", kuri kaip argumentus ima "stud_sk" ir "gen" kintamuosius
//ir grazina vektoriu sudaryta is objektu "studentas"

vector<studentas> ivesk(int stud_sk, string gen) {
    vector<studentas> grupe;

// Vykdomos visos galimos ivestys
if(gen =="T")
    {
        // For ciklas vykdomas tiek kartu, kiek yra ivedama studentu
    for (int j = 0; j < stud_sk; j++)
        {
        studentas temp;
        cout << "Iveskite varda ir pavarde: ";
        cin >> temp.var >> temp.pav;


        if (gen == "T")
            {
            cout << "Iveskite namu darbu pazymius (baigti su dvigubu Enter): ";
            int num;
            while (cin >> num)
                {
                    temp.paz.push_back(num); // pridedame ivesta pazimi i vektoriu, kuriame bus irasomi visi pazymiai
                    if (cin.get() == '\n' && temp.paz.size() > 0 && cin.peek() == '\n') // Tikrinama ar baigiama ivestis (Enter paspaudzaima 2 kartus)
                        {
                            cin.ignore(); // Su sia eilute ignoruojami ivesti naujos eilutes simboliai (Enter)
                            break;
                        }
                }
            cout << "Iveskite egzamino rezultata: ";
            cin >> temp.egz;
            }


        skaiciavimas(grupe, temp); // Iskvieciame vidurkio ir medianos skaiciavimo funkcija
        }
    }

    return grupe;
}






void nuskaitymas(const std::string& failas, std::vector<studentas>& grupe) {
    std::ifstream in(failas);
    if (!in.is_open()) {
        std::cerr << "Klaida: Failas nerastas." << std::endl;
        return;
    }

    string pavadinimas, praleidziam;
    getline(in, pavadinimas);
    studentas temp;
    int laik_kint, suma = 0, m = 0;
    double paz_sk = 0;
    int raidziu_sk = 0;
    for (char ch : pavadinimas) {
        if (isalpha(ch)) {
            raidziu_sk++;
        }
    }

    paz_sk = (raidziu_sk - 6 - 7 - 3) / 2;


    while (in >> temp.var >> temp.pav) {

        for (int i = 0; i < paz_sk; i++) {
        in >> laik_kint;
            temp.paz.push_back(laik_kint);
            suma+=laik_kint;
        }

    in >> temp.egz;
    getline(in, praleidziam);
        // Process the data, for example, by calling the "skaiciavimas" function
        skaiciavimas_2(suma,paz_sk,temp,grupe);
        m++;
    }

    in.close();
}









        //Isvedimo funkcija

void isvedimas(vector<studentas> &grupe, string gen, string ats,string rus_index) {
    if (gen == "T")
        {
            // Rusiuojame pagal pavardes
            pal_pav(grupe,"P");

        cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20);
        if (ats == "M") {
                cout << "Galutinis (Med.)" << endl;
                cout << "--------------------------------------------------------\n";
                for (auto &a : grupe) {
                    cout << left << setw(20) << a.pav << setw(20) << a.var << setw(20) << fixed << setprecision(2) << a.med << endl;
                    }
                        } else if (ats == "V") {
            cout << "Galutinis (Vid.)" << endl;
            cout << "--------------------------------------------------------\n";
            // Imame po elementa is "grupe" vektoriaus (po studenta)
            for (auto &a : grupe) {
                cout << left << setw(20) << a.pav << setw(20) << a.var << setw(20) << fixed << setprecision(2) << a.vid << endl;
            }
        }
        } else if (gen == "F") {
         ofstream out ("rezultatai.txt");
        out << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
        out << "-----------------------------------------------------------------------\n";

        // Rusiuojame pagal pavardes
        pal_pav(grupe,rus_index );

        for (auto &a : grupe) {

            out << left << setw(20) << a.pav << setw(20) << a.var << setw(20) << fixed << setprecision(2) << a.balasv << setw(20) << fixed << setprecision(2) << a.med << endl;
        }
        out.close();
        cout << "Isvesti duomenys irasyti i faila 'rezultatai.txt' "<< endl;
    }
}
