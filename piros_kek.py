from keres import *


class PirosKek(Feladat):
    def __init__(self):
        self.kezdő = (
            "KKKPP",
            "KKKPP",
            "KKUPP",
            "KKPPP",
            "KKPPP"
        )
        self.cél = (
            "PPPKK",
            "PPPKK",
            "PPUKK",
            "PPKKK",
            "PPKKK"
        )

    def célteszt(self, állapot):
        return állapot == self.cél

    def rákövetkező(self, állapot):
        sima = []
        ugras = []
        m = [list(sor) for sor in állapot]

        ur, uc = -1, -1
        for r in range(5):
            for c in range(5):
                if m[r][c] == 'U':
                    ur, uc = r, c
                    break

        if uc > 0 and m[ur][uc - 1] == 'K':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur][uc - 1] = uj[ur][uc - 1], uj[ur][uc]
            sima.append((f"K_{ur}_{uc - 1}", tuple("".join(s) for s in uj)))

        if ur > 0 and m[ur - 1][uc] == 'K':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur - 1][uc] = uj[ur - 1][uc], uj[ur][uc]
            sima.append((f"K_{ur - 1}_{uc}", tuple("".join(s) for s in uj)))

        if uc < 4 and m[ur][uc + 1] == 'P':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur][uc + 1] = uj[ur][uc + 1], uj[ur][uc]
            sima.append((f"P_{ur}_{uc + 1}", tuple("".join(s) for s in uj)))

        if ur < 4 and m[ur + 1][uc] == 'P':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur + 1][uc] = uj[ur + 1][uc], uj[ur][uc]
            sima.append((f"P_{ur + 1}_{uc}", tuple("".join(s) for s in uj)))

        if uc > 1 and m[ur][uc - 2] == 'K' and m[ur][uc - 1] == 'P':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur][uc - 2] = uj[ur][uc - 2], uj[ur][uc]
            ugras.append((f"Ku_{ur}_{uc - 2}", tuple("".join(s) for s in uj)))

        if ur > 1 and m[ur - 2][uc] == 'K' and m[ur - 1][uc] == 'P':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur - 2][uc] = uj[ur - 2][uc], uj[ur][uc]
            ugras.append((f"Ku_{ur - 2}_{uc}", tuple("".join(s) for s in uj)))

        if uc < 3 and m[ur][uc + 2] == 'P' and m[ur][uc + 1] == 'K':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur][uc + 2] = uj[ur][uc + 2], uj[ur][uc]
            ugras.append((f"Pu_{ur}_{uc + 2}", tuple("".join(s) for s in uj)))

        if ur < 3 and m[ur + 2][uc] == 'P' and m[ur + 1][uc] == 'K':
            uj = [list(sor) for sor in állapot]
            uj[ur][uc], uj[ur + 2][uc] = uj[ur + 2][uc], uj[ur][uc]
            ugras.append((f"Pu_{ur + 2}_{uc}", tuple("".join(s) for s in uj)))

        return sima + ugras


if __name__ == '__main__':
    feladat = PirosKek()


    def heurisztika(csúcs):
        h = 0
        for r in range(5):
            for c in range(5):
                if csúcs.állapot[r][c] == 'K':
                    h += (4 - r) + (4 - c)
                elif csúcs.állapot[r][c] == 'P':
                    h += r + c
        return h


    eredmeny = best_first(feladat, heurisztika)
    if eredmeny:
        print(len(eredmeny.megoldás()))
    else:
        print("Nincs megoldás")