#ifndef __COSTUMER_H
#define __COSTUMER_H

class Costumer{
 private:
 char companyname[100];
 char message1[100];
 char message2[100];
 char message3[100];
 int pay;

 public:
 Costumer(char *companyname, char *message1, char *message2, char *message3, int pay);
};

#endif