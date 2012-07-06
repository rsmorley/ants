#include "Bot.h"
#include "AStar.h"

using namespace std;

//constructor
Bot::Bot()
{

};

//plays a single game of Ants.
void Bot::playGame()
{
    //reads the game parameters and sets up
    cin >> state;
    state.setup();
    endTurn();

    //continues making moves while the game is not over
    while(cin >> state)
    {
        state.updateVisionInformation();
        makeMoves();
        endTurn();
    }
};

//makes the bots moves for the turn
void Bot::makeMoves()
{
    state.bug << "turn " << state.turn << ":" << endl;
    state.bug << state << endl;

	AStar star(state.myAnts[0], state.food[0], state, 20);
	if(star.search()) {
		std::vector<Location> path = star.getPath();
		state.bug << path.size() << endl;

	}
	else
	{
		state.bug << "no path found" << endl;
	}

    //picks out moves for each ant
    for(int ant=0; ant<(int)state.myAnts.size(); ant++)
    {
        for(int d=0; d<TDIRECTIONS; d++)
        {
            Location loc = state.getLocation(state.myAnts[ant], d);

				if(doMove(loc)) {
					state.makeMove(state.myAnts[ant], d);
					break;
				}
        }
    }

    state.bug << "time taken: " << state.timer.getTime() << "ms" << endl << endl;
};

bool Bot::doMove(const Location &loc)
{
	if(state.grid[loc.row][loc.col].isWater || (state.grid[loc.row][loc.col].ant != -1)) {
		return false;
	}
	else {
		return true;
	}
};

//finishes the turn
void Bot::endTurn()
{
    if(state.turn > 0)
        state.reset();
    state.turn++;

    cout << "go" << endl;
};
