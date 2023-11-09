#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <memory>

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
        void set(int n, int p);
        void affichage ();
        friend class Prix;
        friend class Usine;
};

class Machine
{
    private:
        string _nom;
        int _prix;
    public:
        Machine(string nom, int prix);
        Machine(json data);
        Machine(int id);
        void set(string n, int p);
        void affichage ();
        friend class Action;
        friend class Usine;

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
        friend class QuantiteIngredient;
        friend class Action;
        friend class Recette;
        friend class Usine;

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

class QuantiteIngredient
{
    private:
        unique_ptr<Ingredient> _ingredient;
        int _quantite;

    public:
        QuantiteIngredient(unique_ptr<Ingredient> ingredient, int quantite);
        QuantiteIngredient(int id);
        void set (string n, int q);
        void affichage();
        friend class Action;
        friend class Recette;
        friend class Usine;

};

class Action
{
    private:
        unique_ptr<Machine> _machine;
        string _commande;
        int _duree;
        vector<unique_ptr<QuantiteIngredient>> _ingredients;

    public:
        Action(unique_ptr<Machine> machine, string commande, int duree, vector<unique_ptr<QuantiteIngredient>> ingredients);
        Action(int id);
        void set (string n, string c, int d, vector<string> i);
        void affichage();
        friend class Recette;
};

class Recette
{
    private:
        string _nom;
        unique_ptr<Action> _action;

    public:
        Recette(string nom, unique_ptr<Action> action);
        Recette(int id);
        void set (string n, vector<string> i);
        void affichage();
        friend class Usine;

};
class Usine
{
    private:
        unique_ptr<Departement> _departement;
        int _taille;
        vector<unique_ptr<Machine>> _machines;
        vector<unique_ptr<Recette>> _recettes;
        vector<unique_ptr<QuantiteIngredient>> _stocks;

    public:
        Usine(unique_ptr<Departement> departement, int taille, vector<unique_ptr<Machine>> machines, vector<unique_ptr<Recette>> recettes,\
         vector<unique_ptr<QuantiteIngredient>> stocks);
        //Usine(int id);
        //void set(string n, int t, vector<string> nsm, vector<string> nsr, vector<string> nsi);
        void affichage();

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
    json data_dep;
    data_dep ["numero"] = 31;
    data_dep ["prix_m2"] = 2000;

    Departement dep_cons_json(data_dep);
    dep_cons_json.affichage();

    Departement dep_cons_id(1);
    dep_cons_id.affichage();

    /*json data_mach;
    data_mach ["nom"] = "four";
    data_mach ["prix"] = 1000;

    Machine mach_cons_json(data_mach);
    mach_cons_json.affichage();*/

    Machine mach_cons("four", 1000);
    mach_cons.affichage();

    Machine mach_cons_id(5);
    mach_cons_id.affichage();

    Ingredient ing_cons("houblon");
    ing_cons.affichage();

    /*json data_ing;
    data_ing ["nom"] = "orge";
    Ingredient ing_cons_json(data_ing);
    ing_cons_json.affichage();*/

    Ingredient ing_cons_id(4);
    ing_cons_id.affichage();


    unique_ptr<Ingredient> houblon = make_unique<Ingredient>("houblon");
    unique_ptr<Departement> departement = make_unique<Departement>(31, 2000);
    Prix prix_cons(move(houblon), move(departement), 20);
    prix_cons.affichage();

    Prix prix_cons_id(4);
    prix_cons_id.affichage();

    unique_ptr<Ingredient> orge = make_unique<Ingredient>("orge");
    QuantiteIngredient qi_cons(move(orge), 100);
    qi_cons.affichage();

    QuantiteIngredient qi_id(9);
    qi_id.affichage();

    // Stockez les objets dans des variables
    unique_ptr<Machine> four = make_unique<Machine>("four", 1000);
    unique_ptr<Ingredient> orge_ = make_unique<Ingredient>("orge");
    unique_ptr<Ingredient> houblon_ = make_unique<Ingredient>("houblon");
    vector<unique_ptr<QuantiteIngredient>> ings;
    ings.push_back(make_unique<QuantiteIngredient>( move(houblon_) , 50));
    ings.push_back(make_unique<QuantiteIngredient>( move(orge_) , 100));

    // Créez un objet Action en utilisant les variables précédemment créées
    Action act_cons(move(four), "ebullition", 5, move(ings));
    act_cons.affichage();

    Action act_cons_id(4);
    act_cons_id.affichage();


    unique_ptr<Machine> ffour = make_unique<Machine>("four", 1000);
    unique_ptr<Ingredient> oorge_ = make_unique<Ingredient>("orge");
    unique_ptr<Ingredient> hhoublon_ = make_unique<Ingredient>("houblon");
    vector<unique_ptr<QuantiteIngredient>> iings;
    iings.push_back(make_unique<QuantiteIngredient>( move(hhoublon_) , 50));
    iings.push_back(make_unique<QuantiteIngredient>( move(oorge_) , 100));

    unique_ptr<Action> actt = make_unique<Action>(move(ffour),"ebullition", 5, move(iings) );

    Recette rec_cons("witbier",move(actt) );
    rec_cons.affichage();

    Recette rec_cons_id (4);
    rec_cons_id.affichage();

    unique_ptr<Departement> dep_ = make_unique<Departement>(31, 2000);
    vector<unique_ptr<Machine>> machs;
    machs.push_back(make_unique<Machine>("four", 1000));
    machs.push_back(make_unique<Machine>("mash_tun", 2000));
    unique_ptr<Ingredient> ooorge_ = make_unique<Ingredient>("orge");
    unique_ptr<Ingredient> hhhoublon_ = make_unique<Ingredient>("houblon");
    vector<unique_ptr<QuantiteIngredient>> iiings;
    iiings.push_back(make_unique<QuantiteIngredient>( move(hhhoublon_) , 50));
    iiings.push_back(make_unique<QuantiteIngredient>( move(ooorge_) , 100));

    unique_ptr<Machine> fffour = make_unique<Machine>("four", 1000);
    unique_ptr<Ingredient> oooorge_ = make_unique<Ingredient>("orge");
    unique_ptr<Ingredient> hhhhoublon_ = make_unique<Ingredient>("houblon");
    vector<unique_ptr<QuantiteIngredient>> iiiings;
    iiiings.push_back(make_unique<QuantiteIngredient>( move(hhhhoublon_) , 50));
    iiiings.push_back(make_unique<QuantiteIngredient>( move(oooorge_) , 100));

    unique_ptr<Action> acttt = make_unique<Action>(move(fffour),"ebullition", 5, move(iiiings) );
    vector<unique_ptr<Recette>> recc;
    recc.push_back(make_unique<Recette>("witbier", move(acttt)));


    Usine usine_cons(move(dep_), 50, move(machs), move(recc), move(iiings));
    usine_cons.affichage();


    return 0;
}
/*----------------------------------------------------------------------------------------------*/
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

void Departement::affichage ()
{
    cout << "Numero de departement:" <<  _numero <<",\t";
    cout << "Prix du metre carre : "<< _prix_m2 << endl;
}
/*--------------------------------------------------------------------------*/
Machine::Machine(string nom, int prix): _nom(nom), _prix(prix)
{}

Machine::Machine(json data): _nom(data["nom"]), _prix(data["prix"])
{}

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

/*Ingredient::Ingredient(json data): _nom(data["nom"])
{}*/

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
Prix::Prix(unique_ptr<Ingredient> ingredient, unique_ptr<Departement> departement, int prix):_ingredient(std::move(ingredient)),\
 _departement(std::move(departement)), _prix(prix)
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
/*----------------------------------------------------------------------------*/
QuantiteIngredient::QuantiteIngredient(unique_ptr<Ingredient> ingredient, int quantite): _ingredient(std::move(ingredient)), _quantite(quantite)
{}

QuantiteIngredient::QuantiteIngredient(int id)
{
    string url = "http://localhost:8000/quantiteingredient/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
	json data = json::parse(r.text);
    set(data["ingredient"], data["quantite"]);
}
void QuantiteIngredient::set (string n, int q)
{
    string nom_ingredient = n;
    int quantite_ = q;

    unique_ptr<Ingredient> ingredient = make_unique<Ingredient>(nom_ingredient);

    _ingredient = move(ingredient);
    _quantite = quantite_;
}
void QuantiteIngredient::affichage()
{
    cout << "Ingredient: " << _ingredient->_nom << ",\t";
    cout << "Quantite: " << _quantite << endl;
}
/*------------------------------------------------------------------*/
Action::Action(unique_ptr<Machine> machine, string commande, int duree, vector<unique_ptr<QuantiteIngredient>> ingredients): _machine(move(machine)),\
 _commande(commande), _duree(duree), _ingredients(move(ingredients))
{}

Action::Action(int id)
{
    string url = "http://localhost:8000/action/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
	json data = json::parse(r.text);
    set(data["machine"], data["commande"], data["duree"], data["ingredients"]);

}
void Action::set (string n, string c, int d, vector<string> i)
{
    string nom_machine = n;
    string commande_ = c;
    int duree_ = d;
    vector<string> ingredients_ = i;

    unique_ptr<Machine> mach = make_unique<Machine>(nom_machine, 1000);
    vector<unique_ptr<QuantiteIngredient>> ingss;
    for(const auto& i : ingredients_)
    {
        ingss.push_back(make_unique<QuantiteIngredient>(move(make_unique<Ingredient>(i)),100));
    }

    _machine = move(mach);
    _ingredients = move(ingss);
    _commande = commande_;
    _duree = duree_;
}

void Action::affichage()
{
    cout << "Machine: " << _machine->_nom << ",\t";
    cout << "Commande: " << _commande << ",\t";
    cout << "Duree: " << _duree << ",\t";
    int i=0;
    cout << "Ingredients: [";
    for (const auto& ing : _ingredients)
    {
        cout << ing-> _ingredient->_nom ;
        i+=1;
        if(i < _ingredients.size()){
            cout<<", ";
        }
    }
    cout << "]" << endl;
}
/*----------------------------------------------------------------------------*/
Recette::Recette(string nom, unique_ptr<Action> action): _nom(nom), _action(std::move(action))
{}

Recette::Recette(int id)
{
    string url = "http://localhost:8000/recette/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
	json data = json::parse(r.text);
    set(data["nom"], data["action_ingredients"]);
}

void Recette::set(string n, vector<string> i)
{
    string nom_recette = n;

    vector<string> action_ingredients_ = i;


    unique_ptr<Machine> four = make_unique<Machine>("four", 1000);
    vector<unique_ptr<QuantiteIngredient>> ingsss;
    for(const auto& i : action_ingredients_)
    {
        ingsss.push_back(make_unique<QuantiteIngredient>(move(make_unique<Ingredient>(i)),100));
    }
    unique_ptr<Action> acttt = make_unique<Action>(move(four),"ebullition", 5, move(ingsss) );


    _nom = nom_recette;
    _action = move(acttt);
}

void Recette::affichage()
{
    cout<<"Recette: "<<_nom<<", \t";
    int i=0;
    cout<<"Ingredients: [";
     for (const auto& ing : _action->_ingredients)
    {
        cout << ing->_ingredient->_nom;
        i+=1;
        if(i < _action->_ingredients.size()){
            cout<<", ";
        }
    }
    cout << "]" << endl;

}
/*----------------------------------------------------------------------------------------*/
Usine::Usine(unique_ptr<Departement> departement, int taille, vector<unique_ptr<Machine>> machines, vector<unique_ptr<Recette>> recettes,\
 vector<unique_ptr<QuantiteIngredient>> stocks): _departement(move(departement)), _taille(taille), _machines(move(machines)), _recettes(move(recettes)),\
  _stocks(move(stocks))
  {}

void Usine::affichage(){
    cout<<"Departement: "<< _departement->_numero <<", \t";
    cout<<"Taille: "<< _taille <<", \t";
    int i=0;
    cout<<"Machine: [";
    for(const auto& mach : _machines){
        cout<<mach->_nom;
        i+=1;
        if(i < _machines.size()){
            cout<<", ";
        }
    }
    cout << "], \t";
    i=0;
    cout<<"Recette: [";
    for(const auto& rec : _recettes){
        cout<<rec->_nom;
        i+=1;
        if(i < _recettes.size()){
            cout<<", ";
        }
    }
    cout << "], \t";
    cout<<"Ingredients: [";
    i=0;
    for (const auto& ing : _stocks){
        cout << ing->_ingredient->_nom;
        i+=1;
        if(i < _stocks.size()){
            cout<<", ";
        }
    }
    cout << "]" << endl;
}
