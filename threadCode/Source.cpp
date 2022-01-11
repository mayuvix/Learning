#include <iostream>
#include <thread>
#include <vector>  
#include <string>  


using namespace std;
class Father
{ 
public:
    void PrintSelf()
    {
        cout << "Father" << endl;
    }
    virtual ~Father() {}
};

class FalseFather
{
public:
    void PrintSelf()
    {
        cout << "FalseFather" << endl;
    }
    virtual ~FalseFather() {}
};

class Child :public Father
{
public:
    void PrintSelf()
    {
        cout << "Child" << endl;
    }
    virtual ~Child() {}
};

void fr(int&& i)
{
    cout << i << endl;
}

void fl(int& i)
{
    cout << i << endl;
}
void flc(const int& i)
{
    cout << i << endl;
}

int&& geti()
{
    return 10;
}


int main()
{
    unsigned int in = std::thread::hardware_concurrency();
    std::cout << "硬件支持并发数："<<in << std::endl;
    
    void* pVoid = nullptr;
    Father* pFa = nullptr;
    Child* pCh = nullptr;
    FalseFather* pFalseFa = nullptr;
    //Father fa;
    //pFa = &fa;

    int&& a = 10;
    int b = 10;
    int&& c = geti();
    fr(10);
    fr(a);
    fl(c);
    fr(b);
    fl(b);
    fr(geti());
    fl(geti());
    flc(geti());
    pFa->PrintSelf();
    pCh->PrintSelf();

    pCh = dynamic_cast<Child*>(pFa);
    pCh->PrintSelf();

    pFa = new Child();
    pFa->PrintSelf();
    pCh = static_cast<Child*>(pFa);
    pCh->PrintSelf();
    pFa = static_cast<Father*>(pFa);
    pFa->PrintSelf();

    pFalseFa = static_cast<FalseFather*>(pVoid);
    pFa->PrintSelf();
}
