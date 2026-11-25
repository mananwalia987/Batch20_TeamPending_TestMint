/*
 ============================================================================
  PROJECT     : TestMint - Validate Before You Build
  COURSE      : C Programming Mini Hackathon (University Assessment)
  BATCH       : Batch 20
  TEAM NAME   : TestMint
  
  TEAM MEMBERS:
    1. Manan Walia   | SAP ID: 590036141 | Batch: 20
    2. Poornika Pant | SAP ID: 590032465 | Batch: 20
    3. Aryan Gangwar | SAP ID: 590042393 | Batch: 20
    
  PROBLEM STATEMENT:
    Aspiring founders often invest significant time and money building startup
    products before knowing whether real customers actually want them.
    
  SOLUTION:
    TestMint is a startup idea validation system where founders submit startup
    concepts and users can explore ideas, vote Interested/Pass, record purchase
    intent, and provide qualitative feedback. The system computes validation
    metrics and delivers an actionable decision verdict: BUILD, REFINE, or PIVOT.
    
  DEMONSTRATED C CONCEPTS:
    1. Variables & Data Types (int, float, char, format specifiers)
    2. Operators (Arithmetic, Relational, Logical, Compound assignment)
    3. Control Structures (if / else if / else)
    4. Selection Control (switch - case - default)
    5. Iteration Control (for loop, while loop, do-while loop)
    6. 1D & 2D Arrays (String literal array CATEGORIES[], buffers)
    7. Strings (Character arrays, safe fgets I/O, newline stripping, string.h)
    8. Functions & Modularity (Pass-by-value and pass-by-reference pointers)
    9. Structures (struct Feedback, struct Startup)
   10. Array of Structures (Startup startups[MAX_STARTUPS])
   11. Robust Input Validation (buffer clearing, range verification)
   12. Zero-Division Safeguard (handling zero votes gracefully)
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STARTUPS 30
#define MAX_FEEDBACK 10
#define STR_SHORT 50
#define STR_MED 100
#define STR_LONG 300

/* Structure for user feedback */
typedef struct {
    char author[STR_SHORT];
    char text[STR_LONG];
} Feedback;

/* Structure for a startup concept */
typedef struct {
    int id;
    char name[STR_MED];
    char founder[STR_MED];
    char category[STR_SHORT];
    char problem[STR_LONG];
    char solution[STR_LONG];
    char audience[STR_LONG];
    int views;
    int interested;
    int pass;
    int purchaseIntent;
    Feedback feedbacks[MAX_FEEDBACK];
    int feedbackCount;
} Startup;

/* Category choices for startup ecosystem */
const char *CATEGORIES[] = {
    "FinTech",
    "AgriTech",
    "EdTech",
    "HealthTech",
    "SaaS",
    "AI",
    "Consumer"
};
const int TOTAL_CATEGORIES = 7;

/* Function Declarations */
void initializeSampleData(Startup startups[], int *count);
void displayBanner(void);
void displayMainMenu(void);
void clearInputBuffer(void);
void readSafeString(const char *prompt, char *buffer, int maxLen, int required);
int readInteger(const char *prompt, int min, int max);

void submitStartupIdea(Startup startups[], int *count);
void exploreStartupIdeas(Startup startups[], int count);
void showSingleStartupDetail(Startup *s);
void validateStartupIdea(Startup startups[], int count);
void founderDashboard(Startup startups[], int count);

void calculateMetrics(int interested, int pass, int purchase,
                      float *interestRate, float *purchaseRate,
                      float *score, char verdict[]);

int findStartupIndexById(Startup startups[], int count, int id);

/* ========================================================================= */
/*                               MAIN FUNCTION                               */
/* ========================================================================= */

int main(void) {
    Startup startups[MAX_STARTUPS];
    int startupCount = 0;
    int choice = 0;

    /* Seed initial sample concepts so the platform is ready to explore */
    initializeSampleData(startups, &startupCount);

    do {
        displayMainMenu();
        choice = readInteger("Enter your choice (1-5): ", 1, 5);
        printf("\n");

        switch (choice) {
            case 1:
                submitStartupIdea(startups, &startupCount);
                break;
            case 2:
                exploreStartupIdeas(startups, startupCount);
                break;
            case 3:
                validateStartupIdea(startups, startupCount);
                break;
            case 4:
                founderDashboard(startups, startupCount);
                break;
            case 5:
                printf("========================================================\n");
                printf("   Thank you for using TestMint. Validate before you build!\n");
                printf("========================================================\n");
                break;
            default:
                printf("[Error] Invalid choice! Please select between 1 and 5.\n");
                break;
        }

        if (choice != 5) {
            printf("\nPress Enter to return to the Main Menu...");
            clearInputBuffer();
        }
    } while (choice != 5);

    return 0;
}

/* ========================================================================= */
/*                         INPUT & UTILITY FUNCTIONS                         */
/* ========================================================================= */

/* Clear leftover characters in standard input buffer */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Discard input characters */
    }
}

/* Read a string safely and strip trailing newline */
void readSafeString(const char *prompt, char *buffer, int maxLen, int required) {
    int valid = 0;
    while (!valid) {
        printf("%s", prompt);
        if (fgets(buffer, maxLen, stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }
            if (required && len == 0) {
                printf("[Error] This field cannot be empty. Please enter text.\n");
            } else {
                valid = 1;
            }
        } else {
            if (feof(stdin)) {
                printf("\n[Notice] Input stream ended. Exiting TestMint...\n");
                exit(0);
            }
            clearerr(stdin);
            printf("[Error] Input error. Please try again.\n");
        }
    }
}

/* Read an integer within range [min, max] with strict validation */
int readInteger(const char *prompt, int min, int max) {
    int value;
    int itemsRead;
    while (1) {
        printf("%s", prompt);
        itemsRead = scanf("%d", &value);
        if (itemsRead == 1) {
            clearInputBuffer();
            if (value >= min && value <= max) {
                return value;
            } else {
                printf("[Error] Value out of range. Enter a number between %d and %d.\n", min, max);
            }
        } else {
            if (feof(stdin)) {
                printf("\n[Notice] Input stream ended. Exiting TestMint...\n");
                exit(0);
            }
            printf("[Error] Invalid input. Please enter a valid number.\n");
            clearInputBuffer();
        }
    }
}

/* Find array index of startup matching given ID; returns -1 if not found */
int findStartupIndexById(Startup startups[], int count, int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (startups[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* ========================================================================= */
/*                          DISPLAY & MENU FUNCTIONS                         */
/* ========================================================================= */

void displayBanner(void) {
    printf("========================================\n");
    printf("              TESTMINT                  \n");
    printf("       VALIDATE BEFORE YOU BUILD        \n");
    printf("========================================\n");
}

void displayMainMenu(void) {
    printf("\n");
    displayBanner();
    printf("1. Submit Startup Idea\n");
    printf("2. Explore Startup Ideas\n");
    printf("3. Validate an Idea\n");
    printf("4. Founder Dashboard\n");
    printf("5. Exit\n");
    printf("========================================\n");
}

/* ========================================================================= */
/*                         VALIDATION METRICS ENGINE                         */
/* ========================================================================= */

/*
   Validation formula:
   Interest Rate        = (Interested Votes / Total Votes) * 100
   Purchase Intent Rate = (Purchase Intent / Total Votes) * 100
   Validation Score     = (Interest Rate * 0.60) + (Purchase Intent Rate * 0.40)

   Decision Verdicts:
   Score >= 75.0           : STRONG DEMAND
   Score >= 40.0 and < 75.0: NEEDS MORE VALIDATION
   Score < 40.0            : WEAK DEMAND
   Total Votes == 0        : NOT ENOUGH DATA YET (Safe zero-division protection)
*/
void calculateMetrics(int interested, int pass, int purchase,
                      float *interestRate, float *purchaseRate,
                      float *score, char verdict[]) {
    int totalVotes = interested + pass;

    if (totalVotes == 0) {
        *interestRate = 0.0f;
        *purchaseRate = 0.0f;
        *score = 0.0f;
        strcpy(verdict, "NOT ENOUGH DATA YET");
        return;
    }

    *interestRate = ((float)interested / (float)totalVotes) * 100.0f;
    *purchaseRate = ((float)purchase / (float)totalVotes) * 100.0f;
    *score = (*interestRate * 0.60f) + (*purchaseRate * 0.40f);

    if (*score >= 75.0f) {
        strcpy(verdict, "STRONG DEMAND");
    } else if (*score >= 40.0f) {
        strcpy(verdict, "NEEDS MORE VALIDATION");
    } else {
        strcpy(verdict, "WEAK DEMAND");
    }
}

/* ========================================================================= */
/*                           SUBMIT STARTUP IDEA                             */
/* ========================================================================= */

void submitStartupIdea(Startup startups[], int *count) {
    int i;
    int catChoice;
    Startup *newIdea;

    printf("--------------------------------------------------------\n");
    printf("             SUBMIT A NEW STARTUP CONCEPT               \n");
    printf("--------------------------------------------------------\n");

    if (*count >= MAX_STARTUPS) {
        printf("[Warning] Maximum capacity reached (%d startups).\n", MAX_STARTUPS);
        printf("Cannot register new ideas at this time.\n");
        return;
    }

    newIdea = &startups[*count];
    newIdea->id = *count + 1;

    readSafeString("Founder Name        : ", newIdea->founder, STR_MED, 1);
    readSafeString("Startup Name        : ", newIdea->name, STR_MED, 1);

    printf("\nAvailable Categories:\n");
    for (i = 0; i < TOTAL_CATEGORIES; i++) {
        printf("  %d. %s\n", i + 1, CATEGORIES[i]);
    }
    catChoice = readInteger("Select Category (1-7): ", 1, TOTAL_CATEGORIES);
    strncpy(newIdea->category, CATEGORIES[catChoice - 1], STR_SHORT - 1);
    newIdea->category[STR_SHORT - 1] = '\0';

    readSafeString("Problem Statement   : ", newIdea->problem, STR_LONG, 1);
    readSafeString("Proposed Solution   : ", newIdea->solution, STR_LONG, 1);
    readSafeString("Target Audience     : ", newIdea->audience, STR_LONG, 1);

    newIdea->views = 0;
    newIdea->interested = 0;
    newIdea->pass = 0;
    newIdea->purchaseIntent = 0;
    newIdea->feedbackCount = 0;

    (*count)++;

    printf("\n>>> SUCCESS! Startup concept \"%s\" registered with ID #%d.\n", newIdea->name, newIdea->id);
    printf(">>> It is now live on Explore and open for user validation.\n");
}

/* ========================================================================= */
/*                          EXPLORE STARTUP IDEAS                            */
/* ========================================================================= */

void exploreStartupIdeas(Startup startups[], int count) {
    int i;
    int subChoice;
    int targetId;
    int idx;
    float iRate, pRate, score;
    char verdict[STR_SHORT];

    printf("--------------------------------------------------------------------------------\n");
    printf("                         EXPLORE STARTUP IDEAS                                  \n");
    printf("--------------------------------------------------------------------------------\n");

    if (count == 0) {
        printf("No startup ideas submitted yet. Be the first to submit one!\n");
        return;
    }

    printf("%-4s | %-16s | %-12s | %-10s | %-6s | %-24s\n",
           "ID", "Startup Name", "Founder", "Category", "Score", "Verdict");
    printf("--------------------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        calculateMetrics(startups[i].interested, startups[i].pass,
                         startups[i].purchaseIntent, &iRate, &pRate, &score, verdict);

        printf("#%-3d | %-16.16s | %-12.12s | %-10.10s | %5.1f | %-24.24s\n",
               startups[i].id,
               startups[i].name,
               startups[i].founder,
               startups[i].category,
               score,
               verdict);
    }
    printf("--------------------------------------------------------------------------------\n");

    printf("\nOptions:\n");
    printf("  1. View full details of an idea\n");
    printf("  2. Return to Main Menu\n");
    subChoice = readInteger("Enter option (1-2): ", 1, 2);

    if (subChoice == 1) {
        targetId = readInteger("Enter Startup ID: ", 1, 999);
        idx = findStartupIndexById(startups, count, targetId);
        if (idx != -1) {
            startups[idx].views++; /* Increment views upon viewing full detail */
            showSingleStartupDetail(&startups[idx]);
        } else {
            printf("[Error] Startup ID #%d not found.\n", targetId);
        }
    }
}

/* Detailed card view for an individual startup */
void showSingleStartupDetail(Startup *s) {
    int j;
    float iRate, pRate, score;
    char verdict[STR_SHORT];
    calculateMetrics(s->interested, s->pass, s->purchaseIntent, &iRate, &pRate, &score, verdict);

    printf("\n========================================================================\n");
    printf(" IDEA DETAIL : %s (ID: #%d)\n", s->name, s->id);
    printf("========================================================================\n");
    printf(" Founder         : %s\n", s->founder);
    printf(" Category        : %s\n", s->category);
    printf(" Views           : %d\n", s->views);
    printf("------------------------------------------------------------------------\n");
    printf(" [01] Problem    : %s\n", s->problem);
    printf(" [02] Solution   : %s\n", s->solution);
    printf(" [03] Audience   : %s\n", s->audience);
    printf("------------------------------------------------------------------------\n");
    printf(" Current Validation Score : %.1f / 100\n", score);
    printf(" Verdict                  : %s\n", verdict);
    printf(" Total Votes              : %d (Interested: %d | Pass: %d)\n",
           s->interested + s->pass, s->interested, s->pass);
    printf(" Purchase Intent Signals  : %d\n", s->purchaseIntent);
    printf("------------------------------------------------------------------------\n");

    printf(" Community Feedback (%d notes):\n", s->feedbackCount);
    if (s->feedbackCount == 0) {
        printf("   No feedback written yet.\n");
    } else {
        for (j = 0; j < s->feedbackCount; j++) {
            printf("   [%d] \"%s\" - by %s\n", j + 1, s->feedbacks[j].text, s->feedbacks[j].author);
        }
    }
    printf("========================================================================\n");
}

/* ========================================================================= */
/*                          VALIDATE STARTUP IDEA                            */
/* ========================================================================= */

void validateStartupIdea(Startup startups[], int count) {
    int i;
    int targetId;
    int idx;
    Startup *s;
    int voteChoice;
    int purchaseChoice;
    int feedbackChoice;
    Feedback *fb;
    float iRate, pRate, score;
    char verdict[STR_SHORT];

    printf("--------------------------------------------------------\n");
    printf("                   VALIDATE AN IDEA                     \n");
    printf("--------------------------------------------------------\n");

    if (count == 0) {
        printf("No startups available to validate yet.\n");
        return;
    }

    printf("Available Startups:\n");
    for (i = 0; i < count; i++) {
        printf("  #%d. %s (by %s) - %s\n",
               startups[i].id, startups[i].name, startups[i].founder, startups[i].category);
    }
    printf("--------------------------------------------------------\n");

    targetId = readInteger("Enter the ID of the startup you want to validate: ", 1, 999);
    idx = findStartupIndexById(startups, count, targetId);

    if (idx == -1) {
        printf("[Error] Startup with ID #%d does not exist.\n", targetId);
        return;
    }

    s = &startups[idx];
    s->views++; /* Validating counts as an active engagement/view */

    printf("\nValidating \"%s\" (by %s):\n", s->name, s->founder);
    printf("Problem  : %s\n", s->problem);
    printf("Solution : %s\n", s->solution);
    printf("--------------------------------------------------------\n");

    /* Step 1: Would you use this? */
    printf("\n[Step 1/3] Would you use this product?\n");
    printf("  1. Yes - Interested (I would use this)\n");
    printf("  2. No  - Pass (Not interested)\n");
    voteChoice = readInteger("Your vote (1-2): ", 1, 2);
    if (voteChoice == 1) {
        s->interested++;
        printf("-> Recorded: INTERESTED vote added.\n");
    } else {
        s->pass++;
        printf("-> Recorded: PASS vote added.\n");
    }

    /* Step 2: Purchase Intent */
    printf("\n[Step 2/3] Would you pay / pre-order this solution?\n");
    printf("  1. Yes - I would pay for this (Purchase Intent)\n");
    printf("  2. No  - Not ready to purchase\n");
    purchaseChoice = readInteger("Your choice (1-2): ", 1, 2);
    if (purchaseChoice == 1) {
        s->purchaseIntent++;
        printf("-> Recorded: PURCHASE INTENT logged.\n");
    } else {
        printf("-> Recorded: No purchase intent logged.\n");
    }

    /* Step 3: Text Feedback */
    printf("\n[Step 3/3] Would you like to leave constructive feedback for %s?\n", s->founder);
    printf("  1. Yes, leave written feedback\n");
    printf("  2. Skip feedback\n");
    feedbackChoice = readInteger("Your choice (1-2): ", 1, 2);

    if (feedbackChoice == 1) {
        if (s->feedbackCount < MAX_FEEDBACK) {
            fb = &s->feedbacks[s->feedbackCount];
            readSafeString("Your Name/Role : ", fb->author, STR_SHORT, 1);
            readSafeString("Your Feedback  : ", fb->text, STR_LONG, 1);
            s->feedbackCount++;
            printf("-> Feedback successfully sent to %s!\n", s->founder);
        } else {
            printf("[Notice] Feedback inbox for this startup is full (%d responses).\n", MAX_FEEDBACK);
        }
    }

    /* Compute updated metrics and display real-time signal */
    calculateMetrics(s->interested, s->pass, s->purchaseIntent, &iRate, &pRate, &score, verdict);

    printf("\n--------------------------------------------------------\n");
    printf(">>> THANK YOU FOR VALIDATING!\n");
    printf("Updated Validation Score : %.1f / 100\n", score);
    printf("Current Verdict          : %s\n", verdict);
    printf("--------------------------------------------------------\n");
}

/* ========================================================================= */
/*                          FOUNDER DASHBOARD                                */
/* ========================================================================= */

void founderDashboard(Startup startups[], int count) {
    int i;
    int k;
    int targetId;
    int idx;
    Startup *s;
    float iRate, pRate, score;
    char verdict[STR_SHORT];
    int totalVotes;

    printf("================================================================================\n");
    printf("                             FOUNDER DASHBOARD                                  \n");
    printf("================================================================================\n");

    if (count == 0) {
        printf("No startup ideas to display in dashboard.\n");
        return;
    }

    printf("Select an idea to generate its Full Validation Report:\n");
    for (i = 0; i < count; i++) {
        printf("  %d. %s (Founder: %s, Category: %s)\n",
               startups[i].id, startups[i].name, startups[i].founder, startups[i].category);
    }
    printf("--------------------------------------------------------------------------------\n");

    targetId = readInteger("Enter Startup ID (or enter 0 to return): ", 0, 999);
    if (targetId == 0) {
        return;
    }

    idx = findStartupIndexById(startups, count, targetId);
    if (idx == -1) {
        printf("[Error] Startup ID #%d not found.\n", targetId);
        return;
    }

    s = &startups[idx];
    calculateMetrics(s->interested, s->pass, s->purchaseIntent, &iRate, &pRate, &score, verdict);
    totalVotes = s->interested + s->pass;

    printf("\n========================================================================\n");
    printf("                  TESTMINT STARTUP VALIDATION REPORT                     \n");
    printf("========================================================================\n");
    printf(" Startup Name    : %s\n", s->name);
    printf(" Founder         : %s\n", s->founder);
    printf(" Category        : %s\n", s->category);
    printf(" Total Views     : %d\n", s->views);
    printf("------------------------------------------------------------------------\n");
    printf(" 1. VOTING BREAKDOWN:\n");
    printf("    - Total Votes Cast      : %d\n", totalVotes);
    printf("    - Interested Votes      : %d\n", s->interested);
    printf("    - Pass / Not Interested : %d\n", s->pass);
    printf("    - Interest Rate         : %.2f%%\n", iRate);
    printf("------------------------------------------------------------------------\n");
    printf(" 2. PURCHASE INTENT BREAKDOWN:\n");
    printf("    - Purchase Intent Count : %d\n", s->purchaseIntent);
    printf("    - Purchase Intent Rate  : %.2f%%\n", pRate);
    printf("------------------------------------------------------------------------\n");
    printf(" 3. VALIDATION FORMULA & SCORE:\n");
    printf("    Formula: (Interest Rate * 0.60) + (Purchase Intent Rate * 0.40)\n");
    printf("    Math   : (%.2f * 0.60) + (%.2f * 0.40)\n", iRate, pRate);
    printf("             = %.2f + %.2f\n", iRate * 0.60f, pRate * 0.40f);
    printf("    FINAL VALIDATION SCORE  : %.1f / 100\n", score);
    printf("------------------------------------------------------------------------\n");
    printf(" 4. OFFICIAL VERDICT:\n");
    printf("    ==> [ %s ] <==\n", verdict);

    if (totalVotes == 0) {
        printf("    Guidance: [REFINE] Not enough data yet. Encourage prospective users to vote\n");
        printf("              and share feedback to validate your concept before building.\n");
    } else if (score >= 75.0f) {
        printf("    Guidance: [BUILD] Users are enthusiastic and willing to pay. Strong candidate\n");
        printf("              to proceed with building an MVP.\n");
    } else if (score >= 40.0f) {
        printf("    Guidance: [REFINE] Promising initial interest, but purchase intent requires\n");
        printf("              further refinement before heavy software investment.\n");
    } else {
        printf("    Guidance: [PIVOT] Weak demand signal detected. Recommend interviewing target\n");
        printf("              users, reformulating the value proposition, or pivoting.\n");
    }
    printf("------------------------------------------------------------------------\n");
    printf(" 5. COMMUNITY FEEDBACK LOG (%d notes):\n", s->feedbackCount);
    if (s->feedbackCount == 0) {
        printf("    No qualitative feedback logged yet.\n");
    } else {
        for (k = 0; k < s->feedbackCount; k++) {
            printf("    * \"%s\" - %s\n", s->feedbacks[k].text, s->feedbacks[k].author);
        }
    }
    printf("========================================================================\n");
}

/* ========================================================================= */
/*                         INITIAL SAMPLE DATA SEED                          */
/* ========================================================================= */

void initializeSampleData(Startup startups[], int *count) {
    /* 1. PaySplit - High demand concept (Verdict: BUILD) */
    Startup *s1 = &startups[0];
    s1->id = 1;
    strcpy(s1->name, "PaySplit");
    strcpy(s1->founder, "Aarav Mehta");
    strcpy(s1->category, "FinTech");
    strcpy(s1->problem, "Flatmates struggle to split rent, groceries and Wi-Fi over WhatsApp, causing awkward follow-ups.");
    strcpy(s1->solution, "UPI-native shared ledger that automatically splits bills and sends polite reminder collect requests.");
    strcpy(s1->audience, "College hostelites and young working professionals sharing apartments in metro cities.");
    s1->views = 412;
    s1->interested = 240;
    s1->pass = 46;
    s1->purchaseIntent = 158;
    s1->feedbackCount = 2;
    strcpy(s1->feedbacks[0].author, "Riya S. (Student)");
    strcpy(s1->feedbacks[0].text, "Our flat uses messy Google Sheets. If reminders are automated I will switch tomorrow.");
    strcpy(s1->feedbacks[1].author, "Karthik N. (Engineer)");
    strcpy(s1->feedbacks[1].text, "Direct UPI settle-up in the same screen is the killer feature.");

    /* 2. KhetiMitra - Strong demand in AgriTech (Verdict: BUILD) */
    Startup *s2 = &startups[1];
    s2->id = 2;
    strcpy(s2->name, "KhetiMitra");
    strcpy(s2->founder, "Priya Deshmukh");
    strcpy(s2->category, "AgriTech");
    strcpy(s2->problem, "Small farmers sell at 10-20% discounts because they lack real-time price discovery across nearby mandis.");
    strcpy(s2->solution, "Vernacular WhatsApp voice/text assistant providing daily crop rates and optimal mandi recommendations.");
    strcpy(s2->audience, "Smallholder farmers with under 5 acres in regional belts.");
    s2->views = 538;
    s2->interested = 341;
    s2->pass = 39;
    s2->purchaseIntent = 212;
    s2->feedbackCount = 1;
    strcpy(s2->feedbacks[0].author, "Ramesh K. (Farmer)");
    strcpy(s2->feedbacks[0].text, "My father calls 3 traders each morning. This WhatsApp bot will save hours.");

    /* 3. GSTEase - Needs more validation / low intent (Verdict: REFINE) */
    Startup *s3 = &startups[2];
    s3->id = 3;
    strcpy(s3->name, "GSTEase");
    strcpy(s3->founder, "Suresh CA");
    strcpy(s3->category, "SaaS");
    strcpy(s3->problem, "MSME owners spend hours matching purchase invoices with GSTR-2B, missing input tax credit.");
    strcpy(s3->solution, "Automated OCR tool that extracts bill amounts and flags mismatches with portal data.");
    strcpy(s3->audience, "Chartered Accountants and small business owners.");
    s3->views = 214;
    s3->interested = 63;
    s3->pass = 79;
    s3->purchaseIntent = 31;
    s3->feedbackCount = 1;
    strcpy(s3->feedbacks[0].author, "CA Suresh B.");
    strcpy(s3->feedbacks[0].text, "Existing accounting tools already do part of this. Value proposition needs to be sharper.");

    *count = 3;
}
