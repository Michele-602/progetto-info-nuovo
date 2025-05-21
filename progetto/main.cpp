#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
using namespace std;
void stampamenu() {
    cout << "*************************************************\n";
    cout << "* 0 - carica dati da file                       *\n";
    cout << "* 1 - cerca corsi di uno studente(matricola)    *\n";
    cout << "* 2 - cerca corsi di uno studente(cognome)      *\n";
    cout << "* 3 - elenca studenti iscritti ad un corso      *\n";
    cout << "* 4 - stampa dati di un esame di un corso       *\n";
    cout << "* 5 - numero di studenti per corso              *\n";
    cout << "* 6 - numero di materie per corso               *\n";
    cout << "* 7 - cerca materie per descrizione             *\n";
    cout << "* 8 - inserisci nuovo studente                  *\n";
    cout << "* 9 - salva dati su file                        *\n";
    cout << "* 10 - esci                                      *\n";
    cout << "*************************************************\n";

}

struct corso {
 string codice_corso;
 string descrizione_corso;

};
struct materia {
 string codice_materia;
 string descrizione_materia;
 string codice_corso;

};
struct studente {
 string matricola_studente;
 string cognome_studente;
 string nome_studente;
 string codice_corso;

};

map<string,  vector<studente> > studentev; // codice corso => tanti studenti
map<string,  vector<corso> > corsov;
map<string,  vector<materia> > materiav;


void carica_dati (   map<string,  vector<studente> > &studentev,map<string,  vector<corso> > &corsov,map<string,  vector<materia> > &materiav){
     string a,lables;
     int i=0;
   ifstream fin("corsi_studenti.csv");
    getline(fin,lables);
   while(!fin.eof()){
    getline(fin,a,',');
    corso tmp;
    materia tmp1;
    studente tmp2;

    tmp.codice_corso=a;
    tmp1.codice_corso=a;
    tmp2.codice_corso=a;

    getline(fin,a,',');
    tmp.descrizione_corso=a;

    getline(fin,a,',');
    tmp1.codice_materia=a;

    getline(fin,a,',');
    tmp1.descrizione_materia=a;

    getline(fin,a,',');
    tmp2.matricola_studente=a;

    getline(fin,a,',');
    tmp2.cognome_studente=a;

    getline(fin,a);
    tmp2.nome_studente=a;




   studentev[tmp.codice_corso].push_back(tmp2);
    corsov[tmp.codice_corso].push_back(tmp);
    materiav[tmp.codice_corso].push_back(tmp1);


   }

   fin.close();


}
string cercaPerMatricola(map<string,  vector<studente> > &studentev,string matricola,map<string,  vector<corso> > corsov){
      string cm;
         for(auto c: studentev){

                for(auto x : c.second){
                      if(x.matricola_studente==matricola){
                          cm=c.first;
                      }
                }
        }
           for(auto c: corsov){

                for(auto x : c.second){
                      if(c.first==cm){
                          return x.descrizione_corso;
                      }
                }
        }
}
string cercaPerCognome(map<string,  vector<studente> > studentev,string cognome,map<string,  vector<corso> > corsov){
        string cc;
         for(auto c: studentev){

                for(auto x : c.second){
                      if(x.cognome_studente==cognome){
                          cc=c.first;
                      }
                }
        }
           for(auto c: corsov){

                for(auto x : c.second){
                      if(c.first==cc){
                          return x.descrizione_corso;
                      }
                }
        }
}

void numeroStudentiCorso(vector<corso> corsov, map<string,int> &csc){
        for(int i=0;i<corsov.size();i++){
           csc[corsov[i].codice_corso]++;
        }
}
void stampaEsamiCorso( vector<string> &sec, vector<materia> materiav,string corsosec) {
    for (int i = 0; i < materiav.size(); i++) {
            if(materiav[i].codice_corso==corsosec){
        sec.push_back(materiav[i].descrizione_materia);
            }
    }
}
void caricaMAPMAP( map<string,  vector<studente> > studentev,      map<string ,  map<string ,studente> > MAPMAP) {
      for(auto x:studentev){
                           for(auto d:x.second){
                            MAPMAP[x.first][d.matricola_studente]=d;

                    }
}
}



int main()
{

    int ch;


    vector<studente> SIC;



    string matricola,cm,cc,x,corsosec,corsoSIC,cognome;
    vector<string> sec;
    map<string ,int> spc;
     map<string ,  map<string ,studente> > MAPMAP;
      map<string , string > aaaa;
    stampamenu();

        cin >> ch;
    while (ch<10) {

        switch (ch) {
               case 0:
                    carica_dati(studentev,corsov,materiav);
                    cout<<"ciao";
                   /* for(auto c: studentev){

                           for(auto x : c.second){
                                cout<<c.first<<"      :      "<<x.cognome_studente<<endl;;
                            }
                    }*/

                break;


            case 1:
                cout<<"dimmi di che matricola vuoi sapere il corso : ";
                cin>>matricola;
                cout<<matricola<<" : "<<cercaPerMatricola(studentev, matricola,corsov)<<endl;
                break;

            case 2:
                cout<<"dimmi di che cognome vuoi sapere il corso : ";
                cin>>cognome;
                cout<<cognome<<" : "<<cercaPerCognome(studentev, cognome,corsov)<<endl;

                break;

            case 3:

                cout<<"dimmi il codice corso di cui vuoi sapere gli studenti : ";
                cin>>corsoSIC;


//METTERELO SOTTOFORMA DI PROCEDURA
                    for(auto x:studentev){
                           for(auto d:x.second){
                            MAPMAP[x.first][d.matricola_studente]=d;

                    }


                    }
                     for(auto corso:MAPMAP){
                        if(corso.first==corsoSIC){
                            for(auto mat:corso.second ){

                                cout<<mat.second.cognome_studente<<endl;

                            }
                        }
                    }






                break;

            case 4:

                break;

            case 5:
                //METTERELO SOTTOFORMA DI PROCEDURA
                       for(auto x:studentev){
                           for(auto d:x.second){
                            MAPMAP[x.first][d.matricola_studente]=d;

                    }
                       }




              for(auto corso:MAPMAP){

                            for(auto mat:corso.second ){

                                spc[corso.first]++;

                            }

                    }
                       for(auto x:spc){

                           cout<<x.first<<" "<<x.second<<endl;

                    }


                break;

            case 6:
                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                break;




        }
     stampamenu();
        cin >> ch;
    }
    return 0;
}

