#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Hanoi_game 
{
    std::vector<int> pegs[3];
    int total_disks;          
    int moves_count;          

    Hanoi_game(int disks) 
    {
        total_disks = disks;
        moves_count = 0;
        for (int i = disks; i >= 1; --i) 
        {
            pegs[0].push_back(i);
        }
    }

    void display() const {
        std::cout << "\n--- CURRENT BOARD STATE ---\n\n";

        for (int i = total_disks - 1; i >= 0; --i) 
        {
            for (int p = 0; p < 3; ++p) 
            {
                if (i < pegs[p].size()) 
                {
                    std::cout << "   [" << pegs[p][i] << "]   ";
                }
                else 
                {
                    std::cout << "    |    ";
                }
            }
            std::cout << "\n";
        }

        std::cout << "=========================\n";
        std::cout << "   (1)      (2)      (3)   \n\n";
        std::cout << "Moves made: " << moves_count << "\n";
        std::cout << "Minimum moves required: " << (pow(2, total_disks) - 1) << "\n\n";
    }

    bool is_won() 
    {
        return pegs[2].size() == total_disks;
    }

    bool make_move(int from, int to) 
    {
        if (from < 0 || from > 2 || to < 0 || to > 2) 
        {
            std::cout << "ERROR: Invalid peg number!\n";
            return false;
        }
        if (from == to) 
        {
            std::cout << "ERROR: You cannot move a disk to the same peg!\n";
            return false;
        }
        if (pegs[from].empty()) 
        {
            std::cout << "ERROR: The selected source peg is empty!\n";
            return false;
        }

        int disk_to_move = pegs[from].back();

        if (!pegs[to].empty() && pegs[to].back() < disk_to_move) 
        {
            std::cout << "ERROR: Cannot place a larger disk on top of a smaller disk!\n";
            return false;
        }

        pegs[from].pop_back();
        pegs[to].push_back(disk_to_move);
        moves_count++;
        return true;
    }
};

int main() 
{
    int disks;
    std::cout << "=== WELCOME TO THE TOWERS OF HANOI ===\n";
    std::cout << "Enter the number of disks (3-5 recommended): ";
    std::cin >> disks;

    if (disks < 2) 
    {
        std::cout << "The game cannot be played with this number of disks.\n";
        return 0;
    }

    Hanoi_game game(disks);

    while (!game.is_won()) 
    {
        game.display();

        int from, to;
        std::cout << "Enter your move (FROM peg and TO peg, e.g., '1 3'): ";
        std::cin >> from >> to;

        if (!game.make_move(from - 1, to - 1)) 
        {
            std::cout << "Please try again.\n";
        }
    }

    game.display();
    std::cout << "Congratulations! You completed the game in " << game.moves_count << " moves!\n";

    return 0;
}
