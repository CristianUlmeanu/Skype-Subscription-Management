#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <regex>

using namespace std;


//------------------
///CLASA PERSOANA
//------------------

class Persoana
{
protected:
    int id;
    string nume;
    static int nr;
public:
    Persoana(int, string);
    Persoana(Persoana&);
    virtual ~Persoana();
    int id_get()
    {
        return id;
    }
    string nume_get()
    {
        return nume;
    }
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream &in, Persoana& a);
    friend ostream& operator<<(ostream &out, Persoana& a);
    Persoana& operator=(Persoana& a);
    static void nr_persoane()
    {
        cout<<endl<<"Numarul de persoane este: "<<nr;
    }
};
int Persoana::nr;

Persoana::Persoana(int id=0, string nume="")
{
    nr++;
    this->id=id;
    this->nume=nume;
}

Persoana::Persoana(Persoana& a)
{
    this->id=a.id;
    this->nume=a.nume;
}

Persoana::~Persoana()
{
    nr--;
    this->id=0;
    this->nume="";
}

void Persoana::citire(istream &in)
{
    cout<<"ID: ";
    //in>>id;
    id=nr;
    cout<<id<<endl;
    cout<<"Nume: ";
    //in.get();
    getline(in,nume);

}

void Persoana::afisare(ostream &out)
{
    out<<endl;
    out<<endl<<"ID: "<<id<<"; Nume: "<<nume;
}

istream& operator>>(istream &in, Persoana& a)
{
    a.citire(in);
    return in;
}

ostream& operator<<(ostream &out, Persoana& a)
{
    a.afisare(out);
    return out;
}

Persoana& Persoana::operator=(Persoana &a)
{
    this->id=a.id;
    this->nume=a.nume;
}

//------------------
///CLASA ABONAT
//------------------

class Abonat:public Persoana
{
protected:
    string nr_telefon;
public:
    Abonat(int, string, string);
    Abonat(Abonat& a);
    ~Abonat();
    string nr_tel_get()
    {
        return nr_telefon;
    }
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Abonat& a);
    friend ostream& operator<<(ostream &out, Abonat& a);
    Abonat& operator=(Abonat& a);
};

Abonat::Abonat(int id=0,string nume="",string nr_tel=""):Persoana(id,nume)
{
    this->nr_telefon=nr_tel;
}

Abonat::Abonat(Abonat& a):Persoana(a)
{
    this->nr_telefon=a.nr_telefon;
}

Abonat::~Abonat()
{

}

void Abonat::citire(istream &in)
{
    try
    {
        Persoana::citire(in);
        string test_nr_telefon;
        cout<<"Ce nr de telefon are utilizatorul? ";
        getline(in,test_nr_telefon);
        for (int i=0; i<test_nr_telefon.length(); i++)
            if(test_nr_telefon[i]<'0'||test_nr_telefon[i]>'9')
                throw 2;
        nr_telefon=test_nr_telefon;
    }
    catch(int exceptie)
    {
        cout<<"Eroare citire. Numaraul de telefon al persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }

}

void Abonat::afisare(ostream &out)
{
    Persoana::afisare(out);
    out<<endl<<"Numarul de telefon este: "<<nr_telefon;
}

istream& operator>>(istream& in, Abonat& a)
{
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Abonat& a)
{
    a.afisare(out);
    return out;
}

Abonat& Abonat::operator=(Abonat& a)
{
    Persoana::operator=(a);
    this->nr_telefon=a.nr_telefon;
}

//------------------
///CLASA ABONAT_SKYPE
//------------------

class Abonat_Skype:public Abonat
{
protected:
    string id_skype;
public:
    Abonat_Skype(int, string, string, string);
    Abonat_Skype(Abonat_Skype& a);
    ~Abonat_Skype();
    string id_skype_get()
    {
        return id_skype;
    }
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream &in, Abonat_Skype& a);
    friend ostream& operator<<(ostream &out, Abonat_Skype& a);
    Abonat_Skype& operator=(Abonat_Skype& a);
};

Abonat_Skype::Abonat_Skype(int id=0,string nume="",string nr_tel="",string id_skype=""):Abonat(id,nume,nr_tel)
{
    this->id_skype=id_skype;
}

Abonat_Skype::Abonat_Skype(Abonat_Skype& a):Abonat(a)
{
    this->id_skype=a.id_skype;
}

Abonat_Skype::~Abonat_Skype()
{
}

void Abonat_Skype::citire(istream &in)
{
    try
    {
        string test_id;
        Abonat::citire(in);
        cout<<"IDul skypeului este: ";
        getline(in,test_id);
        for(int i=0; i<test_id.length(); i++)
            if(test_id[i]==' ')
                throw 3;
        id_skype=test_id;
    }
    catch (int exceptie)
    {
        cout<<"Eroare citire. IDul nu poate contine spatii.\n";
        exit(EXIT_FAILURE);
    }

}

void Abonat_Skype::afisare(ostream &out)
{
    Abonat::afisare(out);
    out<<endl<<"ID skype este: "<<id_skype;
}

istream& operator>>(istream& in, Abonat_Skype &a)
{
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Abonat_Skype &a)
{
    a.afisare(out);
    return out;
}

Abonat_Skype& Abonat_Skype::operator=(Abonat_Skype& a)
{
    Abonat::operator=(a);
    this->id_skype=a.id_skype;
}

//------------------
///CLASA ABONAT_SKYPE_ROMANIA
//------------------

class Abonat_Skype_Romania:public Abonat_Skype
{
private:
    string adresa_mail;
public:
    Abonat_Skype_Romania(int, string, string, string, string);
    Abonat_Skype_Romania(Abonat_Skype_Romania& a);
    ~Abonat_Skype_Romania();
    string adresa_mail_get()
    {
        return adresa_mail;
    }
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Abonat_Skype_Romania& a);
    friend ostream& operator<<(ostream &out, Abonat_Skype_Romania& a);
    Abonat_Skype_Romania& operator=(Abonat_Skype_Romania& a);
};

Abonat_Skype_Romania::Abonat_Skype_Romania(int id=0, string nume="", string nr_tel="", string id_skype="", string mail=""):Abonat_Skype(id,nume,nr_tel,id_skype)
{
    this->adresa_mail=mail;
}

Abonat_Skype_Romania::Abonat_Skype_Romania(Abonat_Skype_Romania& a):Abonat_Skype(a)
{
    this->adresa_mail=a.adresa_mail;
}

Abonat_Skype_Romania::~Abonat_Skype_Romania()
{
}

void Abonat_Skype_Romania::citire(istream &in)
{

    string test_adresa1;
    int ok=0, verificare=0;
    Abonat_Skype::citire(in);
    while(verificare==0)
    {

        try
        {
            string test_adresa2;
            cout<<"Adresa de mail corespunzatoare contului este: ";
            getline(in,test_adresa2);
            for(int i=0; i<test_adresa2.length(); i++)
                if(test_adresa2[i]==' ')
                    throw 4;
                else
                    test_adresa1=test_adresa2;
            ///Verificare exacta mail valid prin regex, pentru asta a trebuit sa fac un update cu un compiler diferit daca nu merge se poate folosi
            ///varianta 2 dar aceasta face decat o verificare basic a mailului.
            const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
            if(regex_match(test_adresa1, pattern))
            {
                adresa_mail=test_adresa1;
                verificare=1;
            }
            else
                throw 'c';
            ///Verificare mail partiala realizata prin metoda basic.
            /*for(int i=0;i<test_adresa1.length();i++)
            {
            if(test_adresa1[i]=='@')
            ok=1;
            }
            if(ok==0)
            throw 5;
            adresa_mail=test_adresa1;
            verificare=1;
            */
        }
        catch (int exceptie)
        {
            system("cls");
            cout<<"Eroare citire. Mailul nu poate contine spatii.\n"<<"Mailul nu este valid. \n";
            cout<<endl;
            //exit(EXIT_FAILURE);
        }
        catch (char c)
        {
            cout<<"Eroare citire. Mailul nu este valid.\n";
            cout<<endl;
            //exit(EXIT_FAILURE);
        }

    }

}

void Abonat_Skype_Romania::afisare(ostream &out)
{
    Abonat_Skype::afisare(out);
    out<<endl<<"Mailul este: "<<adresa_mail;
}

istream& operator>>(istream& in, Abonat_Skype_Romania &a)
{
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Abonat_Skype_Romania &a)
{
    a.afisare(out);
    return out;
}

Abonat_Skype_Romania& Abonat_Skype_Romania::operator=(Abonat_Skype_Romania& a)
{
    Abonat_Skype::operator=(a);
    this->adresa_mail=a.adresa_mail;
}

//------------------
///CLASA ABONAT_SKYPE_EXTERN
//------------------

class Abonat_Skype_Extern:public Abonat_Skype
{
private:
    string tara;
public:
    Abonat_Skype_Extern(int, string, string, string,string);
    Abonat_Skype_Extern(Abonat_Skype_Extern& a);
    ~Abonat_Skype_Extern();
    string tara_get()
    {
        return tara;
    }
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Abonat_Skype_Extern& a);
    friend ostream& operator<<(ostream &out, Abonat_Skype_Extern& a);
    Abonat_Skype_Extern& operator=(Abonat_Skype_Extern& a);
};

Abonat_Skype_Extern::Abonat_Skype_Extern(int id=0, string nume="", string nr_tel="", string id_skype="", string tara=""):Abonat_Skype(id, nume, nr_tel,id_skype)
{
    this->tara=tara;
}

Abonat_Skype_Extern::Abonat_Skype_Extern(Abonat_Skype_Extern& a):Abonat_Skype(a)
{
    this->tara=a.tara;
}

Abonat_Skype_Extern::~Abonat_Skype_Extern()
{
}

void Abonat_Skype_Extern::citire(istream &in)
{
    Abonat_Skype::citire(in);
    cout<<"Abonatul este din tara: ";
    getline(in,tara);
}

void Abonat_Skype_Extern::afisare(ostream &out)
{
    Abonat_Skype::afisare(out);
    out<<endl<<"Tara de unde este abonatul este: "<<tara;
}

istream& operator>>(istream& in, Abonat_Skype_Extern &a)
{
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Abonat_Skype_Extern &a)
{
    a.afisare(out);
    return out;
}

Abonat_Skype_Extern& Abonat_Skype_Extern::operator=(Abonat_Skype_Extern& a)
{
    Abonat_Skype::operator=(a);
    this->tara=a.tara;
}

//------------------
///CLASA AGENDA
//------------------

class Agenda
{
private:
    Abonat** agenda;
    int nr_persoane;
public:
    Agenda();
    //Agenda(Abonat agenda,int nr_persoane);
    Agenda(Agenda& a);
    ~Agenda();
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Agenda& a);
    friend ostream& operator<<(ostream &out, Agenda& a);
    Abonat* operator[](string comparare);
    Agenda& operator=(Agenda& a);
};

Agenda::Agenda()
{
    this->agenda=nullptr;
    this->nr_persoane=0;
}

/*Agenda::Agenda(Abonat agenda,int nr_persoane)
{
    for(int i=0;i<nr_persoane;i++)
    {string tip_persoana;
    cout<<"Ce tip de abonat este? ";
    getline(cin,tip_persoana);

    }

}*/

Agenda::Agenda(Agenda& a)
{
    Agenda b;
    b.nr_persoane=a.nr_persoane;
    b.agenda=new Abonat*[a.nr_persoane];
    for(int i=0; i<a.nr_persoane; i++)
        b.agenda[i]=a.agenda[i];
}

Agenda::~Agenda()
{
    this->agenda=nullptr;
    this->nr_persoane=0;
}



Agenda& Agenda::operator=(Agenda& a)
{
    this->nr_persoane=a.nr_persoane;
    this->agenda=a.agenda;
}



Abonat* Agenda::operator[](string comparare)
{

    for(int i=0; i<nr_persoane; i++)
    {
        if(comparare==agenda[i]->nume_get())
            return agenda[i];

    }

    return nullptr;

}

void Agenda::citire(istream& in)
{
    //system("cls");
    Abonat *a;
    int i;
    for(i=0; i<nr_persoane;)
    {
        try
        {
            system("cls");
            string tip_abonat;
            cout<<"Ce tip de abonat are persoana "<<i+1<<" ? Acesta poate fi unul dintre urmatoarele: "<<endl;
            cout<<"Abonat"<<endl<<"Abonat Skype"<<endl<<"Abonat Skype Romania"<<endl<<"Abonat Skype Extern"<<endl;
            cout<<"__________________________________"<<endl;
            getline (in,tip_abonat);
            //cout<<tip_abonat;
            if(tip_abonat=="Abonat")
            {
                system("cls");
                a=new Abonat;
                in>>*a;
                agenda[i]=a;
                i++;
            }
            else if (tip_abonat=="Abonat Skype")
            {
                system("cls");
                a=new Abonat_Skype;
                in>>*a;
                agenda[i]=a;
                i++;
            }
            else if(tip_abonat=="Abonat Skype Romania")
            {
                system("cls");
                a=new Abonat_Skype_Romania;
                in>>*a;
                agenda[i]=a;
                i++;
            }
            else if(tip_abonat=="Abonat Skype Extern")
            {
                system("cls");
                a=new Abonat_Skype_Extern;
                in>>*a;
                agenda[i]=a;
                i++;
            }
            else

                throw 8;
        }

        catch (int exceptie)
        {
            system("cls");
            cout<<"Eroare alegere abonament. Abonamentul ales nu este valid!"<<endl;
        }

    }


}

void Agenda::afisare(ostream& out)
{
    for(int i=0; i<nr_persoane; i++)
        out<<*agenda[i];
}

istream& operator>>(istream& in, Agenda& a)
{
    cout<<"Cate persoane contine agenda ta? ";
    in>>a.nr_persoane;
    in.get();
    a.agenda=new Abonat*[a.nr_persoane];
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Agenda& a)
{
    a.afisare(out);
    return out;
}

void tip_cont(Persoana *&a, int &i)
{
    system("cls");
    string test1, test2;
    try
    {
        string test;
        cout<<"Persoana respectiva are abonament?(Da/Nu) ";
        cin>>test;
        if(test!="Da"&&test!="Nu")
            throw 6;
        test1=test;
    }
    catch (int exceptie)
    {
        cout<<"Eroare alegere abonament. Nu s-a ales daca persoana are sau nu abonament!";
        exit(EXIT_FAILURE);
    }

    if(test1=="Da")
    {
        try
        {
            cout<<"Ce tip de persoana este aceasta? ";
            cout<<endl<<"Aceasta poate fi una din urmatoarele variante: ";
            cout<<endl<<"'Abonat'"<<endl<<"'Abonat Skype'"<<endl<<"'Abonat Skype Romania'"<<endl<<"'Abonat Skype Extern'"<<endl;
            cout<<"__________________________________"<<endl;
            cin.get();
            getline(cin,test2);
            if(test2=="Abonat")
            {
                system("cls");
                a=new Abonat;
                cin>>*a;
                i++;
            }
            else if(test2=="Abonat Skype")
            {
                system("cls");
                a=new Abonat_Skype;
                cin>>*a;
                i++;
            }
            else if(test2=="Abonat Skype Romania")
            {
                system("cls");
                a=new Abonat_Skype_Romania;
                cin>>*a;
                i++;
            }
            else if(test2=="Abonat Skype Extern")
            {
                system("cls");
                a=new Abonat_Skype_Extern;
                cin>>*a;
                i++;
            }
            else
                throw 7;

        }
        catch (int exceptie)
        {
            system("cls");
            cout<<"Eroare alegere abonament. Abonamentul ales nu este valid! Acesta poate fi unul dintre urmatoarele: "<<endl;
            cout<<"Abonat"<<endl<<"Abonat Skype"<<endl<<"Abonat Skype Romania"<<endl<<"Abonat Skype Extern"<<endl;
        }

    }
    if(test1=="Nu")
    {
        cin.get();
        a=new Persoana;
        cin>>*a;
        i++;
    }


}

void meniu_principal()
{
    cout<<"Ulmeanu Cristian, Grupa 253, Proiect 2, Implementare Clasa 'Conturi Skype' "<<endl;
    cout<<endl<<"|||-------------------------MENIU-------------------------------|||"<<endl;
    cout<<endl<<" In acest meniu sunt prezente toate actiunile cerute de proiect";
    cout<<endl;
    cout<<endl<<" 1. Citirea persoanelor separat"<<endl;
    cout<<" 2. Afisarea tuturor utilizatorilor"<<endl;
    cout<<" 3. Testare constructori citire, afisare si copiere"<<endl;
    cout<<" 4. Testare Upcasting si Downcasting"<<endl;
    cout<<" 5. Testarea functiei si variabilei statice"<<endl;
    cout<<" 6. Crearea clasei Agenda"<<endl;
    cout<<" 7. Afisare agenda creata"<<endl;
    cout<<" 8. Testare returnare Abonat din agenda bazat pe nume"<<endl;
    cout<<" 9. Iesire"<<endl;
}

int meniu()
{
    int opt, nr_conturi;
    Persoana **a;
    Agenda agenda;
    nr_conturi=0;
    opt=1;
    while (opt!=100)
    {
        meniu_principal();
        cout<<endl<<"Ce actiune doriti sa incercati (actiunea aleasa trebuie sa fie unul din numerele de ordine reprezentative de la 1 la 6)? "<<endl;
        cin>>opt;
        if(opt==1)
        {
            system("cls");
            cout<<"Cati utilizatori doresti sa citesti (numarul trebuie sa fie pozitiv)? ";
            cin>> nr_conturi;
            if (nr_conturi>=0)
            {
                a=new Persoana*[nr_conturi];
                for(int i=0; i<nr_conturi;)
                {
                    tip_cont(a[i],i);
                }
                cout<<"Citirea a fost realizata cu success!";
            }
            else
                cout<<"Numarul de persoane trebuie sa fie mai mare sau egal cu 0";
        }

        if(opt==2)
        {
            system("cls");
            if (nr_conturi==0)
                cout<<"Nu s-a citit niciun utilizator";
            else
            {
                cout<<"Utilizatorii salvati sunt: "<<endl;
                for(int i=0; i<nr_conturi; i++)
                {
                    cout<<endl<<"Utilizatorul "<<i+1<<" este: ";
                    cout<<*a[i];
                }
            }
        }

        if(opt==3)
        {
            ///TESTARE CONSTRUCTORI PE FIECARE CLASA
            system("cls");
            try
            {
                string test;
                cout<<"Alege ce clasa doresti sa ii testezi constructorii dintre clasele : ";
                cout<<endl;
                cout<<"'Persoana'"<<endl<<"'Abonat'"<<endl<<"'Abonat_Skype'"<<endl<<"'Abonat_Skype_Romania"<<endl<<"'Abonat_Skype_Extern'"<<endl;
                cout<<"__________________________________"<<endl;
                cin.get();
                getline(cin,test);
                cout<<test;
                if(test=="Persoana")
                {
                    system("cls");///TESTARE CLASA PERSOANA
                    Persoana b;
                    cin>>b;
                    cout<<b;
                    cout<<endl;
                    Persoana b2(1,"Alex");
                    cout<<b2;
                    cout<<endl;
                    Persoana b3(b2);
                    cout<<b3;
                    cout<<endl;
                }
                else if(test=="Abonat")
                {
                    system("cls");;///TESTARE CLASA ABONAT
                    Abonat b;
                    cin>>b;
                    cout<<b;
                    cout<<endl;
                    Abonat b2(1,"Alex","0741289528");
                    cout<<b2;
                    cout<<endl;
                    Abonat b3(b2);
                    cout<<b3;
                    cout<<endl;
                }
                else if(test=="Abonat Skype")
                {
                    system("cls");///TESTARE CLASA ABONAT_SKYPE
                    Abonat_Skype b;
                    cin>>b;
                    cout<<b;
                    cout<<endl;
                    Abonat_Skype b2(1,"Alex","0741289528","username1");
                    cout<<b2;
                    cout<<endl;
                    Abonat_Skype b3(b2);
                    cout<<b3;
                    cout<<endl;
                }
                else if(test=="Abonat Skype Romania")
                {
                    system("cls");///TESTARE CLASA ABONAT_SKYPE_ROMANIA
                    Abonat_Skype_Romania b;
                    cin>>b;
                    cout<<b;
                    cout<<endl;
                    Abonat_Skype_Romania b2(1,"Alex","0741289528","username1","alex@gmail.com");
                    cout<<b2;
                    cout<<endl;
                    Abonat_Skype_Romania b3(b2);
                    cout<<b3;
                    cout<<endl;
                }
                else if(test=="Abonat Skype Extern")
                {
                    system("cls");///TESTARE CLASA ABONAT_EXTERN
                    Abonat_Skype_Extern b;
                    cin>>b;
                    cout<<b;
                    cout<<endl;
                    Abonat_Skype_Extern b2(1,"Alex","0741289528","username1","Germania");
                    cout<<b2;
                    cout<<endl;
                    Abonat_Skype_Extern b3(b2);
                    cout<<b3;
                    cout<<endl;
                }
                else
                    throw 7;
            }

            catch (int exceptie)
            {
                cout<<"Eroare alegere clasa disponibila. "<<endl;
                exit(EXIT_FAILURE);
            }
        }

        if(opt==4)
        {
            ///TESTARE UPCASTING SI DOWNCASTING
            system("cls");
            try
            {
                string test;
                cout<<"Ce doresti sa incerci intre Upcast si Downcast? ";
                cin.get();
                getline(cin,test);
                if(test=="Upcast")
                {
                    system("cls");///DOWNCASTING
                    Persoana *c=new Abonat;
                    cout<<"Tipul obiectului inainte de upcast este: "<<typeid(c).name()<<endl;
                    cout<<"Deci daca se face downcast din Persoana in Abonat ar trebui sa se citeasca ID, Nume si Numar de telefon."<<endl;
                    cin>>*c;
                    cout<<*c;
                }
                else if(test=="Downcast")
                {
                    system("cls");///UPCASTING
                    Abonat *c=(Abonat*) new Persoana;
                    cout<<"Tipul obiectului inainte de downcast este: "<<typeid(c).name()<<endl;
                    cout<<"Deci daca se face upcast din Abonat In Persoana ar trebui sa se citeasca doar ID si Nume."<<endl;
                    cin>>*c;
                    cout<<*c;
                }
                else
                    throw 8;
            }

            catch (int exceptie)
            {
                cout<<"Eroare citire metoda disponibila.";
                exit(EXIT_FAILURE);
            }

        }

        if (opt==5)
        {
            ///TESTARE STATIC
            system("cls");
            Persoana d1(1,"Alex");
            Abonat d2(2,"Vsl","0741289528");
            Abonat_Skype d3(3,"Cristi","0722972837","Cristi_3");
            Abonat_Skype_Romania d4(4,"Marius","0721435289","Marius_4","marius@gmail.com");
            Abonat_Skype_Extern d5(5,"Marian","0737278528","Marian_5","Germania");
            cout<<d1<<endl<<endl<<d2<<endl<<endl<<d3<<endl<<endl<<d4<<endl<<endl<<d5<<endl;
            Persoana::nr_persoane();

        }

        if (opt==6)
        {
            system("cls");
            cin>>agenda;
            cout<<endl<<"Agenda a fost initializata cu succes!";
        }
        if (opt==7)
        {
            system("cls");
            cout<<"Agenda ta este formata din urmatoarele persoane: ";
            cout<<endl;
            cout<<agenda<<endl;
        }
        if (opt==8)
        {
            system("cls");
            string nume;
            cout<<"Utilizatorul cu ce nume doresti sa a il verifica daca exista in agenda? ";
            cin.get();
            getline(cin,nume);
            cout<<endl;
            if(agenda[nume]!=0)
                cout<<*agenda[nume]<<endl;
            else
                cout<<"Nu este niciun abonat cu numele acesta.";

        }


        if (opt==9)
        {
            system("cls");
            cout<<"O zi buna!";
            return 0;
        }
        if ((opt<1)||(opt>10))
        {
            system("cls");
            cout<<"Optiunea nu este valida, te rog alege un numar intre 1 si 9";
        }
        cout<<endl;
        system("pause");
        system("cls");
    }
}

int main()
{

    meniu();
    return 0;
}
