from keres import *

SZOMSZEDOK = {
    (1, 1): [(2, 2)],
    (2, 1): [(2, 2), (3, 2)], (2, 2): [(1, 1), (2, 1), (2, 3)], (2, 3): [(2, 2), (3, 4)],
    (3, 1): [(3, 2), (4, 2)], (3, 2): [(2, 1), (3, 1), (3, 3)], (3, 3): [(3, 2), (3, 4), (4, 4)],
    (3, 4): [(2, 3), (3, 3), (3, 5)], (3, 5): [(3, 4), (4, 6)],
    (4, 1): [(4, 2)], (4, 2): [(3, 1), (4, 1), (4, 3)], (4, 3): [(4, 2), (4, 4)],
    (4, 4): [(3, 3), (4, 3), (4, 5)], (4, 5): [(4, 4), (4, 6)], (4, 6): [(3, 5), (4, 5), (4, 7)], (4, 7): [(4, 6)]
}
SORREND = list(SZOMSZEDOK.keys())

DIST = {}
for start in SORREND:
    DIST[start] = {start: 0}
    q = [start]
    while q:
        curr = q.pop(0)
        for sz in SZOMSZEDOK[curr]:
            if sz not in DIST[start]:
                DIST[start][sz] = DIST[start][curr] + 1
                q.append(sz)


class HaromszogTol(Feladat):
    def __init__(self):
        kezdő_dict = {
            (1, 1): 4, (2, 1): 9, (2, 2): 11, (2, 3): 7, (3, 1): 10, (3, 2): 8, (3, 3): 14,
            (3, 4): 6, (3, 5): 5, (4, 1): 2, (4, 2): 'U', (4, 3): 13, (4, 4): 1, (4, 5): 3,
            (4, 6): 12, (4, 7): 'U'
        }
        cél_dict = {
            (1, 1): 1, (2, 1): 2, (2, 2): 3, (2, 3): 4, (3, 1): 5, (3, 2): 6, (3, 3): 7,
            (3, 4): 8, (3, 5): 9, (4, 1): 10, (4, 2): 11, (4, 3): 12, (4, 4): 13, (4, 5): 14,
            (4, 6): 'U', (4, 7): 'U'
        }
        self.kezdő = tuple(kezdő_dict[p] for p in SORREND)
        self.cél = tuple(cél_dict[p] for p in SORREND)

    def célteszt(self, állapot):
        return állapot == self.cél

    def rákövetkező(self, állapot):
        gyerekek = []
        u_indexek = [i for i, val in enumerate(állapot) if val == 'U']

        for u_idx in u_indexek:
            u_coord = SORREND[u_idx]
            for sz_coord in SZOMSZEDOK[u_coord]:
                sz_idx = SORREND.index(sz_coord)

                uj_allapot = list(állapot)
                uj_allapot[u_idx], uj_allapot[sz_idx] = uj_allapot[sz_idx], uj_allapot[u_idx]
                lapka = állapot[sz_idx]
                gyerekek.append((f"{lapka}_{u_coord}", tuple(uj_allapot)))

        return gyerekek


if __name__ == '__main__':
    feladat = HaromszogTol()


    def heurisztika(csúcs):
        h = 0
        for i, val in enumerate(csúcs.állapot):
            if val != 'U':
                cel_idx = feladat.cél.index(val)
                dist = DIST[SORREND[i]][SORREND[cel_idx]]
                if dist > 0:
                    h += dist * 100 + 100
        return h


    eredmeny = best_first(feladat, heurisztika)
    if eredmeny:
        print(len(eredmeny.megoldás()))
    else:
        print("Nincs megoldás")