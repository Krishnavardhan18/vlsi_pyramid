# Pattern Problems — Implementation & Memorization Guide

Companion notes for [patter_problems.cc](patter_problems.cc) (Strivers A2Z DSA Sheet — 22 pattern problems).

The goal of this doc isn't just to explain each pattern once — it's to give you a **repeatable way of thinking**
so that in an interview you can derive any of these from scratch instead of recalling memorized code.

## The general mental model

Every pattern is built from the same three questions, asked in order:

1. **How many rows?** → controls the outer loop bounds/direction.
2. **How many "things" (stars/numbers/letters) in row `i`?** → controls the inner loop bound. This is almost
   always a simple function of `i`: `i`, `n-i`, `2*i-1`, `2*(n-i)+1`, etc.
3. **What value gets printed at position `j`?** → `*` (constant), `j` (column), `i` (row), or a letter derived
   from either.

Once you can answer those three questions for a shape, the code writes itself. The patterns below are grouped
by family because the *families* share formulas — memorize the family, not 22 separate pieces of code.

---

## Family A — Plain right triangles (Patterns 1–6)

These all share the skeleton:
```cpp
for (int i = <start>; <cond>; <step>)
    for (int j = 0/1; <cond using i>; j++)
        cout << <value>;
```
Only three things change: loop direction, inner bound, and what you print.

### Pattern 1 — Solid square
Outer loop runs `n` times, inner loop *also* runs a fixed `n` times. Neither depends on the other.
**Memorize:** both bounds are the constant `n` → nothing grows, it's just a block.

### Pattern 2 — Right triangle of stars
Outer `i = 1..n`, inner `j = 0..i-1`, print `*`.
**Memorize:** inner bound = outer counter. This is the "root" pattern — every growing triangle is a variation
of this loop.

### Pattern 3 — Right triangle of numbers (1..i)
Identical to Pattern 2, but print `j` (1-indexed) instead of `*`.
**Memorize:** "print the counter, not a constant." Any star pattern becomes a number pattern this way.

### Pattern 4 — Row number repeated (`1`, `22`, `333`, ...)
Same shape as Pattern 2, but print the **outer** variable `i` inside the inner loop instead of `j`.
**Memorize:** stars → `*`, numbers-by-column → `j`, numbers-by-row → `i`. Those are your only three choices
of "what to print" in a triangle.

### Pattern 5 — Inverted right triangle of stars
Pattern 2 with the outer loop reversed: `i = n..1`.
**Memorize:** reversing the outer `for` turns any "growing" pattern into a "shrinking" one — no new logic needed.

### Pattern 6 — Inverted right triangle of numbers
Pattern 3 with the outer loop reversed, same as Pattern 5 vs Pattern 2.
**Memorize:** Patterns 5 & 6 are "free" once you know 2 & 3 — just flip the loop direction.

---

## Family B — Centered pyramids (Patterns 7–10)

The key trick for *any* centered shape: **spaces + content + spaces**, where content is always odd-width and
symmetric.

### Pattern 7 — Pyramid of stars
Row `i`: `(n-i)` spaces, `(2*i-1)` stars, `(n-i)` spaces.
**Memorize the pair of formulas:**
- `stars = 2*i - 1` (always odd, grows by 2 each row — 1, 3, 5, 7...)
- `spaces = n - i` (shrinks to 0 at the last row)

### Pattern 8 — Inverted pyramid of stars
Same two formulas as Pattern 7, but swap `i` for `(n - i + 1)`:
- `stars = 2*(n-i) + 1`
- `spaces = i - 1`
**Memorize:** don't learn this as new math — it's Pattern 7 read bottom-to-top.

### Pattern 9 — Diamond
Literally `pattern7(n)` followed by `pattern8(n)`. No new formula.
**Memorize:** diamond = pyramid + inverted pyramid, glued at the widest row.

### Pattern 10 — Triangle up then down (no spaces)
`pattern2(n)` followed by `pattern5(n-1)` (skip the peak row the second time so it isn't printed twice).
**Memorize:** total rows = `2n - 1`; this is the "no spaces" cousin of the diamond.

---

## Family C — Value tricks inside a fixed shape (Patterns 11–13)

Same right-triangle skeleton as Family A, but the **value** needs a one-line formula instead of `*`/`i`/`j`.

### Pattern 11 — Binary alternating triangle
Print `(i + j) % 2` where `i` is the 1-indexed row and `j` is the 0-indexed column.
**Memorize:** parity of `row + col` alone reproduces the whole checkerboard-in-a-triangle — no `if/else`
needed if you index this way.

### Pattern 12 — Numbers with a shrinking gap, mirrored
Print `1..i` ascending, then `2*(n-i)` spaces, then `i..1` descending.
**Memorize:** "ascend, gap, mirror-descend." The gap formula `2*(n-i)` is the same shrink-to-zero idea as
Pattern 7's spaces, just doubled because it sits between two halves.

### Pattern 13 — Continuously incrementing triangle
Exactly Pattern 2's loop shape, but keep **one counter variable outside the loops** that never resets.
**Memorize:** this is the only pattern where the value depends on *how many cells were printed so far*, not
on `i`/`j` directly. The row-end values are triangular numbers: `i*(i+1)/2`.

---

## Family D — Letters instead of digits (Patterns 14–18)

Every one of these is a Family A/B pattern with the print statement changed to
`char('A' + <same formula you'd use for numbers>)`.

### Pattern 14 — `A`, `AB`, `ABC`, ...
Pattern 2/3's loop; print `char('A' + j - 1)`.

### Pattern 15 — Reversed letters triangle
Pattern 14 with the outer loop reversed — same relationship as Pattern 5 to Pattern 2.

### Pattern 16 — Letter repeated by row (`A`, `BB`, `CCC`, ...)
Pattern 4's loop; the repeated value is `char('A' + i - 1)` instead of `i`.

### Pattern 17 — Alphabet pyramid (`A`, `ABA`, `ABCBA`, ...)
Pattern 7's spacing formulas (`spaces = n-i-1`), but the "stars" are replaced by a letter run that climbs
from `A` up to a peak then mirrors back down. The only new idea is the **breakpoint**:
```
breakpoint = (2*i + 1) / 2   // midpoint of the row
```
Climb (`ch++`) while `j < breakpoint`, descend (`ch--`) afterward.
**Memorize:** "climb to the midpoint, then mirror" — same idea as Pattern 12's ascend/mirror, applied to
letters inside a single loop instead of two separate loops.

### Pattern 18 — Letters ending on the same column (`C` / `BC` / `ABC`)
Row `i` prints letters from `'A' + n - 1 - i` to `'A' + n - 1`.
**Memorize:** the **end** letter is always fixed at `'A' + n - 1`; only the **start** letter slides left
one position per row. Anchor on the fixed end, not the moving start.

---

## Family E — Mirrored halves / hourglass shapes (Patterns 19–20)

Both reuse Pattern 7/8's `spaces`/`stars` idea, just laid out left-right instead of only around the center.

### Pattern 19 — Butterfly (pinched in the middle)
Row: `i` stars, `2*(n-i)` spaces, `i` stars — first for `i = n..1`, then again for `i = 1..n`.
**Memorize:** the gap `2*(n-i)` shrinks to 0 at the **widest** row (top and bottom), exactly mirroring
Pattern 12's gap formula.

### Pattern 20 — Reverse butterfly (pinched top & bottom, solid middle)
Same row formula as Pattern 19 for `i = 1..n-1`, then one fully solid row of `2*n` stars, then the mirror
back down.
**Memorize:** Pattern 20 is Pattern 19 turned upside down — the "pinch points" swap with the "solid" point.

---

## Family F — Structural / geometric patterns (Patterns 21–22)

These don't fit the triangle mold — think in terms of *edges* and *distance from an edge* instead of rows.

### Pattern 21 — Hollow rectangle
First and last row: solid `*` of width `n-1`. Every row in between: `*`, then `(n-3)` spaces, then `*`.
**Memorize:** "border only" — top/bottom rows are 100% filled, every other row only touches the two edge
columns.

### Pattern 22 — Concentric number rings (the "onion" pattern)
Grid is `(2n-1) x (2n-1)`. Value at `(i, j)`:
```
val = n - min(i, j, size-1-i, size-1-j)
```
**Memorize:** picture concentric square rings, like an onion cut in half. The outermost ring is always `n`;
each ring one step inward drops by exactly 1, down to `1` at the dead center. `min(distance to each of the
4 edges)` is *how deep into the onion* a cell is.

---

## Cheat-sheet table — formulas worth memorizing

| # | Shape | Row length / gap formula | Value printed | One-line trigger phrase |
|---|-------|---------------------------|----------------|--------------------------|
| 1 | Solid square | rows = n, cols = n | `*` | "both bounds constant" |
| 2 | Right triangle ↗ | cols = `i` | `*` | "inner bound = outer counter" |
| 3 | Right triangle ↗ (nums) | cols = `i` | `j` | "print the counter" |
| 4 | Right triangle ↗ (row repeat) | cols = `i` | `i` | "print the outer var" |
| 5 | Right triangle ↘ | cols = `n-i+1` | `*` | "reverse the outer loop" |
| 6 | Right triangle ↘ (nums) | cols = `n-i+1` | `j` | "reverse + print counter" |
| 7 | Pyramid | `stars = 2i-1`, `spaces = n-i` | `*` | "odd & growing, spaces shrink" |
| 8 | Inverted pyramid | `stars = 2(n-i)+1`, `spaces = i-1` | `*` | "pattern 7 flipped" |
| 9 | Diamond | pattern 7 + pattern 8 | `*` | "pyramid stacked on inverted pyramid" |
| 10 | Triangle up-down | rows = `2n-1` | `*` | "pattern 2 + pattern 5, no dup peak" |
| 11 | Binary triangle | cols = `i` | `(i+j) % 2` | "parity of row+col" |
| 12 | Mirrored numbers | `gap = 2(n-i)` | `1..i` then `i..1` | "ascend, gap, mirror" |
| 13 | Continuous counter | cols = `i` | running counter | "counter never resets" |
| 14–16 | Letters | same as 2 / 4 | `char('A'+j-1)` or `char('A'+i-1)` | "digits → letters, same loops" |
| 17 | Letter pyramid | `breakpoint = (2i+1)/2`, `spaces = n-i-1` | climb then mirror letters | "climb to midpoint, mirror" |
| 18 | Letter triangle (fixed end) | start = `'A'+n-1-i` | end always `'A'+n-1` | "anchor the fixed end" |
| 19 | Butterfly | `gap = 2(n-i)` | `*` | "pinch in the middle" |
| 20 | Reverse butterfly | `gap = 2(n-i)`, middle row solid `2n` | `*` | "pinch top & bottom" |
| 21 | Hollow rectangle | width `n-1`, inner gap `n-3` | `*` on edges only | "border only" |
| 22 | Concentric rings | `size = 2n-1` | `n - min(dist to 4 edges)` | "onion rings, min distance" |

### The 4 formulas that cover almost everything

If you only remember four numbers, remember these — nearly every pattern above is one of them (or its mirror):

| Formula | Meaning | Shows up in |
|---|---|---|
| `2*i - 1` | odd sequence, grows by 2 | Pattern 7, 9 |
| `n - i` | linear shrink to 0 | Pattern 7, 8 (as `i-1`), 21 |
| `2*(n-i)` | shrinking gap between two mirrored halves | Pattern 12, 19, 20 |
| `min(i, j, size-1-i, size-1-j)` | distance to nearest edge | Pattern 22 |

**Why this matters beyond pattern-printing:** these four formulas reappear constantly in DSA —
`2*i-1`/`n-i` style arithmetic shows up in binary search midpoint math and prefix/suffix symmetric problems;
the "mirrored gap" idea is the same logic used in two-pointer problems that shrink a window from both ends;
and `min(distance to edges)` is exactly the recurrence used in "maximal square" / "distance to nearest 0"
matrix DP problems (e.g. LeetCode 542, 221). Pattern problems are really just loop-control and symmetry
practice in disguise.
