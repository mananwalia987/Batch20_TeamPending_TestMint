# TestMint — 3-Minute Live Demonstration Script

> **Target Duration:** 3–4 Minutes  
> **Target Audience:** Lab Faculty Evaluators  
> **Binary:** `./testmint.exe` (Compiled with `gcc -Wall -Wextra -std=c99 testmint.c -o testmint.exe`)

---

### Step 1: Launch & Problem Introduction (0:00 – 0:30)
* **Action:** Run `./testmint.exe` in the terminal.
* **What to Say:**  
  *"Respected faculty, welcome to our demonstration of **TestMint**. The tagline of our project is **'Validate Before You Build'**. Many aspiring founders spend months writing software nobody wants. TestMint is a lightweight, menu-driven C application that allows founders to test startup ideas with real user validation signals before writing code."*

---

### Step 2: Main Menu Overview (0:30 – 0:50)
* **Action:** Point to the 5 menu choices on screen.
* **What to Say:**  
  *"As you can see on screen, our system has 5 core options: Submit Startup Idea, Explore Startup Ideas, Validate an Idea, Founder Dashboard, and Exit. The application is built using a robust `do-while` loop and `switch-case` architecture."*

---

### Step 3: Explore Existing Startups (0:50 – 1:20)
* **Action:** Type `2` $\rightarrow$ Enter. Then type `1` (View details) $\rightarrow$ Enter $\rightarrow$ type `1` (Startup ID 1: PaySplit) $\rightarrow$ Enter.
* **What to Say:**  
  *"Option 2 opens the startup directory. We have pre-seeded three realistic startup concepts across different sectors—FinTech, AgriTech, and SaaS. Notice the live table showing current scores and verdicts. When we inspect Startup #1, PaySplit, we see its problem statement, proposed UPI solution, target audience, and existing feedback notes."*
* **Action:** Press Enter to return to the main menu.

---

### Step 4: Validate an Idea Live (1:20 – 2:00)
* **Action:** Type `3` $\rightarrow$ Enter $\rightarrow$ type `1` (PaySplit) $\rightarrow$ Enter.
* **What to Say:**  
  *"Now let's validate PaySplit live. TestMint guides the user through three simple steps:*
  1. *Step 1: Would you use this product? We choose `1` for **Interested**.*
  2. *Step 2: Would you pay or pre-order? We choose `1` for **Purchase Intent**.*
  3. *Step 3: Constructive feedback. We choose `1`, enter our name **Aryan**, and write: **'Automated UPI reminders will make this viral'**.*
  *Notice that as soon as our validation is recorded, the score dynamically recalculates on screen."*
* **Action:** Press Enter to return to the main menu.

---

### Step 5: Founder Dashboard & Formula Explanation (2:00 – 2:45)
* **Action:** Type `4` $\rightarrow$ Enter $\rightarrow$ type `1` (PaySplit) $\rightarrow$ Enter.
* **What to Say:**  
  *"Next, we enter Option 4: the Founder Dashboard. This is the heart of TestMint's decision engine.*
  *Here the founder sees:*
  * *First, the **Voting Breakdown**: Total votes, interested votes, and the calculated Interest Rate.*
  * *Second, the **Purchase Intent Rate**: Showing commercial willingness to pay.*
  * *Third, our **Weighted Formula**: `Validation Score = (Interest Rate * 0.60) + (Purchase Intent Rate * 0.40)`. We weight interest at 60% for problem relevance and purchase intent at 40% for economic commitment.*
  * *Fourth, the **Official Verdict**: With a score in the 40–74.99 range, PaySplit receives **`NEEDS MORE VALIDATION`** with guidance to **REFINE** its value proposition before building."*
* **Action:** Press Enter to return to the main menu.

---

### Step 6: Defensive Input Validation Demonstration (2:45 – 3:15)
* **Action:** Type `abc` at the menu prompt $\rightarrow$ Enter.
* **What to Say:**  
  *"We have engineered TestMint defensively against invalid user input. If someone types letters instead of numbers, `readInteger()` safely purges the input buffer using `clearInputBuffer()` and displays: `[Error] Invalid input. Please enter a valid number.`"*
* **Action:** Type `9` $\rightarrow$ Enter.
* **What to Say:**  
  *"Similarly, if an out-of-range number like `9` is entered, the program prevents out-of-bounds execution and re-prompts cleanly."*

---

### Step 7: Conclusion & Clean Exit (3:15 – 3:30)
* **Action:** Type `5` $\rightarrow$ Enter.
* **What to Say:**  
  *"Option 5 performs a graceful exit with code 0. TestMint proves that core first-year C concepts—structs, pointers, arrays, loops, and defensive string handling—can solve an authentic real-world problem. Thank you, and we welcome your questions!"*
