#include "cards.h"

int main(void) {
  card_t card;
  card.value = 11;
  card.suit = SPADES;
  print_card(card);

}
