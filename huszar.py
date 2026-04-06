from keres import *

MEZOK = tuple((r, c) for r in range(1, 9) for c in range(1, 9) if (r, c) not in [(1, 1), (1, 8), (8, 1), (8, 8)])


class HuszarVandorlas(Feladat):
    def __init__(self):
        kezdő_mezo = (1, 2)
        self.kezdő = (kezdő_mezo, tuple([kezdő_mezo]))

    def célteszt(self, állapot):
        aktualis, bejart = állapot
        if len(bejart) == 60:
            r1, c1 = aktualis
            r2, c2 = (1, 2)
            if (abs(r1 - r2) == 1 and abs(c1 - c2) == 2) or (abs(r1 - r2) == 2 and abs(c1 - c2) == 1):
                return True
        return False

    def rákövetkező(self, állapot):
        aktualis, bejart = állapot
        r, c = aktualis
        lepesek = [(r - 2, c - 1), (r - 2, c + 1), (r - 1, c - 2), (r - 1, c + 2),
                   (r + 1, c - 2), (r + 1, c + 2), (r + 2, c - 1), (r + 2, c + 1)]

        validek = []
        for uj_r, uj_c in lepesek:
            if (uj_r, uj_c) in MEZOK and (uj_r, uj_c) not in bejart:
                validek.append((uj_r, uj_c))

        def onward(m):
            ur, uc = m
            count = 0
            for dr, dc in [(-2, -1), (-2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2), (2, -1), (2, 1)]:
                if (ur + dr, uc + dc) in MEZOK and (ur + dr, uc + dc) not in bejart:
                    count += 1
            return count

        validek.sort(key=onward, reverse=True)

        gyerekek = []
        for uj_r, uj_c in validek:
            uj_mezo = (uj_r, uj_c)
            uj_bejart = tuple(list(bejart) + [uj_mezo])
            gyerekek.append((f"lép_{uj_r}_{uj_c}", (uj_mezo, uj_bejart)))

        return gyerekek


if __name__ == '__main__':
    feladat = HuszarVandorlas()
    eredmeny = mélységi_gráfkereső(feladat)
    if eredmeny:
        print(len(eredmeny.megoldás()))
        ut = eredmeny.út()
        ut.reverse()
        print(ut)