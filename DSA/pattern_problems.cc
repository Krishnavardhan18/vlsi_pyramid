#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    /**pattern 1
    How is implemented: outer loop runs n times for rows, inner loop runs n times for columns, printing '*' every time.
    Math to remember: rows = n, cols = n (both fixed, independent of each other).
    Cheat sheet to remember: both loop bounds are the constant n -> solid square. **/
    void pattern1(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << "*";
            cout << "\n";
        }
    }

    /**pattern 2
    How is implemented: outer loop i = 1..n, inner loop j = 1..i, print '*' each time.
    Math to remember: number of stars in row i = i.
    Cheat sheet to remember: inner loop bound = outer counter -> growing right triangle. **/
    void pattern2(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
    }

    /**pattern 3
    How is implemented: same loops as pattern 2, but print the inner loop counter j instead of '*'.
    Math to remember: value printed in column j of row i is j itself (1..i).
    Cheat sheet to remember: "print the variable, not a constant" turns a star triangle into a number triangle. **/
    void pattern3(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) cout << j;
            cout << "\n";
        }
    }

    /**pattern 4
    How is implemented: outer loop i = 1..n, inner loop runs i times printing the outer counter i.
    Math to remember: value = row index i, repeated i times.
    Cheat sheet to remember: print the outer variable inside the inner loop -> "row number repeated row number times". **/
    void pattern4(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) cout << i;
            cout << "\n";
        }
    }

    /**pattern 5
    How is implemented: outer loop i = n..1 (decreasing), inner loop j = 1..i, print '*'.
    Math to remember: number of stars in row = n, n-1, ..., 1.
    Cheat sheet to remember: pattern 2 with the outer loop direction reversed -> inverted right triangle. **/
    void pattern5(int n) {
        for (int i = n; i >= 1; i--) {
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
    }

    /**pattern 6
    How is implemented: outer loop i = n..1, inner loop j = 1..i, print j.
    Math to remember: row lengths decrease n..1, values printed are always 1..i.
    Cheat sheet to remember: pattern 3 with the outer loop reversed -> shrinking number triangle. **/
    void pattern6(int n) {
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= i; j++) cout << j;
            cout << "\n";
        }
    }

    /**pattern 7
    How is implemented: outer loop i = 1..n; print (n-i) spaces, then (2*i-1) stars, then (n-i) spaces.
    Math to remember: spaces = n - i, stars = 2*i - 1.
    Cheat sheet to remember: stars always odd and growing by 2, spaces shrink to 0 -> centered pyramid. **/
    void pattern7(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < n - i; j++) cout << " ";
            for (int j = 0; j < 2 * i - 1; j++) cout << "*";
            for (int j = 0; j < n - i; j++) cout << " ";
            cout << "\n";
        }
    }

    /**pattern 8
    How is implemented: outer loop i = 1..n; print (i-1) spaces, then (2*(n-i)+1) stars, then (i-1) spaces.
    Math to remember: stars = 2*(n-i) + 1, spaces = i - 1.
    Cheat sheet to remember: pattern 7's formula with row i replaced by (n-i+1) -> inverted centered pyramid. **/
    void pattern8(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i - 1; j++) cout << " ";
            for (int j = 0; j < 2 * (n - i) + 1; j++) cout << "*";
            for (int j = 0; j < i - 1; j++) cout << " ";
            cout << "\n";
        }
    }

    /**pattern 9
    How is implemented: run pattern 7 (pyramid) then pattern 8 (inverted pyramid) back to back.
    Math to remember: total rows = 2*n, top half uses pattern 7's formula, bottom half uses pattern 8's.
    Cheat sheet to remember: pyramid + inverted pyramid stacked = diamond. **/
    void pattern9(int n) {
        pattern7(n);
        pattern8(n);
    }

    /**pattern 10
    How is implemented: print an increasing right triangle (rows 1..n), then a decreasing one (rows n-1..1), no spaces.
    Math to remember: total rows = 2*n - 1; row lengths go 1,2,...,n,...,2,1.
    Cheat sheet to remember: pattern 2 immediately followed by pattern 5, skipping the duplicate longest row. **/
    void pattern10(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
        for (int i = n - 1; i >= 1; i--) {
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
    }

    /**pattern 11
    How is implemented: outer loop i = 1..n (1-indexed row), inner loop j = 0..i-1 (0-indexed column), print (i+j) % 2.
    Math to remember: digit = (row + col) % 2.
    Cheat sheet to remember: parity of (row+col) alone gives the alternating 1/0 checkerboard triangle. **/
    void pattern11(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) cout << (i + j) % 2;
            cout << "\n";
        }
    }

    /**pattern 12
    How is implemented: print 1..i ascending, then 2*(n-i) spaces, then i..1 descending.
    Math to remember: gap width in the middle = 2*(n-i), shrinks to 0 on the last row.
    Cheat sheet to remember: ascending run + mirrored descending run with a shrinking gap in between. **/
    void pattern12(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) cout << j;
            for (int j = 0; j < 2 * (n - i); j++) cout << " ";
            for (int j = i; j >= 1; j--) cout << j;
            cout << "\n";
        }
    }

    /**pattern 13
    How is implemented: keep one counter across all rows; row i prints the next i counter values and advances it.
    Math to remember: last value printed in row i = i*(i+1)/2 (triangular numbers mark row ends).
    Cheat sheet to remember: the counter never resets between rows, unlike pattern 3. **/
    void pattern13(int n) {
        int counter = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                cout << counter++;
                if (j < i - 1) cout << " ";
            }
            cout << "\n";
        }
    }

    /**pattern 14
    How is implemented: outer loop i = 1..n, inner loop j = 1..i, print char('A' + j - 1).
    Math to remember: letter = 'A' + (column - 1).
    Cheat sheet to remember: pattern 2's triangle with the column index cast to a letter instead of '*'. **/
    void pattern14(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) cout << char('A' + j - 1);
            cout << "\n";
        }
    }

    /**pattern 15
    How is implemented: outer loop i = n..1 (decreasing), inner loop j = 1..i, print char('A' + j - 1).
    Math to remember: same letter formula as pattern 14, rows shrink n..1.
    Cheat sheet to remember: pattern 14 with the outer loop reversed, exactly like pattern 5 vs pattern 2. **/
    void pattern15(int n) {
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= i; j++) cout << char('A' + j - 1);
            cout << "\n";
        }
    }

    /**pattern 16
    How is implemented: outer loop i = 1..n; the row's letter is 'A' + i - 1, printed i times.
    Math to remember: letter depends only on the row, repeated row-number times.
    Cheat sheet to remember: pattern 4 with digits swapped for letters. **/
    void pattern16(int n) {
        for (int i = 1; i <= n; i++) {
            char ch = 'A' + i - 1;
            for (int j = 0; j < i; j++) cout << ch;
            cout << "\n";
        }
    }

    /**pattern 17
    How is implemented: build the increasing half of the row up to 'A' + i - 1, print it, then mirror it back down, padded with (n-i-1) spaces on both sides.
    Math to remember: breakpoint = (2*i+1)/2 (midpoint of the row), spaces = n-i-1.
    Cheat sheet to remember: pattern 7's centered-pyramid shape, but the stars are replaced by a letter run that climbs then descends. **/
    void pattern17(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++)
                cout << " ";

            char ch = 'A';
            int breakpoint = (2 * i + 1) / 2;
            for (int j = 0; j < 2 * i + 1; j++) {
                cout << ch;
                if (j < breakpoint) ch++;
                else ch--;
            }

            for (int j = 0; j < n - i - 1; j++)
                cout << " ";

            cout << "\n";
        }
    }

    /**pattern 18
    How is implemented: row i prints consecutive letters starting at 'A' + n - 1 - i and ending at 'A' + n - 1.
    Math to remember: start letter = 'A' + (n-1-i), end letter is always 'A' + (n-1).
    Cheat sheet to remember: the last column is always the same, highest letter; only the starting letter moves left each row. **/
    void pattern18(int n) {
        for (int i = 0; i < n; i++) {
            for (char ch = 'A' + n - 1 - i; ch <= 'A' + n - 1; ch++)
                cout << ch << " ";
            cout << "\n";
        }
    }

    /**pattern 19
    How is implemented: two loops -- i = n..1 then i = 1..n -- each row prints i stars, 2*(n-i) spaces, i stars.
    Math to remember: gap = 2*(n-i); it shrinks to 0 at the widest row, then grows back out.
    Cheat sheet to remember: mirror of pattern 7's gap logic running top-half shrinking then bottom-half growing -> butterfly. **/
    void pattern19(int n) {
        for (int i = n; i >= 1; i--) {
            for (int j = 0; j < i; j++) cout << "*";
            for (int j = 0; j < 2 * (n - i); j++) cout << " ";
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) cout << "*";
            for (int j = 0; j < 2 * (n - i); j++) cout << " ";
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
    }

    /**pattern 20
    How is implemented: rows 1..n-1 narrow-to-wide with a gap (like pattern 19), one fully solid row of 2*n stars in the middle, then the mirror back n-1..1.
    Math to remember: gap = 2*(n-i) on the outer rows; the middle row has gap 0 and width 2*n.
    Cheat sheet to remember: pattern 19 flipped upside down -- pinched at top and bottom, solid in the middle. **/
    void pattern20(int n) {
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) cout << "*";
            for (int j = 0; j < 2 * (n - i); j++) cout << " ";
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
        for (int j = 0; j < 2 * n; j++) cout << "*";
        cout << "\n";
        for (int i = n - 1; i >= 1; i--) {
            for (int j = 0; j < i; j++) cout << "*";
            for (int j = 0; j < 2 * (n - i); j++) cout << " ";
            for (int j = 0; j < i; j++) cout << "*";
            cout << "\n";
        }
    }

    /**pattern 21
    How is implemented: print a solid top row and solid bottom row of width (n-1); every row in between has '*' only at the two edges with spaces filling (n-3) columns in between.
    Math to remember: width = n-1, height = n, inner-row gap = n-3.
    Cheat sheet to remember: border-only rectangle -- first/last row solid, every other row is just the two edge characters. **/
    void pattern21(int n) {
        for (int j = 0; j < n - 1; j++) cout << "*";
        cout << "\n";
        for (int i = 0; i < n - 2; i++) {
            cout << "*";
            for (int j = 0; j < n - 3; j++) cout << " ";
            cout << "*\n";
        }
        for (int j = 0; j < n - 1; j++) cout << "*";
        cout << "\n";
    }

    /**pattern 22
    How is implemented: for every cell (i,j) in a (2*n-1) x (2*n-1) grid, the value is n minus the shortest distance to any of the four edges.
    Math to remember: size = 2*n-1; val = n - min(i, j, size-1-i, size-1-j).
    Cheat sheet to remember: picture concentric square rings -- outer ring = n, each ring inward drops by 1 down to the center = 1. **/
    void pattern22(int n) {
        int size = 2 * n - 1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int distToEdge = min(min(i, j), min(size - 1 - i, size - 1 - j));
                cout << (n - distToEdge);
            }
            cout << "\n";
        }
    }
};

int main() {
    Solution sol;
    int n = 5;

    cout << "Pattern 1\n"; sol.pattern1(n); cout << "\n";
    cout << "Pattern 2\n"; sol.pattern2(n); cout << "\n";
    cout << "Pattern 3\n"; sol.pattern3(n); cout << "\n";
    cout << "Pattern 4\n"; sol.pattern4(n); cout << "\n";
    cout << "Pattern 5\n"; sol.pattern5(n); cout << "\n";
    cout << "Pattern 6\n"; sol.pattern6(n); cout << "\n";
    cout << "Pattern 7\n"; sol.pattern7(n); cout << "\n";
    cout << "Pattern 8\n"; sol.pattern8(n); cout << "\n";
    cout << "Pattern 9\n"; sol.pattern9(n); cout << "\n";
    cout << "Pattern 10\n"; sol.pattern10(n); cout << "\n";
    cout << "Pattern 11\n"; sol.pattern11(n); cout << "\n";
    cout << "Pattern 12\n"; sol.pattern12(n); cout << "\n";
    cout << "Pattern 13\n"; sol.pattern13(n); cout << "\n";
    cout << "Pattern 14\n"; sol.pattern14(n); cout << "\n";
    cout << "Pattern 15\n"; sol.pattern15(n); cout << "\n";
    cout << "Pattern 16\n"; sol.pattern16(n); cout << "\n";
    cout << "Pattern 17\n"; sol.pattern17(n); cout << "\n";
    cout << "Pattern 18\n"; sol.pattern18(n); cout << "\n";
    cout << "Pattern 19\n"; sol.pattern19(n); cout << "\n";
    cout << "Pattern 20\n"; sol.pattern20(n); cout << "\n";
    cout << "Pattern 21\n"; sol.pattern21(n); cout << "\n";
    cout << "Pattern 22\n"; sol.pattern22(n); cout << "\n";

    return 0;
}
