# TestMint — Team Presentation & Viva Division Plan

> **University C Programming Mini Hackathon Assessment**  
> *Role assignments, presentation responsibilities, and code mastery checklist for Lab 2.*

---

## 👥 Speaking Responsibilities

### 1. Manan Walia (Team Lead | SAP ID: 590036141)
* **Presentation Scope:**
  * Project Opening & Tagline (*"Validate Before You Build"*)
  * Real-World Problem Statement (42% of startups fail due to building without market demand)
  * Proposed Solution & High-Level Architecture
  * Overall Program Flow & Main Menu Dispatch (`do-while` loop, `switch-case`, `displayMainMenu`)
  * Final Summary & Closing Conclusion
* **Code Modules Owned:**
  * `main()` function lifecycle
  * Program flow control and menu routing
  * High-level system integration

---

### 2. Poornika Pant (Member | SAP ID: 590032465)
* **Presentation Scope:**
  * User-Defined Structures (`struct Startup` and nested `struct Feedback`)
  * Array of Structures (`Startup startups[MAX_STARTUPS]`)
  * Strings & Character Arrays (`char name[100]`, `fgets`, trailing newline stripping)
  * Option 1: Idea Submission Module (`submitStartupIdea`)
  * Option 2: Explore Catalog & Single Startup Detail Card (`exploreStartupIdeas`, `showSingleStartupDetail`)
  * Category Arrays (`CATEGORIES[]`)
* **Code Modules Owned:**
  * Data modeling and struct definitions
  * Text buffers and string handling functions
  * Catalog display and formatting

---

### 3. Aryan Gangwar (Member | SAP ID: 590042393)
* **Presentation Scope:**
  * Option 3: Interactive Validation Module (`validateStartupIdea`)
  * Modular Function Design & Pointers (Pass-by-value vs. Pass-by-reference)
  * Validation Metrics Mathematical Engine (`calculateMetrics` & formula weights)
  * Option 4: Founder Dashboard Report & Official Decision Verdicts
  * Defensive Programming: Input Validation (`readInteger`, `readSafeString`, `clearInputBuffer`)
  * Division-by-Zero Safeguard & Test Suite Results (22/22 tests passed)
* **Code Modules Owned:**
  * Input stream validation and buffer clearing
  * Mathematical engine and pointer return values
  * Automated testing and edge case verification

---

## ⚠️ CRITICAL ACADEMIC REQUIREMENT

Even though presentation roles are divided for a cohesive 3-minute delivery:

> **EVERY TEAM MEMBER MUST BE CAPABLE OF ANSWERING ANY QUESTION ON ANY PART OF THE CODE.**

Faculty members will ask at least one individual question to each member to verify authentic understanding.

### Universal Mastery Checklist:
All three members must understand and be ready to explain:
- [x] Complete program flow from `main()` to exit
- [x] Structure definition of `Startup` and `Feedback`
- [x] Why `char[]` and `fgets()` were chosen over unsafe `scanf("%s")`
- [x] The exact validation formula: $\text{Score} = (I_{\text{rate}} \times 0.60) + (P_{\text{rate}} \times 0.40)$
- [x] The 4 official verdicts: `STRONG DEMAND`, `NEEDS MORE VALIDATION`, `WEAK DEMAND`, `NOT ENOUGH DATA YET`
- [x] How division by zero is safely prevented when total votes equal `0`
- [x] How `readInteger()` purges invalid non-numeric inputs like `abc`
- [x] Why `testmint.exe` is a standalone console application with no external databases or web dependencies
