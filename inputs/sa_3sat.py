#import matplotlib.pyplot as plt
from random import randint, uniform
from math import exp
import re
import numpy as np
import time

interacoes_MAX = 10000 # nr de iteracoes
t0 = 40 ## temp inicial 

## definindo uma solução inicial, 
## e coloca 0 ou 1 no vetor initial_s[]
def initial(s):
    global initial_s
    initial_s = s[:]
    for i in range(len(s)):
        initial_s[i] = randint(0,1)

def viz(s):
    resul = s[:]
    for i in range(len(resul)):
        aux = randint(1,20) # 1 em 20  = 5% de chance de flipar o bit
        if aux == 1:
            resul[i] = abs(s[i]-1)
    return resul

# N = quantas iterações a cada mudança de temperatura 
def sa(T0, TN, N, SAmax):
    global initial_s, formula
    s = initial_s[:]
    best = s[:]
    conv = []
    temp = []
    temp += [T0]
    IterT = 0
    T = T0
    # cooling schedule 2 
    A = ((T0-TN)*(N+1))/(N-1)
    B = T0 - A
    i = 0
    while T > TN:
        while IterT < SAmax:
            IterT += 1
            n = viz(s)
            delta = funcao_objetivo(n) - funcao_objetivo(s)
            if delta > 0:
                s = n[:]
                if funcao_objetivo(n) > funcao_objetivo(best):
                    best = n[:]
            else:
                try:
                    if uniform(0,1) < exp(delta/T):
                        s = n[:]
                except OverflowError:
                    s = n[:]
            print("{:.2f} %".format(100 * (IterT/SAmax * 1/N + i/N)), end='\r')

        conv += [funcao_objetivo(s)]
        i += 1
        T = A/(i+1) + B
        if T >= TN:
            temp += [T]
        print(T)
        
        IterT = 0
    print("100.00 %")
    return (conv,temp)

def funcao_objetivo(s):
    res = 0
    for i in formula:
        _res = 0
        for j in i:
            if j < 0:
                _res += s[-j - 1]==0
            else:
                _res += s[j - 1]==1
            if _res > 0:
                res += 1
                break
    return res

def conjunto_fnc(filename, n_var):
    global formula
    #gera a lista e preenche com os valores iniciais
    initial([0 for _ in range(n_var)])

    f = open(filename, "r")

    contents = re.compile("[ ]*[0][ ]*\n").split(f.read())
    formula = []
    for i in contents:
        cl = list(map(int, i.split()))
        if len(cl) > 0:
            formula += [cl]

def plot(conv,temp,nr_variaveis,clausulas):

    nr_variaveis = str(nr_variaveis)
    nr_clausulas = str(clausulas)

    if (clausulas == 91):       
        plt.ylabel('Temperatura')
        plt.xlabel('Tempo')
        plt.ylim(min(temp), max(temp))
        plt.plot(temp,label = 'Clausulas = %s' %nr_clausulas)
        plt.savefig('%s_temp.png' %nr_variaveis)
        plt.clf()
    

    maxSA = max(conv)
    plt.ylabel('Cláusulas satisfeitas')
    plt.xlabel('Temperatura')
    x_values = []
    x_ticks = []
    for i in range(len(temp)):
        x_values += [i]
        x_ticks += [round(temp[i],4)]
    plt.xticks(x_values, x_ticks)
    plt.ylim(min(conv), max(conv))
    plt.plot(conv,label = 'Resultado = %d / Total = %s' % (maxSA, nr_clausulas))
    plt.legend()
    plt.savefig('sa_%s.png' %nr_variaveis)
    plt.clf()

def mediaPonderada(vetor):

    somatorio = 0
    divisor = 0
    for i in range (len(vetor)):
        somatorio += vetor[i]*i
        divisor += vetor[i]
    resul = somatorio/divisor

    return resul 

def variancia(vetor,media):
    somatorio = 0
    divisor = 0
    for i in range (len(vetor)):
        somatorio += ((i - media) ** 2) * vetor[i]
        divisor += vetor[i]
    divisor = divisor  # -1 
    resul = somatorio/divisor

    return resul

def main ():

    ini_total = time.time()

    v_media_91 = []
    v_media_430 = []
    v_media_1065 = []

    v_variancia_91 = []
    v_variancia_430 = []
    v_variancia_1065 = []

    for i in range(10):

        print("Execução %d \n" %i)
        ini = time.time()
        conjunto_fnc("uf20-01.cnf", 20)
        conv, temp = sa(t0,.0001,15,interacoes_MAX)
        v_media_91 += [max(conv)]
        v_variancia_91 += [max(conv)]
        #plot(conv,temp,20,91)
        fim = time.time()
        print ("Tempo (91 cláusulas): %f " %(fim-ini))

        ini = time.time()
        conjunto_fnc("uf100-01.cnf", 100)
        conv, temp = sa(t0,.0001,15,interacoes_MAX)
        #plot(conv,temp,100,430)
        v_media_430 += [max(conv)]
        v_variancia_430 += [max(conv)]
        fim = time.time()
        print ("Tempo (430 cláusulas): %f " %(fim-ini))


        ini = time.time()
        conjunto_fnc("uf250-01.cnf", 250)
        conv, temp = sa(t0,.0001,15,interacoes_MAX)
       # plot(conv,temp,250,1065)
        v_media_1065 += [max(conv)]
        v_variancia_1065 += [max(conv)]
        fim = time.time()
        print ("Tempo (1065 cláusulas): %f " % (fim-ini))
        print("\n")
    
    media_91 = mediaPonderada(v_media_91)
    media_430 = mediaPonderada(v_media_430)
    media_1065 = mediaPonderada(v_media_1065)

    variancia_91 = variancia(v_media_91,media_91)
    variancia_430 = variancia(v_media_430,media_430)
    variancia_1065 = variancia(v_media_1065,media_1065)

    print("Media 91 = %.3f Variância 91 = %.3f" %(media_91,variancia_91))
    print("Media 430 = %.3f Variância 430 = %.3f" %(media_430,variancia_430))
    print("Media 1065 = %.3f Variância 1065 = %.3f" %(media_1065,variancia_1065))

    fim_total = time.time()
    print ("Tempo Total (10 execuções): %f " % (fim_total-ini_total))

if __name__ == "__main__":
    main()