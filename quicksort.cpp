//#include <iostream>
#include <chrono>
#include "losowanie_wektorow.hpp"

using namespace std;

template <class klasa>
int podzial(klasa Tablica[], int start, int koniec){              //podział na dwie podtablice

    int nr_el = (koniec+start)/2;
    int piwot = Tablica[nr_el];                                    //ustawienie quicksorta gdzie piwot jest ustawiony na środkowym elemencie nieposortowanej tablicy
    int P_index = start;
    
    int pom1=Tablica[nr_el];
    Tablica[nr_el]=Tablica[koniec];
    Tablica[koniec]=pom1;

    for(int i=start; i<koniec; i++){                                
        if (Tablica[i]<piwot){                                     //jesli element tablicy jest mniejszy od piwota to zamien go z P_index
            
            pom1=Tablica[P_index];
            Tablica[P_index]=Tablica[i];
            Tablica[i]=pom1;
            P_index++;                                              //po zamianie zwiekszamy P_index o 1

        }
    }

    pom1=Tablica[P_index];                                          //zamieniamy P_index z piwotem przez co piwot dzieli tablice na dwie czesci
    Tablica[P_index]=Tablica[koniec];
    Tablica[koniec]=pom1;

    return P_index;
}

template <class klasa>
void quicksort(klasa Tablica[], int start, int koniec){               //funkcja dzieląca tablice na coraz mniejsze części

    if(start < koniec){
        int srodek=podzial(Tablica,start,koniec);                   //sortowanie tablicy na dwie posortowane częsci i zwrócenie miejsca podziału
        quicksort(Tablica,start,srodek-1);                          //sortowanie coraz mniejszych tablic przez cowszystkie elementu są posortowane
        quicksort(Tablica,srodek+1,koniec);
    }
}

int main(){
    double czas_calk = 0.000000;
    int dlugosc_tab = 1000000;
    int* Tablica = new int[dlugosc_tab];
    srand(time(NULL));
    
    for(int i=0;i<100;i++){
        losoj_wektor(Tablica, dlugosc_tab,100000);
        //quicksort (Tablica,0,dlugosc_tab-500000);
        
        //Odwracanie_tablicy(Tablica,dlugosc_tab);

        auto poczatek_pom = chrono::steady_clock::now();
        quicksort (Tablica,0,dlugosc_tab-1);
        auto koniec_pom = chrono::steady_clock::now();
        chrono::duration<double> czas = koniec_pom-poczatek_pom;
        czas_calk += czas.count();

        if(Czy_sort(Tablica,dlugosc_tab)==false){
            cout<<"blad"<<endl;
        }

    }
    cout<< "czas: " << czas_calk << "s" <<endl;

    /*for(int k=0; k<dlugosc_tab; k++){
        cout<<Tablica[k]<<endl;
    }*/
    
    delete [] Tablica;
    return 0;
}