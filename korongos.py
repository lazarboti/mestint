from keres import *

class Palacsinta(Feladat):
    def __init__(self):
        self.kezdő = (6, 7, 3, 2, 8, 5, 4, 1)
        self.cél = (1, 2, 3, 4, 5, 6, 7, 8)

    def célteszt(self, állapot):
        return állapot == self.cél

    def rákövetkező(self, állapot):
        gyerekek = []
        for i in range(2, 9):
            uj_allapot = állapot[:i][::-1] + állapot[i:]
            gyerekek.append((f"fordít_{i}", uj_allapot))
        return gyerekek

if __name__ == '__main__':
    feladat = Palacsinta()
    eredmeny = szélességi_gráfkereső(feladat)
    if eredmeny:
        print(eredmeny.megoldás())
        ut = eredmeny.út()
        ut.reverse()
        print(ut)