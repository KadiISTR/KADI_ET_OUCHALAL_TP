#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Departement
{
    private:
        int _numero;
        int _prix_m2;
    public:
        Departement(int numero, int prix_m2 );
        //Departement(json data);
        Departement(int id);
        void set(int n, int p);
        void affichage ();
        friend class Prix;
};

class Machine
{
    private:
        string _nom;
        int _prix;
    public:
        Machine(string nom, int prix);
        //Machine(json data);
        Machine(int id);
        void set(string n, int p);
        void affichage ();

};

class Ingredient
{
    private:
        string _nom;

    public:
        Ingredient(string nom);
        //Ingredient(json data);
        Ingredient(int id);
        void set (string n);
        void affichage ();
        friend class Prix;

};

class Prix
{
    private:
        unique_ptr<Ingredient> _ingredient;
	    unique_ptr<Departement> _departement;
	    int _prix;
    public:
        Prix(unique_ptr<Ingredient> ingredient, unique_ptr<Departement> departement, int prix);
        Prix(int id);
        void set (string n, int d, int p);
        void affichage ();

};
/*-----------------------------------------------------------------------------------*/
int main()
{

    Departement dep_cons(31,2000);
    dep_cons.affichage();
    /*
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/departement/1"});
    cout << "la réponse est: " << r.text << endl;
    json j= json::parse(r.text);
    cout << "numero: " << j["numero"]<< " et " << "prix_m2: "<< j["prix_m2"]<< endl;
    */
    Departement dep_cons_id(1);
    dep_cons_id.affichage();

    Machine mach_cons("four", 1000);
    mach_cons.affichage();

    Machine mach_cons_id(5);
    mach_cons_id.affichage();

    Ingredient ing_cons("houblon");
    ing_cons.affichage();

    Ingredient ing_cons_id(4);
    ing_cons_id.affichage();


    unique_ptr<Ingredient> houblon = make_unique<Ingredient>("houblon");
    unique_ptr<Departement> departement = make_unique<Departement>(31, 2000);
    Prix prix_cons(move(houblon), move(departement), 20);
    prix_cons.affichage();

    Prix prix_cons_id(4);
    prix_cons_id.affichage();

    return 0;
}
/*----------------------------------------------------------------------------------------------*/
Departement::Departement(int numero, int prix_m2 ) : _numero(numero), _prix_m2(prix_m2)
{}

//Departement::Departement(json data) : _numero(data["numero"]), _prix_m2(data["prix_m2"])
//{}

Departement::Departement(int id)
{
    string url = "http://localhost:8000/departement/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
	json data = json::parse(r.text);
    set(data["numero"], data["prix_m2"]);
}

void Departement::set(int n, int p)
{
    _numero = n;
    _prix_m2 = p;
}

void Departement::affichage ()
{
    cout << "Numero de departement:" <<  _numero <<",\t";
    cout << "Prix du metre carre : "<< _prix_m2 << endl;
}
/*--------------------------------------------------------------------------*/
Machine::Machine(string nom, int prix): _nom(nom), _prix(prix)
{}

//Machine::Machine(json data): _nom(data["nom"]), _prix(data["prix"])
//{}

Machine::Machine(int id)
{
    string url = "http://localhost:8000/machine/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
	json data = json::parse(r.text);
    set(data["nom"], data["prix"]);
}

void Machine::set(string n, int p)
{
    _nom = n;
    _prix = p;
}

void Machine::affichage ()
{
    cout<<"Nom de la machine: "<<_nom<<",\t";
    cout<<"Prix:"<<_prix<<endl;
}
/*-----------------------------------------------------------------------*/
Ingredient::Ingredient(string nom): _nom(nom)
{}

//Ingredient::Ingredient(json data): _nom(data["nom"])
//{}

Ingredient::Ingredient(int id)
{
    string url = "http://localhost:8000/ingredient/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
	json data = json::parse(r.text);
    set(data["nom"]);
}

void Ingredient::set(string n)
{
    _nom = n;
}

void Ingredient::affichage()
{
    cout << "Ingredient: "<< _nom << endl;
}
/*------------------------------------------------------------------------*/
Prix::Prix(unique_ptr<Ingredient> ingredient, unique_ptr<Departement> departement, int prix):_ingredient(std::move(ingredient)), _departement(std::move(departement)), _prix(prix)
{}

Prix::Prix(int id)
{
    string url = "http://localhost:8000/prix/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
	json data = json::parse(r.text);
    set(data["ingredient"], data["departement"], data["prix"]);
}

void Prix::set (string n, int d, int p)
{
    string nom_ingredient = n;
    int numero_departement = d;
    int prix_ = p;

    unique_ptr<Ingredient> ingredient = make_unique<Ingredient>(nom_ingredient);
    unique_ptr<Departement> departement = make_unique<Departement>(numero_departement, 2000);

    _ingredient = move(ingredient);
    _departement = move(departement);
    _prix = prix_;
}

void Prix::affichage ()
{
    cout << "Ingredient: " << _ingredient->_nom << ",\t";
    cout << "Departement: " << _departement->_numero << ",\t";
    cout << "Prix: " << _prix << endl;
}
