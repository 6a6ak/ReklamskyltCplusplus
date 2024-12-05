#ifndef __COSTUMER_H
#define __COSTUMER_H

class Costumer
{
public:
    char companyname[100];
    char message1[100];
    char message2[100];
    char message3[100];
    int pay;

public:
    Costumer(const char *companyname, const char *message1, const char *message2, const char *message3, int pay);

    // Getter methods
    const char* getCompanyName() const;
    const char* getMessage1() const;
    const char* getMessage2() const;
    const char* getMessage3() const;
    int getPay() const;

    // Setter methods
    void setCompanyName(const char* companyname);
    void setMessage1(const char* message1);
    void setMessage2(const char* message2);
    void setMessage3(const char* message3);
    void setPay(int pay);
};

#endif