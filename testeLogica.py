s = int(input('segundos: '))

hora = s / 3600
resto = s % 3600
minutos = resto / 60
segundos = resto % 60

print(f'{int(hora)}:{int(minutos)}:{int(segundos)}')

#Entrada: 3672
#saida: 1:1:12
