//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_PASTSTREAM_H
#define PROJETO1_PASTSTREAM_H

#include <string>

struct PastStream{
    PastStream(){;};
    PastStream(Stream* stream){this->name = stream->getTitle(), this->noViewers = 0, this->id = stream->getId();};
    std::string name;
    int noViewers;
    unsigned int id;
};

#endif //PROJETO1_PASTSTREAM_H
