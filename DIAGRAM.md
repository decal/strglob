# Visual representation of how the show_strglob function behaves..

# If you're on the last pointer of the last element, then the element before it advances its pointer by one
  and the last element itself resets its pointer.

# If you're on the last pointer of the first element, then it's over. 

1. First iteration
=>[1] =>[1] =>[1]
  [2]   [2]   [2]
  [3]   [3]   [3]

2. Second iteration
=>[1] =>[1]   [1]
  [2]   [2] =>[2]
  [3]   [3]   [3]

3. Third iteration

=>[1] =>[1]   [1]
  [2]   [2]   [2]
  [3]   [3] =>[3]

4. Fourth iteration

=>[1]   [1]   [1]
  [2] =>[2]   [2]
  [3]   [3] =>[3]

5. Fifth iteration

=>[1]   [1] =>[1]
  [2]   [2]   [2]
  [3] =>[3]   [3]

6. Sixth iteration

  [1] =>[1] =>[1]
=>[2]   [2]   [2]
  [3]   [3]   [3]

7. Seventh iteration

  [1] =>[1]   [1]
=>[2]   [2] =>[2]
  [3]   [3]   [3]

8. Eighth iteration

  [1] =>[1]   [1]
=>[2]   [2]   [2]
  [3]   [3] =>[3]

9. Ninth iteration

  [1]   [1] =>[1]
=>[2] =>[2]   [2]
  [3]   [3]   [3]

10. Tenth iteration

  [1]   [1]   [1]
  [2] =>[2] =>[2]
=>[3]   [3]   [3]

11. Eleventh iteration

  [1]   [1]   [1]
  [2] =>[2]   [2]
=>[3]   [3] =>[3]

12. Twelve iteration

  [1]   [1] =>[1]
  [2]   [2]   [2]
=>[3] =>[3]   [3]

13. o
