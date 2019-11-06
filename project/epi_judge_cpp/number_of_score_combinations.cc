#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
	const vector<int>& individual_play_scores)
{
	vector<vector<int>> combos_for_score(individual_play_scores.size(), vector<int>(final_score + 1, 0));
	for (auto& combo : combos_for_score)
		combo[0] = 1;

	for (int play = 0; play < combos_for_score.size(); ++play) {
		for (int score = 1; score <= final_score; ++score) {
			int without_play = (play > 0) ? combos_for_score[play - 1][score] : 0;
			int with_play = (score >= individual_play_scores[play])
				? combos_for_score[play][score - individual_play_scores[play]]
				: 0;
			combos_for_score[play][score] = without_play + with_play;
		}
	}

	return combos_for_score.back()[final_score];
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "final_score", "individual_play_scores" };
	return GenericTestMain(args, "number_of_score_combinations.cc",
		"number_of_score_combinations.tsv",
		&NumCombinationsForFinalScore, DefaultComparator{},
		param_names);
}