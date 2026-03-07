class NKiralyno:

    def __init__(self, n):
        self.N = n
        koordinatak = tuple((0, 0) for i in range(n))
        self.kezdo = (koordinatak, 1)

    def celteszt(self, a):
        koordinatak, s = a
        return s == self.N + 1

    def rakovetkezo(self, a):
        gyerekek = []
        koordinatak, s = a
        if s > self.N:
            return gyerekek
        for i in range(1, self.N + 1):
            utkozik = False
            sor_most = s - 1
            oszlop_most = i

            for j in range(1, s):
                sor_regi, oszlop_regi = koordinatak[j - 1]
                if oszlop_regi == oszlop_most or abs(sor_regi - sor_most) == abs(oszlop_regi - oszlop_most):
                    utkozik = True
                    break
            if not utkozik:
                uj_koordinatak = list(koordinatak)
                uj_koordinatak[s - 1] = (sor_most, oszlop_most)
                uj_allapot = (tuple(uj_koordinatak), s + 1)
                gyerekek.append(uj_allapot)

        return gyerekek

if __name__ == '__main__':
    feladat = NKiralyno(4)
    print(f"Kezdőállapot: {feladat.kezdo}")
    elso_lepesek = feladat.rakovetkezo(feladat.kezdo)
    print(f"Lehetséges első lépések száma: {len(elso_lepesek)}")
    for allapot in elso_lepesek:
        print(allapot)
