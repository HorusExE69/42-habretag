import random


def gen_event(players_lst, actions_list):
    while True:
        player = random.choice(players_lst)
        action = random.choice(actions_list)
        yield (player, action)


def consume_event(tuple_lst) :
    while tuple_lst:
        event = random.choice(tuple_lst)
        tuple_lst.remove(event)
        yield event

if __name__ == "__main__":
    print("=== Game Data Stream Processor ===")

    players = [
        "Horus",
        "Coldified",
        "Tenz",
        "Faker",
        "ItzTimmy",
        "Guesti",
        "Swight",
        "Fugu",
        "Zen",
        "Pixie",
        "Benjyfishy",
        "Wemmbu"
    ]

    actions = [
        "Win RLCS",
        "Win FNCS",
        "Win ALGS",
        "Win VCT",
        "Win LCS",
        "Win BSCS",
        "No Scope",
        "Ace",
        "Clutch",
        "Triple Reset",
        "Psycho",
        "Kill Framefrags",
        "Do Elytra Mace + Minecart TNT",
        "Reach HT1"
    ]

    gen = gen_event(players, actions)
    tuple_lst = []

    for i in range(1000):
        event = next(gen)
        print(f"Event {i}: Player {event[0]} did action {event[1]}")

    for j in range(10):
        tuple_lst.append(next(gen))

    print(f"Built list of 10 events: {tuple_lst}")

    for evnt in consume_event(tuple_lst):
        print(f"Got event from list: {evnt}")
        print(f"Remains in list: {tuple_lst}")

