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
        Departement(json data);
        Departement(int id);
        friend ostream & operator<< (ostream & f, const Departement & d);
        void set(int n, int p);
        void affichage ();

};

int main()
{
    Departement dep1(31,1500);
    dep1.affichage();

    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/departement/1"});
    cout << "la réponse est: " << r.text << endl;
    json j= json::parse(r.text);
    cout << "numero: " << j["numero"]<< " et " << "prix_m2: "<< j["prix_m2"]<< endl;

    Departement dep2(89,3000);
    cout<<dep2;

    return 0;
}

Departement::Departement(int numero, int prix_m2 ) : _numero(numero), _prix_m2(prix_m2)
{}

Departement::Departement(json data) : _numero(data["numero"]), _prix_m2(data["prix_m2"])
{}

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

ostream & operator<< (ostream & f, const Departement & d)
{
    return f<<"Numero de departement: "<<d._numero <<",\t"<<"Prix du metre carre: "<<d._prix_m2 <<endl;
}

void Departement::affichage ()
{
    cout << "Numero de departement:" <<  _numero <<",\t";
    cout << "Prix du metre carre : "<< _prix_m2 << endl;
}
