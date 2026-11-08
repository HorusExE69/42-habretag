import sys


class ScoreError(Exception):
    def __init__(self, message):
        super().__init__(message)


class InvalidParam(Exception):
    def __init__(self, lst_message):
        str_message = ""
        for i in range(0, len(lst_message)):
            if i != len(lst_message) - 1:
                str_message += f"{lst_message[i]}\n"
            else:
                str_message += f"{lst_message[i]}"
        super().__init__(str_message)


class Score:
    def __init__(self, score):
        self.score = score
        score = list(map(int, score))
        self.players = len(score)
        self.total_score = sum(score)
        if self.players != 0:
            self.average_score = self.total_score / self.players
        else:
            self.average_score = 0
        self.highest_score = max(score)
        self.lowest_score = min(score)
        self.score_range = self.highest_score - self.lowest_score

    def show_analytics(self):
        print(f"Total Players: {self.players}")
        print(f"Total Score: {self.total_score}")
        print(f"Average Score: {self.average_score:.1f}")
        print(f"Highest Score: {self.highest_score}")
        print(f"Lowest Score: {self.lowest_score}")
        print(f"Score Range: {self.score_range}")

    @staticmethod
    def check_score(score):
        errors = []
        new_score = []
        j = 0
        for i in range(0, len(score)):
            try:
                new_score.append(int(score[i]))
            except (ValueError, TypeError):
                errors.append(f"Non-numeric score provided: '{score[i]}'")
            else:
                if int(score[i]) < 0:
                    errors.append(f"Negative score provided: '{score[i]}'")
                else:
                    j += 1
        return new_score, errors


if __name__ == "__main__":
    print("=== Player Score Analytics ===")
    lst_score = sys.argv[1:]
    try:
        n_score, err = Score.check_score(lst_score)
        if n_score != lst_score:
            raise InvalidParam(err)
    except InvalidParam as e:
        print(e)
    try:
        if not n_score:
            raise ScoreError(
                "No score provided. Usage: python3 ft_score_analytics.py <score1> <score2> ...")
        analytics = Score(n_score)
        analytics.show_analytics()
    except ScoreError as e:
        print(e)
