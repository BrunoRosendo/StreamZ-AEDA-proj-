//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_PASTSTREAM_H
#define PROJETO1_PASTSTREAM_H

#include <string>

struct PastStream{
    /**
     * @brief Creates an empty past stream struct. Its members should be updated before using it
     */
    PastStream(){};

    /**
     * @brief Creates a struct storing a past stream, containing the stream title, its ID and the number of viewers
     * when it ended
     * @param stream Pointer to the stream intended to store
     */
    PastStream(Stream* stream){this->name = stream->getTitle(), this->noViewers = 0, this->id = stream->getId();};
    std::string name;
    int noViewers;
    unsigned int id;
};

#endif //PROJETO1_PASTSTREAM_H
