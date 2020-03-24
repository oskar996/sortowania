#include "losowanie_wektorow.hpp"

void losoj_wektor(int tablica[],int l_elementow,int zakres){

    for(int i=0;i<l_elementow;i++){
        tablica[i]=rand()%zakres;
    }

}


void Odwracanie_tablicy(int Tablica[],int rozm_tab){
    int i = 0;
    int j = rozm_tab-1;
    
    while(i<j){
        int pom = Tablica[i];
        Tablica[i] = Tablica[j];
        Tablica[j] = pom;
        i++;
        j--;
    }
}

bool Czy_sort(int Tablica[],int rozm_tab){

    for(int i=0;i<rozm_tab-1;i++){
        if(Tablica[i]>Tablica[i+1]){
            return false;
        }
        
    }

    return true;

}