
class Kiralyno:

    def __init__(self, k , c):
        self.kezdo = k
        self.cel = c
        self.N = len(k) - 1

    def celteszt(self, a):  # a= (a1,a2,a3....an,s)
        return a[-1] == self.cel

    def rakovetkezo(self, a): # a= (a1,a2,a3....an,s)
        gyerekek = []
        s = a[-1] # következő sor indexe
        for i in range(1,self.N+1):
            előfeltétel = True # lerak (s,i) alkalmazható????
            for m in range(1,s): #bármely m < s:
                if a[m-1] != i and abs(s-m) != abs(i -a[m-1]):
                    pass
                else:
                    előfeltétel = False
                    break

            if előfeltétel:
                uj_allapot = list(a)
                uj_allapot[s-1] = i
                uj_allapot[-1] = s+1
                gyerekek.append(tuple(uj_allapot))
        return gyerekek

if __name__ == '__main__':
    feladat = Kiralyno((0,0,0,0,1), 5)
    feladat2 = Kiralyno((0,0,0,0,0,0,0,0,0,1),9)