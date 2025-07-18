#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  card_t ** cards = hand->cards;
  for (size_t i = 0; i < hand->n_cards; i++) {
    print_card(*cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** cards = d->cards;
  for (size_t i = 0; i < d->n_cards; i++) {
    if (cards[i]->value == c.value && cards[i]->suit == c.suit) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t ** cards = d->cards;

  // Fisher-Yates algorithm
  for (size_t i = d->n_cards - 1; i > 0; i--) {

    // randomly generate j between [0, i]
    size_t j = rand() % (i + 1);

    // samp cards[i] and cards[j];
    card_t * temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for (int i = 0; i < 51; i++) {
    assert(deck_contains(d, card_from_num(i)) == 1);
  }
}

void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards,
    deck->n_cards * sizeof(card_t*));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(card_t));
  deck->cards[deck->n_cards - 1]->value = c.value;
  deck->cards[deck->n_cards - 1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck) {
  card_t * card = malloc(sizeof(card_t));
  card->suit = 0;
  card->value = 0;
  add_card_to(deck, *card);
  free(card);
  return deck->cards[deck -> n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * deck = malloc(sizeof(deck_t));
  deck->n_cards = 0;
  deck->cards = NULL;

  for (size_t i = 0; i < 52; i++) {
    card_t tmp = card_from_num(i);
    if (!deck_contains(excluded_cards, tmp)) {
      add_card_to(deck, tmp);
    }
  }
  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * exclude  = malloc(sizeof(deck_t));
  exclude->cards = NULL;
  exclude->n_cards = 0;
  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++) {
      if (hands[i]->cards[j]->value != 0) {
	if (deck_contains(exclude, *hands[i]->cards[j]) == 0) {
	  add_card_to(exclude, *hands[i]->cards[j]);
	}
      }
    }
  }
  deck_t * ans = make_deck_exclude(exclude);
  free_deck(exclude);
  return ans;
}

void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
