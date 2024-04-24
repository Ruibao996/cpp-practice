# include <iostream>
# include <string>
using namespace std;

class CMyString
{
    public:
        CMyString(char* pData = nullptr);
        CMyString(const CMyString& str);
        ~CMyString(void);

        CMyString& operator=(const CMyString &str);
    private:
        char* m_pData;
};

CMyString::CMyString(char* pData) {
    if (pData == nullptr)
    {
        this->m_pData = new char[1];
        this->m_pData[0] = '\0';
    }
    else{
        m_pData = new char[strlen(pData) + 1];
        strcpy(this->m_pData, pData);
    }
}

CMyString::CMyString(const CMyString& str) {
    this->m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(this->m_pData, str.m_pData);
}

CMyString::~CMyString() {
    delete[] m_pData;
}

CMyString& CMyString::operator=(const CMyString &str)
{
    if (this == &str)
    {
        return *this;
    }

    delete []m_pData;
    m_pData = nullptr;

    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);

    return *this;
}

/*
however this copy operator fuction can't deal with the Exceptation Safety, its success
on running is based on that we can allocate enough memory, if we can't the MyString
can't stay robust, therefore we should creat a tempstring then copy it.
*/


CMyString& CMyString::operator=(const CMyString &str)
{
    if (this != &str)
    {
        CMyString strTemp(str);

        char* pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData;

        m_pData = pTemp;
    }

    return *this;
}

/* 
here we say the second one copy-and-swap is better when we creat a new CMystring
 if the memory is out of usage we could throw a warning in creat the CMystring and
 don't change the origianl one.
*/