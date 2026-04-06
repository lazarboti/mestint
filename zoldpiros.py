from keres import *

SZOMSZEDOK_11 = {
    (1, 1): [(1, 2)], (1, 2): [(1, 1), (1, 3), (2, 2)], (1, 3): [(1, 2)],
    (2, 2): [(1, 2), (3, 2)],
    (3, 1): [(3, 2)], (3, 2): [(3, 1), (3, 3), (2, 2), (4, 2)], (3, 3): [(3, 2)],
    (4, 2): [(3, 2), (5, 2)],
    (5, 1): [(5, 2)], (5, 2): [(5, 1), (5, 3), (4, 2)], (5, 3): [(5, 2)]
}
SORREND_11 = list(SZOMSZEDOK_11.keys())


class ZoldPiros(Feladat):
    def __init__(self):
        k_dict = {p: 'Z' if p[0] == 1 else ('P' if p[0] == 5 else 'U') for p in SORREND_11}
        c_dict = {p: 'P' if p[0] == 1 else ('Z' if p[0] == 5 else 'U') for p in SORREND_11}
        self.kezdő = tuple(k_dict[p] for p in SORREND_11)
        self.cél = tuple(c_dict[p] for p in SORREND_11)

    def célteszt(self, állapot):
        return állapot == self.cél

    def rákövetkező(self, állapot):
        gyerekek = []
        u_indexek = [i for i, val in enumerate(állapot) if val == 'U']

        for u_idx in u_indexek:
            u_coord = SORREND_11[u_idx]
            for sz_coord in SZOMSZEDOK_11[u_coord]:
                sz_idx = SORREND_11.index(sz_coord)

                if állapot[sz_idx] != 'U':
                    uj_allapot = list(állapot)
                    uj_allapot[u_idx], uj_allapot[sz_idx] = uj_allapot[sz_idx], uj_allapot[u_idx]
                    gyerekek.append((f"{állapot[sz_idx]}_{sz_coord}_{u_coord}", tuple(uj_allapot)))

        return gyerekek


if __name__ == '__main__':
    feladat = ZoldPiros()


    def heurisztika(csúcs):
        return sum(10 for a, b in zip(csúcs.állapot, feladat.cél) if a != 'U' and a != b)


    eredmeny = a_csillag(feladat, heurisztika)
    if eredmeny:
        print(len(eredmeny.megoldás()))
        ut = eredmeny.út()
        ut.reverse()
        print(ut)