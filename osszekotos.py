from keres import *

POTTYOK = tuple([(1, 1), (1, 5), (2, 4), (2, 7), (3, 3), (4, 6),
                 (5, 2), (5, 5), (6, 3), (6, 8), (7, 1), (7, 6), (8, 4), (8, 8)])


class Vonalrajzolo(Feladat):
    def __init__(self):
        self.kezdő = ((1, 1), None, tuple([(1, 1)]))

    def célteszt(self, állapot):
        curr, prev, bejart = állapot
        if len(bejart) == 64:
            r1, c1 = bejart[0]
            if abs(curr[0] - r1) + abs(curr[1] - c1) == 1:
                if curr in POTTYOK:
                    if prev[0] == r1 or prev[1] == c1:
                        return False
                if (r1, c1) in POTTYOK:
                    r2, c2 = bejart[1]
                    if curr[0] == r2 or curr[1] == c2:
                        return False
                return True
        return False

    def rákövetkező(self, állapot):
        curr, prev, bejart = állapot
        r, c = curr
        szomszedok = [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]
        validek = []

        for uj_r, uj_c in szomszedok:
            if 1 <= uj_r <= 8 and 1 <= uj_c <= 8:
                uj_mezo = (uj_r, uj_c)
                if uj_mezo not in bejart:
                    if curr in POTTYOK and prev is not None:
                        if prev[0] == uj_r or prev[1] == uj_c:
                            continue
                    validek.append(uj_mezo)

        def unvisited_neighbors(m):
            ur, uc = m
            count = 0
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                if 1 <= ur + dr <= 8 and 1 <= uc + dc <= 8 and (ur + dr, uc + dc) not in bejart:
                    count += 1
            return count

        validek.sort(key=unvisited_neighbors, reverse=True)

        gyerekek = []
        for uj_mezo in validek:
            uj_bejart = tuple(list(bejart) + [uj_mezo])
            gyerekek.append((f"{uj_mezo[0]}_{uj_mezo[1]}", (uj_mezo, curr, uj_bejart)))

        return gyerekek


if __name__ == '__main__':
    feladat = Vonalrajzolo()
    eredmeny = mélységi_fakereső(feladat)
    if eredmeny:
        print(len(eredmeny.megoldás()))
    else:
        print("Nincs megoldás")