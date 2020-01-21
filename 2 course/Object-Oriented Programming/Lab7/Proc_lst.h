#pragma once
#include "References.h"
#include "MyList.h"
#include "Iterator.h"


void load_csv(string file, List <References> &ref);
void main_proc(List <References> &ref, List <References> &del_ref);
void delete_elem(List <References> &ref, List <References> &del_ref, char *_word);
void restore_elem(List <References> &ref, List <References> &del_ref, char *_word);
void change_word(List <References> &ref, const char *_word, const char *_new);
void delete_less(List <References> &ref, List <References> &del_ref, int less);