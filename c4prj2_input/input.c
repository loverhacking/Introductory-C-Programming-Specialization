

#include <stdio.h>
#include <string.h>
#include "deck.h"
#include "future.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t * deck = malloc(sizeof(deck_t));
    deck->n_cards = 0;
    deck->cards = NULL;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '\n' || str[i] == ' ') {
            continue;
        }
        if (str[i] == '?') {
	    int index = atoi(&str[i + 1]);
	    add_future_card(fc, index, add_empty_card(deck));
            while (str[i] != '\n' && str[i] != ' ') {
                i++;
            }
        } else {
            card_t card = card_from_letters(str[i],
                str[i + 1]);
            add_card_to(deck, card);
            i++;
        }
    }
    if (deck->n_cards < 5) {
        fprintf(stderr, "no enough cards");
        exit(EXIT_FAILURE);
    }
    return deck;
}


deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    size_t sz = 0;
    char * line = NULL;
    deck_t ** decks = NULL;
    size_t count = 0;

    while (getline(&line, &sz, f) >= 0) {
        decks = realloc(decks, (count + 1) * sizeof(deck_t*));
        decks[count] = hand_from_string(line, fc);
        count++;

    }
    free(line);
    *n_hands = count;

    return decks;
}
