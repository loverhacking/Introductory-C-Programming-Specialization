#include <stdio.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
    if (fc->n_decks <= index) {
        fc->decks = realloc(fc->decks, (index + 1) * sizeof(deck_t));
	for (size_t i = fc->n_decks; i <= index; i++) {
            fc->decks[i].cards = NULL;
            fc->decks[i].n_cards = 0;
        }
        fc->n_decks = index + 1;
    }
    fc->decks[index].n_cards++;
    fc->decks[index].cards = realloc(fc->decks[index].cards,
      fc->decks[index].n_cards * sizeof(card_t*));
    fc->decks[index].cards[fc->decks[index].n_cards - 1]= ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    if (deck->n_cards < fc->n_decks) {
        fprintf(stderr, "no enough cards in deck");
        exit(EXIT_FAILURE);
    }
    card_t ** cards = deck->cards;
    for (size_t i = 0; i < fc->n_decks; i++) {
        for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
             fc->decks[i].cards[j]->suit = cards[i]->suit;
             fc->decks[i].cards[j]->value = cards[i]->value;
        }
    }
}
