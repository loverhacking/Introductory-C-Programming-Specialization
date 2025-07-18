#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  // Check command line arguments/report errors
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "incorrect number of arguments");
    return EXIT_FAILURE;
  }

  // Open the input file
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "can not open file");
    return EXIT_FAILURE;
  }

  unsigned num_trials = 10000;

  if (argc == 3) {
    num_trials = atoi(argv[2]);
  }

  // read the hands in it
  size_t n_hands = 0;

  future_cards_t * future_cards = malloc(sizeof(future_cards_t));
  future_cards->n_decks = 0;
  future_cards->decks = NULL;
  deck_t ** hands = read_input(f, &n_hands, future_cards);

  // Create a deck with the remaining cards
  deck_t * hand = build_remaining_deck(hands, n_hands);

  // Create an array to count how many times each hand
  unsigned * count = malloc((n_hands + 1) * sizeof(unsigned));
  for (size_t i = 0; i < n_hands + 1; i++) {
    count[i] = 0;
  }

  // Do each Monte Carlo trial
  for (size_t i = 0; i < num_trials; i++) {
    shuffle(hand);
    future_cards_from_deck(hand, future_cards);

    size_t max_index = 0;
    unsigned max_count = 1;
    for (size_t j = 1; j < n_hands; j++) {
      int cmp = compare_hands(hands[j], hands[max_index]);
      if (cmp > 0) {
        max_index = j;
        max_count = 1;
      } else if (cmp == 0) {
        max_count++;
      }
    }
    if (max_count > 1) {
      count[n_hands]++; // a tie
    } else {
      count[max_index]++; // win
    }
  }

  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i,
           count[i], num_trials, count[i] / (double) num_trials * 100);
  }
  printf("And there were %u ties\n", count[n_hands]);

  int result = fclose(f);
  if (result != 0) {
    fprintf(stderr, "can not close file");
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < n_hands; i++) {
     free_deck(hands[i]);
  }
  free(hands);

  free_deck(hand);

  for (size_t i = 0; i < future_cards->n_decks; i++) {
    // notice the specific cards in future_cards have been freed in hands
    free(future_cards->decks[i].cards);
  }
  free(future_cards->decks);
  free(future_cards);

  free(count);

  return EXIT_SUCCESS;
}
