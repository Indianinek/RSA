#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;

class RSA
{
public:
    long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
    string msg;
    
    RSA(long x, long y, string s)// funkcja ktora otrzymuje P i Q oraz tekst do zaszyfrowania
    {
        long i;
        p = x;
        q = y;
        msg = s;
        n=p*q;
        t=(p-1)*(q-1); // funkcja eulera jest opisana t
        for(i=0;i<msg.size();i++)
        {
            m[i] = msg[i];
        }
    }
    
    
    int prime(long pr) // funkcja ktora sprawdza czy liczba jest pierwsza
    {
        int i;
        j=sqrt(pr);
        for (i=2;i<=j;i++) {
            if(pr%i==0)
                return 0;
        }
        return 1;
    }
    
    
    void ce() // obliczenia funkcji klucza prywatnego d na podstawie e klucza publicznego
    {
        int k;
        k=0;
        for (i=2;i<t;i++)
        {
            if(t%i==0)
                continue;
            flag=prime(i);
            if( flag==1 && i!=p && i!=q)
            {
                e[k]=i;
                flag=cd(e[k]);
                if(flag>0) {
                    d[k]=flag;
                    k++;
                }
                if(k==99)
                    break;
            }
        }
        for (i=0;i<j-1;i++)
        {
            cout<<(i+1)<<"\t("<<e[i]<<","<<d[i]<<")"<<endl; // wyswietlanie d obliczane jest na podstawie e
        }
        cout<<endl;
    }
    
    
    long int cd(long int x)
    {
        long int k=1;
        while(1) {
            k=k+t;
            if(k%x==0)
                return(k/x);
        }
    }
    
    
    void encrypt(int x) // funkcja szyfrująca
    {
        long int pt,ct,key=e[x-1],k,len; //
        cout<<"Uzyta wartosc e to: "<<key<<endl;
        i=0;
        len = msg.size();
        while(i!=len) // pętla szyfruje kazdy znak
        {
            pt=m[i];
            pt=pt-96;
            k=1;
            for (j=0;j<key;j++)
            {
                k=k*pt;
                k=k%n;
            }
            temp[i]=k;
            ct=k+96;
            en[i]=ct;
            i++;
        }
        en[i]=-1;
        cout<<"Zaszyfrowana wiadomosc : "<<endl;
        for (i=0;en[i]!=-1;i++) // wyswietlanie zaszyfrowanego tekstu
            cout<<(char)en[i];
        cout<<endl;
    }
    
    void decrypt(int x) // funkcja deszyfrująca x to parametr e
    {
        long int pt,ct,key=d[x-1],k; // key to
        cout<<"Wartosc d rowna sie:"<<key<<endl;
        i=0;
        while(en[i]!=-1) // operacja szyfrująca kazdy znak
        {
            ct=temp[i];
            k=1;
            for (j=0;j<key;j++) {
                k=k*ct;
                k=k%n;
            }
            pt=k+96;
            m[i]=pt;
            i++;
        }
        m[i]=-1;
        cout<<"Odszyfrowana wiadomosc: "<<endl;
        for (i=0;m[i]!=-1;i++) //
            cout<<(char)m[i];
        cout<<endl;
    }
};


int main()
{
    long i,n,t,p,q,x;
    cout<<"Podaj liczby pierwsze P i Q"<<endl;
    cin>>p>>q;
    cout<<"Podaj wiadomosc"<<endl;
    string msg;
    getchar();
    getline(cin,msg);
    RSA ob(p,q,msg);
    cout<<"Mozlwie wartosci (e,d)"<<endl;
    ob.ce();
    cout<<"Jakie wartosci wybrac(e,d)?"<<endl;
    cin>>x;
    cout<<endl;
    ob.encrypt(x);
    cout<<endl;
    ob.decrypt(x);
    return 0;
}


