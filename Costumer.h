#ifndef __COSTUMER_H
#define __COSTUMER_H

class Costumer{
 private:
 char messages[3][100];

 public:
 Costumer(char *message1, char *message2, char *message3);
 char* GetMessage(int i);

};


#endif