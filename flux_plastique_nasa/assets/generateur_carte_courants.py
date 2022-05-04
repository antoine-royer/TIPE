from coordonnees import *
from math import pi, tan, asinh


def deg_to_rad(angle):
	return angle * pi / 180


def sign(n):
	if n == 0: return 1
	else: return abs(n) // n


# longitude[0:360] -> x ; latitude[-90;90] -> y
def conversion(lon, lat):
	# Conversion en degrés
	lon = deg_to_rad(lon % 360)
	lat = 90 - deg_to_rad(lat)

	# Calcul des coordonnées cartésiennes
	x = lon
	y = 5/4 * asinh(tan(4/5 * lat))

	# Mise à l'échelle
	x *= 1000 / (2 * pi)
	y *= (500 / 4)
	y = (y - 1125) % 1500
	return int(x), int(y)


with open("longitude.txt", 'r') as lon_file:
	longitude = eval(lon_file.read())

with open("latitude.txt", 'r') as lat_file:
	latitude = eval(lat_file.read())


size = (1000, 530)

currents = [[[0, 0] for _ in range(size[0])] for _ in range(size[1])]

index = 0
for lat in latitude:
	for lon in longitude:
		if 20 <= lon <= 420:
			x, y = conversion(lon, lat)
			if not (0 <= x < 1000): print(f"x non-valide, x={x}")
			if not (0 <= y < 530): print(f"y non-valide, y={y}")

			if coords[index][0] and coords[index][1]:
				vect = [50, 50]
				if coords[index][0] > 0: vect[0] = 52
				elif coords[index][0] < 0: vect[0] = 48

				if coords[index][1] > 0: vect[1] = 52
				elif coords[index][1] < 0: vect[1] = 48
				currents[y][x] = vect
		index += 1

output = "#include \"../include/carte_vecteurs.h\"\n\n" + f"uint8_t courants[{size[1]}][{size[0]}][2] = " + "{\n{"

for line in currents:
	for vect in line:
		output += f"{{{vect[0]}, {vect[1]}}}, "
	output += "},\n{"
output = output[:-1] + "};"

with open("../src/carte_vecteurs.c", "w") as file:
	file.write(output)



