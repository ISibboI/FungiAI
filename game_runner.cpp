#include "game_runner.h"
#include "debug.h"
#include "structured_pile.h"

#include <stdexcept>
#include <sstream>

using namespace std;

void run_game(GameState& game_state, int& result, Action* (&p1)(PlayerView*, GameState*),
    Action* (&p2)(PlayerView*, GameState*), void (&event_illegal_turn)(GameState&, Action&)) {

    bool game_running = true;
    bool turn_p1 = true;
    PlayerView* player_view = 0;
    Action* action = 0;

    while (game_running) {
        if (turn_p1) {
            player_view = game_state.get_p1_view();
            action = p1(player_view, &game_state);
        } else {
            player_view = game_state.get_p2_view();
            action = p2(player_view, &game_state);
        }

        print("Trying action: " + action->str());
        bool successful_turn = game_state.action(action);

        if (!successful_turn) {
            event_illegal_turn(game_state, *action);
            result = turn_p1 ? -1 : 1;
            return;
        }

        delete player_view;
        delete action;

        game_running = game_state.finalize_turn(turn_p1);
        turn_p1 = !turn_p1;
        print("New game state:\n" + game_state.str());
    }

    int points_p1 = 0;
    int points_p2 = 0;
    int shrooms_p1 = 0;
    int shrooms_p2 = 0;

    for (unsigned i = 0; i < shroom_max_id; i++) {
        shrooms_p1 += game_state.display_p1[i];
        shrooms_p2 += game_state.display_p2[i];
        points_p1 += game_state.display_p1[i] * cards[i].tastyness;
        points_p2 += game_state.display_p2[i] * cards[i].tastyness;
    }

    #ifdef DEBUG
    cout << "Game finished!" << endl;
    cout << "Points player 1 -- 2: " << points_p1 << " -- " << points_p2 << endl;
    cout << "Mushroom count player 1 -- 2: " << shrooms_p1 << " -- " << shrooms_p2 << endl;
    #endif // DEBUG

    if (points_p1 == points_p2) {
        if (shrooms_p1 == shrooms_p2) {
            result = 0;
        } else {
            result = (shrooms_p1 > shrooms_p2) * 2 - 1;
        }
    } else {
        result = (points_p1 > points_p2) * 2 - 1;
    }
}
