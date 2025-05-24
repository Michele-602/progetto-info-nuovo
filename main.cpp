
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
void inserisci_nuovo_studente (  corso tmpp,    materia tmpp1,    studente tmpp2){
    studentev[tmpp.codice_corso].push_back(tmpp2);
    corsov[tmpp.codice_corso].push_back(tmpp);
    materiav[tmpp.codice_corso].push_back(tmpp1);



}




int main()
{

    int ch;


    vector<studente> SIC;



    string matricola,cm,cc,x,corsosec,corsoSIC,cognome,codice_esame,CERCA_DESCR;
    vector<string> sec;
    map<string ,int> spc;
    map<string ,int> mpc;
    corso tmpp;
    materia tmpp1;
    studente tmpp2;
     map<string ,  map<string ,studente> > MAPMAPs;
    map<string ,  map<string ,materia> > MAPMAPm;
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
 MAPMAPs.clear();
                    for(auto x:studentev){
                           for(auto d:x.second){
                            MAPMAPs[x.first][d.matricola_studente]=d;

                    }


                    }
                     for(auto corso:MAPMAPs){
                        if(corso.first==corsoSIC){
                            for(auto mat:corso.second ){

                                cout<<mat.second.cognome_studente<<"  "<<mat.second.nome_studente<<"  "<<mat.second.matricola_studente<<endl;

                            }
                        }
                    }






                break;

            case 4:
                cout<<"inserisci codice corso per sapere gli esami : " ;
             cin>>codice_esame;
             MAPMAPm.clear();
                for(auto x:materiav){
                           for(auto d:x.second){
                            MAPMAPm[x.first][d.descrizione_materia]=d;

                    }
                }
                  for(auto corso:MAPMAPm){

                            for(auto desc:corso.second ){
                                if(codice_esame==corso.first){
                                    cout<<corso.first<<"  "<<desc.second.descrizione_materia<<"  "<<desc.second.codice_materia<<endl;
                                }

                            }

                    }


                break;

            case 5:
                  MAPMAPs.clear();
                //METTERELO SOTTOFORMA DI PROCEDURA
                       for(auto x:studentev){
                           for(auto d:x.second){
                            MAPMAPs[x.first][d.matricola_studente]=d;

                    }
                       }




              for(auto corso:MAPMAPs){

                            for(auto mat:corso.second ){

                                spc[corso.first]++;

                            }

                    }
                       for(auto x:spc){

                           cout<<x.first<<" "<<x.second<<endl;

                    }


                break;

            case 6:
                MAPMAPm.clear();
                    for(auto x:materiav){
                           for(auto d:x.second){
                            MAPMAPm[x.first][d.descrizione_materia]=d;

                    }
                }

              for(auto corso:MAPMAPm){

                            for(auto mat:corso.second ){

                                mpc[corso.first]++;

                            }

                    }
                       for(auto x:mpc){

                           cout<<x.first<<" "<<x.second<<endl;

                    }

                break;

            case 7:
                   cout<<"inserisci descrizion di cui vuoi sqapere le materia : " ;
                cin.ignore();
             getline(cin,CERCA_DESCR);

                for(auto x:materiav){
                           for(auto d:x.second){
                            MAPMAPm[x.first][d.descrizione_materia]=d;

                    }
                }
                  for(auto corso:MAPMAPm){

                            for(auto desc:corso.second ){
                                if(CERCA_DESCR==desc.second.descrizione_materia){
                                    cout<<corso.first<<"  "<<desc.second.descrizione_materia<<"  "<<desc.second.codice_materia<<endl;
                                }

                            }

                    }

                break;

            case 8:
                cout<<"inseisci il codice corso : ";
                cin>>tmpp.codice_corso;
                tmpp1.codice_corso=tmpp.codice_corso;
                 tmpp2.codice_corso=tmpp.codice_corso;
                cout<<"inseisci la descrizione corso : ";
                cin>>tmpp.descrizione_corso;
                       cout<<endl;
                 cout<<"inseisci il codice materia : ";
                cin>>tmpp1.codice_materia;
                       cout<<endl;
                 cout<<"inseisci la descrizione materia : ";
                cin>>tmpp1.descrizione_materia;
                       cout<<endl;
                 cout<<"inseisci la matricola studente : ";
                cin>>tmpp2.matricola_studente;
                       cout<<endl;
                 cout<<"inseisci il cognome studente : ";
                cin>>tmpp2.cognome_studente;
                cout<<endl;
                 cout<<"inseisci il nome studente : ";
                cin>>tmpp2.nome_studente;
                inserisci_nuovo_studente(   tmpp,     tmpp1,     tmpp2);
                for(auto c:studentev){
                             for(auto x:c.second){
                                cout<<x.nome_studente<<endl;

                             }
                }



                break;

            case 9:
                break;




        }
     stampamenu();
        cin >> ch;
    }
    return 0;
}
