class Hanoi:

    def __init__(self, ke, c):
        self.kezdo = ke
        self.cel = c
        self.N = sum(len(rud) for rud in ke)

    def celteszt(self, a):
        return a == self.cel

    def rakovetkezo(self, a):
        gyerekek = []
        for honnan in range(3):
            for hova in range(3):
                if honnan == hova:
                    continue

                if len(a[honnan]) > 0:
                    korong = a[honnan][0]
                    if len(a[hova]) == 0 or korong < a[hova][0]:
                        uj_listak = [list(rud) for rud in a]
                        uj_listak[honnan].pop(0)
                        uj_listak[hova].insert(0, korong)
                        uj_allapot = tuple(tuple(rud) for rud in uj_listak)
                        gyerekek.append(uj_allapot)

        return gyerekek


if __name__ == '__main__':

    kezdo_allapot = ((1, 2, 3, 4, 5), (), ())
    cel_allapot = ((), (), (1, 2, 3, 4, 5))

    feladat = Hanoi(kezdo_allapot, cel_allapot)
    kovetkezok = feladat.rakovetkezo(feladat.kezdo)

    print("Lehetséges lépések száma")
    for allapot in kovetkezok:
        print(allapot)