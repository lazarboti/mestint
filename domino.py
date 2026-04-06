from keres import *

MEZOK = tuple((r, c) for r in range(1, 9) for c in range(1, 9))


class DominoLefedes(Feladat):
    def __init__(self):
        self.kezdő = (tuple(), None)

    def célteszt(self, állapot):
        lefedett, kihagyott = állapot
        return len(lefedett) == 63 and kihagyott is not None

    def rákövetkező(self, állapot):
        lefedett, kihagyott = állapot
        elso_szabad = None
        for m in MEZOK:
            if m not in lefedett and m != kihagyott:
                elso_szabad = m
                break

        if not elso_szabad: return []

        gyerekek = []
        r, c = elso_szabad

        if kihagyott is None:
            gyerekek.append((f"kihagy_{r}_{c}", (lefedett, elso_szabad)))

        if c + 2 <= 8 and (r, c + 1) not in lefedett and (r, c + 1) != kihagyott and \
                (r, c + 2) not in lefedett and (r, c + 2) != kihagyott:
            uj_lefedett = tuple(sorted(list(lefedett) + [(r, c), (r, c + 1), (r, c + 2)]))
            gyerekek.append((f"viz_{r}_{c}", (uj_lefedett, kihagyott)))

        if r + 2 <= 8 and (r + 1, c) not in lefedett and (r + 1, c) != kihagyott and \
                (r + 2, c) not in lefedett and (r + 2, c) != kihagyott:
            uj_lefedett = tuple(sorted(list(lefedett) + [(r, c), (r + 1, c), (r + 2, c)]))
            gyerekek.append((f"fug_{r}_{c}", (uj_lefedett, kihagyott)))

        return gyerekek


if __name__ == '__main__':
    feladat = DominoLefedes()
    eredmeny = mélységi_gráfkereső(feladat)
    if eredmeny:
        print(len(eredmeny.megoldás()))
        ut = eredmeny.út()
        ut.reverse()
        print(ut)