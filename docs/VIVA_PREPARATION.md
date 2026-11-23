# TestMint — Viva Preparation Guide for Lab 2

> **University C Programming Mini Hackathon Assessment**  
> *Clear, concise, first-year level answers to approximately 28 likely faculty viva questions based directly on the actual `testmint.c` code.*

---

### Q1: What problem does TestMint solve?
**Answer:** Aspiring entrepreneurs often spend months writing code and money building products without knowing if real customers actually want them. TestMint solves this by letting founders validate startup concepts early through user votes, purchase intent signals, and written feedback.

### Q2: Why did you choose this problem?
**Answer:** It is a genuine real-world problem faced by student developers. Most hackathon projects build apps without asking if anyone needs them. TestMint emphasizes "Validate Before You Build" to prevent wasted development effort.

### Q3: Why implement this in C?
**Answer:** C is fast, lightweight, and teaches core computer science fundamentals—memory management, data structures (`struct`), pointers, and low-level algorithmic control. It proves that meaningful business logic can be built with pure first-year C concepts without heavy frameworks.

### Q4: What is a structure in C?
**Answer:** A `struct` is a user-defined data type in C that groups multiple related variables of different types (like `int`, `char[]`, `float`) under a single name.

### Q5: Why did you use an array of structures?
**Answer:** We defined `Startup startups[MAX_STARTUPS]`. An array of structures allows our program to store and manage multiple startup records in contiguous memory, indexed from `0` to `count - 1`.

### Q6: What is the Feedback structure?
**Answer:** `struct Feedback` stores qualitative comments:
```c
typedef struct {
    char author[50];
    char text[300];
} Feedback;
```
It holds the reviewer's name/role and their written feedback note.

### Q7: Why use character arrays instead of a single char for text?
**Answer:** A single `char` can only store one character (e.g., `'A'`). A character array (like `char name[100]`) stores an entire sequence of characters forming a string, terminated by a null character (`'\0'`).

### Q8: What does `fgets()` do?
**Answer:** `fgets(buffer, maxLen, stdin)` reads a full line of text from standard input, including spaces, up to `maxLen - 1` characters. It prevents buffer overflow and is much safer than `gets()`.

### Q9: Why not use only `scanf("%s")` for reading sentences?
**Answer:** `scanf("%s")` stops reading as soon as it encounters any whitespace (space or newline). Therefore, names or descriptions with spaces like "Aarav Mehta" or "Direct UPI split" would be cut off after the first word.

### Q10: What does the main `switch-case` do?
**Answer:** It handles menu routing based on user input (`1` to `5`). Case 1 submits an idea, Case 2 explores, Case 3 validates, Case 4 opens the founder dashboard, Case 5 exits, and `default` handles invalid selections.

### Q11: Why use a `do-while` loop in `main()`?
**Answer:** A `do-while` loop executes the loop body at least once before checking the condition (`choice != 5`). This guarantees that the user always sees the menu upon launching the application.

### Q12: Where are `for` loops used in your program?
**Answer:** `for` loops are used to iterate through arrays:
1. Iterating through `CATEGORIES[]` to list available categories.
2. Iterating through `startups[]` to display the Explore table and Dashboard selector.
3. Iterating through `feedbacks[]` to print user reviews.

### Q13: Where are `while` loops used?
**Answer:** `while` loops are used for input validation in `readSafeString()` and `readInteger()`, and to flush leftover characters from the standard input buffer in `clearInputBuffer()`.

### Q14: What is a pointer?
**Answer:** A pointer is a variable that stores the memory address of another variable rather than the value itself.

### Q15: Where are pointers used in TestMint?
**Answer:** 
1. In `calculateMetrics()` to pass `float *interestRate`, `float *purchaseRate`, and `float *score` by reference.
2. In `Startup *s = &startups[idx]` to reference and modify startup records in place.
3. In `int *count` in `submitStartupIdea()` to increment the total startup count in `main()`.

### Q16: What is pass-by-reference and why is it needed?
**Answer:** In C, functions normally pass parameters by value (copying them). Pass-by-reference passes the address of variables using pointers, allowing the function to modify the original variables in the caller and effectively return multiple calculated results.

### Q17: How is startup data updated in memory?
**Answer:** When a user validates a startup, we obtain a pointer to that startup in the array (`Startup *s = &startups[idx]`) and increment its fields directly (`s->interested++`, `s->purchaseIntent++`, `s->views++`).

### Q18: How does Interested / Pass voting work?
**Answer:** The user chooses Option 1 ("Interested") or Option 2 ("Pass"). If Option 1, `s->interested` increments; if Option 2, `s->pass` increments. Total votes equals `interested + pass`.

### Q19: What is Purchase Intent?
**Answer:** It is a validation signal measuring commercial commitment: asking whether the user is willing to pay or pre-order the solution. It is stored as an integer count (`purchaseIntent`) and represents demand, not an actual financial transaction.

### Q20: Explain the validation formula.
**Answer:**
1. $\text{Interest Rate} = \left(\frac{\text{Interested}}{\text{Total Votes}}\right) \times 100$
2. $\text{Purchase Intent Rate} = \left(\frac{\text{Purchase Intent}}{\text{Total Votes}}\right) \times 100$
3. $\text{Validation Score} = (\text{Interest Rate} \times 0.60) + (\text{Purchase Intent Rate} \times 0.40)$

### Q21: Why weight interest at 60% and purchase intent at 40%?
**Answer:** Interest validates problem-market fit (does the problem exist and does the user care?), while purchase intent validates pricing and business viability. The 60/40 split rewards broad curiosity while heavily penalizing concepts that people say they like but would never pay for.

### Q22: How do you prevent division by zero?
**Answer:** Before calculating rates, `calculateMetrics()` checks `if (totalVotes == 0)`. If zero, it immediately sets score to `0.0`, assigns the verdict `"NOT ENOUGH DATA YET"`, and returns early before any division operator executes.

### Q23: What happens when there are 0 votes on an idea?
**Answer:** Division by zero is avoided. The score is displayed as `0.0 / 100`, the verdict is `"NOT ENOUGH DATA YET"`, and the founder dashboard advises the founder to gather initial user feedback before building.

### Q24: What happens if an invalid startup ID like 99 is entered?
**Answer:** `findStartupIndexById()` traverses the array. If no startup matches ID 99, it returns `-1`, and the program displays `[Error] Startup with ID #99 does not exist.` without crashing or accessing invalid memory.

### Q25: How do you validate numeric input against letters like `abc`?
**Answer:** `readInteger()` uses `scanf("%d", &value)`. If the user types letters, `scanf` returns `0` (or `EOF`). The function detects that `itemsRead != 1`, purges the buffer with `clearInputBuffer()`, and re-prompts the user with `[Error] Invalid input. Please enter a valid number.`

### Q26: What happens when maximum capacity is reached?
**Answer:** `submitStartupIdea()` checks `if (*count >= MAX_STARTUPS)`. If true, it displays `[Warning] Maximum capacity reached (30 startups)` and prevents memory overflow. Similarly, feedback checks `feedbackCount < MAX_FEEDBACK (10)`.

### Q27: What would you improve in the future?
**Answer:** 
1. Add file I/O (`fopen`, `fread`, `fwrite`) to persist startups to disk across program runs.
2. Use dynamic memory allocation (`malloc`/`realloc`) or linked lists for unlimited startups.
3. Implement sorting to rank ideas by validation score.

### Q28: What is the difference between the C prototype and the web UI prototype?
**Answer:** The C program (`testmint.c`) is the official, complete, assessed university implementation. The Next.js web prototype in `optional_prototype/` is strictly an exploratory UI/UX product-vision mockup demonstrating what a future web version could look like.
