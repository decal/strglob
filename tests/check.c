/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include<stdio.h>
#include<stdlib.h>
#include<check.h>
#include"strglob.h"
 
START_TEST(test_strglob_empty_string) {
  HAND_GLOB *hglob = handle_strglob("");

  ck_assert_str_eq(hglob->glob->str, "");
} END_TEST

START_TEST(test_strglob_space_string) {
  HAND_GLOB *hglob = handle_strglob(" ");

  ck_assert_str_eq(hglob->glob->str, " ");
} END_TEST

START_TEST(test_strglob_bracket_chars) {
  HAND_GLOB *hglob = handle_strglob("[a-z]");
  STR_GLOB *strg = hglob->glob;
  char bracket_beg = strg->beg, bracket_end = strg->end;

  ck_assert_int_eq(bracket_beg, 'a');
  ck_assert_int_eq(bracket_end, 'z');
} END_TEST

START_TEST(test_strglob_bracket_prepzero) {
  HAND_GLOB *hglob = handle_strglob("[00-01]");
  STR_GLOB *strg = hglob->glob;
  const size_t zlen = strg->zlen;
  const int bracket_beg = strg->beg, bracket_end = strg->end;

  if(!zlen)
    ck_abort_msg("No zeroes are prepended to integer quantity");

  ck_assert_int_eq(bracket_beg, 0);
  ck_assert_int_eq(bracket_end, 1);
} END_TEST

START_TEST(test_strglob_brace_digits) {
  HAND_GLOB *hglob = handle_strglob("{1..9}");
  STR_GLOB *strg = hglob->glob;
  const int brace_beg = strg->beg, brace_end = strg->end;

  ck_assert_int_eq(brace_beg, '1');
  ck_assert_int_eq(brace_end, '9');
} END_TEST

START_TEST(test_strglob_brace_chars) {
  HAND_GLOB *hglob = handle_strglob("{a..z}");
  STR_GLOB *strg = hglob->glob;
  const int brace_beg = strg->beg, brace_end = strg->end;

  ck_assert_int_eq(brace_beg, 'a');
  ck_assert_int_eq(brace_end, 'z');
} END_TEST
 
Suite *strglob_suite(void) {
  Suite *test_suite = suite_create("strglob");
  TCase *case_string = tcase_create("string");
  TCase *case_bracket = tcase_create("bracket");
  TCase *case_brace = tcase_create("brace");
 
  tcase_add_test(case_string, test_strglob_empty_string);
  tcase_add_test(case_string, test_strglob_space_string);

  suite_add_tcase(test_suite, case_string);

  tcase_add_test(case_bracket, test_strglob_bracket_chars);
  tcase_add_test(case_bracket, test_strglob_bracket_prepzero);

  suite_add_tcase(test_suite, case_bracket);

  tcase_add_test(case_brace, test_strglob_brace_digits);
  tcase_add_test(case_brace, test_strglob_brace_chars);

  suite_add_tcase(test_suite, case_brace);

  return test_suite;
}
 
int main(void) {
  Suite *s = strglob_suite();
  SRunner *sr = srunner_create(s);
 
  srunner_run_all(sr, CK_NORMAL);

  const int number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  exit(!number_failed ? EXIT_SUCCESS : EXIT_FAILURE);
}
