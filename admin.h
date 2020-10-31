//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_ADMIN_H
#define PROJETO1_ADMIN_H

#include <string>
#include "user.h"
#include "streamZ.h"


class Admin{
private:
    std::string name;
    StreamZ site;
public:
    Admin(std::string name, StreamZ& site);  //feito
    int getNumStreams() const;                                                          //feito
    int getNumCreatedStreams(Date from, Date to) const;                                 //feito
    float getAvgViews() const;                                                          //feito
    float getAvgViews(Date from, Date to) const;                                        //feito
    int getNumPublicStreams() const;
    int getNumPublicStreams(Date from, Date to) const;
    int getNumPrivateStreams() const;
    int getNumPrivateStreams(Date from, Date to) const;
    std::string getPreferredLanguage(std::vector<Stream*>& streams) const;              //feito
    std::string getPreferredStreamType() const;
    Streamer* getMostViewedStreamer() const;
};

/*exceçoes
-Date to > Date from
-em getAvgViews, getNumStreams()==0  (divisao por 0)
-vetor streams vazio
*/

class badDateComp{
private:
    string reason;
public:
    badDateComp(string reason);
    string what() const;
};

class noActiveStreams{
private:
    string reason;
public:
    noActiveStreams(string reason);
    string what() const;
};

#endif //PROJETO1_ADMIN_H
//A aplicação permite ainda o registo de uma conta de administrador que monitoriza os utilizadores e as
//“streams”. Ao administrador interessa saber a quantidade de “streams” criadas, a média de visualizações por
//“stream” e a quantidade de “streams” privadas ou públicas num determinado intervalo de tempo. Para
//efeitos estatísticos, o administrador quer também saber a linguagem e o tipo de “stream” mais criada
//(privada ou pública) para além do “streamer” com mais visualizações.