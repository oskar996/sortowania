#include <cstdlib>
//#include <ctime>
//#include <iostream>
#include <chrono>
#include "losowanie_wektorow.hpp"

using namespace std;

int* pom;                                           //jeśli tablica ma sortować dane inne niż int trzeba zmienić typ tej zmiennej na porządany

template <class klasa>
void scalanie(klasa tab[], int lewa, int prawa){      //funkcja scalająca dwie posortowane połowy tablicy 

    int srodek = (lewa+prawa)/2;                       
    int j = srodek+1;
    int i = lewa;    

    for(int i = lewa; i<=prawa; i++){               //przygotowanie tablicy pomocniczej
        pom[i]=tab[i];
    }

    for(int k=lewa; k<=prawa; k++){                 //przechodzenie po dwóch częsciach tablicy
        if(i<=srodek){
            if(j<=prawa){
                if(pom[j]<pom[i]){                  //sprawdzanie z której tablicy aktualny element jest większy
                    tab[k]=pom[j];
                    j++;
                }
                else{
                    tab[k]=pom[i];
                    i++;
                }
            }
            else{
                tab[k]=pom[i];
                i++;
            }
        }
        else{
            tab[k]=pom[j];
            j++;
        }
    }
}

template <class klasa>
void sort_przez_scalanie(klasa tab[],int lewa, int prawa){            //sortowanie przez scalanie z wykorzystaniem rekurencji
    
    int srodek = (lewa+prawa)/2;                                    
    
    if(prawa<=lewa){                                                //sprawdzanie czy sortowanie doszło do tablic posortownych(jednokomórkowych)
        return;
    }
    
    sort_przez_scalanie(tab, lewa, srodek);                         //podział na dwie podtablice do sortowania
    sort_przez_scalanie(tab, srodek+1, prawa);

    scalanie(tab, lewa, prawa);
}


int main(){
    double czas_calk = 0.000000;    
    int dlugosc_tab = 1000000;
    pom = new int[dlugosc_tab];
    int* tab = new int[dlugosc_tab];

    srand(time(NULL));
    
    for(int i = 0;i<100;i++){
        losoj_wektor(tab,dlugosc_tab,100000);
        
        
        //sort_przez_scalanie(tab,0,dlugosc_tab-1);
        
        //Odwracanie_tablicy(tab,dlugosc_tab);

        auto poczatek_pom = chrono::steady_clock::now();
        sort_przez_scalanie(tab,0,dlugosc_tab-1);
        auto koniec_pom = chrono::steady_clock::now();
        chrono::duration<double> czas = koniec_pom-poczatek_pom;
        czas_calk +=czas.count();

        if(Czy_sort(tab,dlugosc_tab)==false){
            cout<<"blad"<<endl;
        }

    }
    cout<< "czas: " << czas_calk << "s" <<endl;


    /*cout << endl;
    for(int g=0;g<dlugosc_tab;g++){
        cout << tab[g] <<endl;
    }*/
    
    delete [] pom;
    delete [] tab;
    return 0;
}