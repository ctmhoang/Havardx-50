#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isCycle(int loserIdx, int winnerIdx);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // Check if name is validated
    for(int i = 0, n = candidate_count; i < n; i++)
    {
        if(strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int i = 0; i < candidate_count - 1; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            int win = ranks[i], lose = ranks[j];
            preferences[win][lose] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for(int i = 0 ; i < candidate_count - 1; i ++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            int num_pre_1 = preferences[i][j],
            num_pre_2 = preferences[j][i];
            if(num_pre_1 > num_pre_2)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (num_pre_2 > num_pre_1)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Selection sort
    for(int i = 0; i < pair_count - 1; i++)
    {
        int maxStrIdx = i, maxStr = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        pair maxStrPair= pairs[i];
        // Linear search
        // Find the most powerful strength of victory
        for(int j = i + 1; j < pair_count; j++)
        {
            int strength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if(strength > maxStr)
            {
                maxStr = strength;
                maxStrPair = pairs[j];
                maxStrIdx = j;
            }
        }
        // Swap
        pair tempPair = pairs[i];
        pairs[i] = maxStrPair;
        pairs[maxStrIdx] = tempPair;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for(int i = 0; i < pair_count; i ++)
    {
        int winnerIdx = pairs[i].winner;
        int loserIdx = pairs[i].loser;
        if(!isCycle(loserIdx, winnerIdx))
        {
            locked[winnerIdx][loserIdx] = true;
        }
    }
    return;
}

//Detect cycles
bool isCycle(int loserIdx, int winnerIdx)
{
    //Find winnerIdx
    int cmpIdx[pair_count - 1];
    memset( cmpIdx, -1, (pair_count - 1)*sizeof(int));
    int countCase = 0;
    //Update case has loserIdx win over someone
    for(int i = 0 ; i < pair_count; i++)
    {
        if(pairs[i].winner == loserIdx)
        {
            cmpIdx[countCase] = pairs[i].loser;
            countCase ++;
        }
    }
    if(!countCase) //No more case
    {
        if(loserIdx == winnerIdx)
        {
            return true;
        }
        return false;
    }
    else
    {
        bool res = false;
        for(int i = 0 ; i < countCase; i++)
        {
            if(cmpIdx[i] != -1) //should always true
            {
                res += isCycle(cmpIdx[i],winnerIdx);
            }
        }
        return res;
    }
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
    for(int i = 0; i < pair_count; i++)
    {
        candidates[pairs[i].loser] = "0";
    }
    for(int i = 0 ; i < candidate_count; i++)
    {
        if(strcmp(candidates[i], "0") != 0)
        {
            printf("%s",candidates[i]);
        }
    }
    return;
}
