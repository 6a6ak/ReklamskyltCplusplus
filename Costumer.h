#ifndef __COSTUMER_H
#define __COSTUMER_H

class Costumer{
 public:
 char companyname[100];
 char messages[3][100];
 int pay;

 public:
 Costumer(char *companyname, char *message1, char *message2, char *message3, int pay);
 
};


#endif