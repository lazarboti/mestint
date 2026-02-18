
class KancsoFeladat:

    def __init__(self, ke ,c, max):
        self.kezdő = ke
        self.cél = c
        self.MAX = max

    def célteszt(self,a): # a= (a1,a2,a3) allapot
        return a[0] == self.cél or a[1] == self.cél or a[2] == self.cél

    def rákövetkező(self, a): # a= (a1,a2,a3) allapot
        gyereke = []
        a1, a2, a3 = a
        max1,max2,max3 = self.MAX

        lista_a = [a1,a2,a3]
        lista_a_max = [max1,max2,max3]

        for i in range(3):
            for j in range(3):
                if i == j:
                    continue
                if lista_a[i] != 0 and lista_a[j] != lista_a_max[j]:
                    T = min(lista_a[i], lista_a_max[j] - lista_a[j])
                    lista_a[i] = lista_a[i] - T
                    lista_a[j] = lista_a[j] + T

                    gyereke.append((lista_a[0], lista_a[1], lista_a[2]))





        #tölt 1,2 operátor alkamazási előfeltétele:
        if a1 != 0 and a2 != max2:
            T = min(a1 ,max2-a2)
            gyereke.append("Tölt 1 -> 2", (a1-T,a2+T,a3))

        #tölt 1,3 operátor alkamazási előfeltétele:
        if a1 != 0 and a3 != max3:
            T = min(a1 ,max3-a3)
            gyereke.append("Tölt 1 -> 3", (a1-T,a2,a3+T))
        #tölt 2,1 operátor alkamazási előfeltétele:
        if a2 != 0 and a1 != max1:
            T = min(a2 ,max1-a1)
            gyereke.append("Tölt 2 -> 1", (a1+T,a2-T,a3))
        #tölt 2,3 operátor alkamazási előfeltétele:
        if a2 != 0 and a3 != max3:
            T = min(a2 ,max3-a3)
            gyereke.append("Tölt 2 -> 3", (a1,a2-T,a3+T))

           # ezt befejezni for ciklusssal ne 6 szor irjuk
        #tölt 3,1 operátor alkamazási előfeltétele:
        if a3 != 0 and a1 != max1:
            T = min(a3 ,max1-a1)
            gyereke.append("Tölt 3 -> 1", (a1,a2-T,a3+T))

        #tölt 2,3 operátor alkamazási előfeltétele:
        if a2 != 0 and a3 != max3:
            T = min(a2 ,max3-a3)
            gyereke.append("Tölt 2 -> 3", (a1,a2-T,a3+T))

##############################################################################

if __name__ == "__main__":
    feldat = KancsoFeladat((0,0,8),4,(3,5,8))