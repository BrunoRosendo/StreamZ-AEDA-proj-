//
// Created by joaog on 10/23/2020.
//

#ifndef PROJETO1_PASTSTREAM_H
#define PROJETO1_PASTSTREAM_H

#include <string>

/**
 * @brief Struct used to store a Stream which has already ended
 */
struct PastStream{
    /**
     * @brief Creates an empty PastStream struct. Its members should be updated before using it
     */
    PastStream(){Stream::nextID++;};

    /**
     * @brief Creates a struct storing a past Stream, containing the Stream title, its ID and the number of Viewers
     * when it ended
     * @param stream Pointer to the stream intended to store
     */
    PastStream(Stream* stream){this->name = stream->getTitle(), this->noViewers = 0, this->id = stream->getId(),
                               this->StartDate = stream->getStartDate();};

    /**
     * @brief Name of the Stream
     */
    std::string name;

    /**
     * @brief Number of Viewers the moment the Stream ended
     */
    int noViewers;

    /**
     * @brief ID of the Stream
     */
    unsigned int id;

    /**
     * @brief Start Date of the Stream
     */
    Date StartDate;
};

#endif //PROJETO1_PASTSTREAM_H
