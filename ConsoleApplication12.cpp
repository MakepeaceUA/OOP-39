#include <iostream>
#include <string>
#include<windows.h>
using namespace std;


class IDocument
{
public:
    virtual void Open() abstract;
    virtual void Close() abstract;
    virtual void Read() abstract;
};

class RealDocument : public IDocument
{
public:
    RealDocument()
    {
        cout << "Loading new document. Wait...\n";
        Sleep(3000);
    }
    void Open() override
    {
        cout << "Document opened.\n";
    }
    void Close() override
    {
        cout << "Document closed.\n";
    }
    void Read() override
    {
        cout << "Document reading.\n";
    }
};

class DocumentProxy : public IDocument
{
    RealDocument* doc;  
public:
    DocumentProxy()
    {
        doc = nullptr;
    }
    ~DocumentProxy()
    {
        delete doc;
    }
    void Open()
    {
        if (doc == nullptr)
            doc = new RealDocument();
        doc->Open();
    }
    void Close()
    {
        doc->Close();
    }
    void Read()
    {
        if (doc == nullptr)
            doc = new RealDocument();
        doc->Read();
    }
};

void client(IDocument* p)
{
    p->Open();
    p->Read();
    p->Close();
}
int main()
{
    IDocument* p = new DocumentProxy();
    client(p);
}
