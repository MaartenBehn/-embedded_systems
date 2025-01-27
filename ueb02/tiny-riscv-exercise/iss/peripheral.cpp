/*
 * peripheral.cpp
 *
 *  Created on: Oct 27, 2022
 *      Author: pp
 */

#include <cassert>
#include <iostream>
#include <random>
#include <cstring>
#include "peripheral.hpp"

uint32_t CharacterPrinter::load_data(const Address addr) {
    if (addr == 0x0) {
        return selector;
    }

    assert(addr == 0x4);

    switch (selector) {
        case 0:
        {
            uint32_t value = rand();
            return value;
        }
        case 1:
        {
            // https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
            // https://www.oreilly.com/library/view/secure-programming-cookbook/0596003943/ch11s14.html
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(33, 126);

            uint32_t value = distr(gen);
            return value;
        }
        case 2:
        {
            // https://stackoverflow.com/questions/21022644/how-to-get-the-real-and-total-length-of-char-char-array
            
            char* text = "Never gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you";

            uint32_t value = text[song_counter];
            song_counter = ((song_counter + 1) % strlen(text));

            return value;
        }
    }

	return 0;
}

void CharacterPrinter::store_data(const Address addr, const uint32_t value) {
    assert(addr == 0x0);

    selector = value;
}
