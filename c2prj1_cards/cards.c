#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch (r) {
    case STRAIGHT_FLUSH:  return "STRAIGHT_FLUSH";
    case FOUR_OF_A_KIND:  return "FOUR_OF_A_KIND";
    case FULL_HOUSE:      return "FULL_HOUSE";
    case STRAIGHT:        return "STRAIGHT";
    case FLUSH:           return "FLUSH";
    case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
    case TWO_PAIR:        return "TWO_PAIR";
    case PAIR:            return "PAIR";
    case NOTHING:         return "NOTHING";
    default:              return " ";
  }
}

char value_letter(card_t c) {
  if (c.value <= 9) {
    return c.value + '0';
  }
  if (c.value == 10) {
    return '0';
  }
  if (c.value == VALUE_JACK) {
    return 'J';
  }
  if (c.value == VALUE_QUEEN) {
    return 'Q';
  }
  if (c.value == VALUE_KING) {
    return 'K';
  }
  if (c.value == VALUE_ACE) {
    return 'A';
  }
  return ' ';
}

char suit_letter(card_t c) {
  switch (c.suit) {
    case SPADES:   return 's';
    case HEARTS:   return 'h';
    case DIAMONDS: return 'd';
    case CLUBS:    return 'c';
    default:       return ' ';
  }
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  assert((value_let >= '2' && value_let <= '9') || value_let == '0'
    || value_let == 'J' || value_let == 'Q' || value_let == 'K'
    || value_let == 'A');
  assert(suit_let == 's' || suit_let == 'h'
    || suit_let == 'd' || suit_let == 'c');

  card_t temp;
  switch (suit_let) {
    case 's': temp.suit = SPADES; break;
    case 'h': temp.suit = HEARTS; break;
    case 'd': temp.suit = DIAMONDS; break;
    case 'c': temp.suit = CLUBS; break;
    default: break;
  }
  
  if (value_let <= '9') {
    temp.value = value_let - '0';
  }
  if (value_let == '0') {
    temp.value = 10;
  }
  if (value_let == 'J') {
    temp.value = VALUE_JACK;
  }
  if (value_let == 'Q') {
    temp.value = VALUE_QUEEN;
  }
  if (value_let == 'K') {
    temp.value = VALUE_KING;
  }
  if (value_let == 'A') {
    temp.value = VALUE_ACE;
  }
  return temp;
}

card_t card_from_num(unsigned c) {
  unsigned num_value = c / 4;
  char value = 0;
  if (num_value >= 0 && num_value <= 7) {
    value = '0' + num_value + 2;
  }
  if (num_value == 8) {
    value = '0';
  }
  if (num_value == 9) {
    value = 'J';
  }
  if (num_value == 10) {
    value = 'Q';
  }
  if (num_value == 11) {
    value = 'K';
  }
  if (num_value == 12) {
    value = 'A';
  }

  unsigned num_suit = (c + 1) % 4;
  char suit = 0;
  switch (num_suit) {
    case 0: suit = 's'; break;
    case 1: suit = 'h'; break;
    case 2: suit = 'd'; break;
    case 3: suit = 'c'; break;
    default: break;
  }
  return card_from_letters(value, suit);
}
