#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
using namespace std;
void stampamenu(){
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
    cout << "* 10 - esci                                     *\n";
    cout << "*************************************************\n";

}

struct corso{
    string codice_corso;
    string descrizione_corso;

};
struct materia{
    string codice_materia;
    string descrizione_materia;
    string codice_corso;

};
struct studente{
    string matricola_studente;
    string cognome_studente;
    string nome_studente;
    string codice_corso;

};

map<string,  vector<studente> > studentev; // codice corso => tanti studenti
map<string,  vector<corso> > corsov;
map<string,  vector<materia> > materiav;


void carica_dati (   map<string,  vector<studente> > &studentev,map<string,  vector<corso> > &corsov,map<string,  vector<materia> > &materiav,string &lables){
    string a;
    int i=0;
    ifstream fin("corsi_studenti.csv");
    getline(fin,lables);
    while(!fin.eof()){
        getline(fin,a,',');
        if(a=="") break;

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
    string cerca_matricola;
    for(auto c: studentev){

        for(auto x : c.second){
            if(x.matricola_studente==matricola){
                cerca_matricola=c.first;
            }
        }
    }
    for(auto c: corsov){

        for(auto x : c.second){
            if(c.first==cerca_matricola){
                return x.descrizione_corso;
            }
        }
    }
    return "matricola non trovato";
}
string cercaPerCognome(map<string,  vector<studente> > studentev,string cognome,map<string,  vector<corso> > corsov){
    string cerca_cognome;
    for(auto c: studentev){

        for(auto x : c.second){
            if(x.cognome_studente==cognome){
                cerca_cognome=c.first;
            }
        }
    }
    for(auto c: corsov){

        for(auto x : c.second){
            if(c.first==cerca_cognome){
                return x.descrizione_corso;
            }
        }
    }
    return "cognome non trovato";

}
void caricaento_MAPMAP_STUDENTE ( map<string,  map<string,studente> > &MAPMAP_studente ){
    MAPMAP_studente.clear();
    for(auto x:studentev){
        for(auto d:x.second){
            MAPMAP_studente[x.first][d.matricola_studente]=d;

        }

    }
}
void caricaento_MAPMAP_MATERIE ( map<string,  map<string,materia> > &MAPMAP_materia ){
    MAPMAP_materia.clear();
    for(auto x:materiav){
        for(auto d:x.second){
            MAPMAP_materia[x.first][d.descrizione_materia]=d;

        }
    }
}
int studenti_per_corsi_funzione (map<string,  map<string,studente> > &MAPMAP_studente,  int studenti_per_corsi,string numero_stud_corsi){
    caricaento_MAPMAP_STUDENTE ( MAPMAP_studente );
    for(auto corso:MAPMAP_studente){
        if(corso.first==numero_stud_corsi){
            for(auto mat:corso.second ){

                studenti_per_corsi++;

            }
        }

    }
    return studenti_per_corsi;



}
int materie_per_corsi_funzione (map<string,  map<string,materia> > &MAPMAP_materia,  int materie_per_corsi,string numero_materie_corsi){
    caricaento_MAPMAP_MATERIE ( MAPMAP_materia );
    for(auto corso:MAPMAP_materia){
        if(corso.first==numero_materie_corsi){
            for(auto mat:corso.second ){

                materie_per_corsi++;

            }
        }

    }
    return materie_per_corsi;



}
void materie_per_descrizoine (string CERCA_DESCR ){
    transform(CERCA_DESCR.begin(),CERCA_DESCR.end(),CERCA_DESCR.begin(),::tolower);
    set<string> appoggio;
    bool presente=false;
    for(auto c :materiav){
        for(auto x :c.second){
            string descrizione=x.descrizione_materia;
            transform(descrizione.begin(),descrizione.end(),descrizione.begin(),::tolower);
            if(descrizione.find(CERCA_DESCR)!=string::npos){
                if(appoggio.find(x.codice_materia)==appoggio.end()){
                    cout<<x.codice_materia<<"  :  "<<x.descrizione_materia<<endl;;
                    appoggio.insert(x.codice_materia);
                    presente=true;
                }
            }


        }
    }
    if(!presente){
        cout<<"non e prensente"<<endl;
    }

}




void inserisci_nuovo_studente (  corso tmpp,    materia tmpp1,    studente tmpp2){
    studentev[tmpp.codice_corso].push_back(tmpp2);
    corsov[tmpp.codice_corso].push_back(tmpp);
    materiav[tmpp.codice_corso].push_back(tmpp1);



}





int main(){

    int ch;


    vector<studente> SIC;



    string matricola,corsosec,n_studente_corso,cognome,codice_esame,CERCA_DESCR,numero_stud_corsi,numero_materie_corsi;
    vector<string> sec;
    int studenti_per_corsi;
    int materie_per_corsi;
    string lables;
    corso tmpp;
    materia tmpp1;
    studente tmpp2;
    map<string,  map<string,studente> > MAPMAP_studente;
    map<string,  map<string,materia> > MAPMAP_materia;

    stampamenu();

    cin >> ch;
    while (ch<10){

        switch (ch){
        case 0:
            carica_dati(studentev,corsov,materiav,lables);


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

        case 3:{
                bool trovato = false;
                cout<<"dimmi il codice corso di cui vuoi sapere gli studenti : ";
                cin>>n_studente_corso;


    //METTERELO SOTTOFORMA DI PROCEDURA
                MAPMAP_studente.clear();
                caricaento_MAPMAP_STUDENTE ( MAPMAP_studente );



                for(auto corso:MAPMAP_studente){
                    if(corso.first==n_studente_corso){
                                    trovato = true;
                        for(auto mat:corso.second ){

                            cout<<mat.second.cognome_studente<<"  "<<mat.second.nome_studente<<"  "<<mat.second.matricola_studente<<endl;

                        }
                    }
                }
            if (!trovato){
                cout << " Errore: codice corso non trovato." << endl;
            }
        }





            break;

        case 4:{
                 bool trovato1 = false;
            cout<<"inserisci codice corso per sapere gli esami : " ;
            cin>>codice_esame;

            caricaento_MAPMAP_MATERIE ( MAPMAP_materia );
            for(auto corso:MAPMAP_materia){

                for(auto desc:corso.second ){
                    if(codice_esame==corso.first){
                                trovato1 = true;
                        cout<<corso.first<<"  "<<desc.second.descrizione_materia<<"  "<<desc.second.codice_materia<<endl;
                    }

                }

            }
               if (!trovato1){
                cout << " Errore: codice corso non trovato." << endl;
            }
        }


            break;

        case 5:

            cout<<"inserisdci il corso di cui vuoi vedere in numero di studenti : ";
            cin>>numero_stud_corsi;

            cout<<numero_stud_corsi<<" : "<<studenti_per_corsi_funzione (MAPMAP_studente, studenti_per_corsi, numero_stud_corsi)<<endl;


            break;

        case 6:

            cout<<"inserisdci il corso di cui vuoi vedere il numero di meterie : ";
            cin>>numero_materie_corsi;

            cout<<numero_materie_corsi<<" : "<<materie_per_corsi_funzione (MAPMAP_materia,   materie_per_corsi, numero_materie_corsi)<<endl;
            break;

        case 7:
            cout<<"inserisci descrizione di cui vuoi sapere le materie : " ;
           cin.ignore();
           getline(cin,CERCA_DESCR);


            materie_per_descrizoine ( CERCA_DESCR );

            break;

        case 8:
            cout<<"inseisci il codice corso : ";
            cin>>tmpp.codice_corso;
            tmpp1.codice_corso=tmpp.codice_corso;
            tmpp2.codice_corso=tmpp.codice_corso;
            cout<<endl;
            cout<<"inseisci la descrizione corso : ";
            cin.ignore();
            getline(cin,tmpp.descrizione_corso);
            cout<<endl;
            cout<<"inseisci il codice materia : ";
            cin>>tmpp1.codice_materia;
            cout<<endl;
            cout<<"inseisci la descrizione materia : ";
            cin.ignore();

            getline(cin,tmpp1.descrizione_materia);
            cout<<endl;
            cout<<"inseisci la matricola studente : ";
            cin>>tmpp2.matricola_studente;
            cout<<endl;
            cout<<"inseisci il cognome studente : ";
            cin>>tmpp2.cognome_studente;
            cout<<endl;
            cout<<"inseisci il nome studente : ";
            cin>>tmpp2.nome_studente;
            cout<<endl;
            inserisci_nuovo_studente(   tmpp,     tmpp1,     tmpp2);




            break;

        case 9:
            ofstream fout ("corsi_studenti.csv");
            fout << lables << "\n";
            for (auto c : studentev){
                for (int i = 0; i < c.second.size(); i++){
                    fout << c.first << ",";

                    fout << corsov[c.first][i].descrizione_corso << ",";
                    fout << materiav[c.first][i].codice_materia << ",";
                    fout << materiav[c.first][i].descrizione_materia << ",";

                    fout << c.second[i].matricola_studente << ",";
                    fout << c.second[i].cognome_studente << ",";
                    fout << c.second[i].nome_studente << endl;
                }
            }

            fout.close();
            break;




        }
        stampamenu();
        cin >> ch;
    }
    return 0;
}
