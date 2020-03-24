//#include <iostream>
#include <cmath>
#include <chrono>
#include "losowanie_wektorow.hpp"

using namespace std;

template <class klasa>
void sort_przez_wstawianie(klasa Tabela[], int koniec){                     //funkcja zajmująca się sortowanie poprzez wstawianie
    
  int pom,j;
    
  for(int i=1; i<koniec; i++){
        
    pom=Tabela[i];
    j=i-1;
        
    while(j>=0 && Tabela[j]>pom){                                       //sprawdzanie czy element poprzedający jest większy 

      Tabela[j+1]=Tabela[j];                                          //jeśli tak przesuwanie tabeli
      j--;
            
    }
    Tabela[j+1]=pom;
  }
}

template <class klasa>
int podzial(klasa Tablica[], int start, int koniec){              //podział na dwie podtablice

  int nr_el = (koniec+start)/2;
  int piwot = Tablica[nr_el];                                    //ustawienie quicksorta gdzie piwot jest ustawiony na środkowy elem nieposortowanej tablicy
  int P_index = start;                                           //P_index uczestniczy w przestawianiu liczb mniejszych od piwota
    
  int pom1=Tablica[nr_el];                                        //piwot przerzucamy na koniec żeby nie brał udziału w sortowaniu
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
void Kopcowanie (klasa Tablica[], int wezel, int N)                                         //funkcja sortująca 
{
  long lewe_dziecko,prawe_dziecko,wiekszy_potomek;                                
  
  while (wezel<=N/2){                                                                     //sprawdzanie czy nie wychodzimy poza wartości tablicy
    
    lewe_dziecko=2*wezel;                                                                 //coraz niższe węzły kopca
    prawe_dziecko=2*wezel+1;
    wiekszy_potomek=lewe_dziecko;
    
    
    if (prawe_dziecko<=N && Tablica[prawe_dziecko]>Tablica[lewe_dziecko]){                //sprawdzanie który węzeł potomny jest największy
      
      wiekszy_potomek=prawe_dziecko;
    
    }
    
    if (Tablica[wezel] < Tablica[wiekszy_potomek]){                                       //podmiana węzła z największym potomkiem jeśli wartość potomka jest większa
      
      int pom = Tablica[wezel];
      Tablica[wezel] = Tablica[wiekszy_potomek];
      Tablica[wiekszy_potomek] = pom;
    
    }
    
    else{                                                                           //jeśli wszystko jest posortowane wychodzimy z pętli
      break;                                                                  
    }
    
    wezel=wiekszy_potomek;                                                          //przełączanie na kolejny węzeł żeby je posortować dalszą część tablicy
  }
}

template <class klasa>
void Sort_przez_kopcowanie (klasa Tablica[], int N)
{
  long i;
  for (i=N/2; i>0; --i)                                 //tworzenie kopca - tablica kopcowa
    Kopcowanie(Tablica-1,i,N);
  for (i=N-1; i>0; --i)                                 //wlasciwe sortowanie
  {
    int pom = Tablica[0];                               //usuniecie najwiekszego elementu z kopca i przeniesienie go na tył tablicy
    Tablica[0] = Tablica[i];
    Tablica[i] = pom;

    Kopcowanie(Tablica-1,1,i);                          //sortowanie kopca po usunieciu największego elementu z kopca
  }
}

template <class klasa>
void Sort_Introspektywne_v2(klasa Tabela[],int N, int glebokosc){
    
  if(glebokosc<=0){                                             //jesli dozwolona glebokosc rekurencji jest równa lub mniejsza zero wukorzystujemy sortowanie pomocnicze (przez kopcowanie)
    Sort_przez_kopcowanie(Tabela,N);
    return;
  }
    
  int i=podzial(Tabela,0,N-1);                                  //podział tablicy na dwie częsci i zwrócenie punktu podziału
  if(i>9){                                                
    Sort_Introspektywne_v2(Tabela,i,glebokosc-1);               //jeśli ilość elementów w podtablicy jest wieksza niż 9 wykonaj rekurencyjne sortowanie 
  }
  if(N-1-i>9){
    Sort_Introspektywne_v2(Tabela+1+i,N-1-i,glebokosc-1);       //jeśli ilość elem w drugiej podtablicy jest większa niż 9 wykonaj rekurencje
  }
}

template <class klasa>
void Hybrid_Introsort(klasa Tabela[],int N){                          //funkcja dodatkowo wykorzystująca sortowanie przez wstawianie
  Sort_Introspektywne_v2(Tabela,N,floor(2*log(N)));                 //sortowanie introspektywne tablic większych niż 9
  sort_przez_wstawianie(Tabela,N);                                  //sortowanie pozostałych elementów przez wstawianie
}

int main(){

  double czas_calk = 0.000000; 
  int dlugosc_tab = 1000000;
  int* tab = new int[dlugosc_tab];

  srand(time(NULL));
    
  for(int i=0;i<100;i++){
    losoj_wektor(tab,dlugosc_tab,100000);

    //Hybrid_Introsort(tab,dlugosc_tab);

    //Odwracanie_tablicy(tab,dlugosc_tab);

    auto poczatek_pom = chrono::steady_clock::now();
    Hybrid_Introsort(tab,dlugosc_tab);
    auto koniec_pom = chrono::steady_clock::now();
    chrono::duration<double> czas = koniec_pom-poczatek_pom;
    czas_calk += czas.count();

    if(Czy_sort(tab,dlugosc_tab)==false){
      cout<<"blad"<<endl;
    }

  }
  cout<< "czas: " << czas_calk << "s" <<endl;

  /*for(int k=0; k<dlugosc_tab; k++){
    cout<<tab[k]<<endl;
  }*/

  delete [] tab;
  return 0;
}