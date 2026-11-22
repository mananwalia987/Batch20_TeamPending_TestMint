# TestMint — Submission & Lab Preparation Checklist

> ### ⚠️ MANDATORY ACADEMIC WARNING
> **Faculty approval required for self-proposed problem statement.**
> 
> *TestMint is a student-proposed problem statement ("Startup Idea Validation Platform") rather than one of the 10 pre-assigned problem statements listed in the official hackathon guide. As mandated by university guidelines, prior approval from the subject lab faculty must be formally obtained before final Lab 2 evaluation. Faculty approval has **NOT** been pre-marked as obtained; ensure your team presents this topic to your lab faculty during Lab 1 for sign-off.*

---

## 👥 Team Information & Pending Assignment

| Field | Official Value |
|---|---|
| **Project Name** | **TestMint** |
| **Project Tagline** | *Validate Before You Build.* |
| **Course** | C Programming Lab (Mini Hackathon Assessment) |
| **Batch** | Batch 20 |
| **Team Number** | `TEAM_NUMBER_PENDING` *(Awaiting faculty allocation)* |
| **Member 1 (Leader)** | **Manan Walia** (SAP ID: `590036141`) |
| **Member 2** | **Poornika Pant** (SAP ID: `590032465`) |
| **Member 3** | **Aryan Gangwar** (SAP ID: `590042393`) |

### 🔄 How to Replace the Pending Team Number
When the faculty communicates your official team number (e.g., Team 05):
1. Rename folder `Batch20_TeamPending_TestMint` to `Batch20_Team05_TestMint`.
2. In `README.md`, replace `TEAM_NUMBER_PENDING` with `Team 05`.
3. In `testmint.c` (header comment block), replace `TEAM_NUMBER_PENDING` with `Team 05`.
4. In `presentation.pptx` (Slide 1), update `TEAM_NUMBER_PENDING` with `Team 05`.
5. Update your remote GitHub repository name if required.

---

## 📋 Lab 1 Phase: Development & GitHub Submission (120 Minutes)

| Status | Task | Verification Command / Details |
|:---:|---|---|
| [x] | **Verify C Code Completeness** | All 5 options implemented (`Submit`, `Explore`, `Validate`, `Dashboard`, `Exit`) in [`testmint.c`](testmint.c) |
| [x] | **Zero Compilation Warnings** | `gcc -Wall -Wextra -std=c99 testmint.c -o testmint.exe` produces 0 errors and 0 warnings |
| [x] | **Defensive Input Handling** | Rejection of out-of-range integers, character buffer overflow prevention, zero-division protection |
| [x] | **Test Case Execution** | All 5 sample test cases executed and verified; logs stored in [`screenshots/`](screenshots/) |
| [x] | **Repository Documentation** | Comprehensive [`README.md`](README.md) with algorithms, C concepts table, and test results |
| [x] | **Presentation Deck Ready** | Professional 10-slide [`presentation.pptx`](presentation.pptx) generated for Lab 2 |
| [x] | **Supporting Prototype Separation** | Web prototype kept isolated in [`optional_prototype/`](optional_prototype/) |
| [ ] | **Seek Faculty Approval** | Request subject faculty sign-off for self-proposed problem statement |
| [ ] | **Receive Official Team Number** | Update `TEAM_NUMBER_PENDING` with assigned team number |
| [ ] | **Initialize & Push Git Repo** | Run `git init`, `git add .`, `git commit -m "Initial TestMint submission"`, push to GitHub |
| [ ] | **Submit Repo Link to Faculty** | Submit repository link via designated portal before Lab 1 ends |

---

## 🎤 Lab 2 Phase: Live Demonstration & Viva Defense (120 Minutes)

### 10-Mark Rubric Breakdown & Preparation
The university assesses each team on a strict **10-mark rubric**. Every team member will be asked at least one direct question.

| Rubric Criterion | Marks | How TestMint Satisfies It | Prepared Speaker |
|---|:---:|---|---|
| **1. Understanding Problem & Logic** | **2** | Addresses real startup failure problem; structured validation logic (Interested, Pass, Purchase Intent, Feedback, Decision Matrix) | **Manan Walia** |
| **2. Correctness & Completeness of C Program** | **2** | Compiles with `-Wall -Wextra -std=c99` with 0 warnings; handles edge cases, zero-division safeguard, buffer clearing | **Aryan Gangwar** |
| **3. Effective Use of C Concepts** | **2** | Demonstrates structs, nested structs, array of structs, pointers (pass-by-reference), switch-case, do-while, loops, safe strings (`fgets`) | **Poornika Pant** |
| **4. Presentation, Demo & Explanation** | **2** | High-impact 10-slide deck (`presentation.pptx`), interactive live demo executing options 1 to 5 | **Entire Team** |
| **5. Communication Skills** | **1** | Confident articulation, clear explanation of mathematical formulas and business rationale | **Entire Team** |
| **6. Dressing & Professional Appearance** | **1** | Formal attire as mandated by university lab assessment guidelines | **Entire Team** |
| **Total** | **10** | **Targeting 10 / 10 Evaluation** | |

### Individual Viva Question Preparation Guide

#### Manan Walia (Lead & Logic Engine):
* **Expected Question:** *"Explain how your validation formula calculates the score and prevents division by zero."*
* **Key Answer:** Explain function `calculateMetrics()`. Total votes = `interested + pass`. If `totalVotes == 0`, early-return sets score to `0.0` and verdict to `REFINE (No Votes Yet)`. Otherwise, `Interest Rate = (interested / totalVotes) * 100`, `Purchase Intent Rate = (purchase / totalVotes) * 100`. Score is weighted: $0.6 \times \text{Interest} + 0.4 \times \text{Purchase Intent}$.

#### Poornika Pant (Data Structures & Views):
* **Expected Question:** *"Why did you use an array of structures, and how does nested feedback work?"*
* **Key Answer:** `struct Feedback` stores author and text character arrays. `struct Startup` nests an array `Feedback feedbacks[MAX_FEEDBACK]`, alongside startup metadata. An array `Startup startups[MAX_STARTUPS]` stores multiple records in memory. Pointers (`Startup *s = &startups[idx]`) are used for efficient access.

#### Aryan Gangwar (Input Validation & Control Flow):
* **Expected Question:** *"How did you prevent buffer overflow and infinite loops on invalid input?"*
* **Key Answer:** Replaced unsafe `gets()` and plain `scanf("%s")` with `readSafeString()` using `fgets()` with fixed buffer limits and trailing newline stripping. For integers, `readInteger()` verifies `scanf("%d") == 1`, purges leftover characters using `clearInputBuffer()`, checks boundaries `[min, max]`, and safely checks `feof(stdin)` to prevent infinite loops.
