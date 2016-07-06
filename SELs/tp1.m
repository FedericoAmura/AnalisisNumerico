#METODO DIRECTO

#cargamos matrix de ecuaciones y vector de resultados
A = csvread("MatrixFinal.csv")
b = csvread("MatrixFinalResultado.csv")

#calculamos solucion por metodo directo
xd = A\b

#sacamos el resultado afuera
csvwrite("MatrixFinalTemperaturasDirecto.csv",xd)

#leemos el valor de matrix representando el perfil y graficamos
#PerfilDirecto = csvread("PerfilFinalTemperaturasDirecto.csv")
#contour(PerfilDirecto)
#imagesc(PerfilDirecto)
#pcolor(PerfilDirecto)


#JACOBI

#chequeamos si es diagonal dominante (1 es true y vale jacobi)
#el segundo termino suma todos los valores absolutos de una matrix de 2 dimensiones
#el primero es dos veces el valor absoluto del valor de cada fila sobre la diagonal
#dos veces porque la suma de la derecha lo esta considerando (y no deberia)
#se verifica esta condicion para todas las filas con el all
all((2*abs(diag(A))) >= sum(abs(A),2))

#obtenemos la matrix diagonal
D = diag(diag(A),0)
#y su inversa
Di=inv(D)

#y la restante de sacarle la diagonal, es decir L+U
R = A-D

#definimos el vector inicial para hacer jacobi
xk=100*ones(56,1)
aux=ones(56,1)	#vector auxiliar

#empezamos a iterar hasta cumplir con la convergencia
while (max(abs(xk-aux))>10E-3)
	aux = xk
	xk = Di*(b-R*xk)
endwhile

#sacamos el valor afuera
csvwrite("MatrixFinalTemperaturasJacobi.csv",xk)

#leemos el valor de matrix representando el perfil y graficamos
#PerfilJacobi = csvread("PerfilFinalTemperaturasJacobi.csv")
#contour(PerfilJacobi)
#imagesc(PerfilJacobi)
#pcolor(PerfilJacobi)
